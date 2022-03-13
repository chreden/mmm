EntityTest = { }
initMetatable( EntityTest )

function EntityTest.new( )
	local test = { }
	setmetatable( test, EntityTest.mt )
	UI.setTeamText( "Running Entity Test" )
	return test
end

function EntityTest:run( )
	return true
end

