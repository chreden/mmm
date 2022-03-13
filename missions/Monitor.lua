--Excellent test of monitors and the like.
--Basically what we want to happen.

MonitorTest = { }
initMetatable( MonitorTest )
inherit( MonitorTest, MMMApp )

function MonitorTest.new( )
	return setmetatable( { }, MonitorTest.mt )
end

function MonitorTest:init( )
	local monitor = Monitor.new( "checkResources", self, checkResources, 1 )
	monitor.listen( self, onResourcesGathered )
end


function MonitorTest:checkResources( id, arg )
	return Team.new( arg ):getResource( Resource.Dilithium ) > 1000
end


function MonitorTest:onResourcesGathered( id, arg )
	UI.setTeamText( "Congrats, you got the resources" )
end

MMMApp.register( MonitorTest.new( ) )
