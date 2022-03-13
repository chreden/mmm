class 'ResourceArea'

ResourceArea.Type = 
{
	Dilithium = 0,
	Tritanium = 1
}

function ResourceArea:__init( team, moon )
	--Store the moon so we can get at it later.
	self.moon = moon
	self.team = team
	
	--Detect what type of moon this is.
	if string.find( self.moon.odf, "dilithium" ) ~= nil then
		self.type = ResourceArea.Type.Dilithium
	else 
		self.type = ResourceArea.Type.Tritanium
	end		
end

--Calculates the optimal position 
function ResourceArea:calculateStationPosition( base )
	return self.moon.position - (self.moon.position - base.position):normalize() * 400
end

--This function checks to see if we have a station in the area. If we 
--do then it returns the station. If not, returns nil.
function ResourceArea:hasStation( ) 
	--local stations = EntityFinder( function(e) return e:isType( EntityType.MiningStation ) and e.team.number = self.team end ):find()
	
		
end


