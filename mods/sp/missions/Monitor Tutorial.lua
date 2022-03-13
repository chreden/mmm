class 'MonitorTutorial'

function MonitorTutorial:__init( )
	
end

function MonitorTutorial:setup( )
	--This function checks to see if the player has the required amount of 
	--dilithium
	function checkDilithium( amount )
		return Player( 1 ).resources.dilithium >= amount
	end
	
	--This function is called when the target is reached ( the monitor condition
	--becomes true )
	function onDilithiumTargetReached( monitor, hook )		
		--When the player gets 500, spawn an Akira class as a reward.
		Entity.add( "fed_akiraZ.odf", 1, Vector(500, 0, 250) )
		--We don't want this to happen again, so we kill the monitor
		monitor:stop()
	end
	
	local newMonitor = Monitor( "DilithiumMonitor", false, nil, checkDilithium, 500 )
	
	newMonitor:hook( "onDilithiumTargetReached", MonitorHook.Type.OnTrue, nil, onDilithiumTargetReached, nil )
end

MMM.register( MonitorTutorial( ) )
