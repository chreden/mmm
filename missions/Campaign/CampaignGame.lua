include ("StateStack.lua")
include ("MapState.lua")

--Campaign game needs to inherit from the database object interface
--so that it can be serialised properly. Does it? Can it not just go
--on an unwritten contract?
CampaignGame = { }
initMetatable( CampaignGame )

function CampaignGame.new( )
	local newGame = { }
	
	setmetatable( newGame, CampaignGame.mt )
	
	return newGame
end

function CampaignGame:init( )
	--Set up our campaign stack thing.
	self.states = StateStack.new( )
	self.states:push( MapState.new( ) )
end

function CampaignGame:update( )
	--Soon check ships and that.
	self.states:update()
end
