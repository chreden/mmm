include( "MapHex.lua" )

CampaignMap = {}
initMetatable( CampaignMap )

function CampaignMap.new( )
	local newMap = { }
	setmetatable( newMap, CampaignMap.mt )
	
	--Hexes will be populated later - it is in fact a 2d array of hexes
	newMap.hexes = nil
	
	return newMap
end

--This function is called by the database when a matching entry was foud
--It is expected to return a valid object from the data, or nil.
function CampaignMap.deserialize( dbentry )
	--Not sure what dbentry is at the minute, but will probably just
	--be a node or something.
	local newCampaignMap = CampaignMap.new( )
	
	--Some amount of hex loading here - we would load all nodes? Or is this actually
	--stored as children? Will need to think about that.
	
	return newCampaignMap
end

function CampaignMap.serialise( obj, dbentry )
	--Should serialise the entity given into the db entry given.
	--Does not need to return anything.
	
end

--This function will default initialise the map if it is not being loaded by the
--database. Ideally this would be done in a more data driven way, but whatever, I
--can deal with it this way.
function CampaignMap:createDefault( )
	
	function generateMap( width, height )
		local newHexes = { }
		for y = 0, height do
			local newRow = { }
			for x = 0, width do
				table.insert( newRow, Owner.None )
			end
			table.insert( newHexes, newRow )
		end
		return newHexes
	end
	
	local newHexes = generateMap( 6, 6 )
	
	self.hexes = { }
	
	local y = 0	
	for _, row in pairs( newHexes ) do
		local newRow = { }
		local x = 0		
		for _, col in pairs( row ) do
			local newHex = MapHex.new( Owner.None, x, y, self )
			table.insert( newRow, newHex )			
			x = x + 1
		end	
		table.insert( self.hexes, newRow )
		y = y + 1
	end
	
	self:create()
end

function CampaignMap:create() 
	--Create the hexes in the world.
	for _, row in pairs( self.hexes ) do
		for _, hex in pairs(row) do
			hex:create()
		end
	end
end

function CampaignMap:getDimensions( )
	--Find the maximum width
	local maxWidth = 0
	for _, row in pairs(self.hexes) do
		if #row > maxWidth then
			maxWidth = #row
		end
	end
	return Vector.new( maxWidth * 580, 0, #self.hexes * 670 )
end

function CampaignMap:getHex( pos )
	--Figure out what hex we are in somehow??
	
	
end

function CampaignMap:setHexOwner( x, y, owner )
	self.hexes[y][x]:setOwner( owner )
end
