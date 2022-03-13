--The Borg state is a simple state. It just makes a monitor that checks to
--see if the Borg are still alive.

include( "Chatting.lua" )
include( "ShipDies.lua" )

class 'Borg' (State)

function Borg:__init( )

end

function Borg:onEnter( machine )

	--Add the requirement for the Premonition to not die. Similar to the Enterprise condition.
	setupShipDeathHook( EntityFinder( NameFinder("USS Premonition") ):findOne(),
						"The Premonition",
						machine )

	--Show the objectives for this state.
	Objectives:load( "PremonitionsBorgObjectives.txt" )
	Objectives.show = true
	
	--Condition function that checks to see if there are any more
	--Borg ships left (player 2 ships).
	function checkBorgDead( monitor, arg )
		return EntityFinder( function(e) 
								return e:isType(Entity.Type.Craft) and 
								  	   e.player.number == 2 
								end ):findOne() == nil
	end
	
	--Hook function that simply moves us on to the final cineractive state
	function onBorgDead( monitor, arg )
		--Just set the objective. Not that important really as the next
		--state is just cutscene.
		Objectives.objectives[1].state = true
		--Stop all existing monitors so they don't interfere.
		Monitor.stopAll()
		--Move to the final cineractive state.
		machine:setState( Chatting() )
	end
	
	--Create the monitor that will check for borg ships being alive.
	Monitor( "checkBorgShips", false, nil, checkBorgDead, nil ):hook( "onBorgDead", MonitorHook.Type.OnTrue, nil, onBorgDead, nil )
end
