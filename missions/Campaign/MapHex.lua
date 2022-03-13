
Owner = { 
			None 		= 1,
			Federation  = 2,
			Klingon 	= 3,
			Borg		= 4,
			Dominion	= 5,
			Romulan		= 6
		}

HexModel = { "mmm_hex_gy",
			 "mmm_hex_b",
			 "mmm_hex_r",
			 "mmm_hex_g",
			 "mmm_hex_p",
			 "mmm_hex_g2" }
		
MapHex = {}
initMetatable( MapHex )

function MapHex.new( owner, col, row, map )
	local newHex = { }
	setmetatable( newHex, MapHex.mt )

	newHex.map 	 = map
	newHex.owner = owner
	newHex.col   = col
	newHex.row   = row
	
	return newHex
end

function MapHex:create( )
	--X offset is constant - the y flip flops.
	--X diff is apparently 580?
	--These are the dimensions for the hex map
	local mapDimensions = self.map:getDimensions( )
	
	--World map dims
	local centre = Map.getMax( ) / 2
	local startX = centre.x - mapDimensions.x * 0.5
	local startZ = centre.z - mapDimensions.z * 0.5 --Wrong?
	
	local pos = Vector.new( startX + self.col * 580, 0, startZ + self.row * 670 + self.col % 2 * 335 )
	--Actually creates the object
	self.ent = Entities.add( HexModel[ self.owner ], 0, pos )
end

function MapHex:setOwner( owner )
	--Simply replace the hex with the hex for the new value, if the owner is different.
	if( self.owner == owner ) then return end
	self.owner = owner
	self.ent:replace( HexModel[ self.owner ] )
end
