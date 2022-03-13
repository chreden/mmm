--Graph 'class'
include( "missions/multi_aas_graph.lua" )

local nodemap = nil

function init( )
	if Armada.isHost( ) then
		Armada.setTeamText( "This is the host" )
	else
		Armada.setTeamText( "This is not the host" )
	end
	
	TextInput.hook( nil, hooker )

	--Quick map test
	nodemap = Node.new( 1, Vector.new( 1000, 0, 1000 ) )
	
	Timers.add( "nodeflasher", 2.5, nil, flashnodes, nil )
	
end

function update( )
	
end

function flashnodes( id, parameter )
	UI.addMinimapMark( nodemap.position, 50, 0.02, Armada.getTeam( nodemap.team ):getColor( ) )
	return CallbackResult.Repeat
end

function hooker( str )
	local p = loadstring(str)
	p( )
end

--[[
	Right, just need to get down what needs to be done, then work through it. 
	We want to be able to have a kind of linked nodemap. This should be editable
	in the map editor if possible.
	At the moment, we'll just do it in the code, since I cant be bothered otherwise.
--]]