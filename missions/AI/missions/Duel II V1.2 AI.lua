include( "resourcearea.lua" )

class 'TestAI'

function TestAI:__init( )

end

function TestAI:setup( )
	--Figure out who we are. Find the AI - apparently this is not always team
	--1. Annoying. Just take the first AI that we find since we are only supposed
	--to be playing on a single player map.
	for i = 1, 8 do 
		if Team(i).isAI then self.team = Team(i) break end
	end
	
	self.previousTime = Armada.time
	
	--Right, now disable the AI so it doesn't just take over.
	--This is just one line but you have no idea how hard it
	--was to stop the stupid thing.
	self.team.isAI = false
	
	--Tables for the different types of ships that we can have.
	self.constructors = {}
	
	--Monitors and the like.
	self:setupStarbaseMonitor()
	--self:setupTestYard()
	self:detectResources()
	self:setupResourceReport()
	
	self.derp = false
	
end

function TestAI:setupResourceReport( )

	function doReport( arg )
		UI.setTeamText( "…" .. self.team.resources.dilithium .. "   " ..
						"†" .. self.team.resources.latinum .. "   " ..
						"‡" .. self.team.resources.biomatter .. "   " ..
						"™" .. self.team.resources.metal )
		Timer.add( "resource_report", 0.25, nil, doReport, nil )
		return CallbackResult.Remove
	end
	doReport()
end


function TestAI:setupStarbaseMonitor() 
	--We want to keep an eye on everything that we build, so that we know what we have.
	self.starbase = EntityFinder( function(e) 
									return e:isType(EntityType.Starbase) and 
											   e.team.number == self.team.number 
									end ):findOne()
	
	--This function keeps track of the last ship that was built
	--by the starbase
	function monitorProduction( info )
		if info.target.lastBuilt ~= nil then
			if info.previous == nil then
				info.previous = info.target.lastBuilt	
				return true
			else
				if info.target.lastBuilt.id ~= info.previous.id then
					info.previous = info.target.lastBuilt
					return true
				end
			end
		end
		return false
	end
	
	function constructorDestroyed( ship )
		table.remove( self.constructors, ship )
	end
	
	function constructorBuilt( ship )
		function constructorReady()
			ship:hook("onDestroy", nil, constructorDestroyed, nil) 
			table.insert( self.constructors, ship )	
		end
		--Have to wait for the idiot thing to exit the dock.
		Timer.add( "wait_for_constructor", 4.0, nil, constructorReady, nil )
	end
	
	function registerShip( arg )
		--Setting in local to stop any confusion.
		local ship = arg.lastBuilt
		
		if ship:isType( EntityType.Constructor ) then
			constructorBuilt( ship )
		elseif ship.odf == "kli_noqdujs.odf" or
			   ship.odf == "kli_noqduj.odf" then
			--handle construction of the scout. Probably send them off somewhere
			--and at least cloak them. Who knows.	
			print("scout")			
		elseif ship.odf == "kli_topmeyz.odf" then
			--Miners will be used to fill up mining slots on the resource areas that we own, 
			--or to go to ones we are trying to take.
			print("freighter")
		end
	end
	
	--Well, starbase should not be nil, so we just assume everything is ok.
	local productionMonitor = Monitor.new( "starbase_production",
										   false,
										   nil,
										   monitorProduction,
										   { target = self.starbase, previous = nil } )
	productionMonitor:hook( MonitorHooks.OnTrue,
							nil,
							registerShip,
							self.starbase )
							
	self.starbase:hook( "onDestroy", nil, function() 
												self.starbase = nil 
												productionMonitor:stop() 
										   end, nil )	

	--Queue initial miners
	self.starbase:pushBuildQueue( "kli_topmeyZ.odf" )
	self.starbase:pushBuildQueue( "kli_topmeyZ.odf" )
	self.starbase:pushBuildQueue( "kli_topmeyZ.odf" )
	self.starbase:pushBuildQueue( "kli_topmeyZ.odf" )
										   
	
end

function TestAI:detectResources( )
	local allMoons = EntityFinder( function(e) return e:isType( EntityType.Scrap ) end ):find()
	
	--We store them as resource areas, which are "owned" or whatever.	
	self.moons = { }
	
	for _, moon in pairs(allMoons) do
		table.insert( self.moons, ResourceArea( self.team, moon ) )
	end
end

function TestAI:setupTestYard() 
	local yard = Entities.add( "kli_field_yardY.odf", self.team.number, Vector(4000,0,4000) )
	yard:pushBuildQueue( "kli_field_yardP1Y" )
	
	function checkItemBuilt( arg ) 
		return EntityFinder( function(e) 
								return e:isType(EntityType.Shipyard) and 
									   e.odf == "kli_field_yardp1y.odf" and 
									   e.team.number == self.team.number 
							 end ):findOne() ~= nil
	end
	
	function queueAThing( arg )
		EntityFinder( function(e) 
						return e:isType(EntityType.Shipyard) and 
							   e.odf == "kli_field_yardp1y.odf" and
							   e.team.number == self.team.number
					  end ):findOne():pushBuildQueue("kli_kbeajq")
	end
	
	local mon = Monitor.new( "monitor_yard_build",
							 false,
							 nil,
							 checkItemBuilt,
							 { target = yard, previous = nil } )
	mon:hook( MonitorHooks.OnTrue, 
			  nil,
			  queueAThing,
			  yard )
end

function TestAI:findNearestMoon( ent, res )
	local nearestMoon 		= nil
	local nearestDistance 	= 1000000
	for _, v in pairs(self.moons) do
		if v.type == res then
			local to = v.moon.position - self.starbase.position
			if to.length < nearestDistance then 
				nearestDistance = to.length 
				nearestMoon = v
			end
		end
	end
	return nearestMoon
end

--The AI in fleet ops is given 5 supply for the main starbase. We have to remove
--5 supply from the AI's resources every second.
function TestAI:supplyBalance( dt )
	if self.starbase then 
		self.team.resources.biomatter = self.team.resources.biomatter - 5 * dt
	end
end

function TestAI:update( )
	self.team.isAI = false
	
	if self.starbase then
		if #self.constructors == 2 and not self.derp then
			local nearestDi = self:findNearestMoon( self.constructors[1], ResourceArea.Type.Dilithium )
			if nearestDi then
				self.constructors[1]:giveOrder( Order.Build, "kli_mining_stationZ.odf",	nearestDi:calculateStationPosition( self.starbase ) )
			end
			
			local nearestTri = self:findNearestMoon( self.constructors[2], ResourceArea.Type.Tritanium )
			if nearestTri then
				self.constructors[2]:giveOrder( Order.Build, "kli_mining_stationZ.odf",	nearestTri:calculateStationPosition( self.starbase ) )
			end
			
			self.derp = true
		end
	end
	
	local dt = Armada.time - self.previousTime
	self.previousTime = Armada.time
	self:supplyBalance( dt )
end

MMM.register( TestAI() )