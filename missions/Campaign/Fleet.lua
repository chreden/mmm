Fleet = { }
initMetatable( Fleet )

FleetType = { Economy = 0, Military = 1 }

function Fleet.new( fleetType, owner, position, team )
	local fleet = setmetatable( {}, Fleet.mt )
	fleet.ent = Entities.add( FleetManager.lookup[owner][fleetType], team, position )
	fleet.type = fleetType
	fleet.owner = owner
	fleet.team = team
	return fleet
end

function Fleet:update( map )
	local hex = map:getHex( self.ent:getPosition() )
	if( hex == nil ) then return end
	
	--Check where we are - this of course depends on the type.
	if( self.type == FleetType.Economy ) then
		--Check to see what sector we are in.
		
		
		
		
	elseif( self.type == FleetType.Military ) then
		--Do something military
		
	end
	
	
end
