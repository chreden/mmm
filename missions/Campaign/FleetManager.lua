--[[
	Fleet manager cotrols all the fleets that we have in the world, and 
	the addition of new fleets to the game.
--]]

include( "Fleet.lua" )

FleetManager = { }
initMetatable( FleetManager )

function FleetManager.new( )
	local manager = { }
	setmetatable( manager, FleetManager.mt )
	
	manager.fleets = { }
	
	--Default initialise the lookup table for the fleets.
	if( FleetManager.lookup == nil ) then
		FleetManager.lookup = { }
	end
	
	FleetManager.lookup[Owner.Federation] = { }
	FleetManager.lookup[Owner.Federation][FleetType.Economy] = "mmm_fleet_econ_fed.odf"
	FleetManager.lookup[Owner.Federation][FleetType.Military] = "mmm_fleet_def_fed.odf"
	return manager
end

function FleetManager:add( fleetType, owner, position, isPlayer )
	--A fleet will actually not just be an entity - it will be yet another class which
	--will manage things some more. Woo management.
	local newFleet = Fleet.new( fleetType, owner, position, 1 )
	table.insert( self.fleets, newFleet )
end

function FleetManager:update( map )
	for _, v in pairs(self.fleets) do 
		v:update( map )
	end
end