--########################################################################

class 'Dominion' (State)

function Dominion:__init( )
end

function Dominion:onEnter( machine )
	
	Media.playSound( "premdom.wav" )
	Objectives:load( "Premonitions1.txt" )
	Objectives.visible = true
	
	function checkShipsDead( monitor, arg )
		return EntityFinder( function(e) return e:isType(EntityType.Craft) and e.team.number == 2 end ):findOne() == nil
	end
	
	function onShipsDead( monitor, hook, arg )
		Objectives:setObjectiveState( 1, true )
		Objectives.visible = true
		--Clear all monitors as they will clash with the Borg state.
		for _, v in pairs(Monitor.getAll()) do
			v:stop()
		end
		machine:setState( PremCine( ) )
	end
	
	Monitor.new( "checkShipsDead", false, nil, checkShipsDead, nil):hook( MonitorHooks.OnTrue, nil, onShipsDead, nil )
end
