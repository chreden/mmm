include( "EntityTest.lua" )

TestSuite = { }
initMetatable( TestSuite )

function TestSuite.new( )
	local suite = { }
	setmetatable( suite, TestSuite.mt )
	
	suite.tests = {}
	
	--We need to hook up text input to the Test Suite class so
	--that we can respond to input.
	TextInput.hook( suite, TestSuite.onTextInput )
	
	suite:registerTest( "entity", EntityTest.new )
	
	return suite
end

function TestSuite:findTest( testName )
	for _, v in pairs( self.tests ) do
		if v.name == testName then
			return v
		end
	end
	return nil
end

function TestSuite:registerTest( testName, testCreator )
	if ( self:findTest( testName ) ~= nil ) then
		return false
	end
	
	if ( testCreator == nil ) then
		return false
	end

	table.insert( self.tests, { name = testName, creator = testCreator } )
	return true
end

function TestSuite:beginTests( )
	--Rather than using print, we are going to use team text.
	--At least for persistent messages - everything else will
	--use UI messages instead of print.
	UI.setTeamText( "Welcome to the MMM Test Suite\n" ..
					"Enter a command to begin" )	
end

function TestSuite:runTest( testName )
	local test = self:findTest( testName )
	if ( test == nil ) then
		return false
	end
	
	test.creator( ):run()
end

function TestSuite:onTextInput( input )
	if( input == "list" ) then
		--Print each of the tests
		
	else
		self:runTest( input )
	end
end
