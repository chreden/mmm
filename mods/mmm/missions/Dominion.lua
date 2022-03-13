--The Dominion state just involves the player fighting the Dominion ships dotted around the
--map.

include( "PremCine.lua" )

class 'Dominion' (State)

function Dominion:__init( )
end

function Dominion:giveAttackOrder( )
	local starbase = EntityFinder( function(e) return e:isType(Entity.Type.Starbase) and e.player.number == 1 end ):findOne()
	if starbase.valid then
		local bugs = EntityFinder( function(e) return e:isType(Entity.Type.Craft) and e.player.number == 2 end ):find()
		for _, v in pairs(bugs) do
			--Space out the attack orders over about 2 minutes.
			Timer( "bug" .. v.name, math.random() * 120, Timer.State.Started ):hook( "giveOrder", nil,
				function()
					if v.valid and starbase.valid then
						v:giveOrder( GameObject.Order.Attack, starbase.position + Vector(-300 + math.random() * 600, 0, -300 + math.random() * 600) )
					end
				end, nil )
		end
	end
end

function Dominion:onEnter( machine )
	
	--Dialog where she announces that there are Dominion ships.
	Media:playSound( "PremonitionsDominion.ogg" )
	--Load and show objectives to inform the user.
	Objectives:load( "PremonitionsDominionObjectives.txt" )
	Objectives.visible = true
	
	--Tell some of the ships to attack the player (give them an attack order 
	--and the general position of the starbase).
	self:giveAttackOrder( )
	
	--Simple monitor function that checks that there are no Dominion ships
	--left. If there are no ships, the findOne function on the finder will
	--return nil.
	function checkShipsDead( monitor, arg )
		return EntityFinder( function(e) 
								return e:isType(Entity.Type.Craft) and
								 	   e.player.number == 2 
								end ):findOne() == nil
	end
	
	--Hook function that is called when there are no Dominion ships left alive.
	function onShipsDead( monitor, hook )
		--Update and show objectives.
		Objectives.objectives[1].state = true
		Objectives.visible = true
		
		--Member of the crew says the dominion ships are destroyed, but there is temporal
		--things going on.
		Media:playSound( "PremonitionsSecure.ogg" )
		
		--Clear all monitors as they will clash with the Borg state.
		Monitor.stopAll()
		machine:setState( PremCine( ) )
	end
	
	--Simple monitor to check to see if there are any ships left. When there are no ships left
	--the hook is called and we move on to the next state.
	Monitor( "checkShipsDead", false, nil, checkShipsDead, nil):hook( "onShipsDead", MonitorHook.Type.OnTrue, nil, onShipsDead, nil ) 
end
