--This part creates the table we will use for the mission
--an initialises the metatable, allowing it to work properly
--with MMMApp
TestMission = { }
initMetatable( TestMission )
inherit( TestMission, MMMApp )

--Some constant values for lookups
Objective_Starbase  = 0
Objective_Shipyard  = 1
Objective_Ships	    = 2
Objective_Dilithium = 3

function TestMission.new( )
	local newMission = { }
	setmetatable( newMission, TestMission.mt )
	
	--You can set up properties for the mission here, or you can do it in init. 
	
	--This creates a new lookup table.
	newMission.objectives = {}
	
	return newMission
end

--Called once when the mission is first started. Ideal place to set up the variables and structures
--needed for the mission.
function TestMission:init( )
    
	Mission.loadObjectives( "first_mission.txt" )
	Mission.showObjectives( true )
	
	--Here we will initialise our objectives
	self.objectives[Objective_Starbase]  = false
	self.objectives[Objective_Shipyard]  = false
	self.objectives[Objective_Ships]	 = false
	self.objectives[Objective_Dilithium] = false
		
end

--Called when the mission is loaded from a save game. You should load any data that was saved in this
--function and prepare for the mission to carry on.
function TestMission:resume( )

end

--This is called some time after you tell MMM to start a cineractive - you can set up the cineractive that
--is going to be played and prepare the game world for cineractive mode.
function TestMission:cineractiveBegin( )

end

--This is called every update while a cineractive is running. You should check for conditions you require for
--the end of the cineractive and end it if needed. You can also change the running cineractive, to focus on another
--ship for example.
function TestMission:cineractiveUpdate( )

end

--The is called some time after you tell MMM to end the cineractive. This is where you prepare the game world for
--game mode again.
function TestMission:cineractiveFinish( )
	
end

--This is called every time MMM updates. This frequency can change based on the value specified to Armada.setUpdateTime.
function TestMission:update( )
	self:checkStarbaseObjective( )
	self:checkShipyardObjective( )
	self:checkShipsObjective( )
	self:checkDilithiumObjective( )
    self:synchroniseObjectivesDisplay( ) 
end

function TestMission:checkDilithiumObjective( )
	if not self.objectives[Objective_Dilithium] then
		local team = Team.new( 1 )
		local amount = team:getResource( Resource.Dilithium )
		if amount > 5000 then
			self.objectives[Objective_Dilithium] = true
			Mission.showObjectives( true )
		end
	end
end

function TestMission:checkShipsObjective( )
	if not self.objectives[Objective_Ships] then
		local ents = Team.new( 1 ):getEntities( )
		local shipCount = 0
		for _, v in pairs( ents ) do
			if v:getOdfName() == "fdestroy2.odf" then
				shipCount = shipCount + 1
			end
		end
		
		if shipCount >= 10 then
			self.objectives[Objective_Ships] = true
			Mission.showObjectives( true )
		end
	end		
end

function TestMission:checkShipyardObjective( )
	if not self.objectives[Objective_Shipyard] then
		local ents = Team.new( 1 ):getEntities( )
		for _, v in pairs( ents ) do
			if v:getOdfName() == "fyard.odf" then
				self.objectives[Objective_Shipyard] = true
				Mission.showObjectives( true )
				break
			end
		end
	end	
end

function TestMission:checkStarbaseObjective( )
	if not self.objectives[Objective_Starbase] then
		local ents = Team.new( 1 ):getEntities( )
		for _, v in pairs( ents ) do
			if v:getOdfName() == "fbase.odf" then
				self.objectives[Objective_Starbase] = true
				Mission.showObjectives( true )
				break
			end
		end
	end
end

function TestMission:synchroniseObjectivesDisplay( )
	for index, value in pairs( self.objectives ) do
		Mission.setObjective( index, value )
	end
end

--This line registers the App with MMM. This makes it MMM call the app's functions.
MMMApp.register( TestMission.new( ) )