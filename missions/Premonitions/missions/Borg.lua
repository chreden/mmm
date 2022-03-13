--########################################################################

class 'Borg' (State)

function Borg:__init( )
end

function Borg:onEnter( machine )

	Objectives:load( "Premonitions2.txt" )
	Objectives.show = true
	
	function checkBorgDead( monitor, arg )
		return EntityFinder( function(e) return e:isType(EntityType.Craft) and e.team.number == 2 end ):findOne() == nil
	end
	
	function onBorgDead( monitor, arg )
		Objectives:setObjectiveState( 1, true )
		for _, v in pairs(Monitor.getAll()) do
			v:stop()
		end
		machine:setState( Chatting() )
	end
	
	Monitor.new( "checkBorgShips", false, nil, checkBorgDead, nil ):hook( MonitorHooks.OnTrue, nil, onBorgDead, nil )
end
