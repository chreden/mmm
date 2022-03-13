include( "FleetManager.lua" )

MapState = { }
inherit( MapState, BaseState )
initMetatable( MapState )

function MapState.new( )
	local newMap = { }
	setmetatable( newMap, MapState.mt )
	
	--Fleets might be a proper manage or things soon, because an array would just mean more
	--work in this class.
	
	newMap.fleets = FleetManager.new()
	newMap.scanner = nil
	
	return newMap
end

function MapState:onEnter( stack )
	BaseState:onEnter( stack )

	--Since we are entering the campaign map phase, we have to set the map to the correct size.
	Map.setMax( Vector.new( 6500, 0, 6500 ) )
	
	Camera.center( Vector.new( 3250, 0, 3250 ) )
	
	--Allocate the default sectors to each team. Perhaps this can be random in the future?
	self.campaignMap = CampaignMap.new( )	
	self:createDefaultMap()
	
	--These two will need to be managed better - add fleet or something?
	self.fleets:add( FleetType.Economy, Owner.Federation, Vector.new( 3250, 0, 3250 ), true )
	self.fleets:add( FleetType.Military, Owner.Federation, Vector.new( 3250, 0, 3250 ), true )
	
	--We need to add the scanner so that the player can see everything. At the minute the scanner can be
	--selected though, so might need to think about that too.
	self.scanner = Entities.add( "mmm_scanner.odf", 1, Vector.new( 50, 0, 50 ) ):hide( true )
end

function MapState:onUpdate( )
	self.fleets:update( self.campaignMap )
end

function MapState:createDefaultMap( )
	self.campaignMap:createDefault()
		
	--Initial map allocations. Federation get a lot because they are the
	--federation. Obviously. Not really important.
	--Federation
	self.campaignMap:setHexOwner( 1, 1, Owner.Federation )
	self.campaignMap:setHexOwner( 2, 1, Owner.Federation )
	self.campaignMap:setHexOwner( 3, 1, Owner.Federation )
	self.campaignMap:setHexOwner( 1, 2, Owner.Federation )
	self.campaignMap:setHexOwner( 1, 3, Owner.Federation )
	self.campaignMap:setHexOwner( 2, 2, Owner.Federation )
	self.campaignMap:setHexOwner( 3, 2, Owner.Federation )
	--Klingon
	self.campaignMap:setHexOwner( 1, 7, Owner.Klingon )
	self.campaignMap:setHexOwner( 2, 7, Owner.Klingon )
	self.campaignMap:setHexOwner( 3, 7, Owner.Klingon )
	self.campaignMap:setHexOwner( 1, 6, Owner.Klingon )
	self.campaignMap:setHexOwner( 2, 6, Owner.Klingon )
	--Romulan
	self.campaignMap:setHexOwner( 5, 1, Owner.Romulan )
	self.campaignMap:setHexOwner( 7, 2, Owner.Romulan )
	self.campaignMap:setHexOwner( 6, 1, Owner.Romulan )
	self.campaignMap:setHexOwner( 7, 1, Owner.Romulan )
	--Dominion
	self.campaignMap:setHexOwner( 4, 4, Owner.Dominion )
	self.campaignMap:setHexOwner( 4, 5, Owner.Dominion )
	self.campaignMap:setHexOwner( 5, 4, Owner.Dominion )
	self.campaignMap:setHexOwner( 5, 5, Owner.Dominion )
	--Borg
	self.campaignMap:setHexOwner( 7, 7, Owner.Borg )
	self.campaignMap:setHexOwner( 6, 6, Owner.Borg )
	self.campaignMap:setHexOwner( 6, 7, Owner.Borg )
	self.campaignMap:setHexOwner( 7, 6, Owner.Borg )
end





