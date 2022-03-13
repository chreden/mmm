TimersMission = { }
initMetatable( TimersMission )
inherit( TimersMission, MMMApp )

function TimersMission.new( )
	local timersMission = { }
	setmetatable( timersMission, TimersMission.mt )
	return timersMission
end

function TimersMission:init( )
	--Used by the createShip timer.
	self.ships = { "fconst.odf", "fscout.odf", "ffreight.odf" }
	
	--Creating a timer that is part of a table - we pass self as the table instance.
	--Not using any arguments so we are passing nil for that.
	Timers.add( "createShip", 3, self, TimersMission.createNewShip, nil )
	
	--Timer that prints a message after a bit.
	Timers.add( "info", 13, nil, printMessage, "Hello" )
end

--Timer function that is a member of the self.ships field of the TestMission
--table instance.
function TimersMission:createNewShip( id, arg )
	--Choose a random ship to create
	local shipIndex = math.random( #self.ships )
	--Create that ship at the centre of the map on team 1
	Entities.add( self.ships[ shipIndex ], 1, Vector.new( 3200, 0, 3200 ) )
	--We want this to repeat
	return CallbackResult.Repeat
end

--Timer to print a message.
function printMessage( id, arg )
	print( arg )
	return CallbackResult.Remove
end

MMMApp.register( TimersMission.new() )
