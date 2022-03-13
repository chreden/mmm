--[[
	This is the file for the non-linear campaign that is being developed for MMM.
	This file will contain some amount of code that will not currently work becase
	I have yet to implement some of the functionality.
--]]

include( "CampaignGame.lua" )
include( "CampaignMap.lua" )

Campaign = {}
initMetatable( Campaign )
inherit( Campaign, MMMApp )

function Campaign.new( )
	return setmetatable( {}, Campaign.mt )
end

function Campaign:init( )
	self.game = CampaignGame.new( )
	self.game:init()
	
	--Media.playMusic( "Federation.wav" )
	Media.playMusic( "premintro.wav" )
end

function Campaign:cineractiveUpdate( )
	--local ent = Entities.add( "mmm_crate.odf", 1, Vector.new( 0,0,0 ) )
	
	--Cineractive.lookAtGameObject
	--Cineractive.lookAtGameObject( nil )
	--Cineractive.lookFromPath( nil, 1 )
	--Cineractive.lookFromPosition
	
end

function Campaign:update()
	--Check to see if the map has been created yet. We create it if it has been.
end

MMMApp.register( Campaign.new( ) )
