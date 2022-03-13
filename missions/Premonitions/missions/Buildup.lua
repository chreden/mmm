class 'Buildup' (State)

function Buildup:__init( )
end

function Buildup:onEnter( machine )

	function checkStarbaseDone( monitor, arg )
		return EntityFinder( function(e) return e.odf == "fed_outpostya.odf" and e.team.number == 1 end ):findOne() ~= nil
	end
	
	function onStarbaseDone( monitor, hook, arg )
		Objectives:setObjectiveState( 1, true )
		Objectives.visible = true
	end
	
	Monitor.new( "starbaseDone", false, nil, checkStarbaseDone, nil ):hook( MonitorHooks.OnTrue, nil, onStarbaseDone, nil )
	
	function checkMiningDone( monitor, arg )
		return EntityFinder( function(e) return e.odf == "fed_storage_dock.odf" and e.team.number == 1 end ):findOne() ~= nil
	end
	
	function onMiningDone( monitor, hook, arg )
		Objectives:setObjectiveState( 2, true )
		Objectives.visible = true
	end
	
	Monitor.new( "miningDone", false, nil, checkMiningDone, nil ):hook( MonitorHooks.OnTrue, nil, onMiningDone, nil )
	
	function checkObjectivesDone( monitor, arg )
		return Objectives:getObjectiveState(1) and
			   Objectives:getObjectiveState(2)
	end
	
	function onObjectivesDone( monitor, hook, arg )
		--Clear all monitors - we don't want them interfering with the next state.
		for _, v in pairs(Monitor.getAll()) do
			v:stop()
		end
		machine:setState( Dominion() )
	end
	
	Monitor.new( "buildObjectivesDone", false, nil, checkObjectivesDone, nil ):hook( MonitorHooks.OnTrue, self, onObjectivesDone, nil )

	Media.playMusic( "prembgm.wav" )
	Objectives:load( "Premonitions.txt" )
	Objectives.visible = true
end
