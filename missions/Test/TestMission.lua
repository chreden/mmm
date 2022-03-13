--The test mission will allow for the tester to run specific tests - obviously
--this will all have to be tested. THE CYCLE NEVER ENDS.
include( "TestSuite.lua" )

TestMission = { }
initMetatable( TestMission )
inherit( TestMission, MMMApp )

function TestMission.new( )
	local testMission = { }
	setmetatable( testMission, TestMission.mt )
	testMission.testSuite = TestSuite.new( )
	return testMission
end

function TestMission:init( )
	self.testSuite:beginTests( )
end

MMMApp.register( TestMission.new() )
