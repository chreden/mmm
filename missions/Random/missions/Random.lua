include( "Avoidance.lua" )

--[[
	Map sizes for different amounts of players. General sizes, anyway.
--]]
MapSizes = 
{
	Vector( 7500, 250, 7500 ),		--1
	Vector( 12500, 250, 12500 ),	--2
	Vector( 13000, 250, 13000 ),	--3
	Vector( 14000, 250, 14000 ),	--4
	Vector( 15000, 250, 15000 ),	--5
	Vector( 17000, 250, 17000 ),	--6
	Vector( 18000, 250, 18000 ),	--7
	Vector( 22000, 250, 22000 )		--8
}

--[[
	Team Checker is used to search for entities using the EntityFinder.
--]]

class 'TeamChecker'

function TeamChecker:__init( t ) 
	self.team = t
end

function TeamChecker:evaluate( ent )
	return ent:isType(EntityType.GameObject) and ent.team.number == self.team.number
end

--[[
	Main application table and definition
--]]

class 'Random'

function Random:__init( )
	
end

function Random:setup( )
	--This ensures that we do the same thing on all computers. Basically the only
	--thing that is holding this mission together.
	math.randomseed( Armada.seed )
	
	self:setupAvoidance()
	--Figure out what players we have on the map
	self:arrangePlayers()
	--Now that we have found the players we can place some resources around as well
	--as some nebulae.
	self:createMapObjects()
end

--[[
	The avoidance map is used to place things in a way that they won't block.
--]]
function Random:setupAvoidance( )
	self.avoidance = Avoidance()
end

--[[
	Place the players aroound the map so that they are in team groups and are apart
	from the enemy.
--]]
function Random:arrangePlayers( )
	--First we acquire the players and the alliances that are present in the game.
	self.players = self:findPlayers( )
	self.alliances = self:findAlliances( self.players )
	--Now that we have the players we can adjust the size of the map and place the 
	--players into alliances.
	self:adjustMapSize(self.players)
	self:placeAlliances( self.alliances )
end

--[[
	Find active players (both AI and Human). Empty slots are not counted
--]]
function Random:findPlayers( )
	local actualPlayers = { }
	for i = 1, 8 do
		local team = Team( i )
		if( team.slotType ~= SlotType.None and team.slotType ~= SlotType.Observer ) then
			table.insert( actualPlayers, team )
		end
	end	
	return actualPlayers
end

--[[
	This function figures out what the teams are (not team as in the MMM sense, but Team as in
	the Alliance sense. Returns a table of tables (the inner table being each alliance).
--]]
function Random:findAlliances( players )
	
	local allies = { }
	
	--[[
		Check the compatibility of a team with all members of the alliance
		given.
	--]]
	function isAllied( team, allyGroup )
		for _, t in pairs( allyGroup ) do
			if team:getRelation( t ) ~= Relation.Ally then
				return false
			end
		end
		return true
	end
	
	--[[
		Attempts to fit the team into one of the existing
		alliances. If it cannot do this it does not add it, instead
		it returns false.
	--]]
	function attemptAlly( team )
		for _, allyGroup in pairs(allies) do
			if isAllied( team, allyGroup ) then
				table.insert( allyGroup, team )
				return true
			end
		end
		return false
	end
	
	--Try and group every player into the alliances that they are in. This is needed
	--so that we can place people properly.
	for _, team in pairs(players) do
		if false == attemptAlly( team ) then
			table.insert( allies, { team } )
		end
	end
	
	return allies
end

--[[
	Resizes the map based on the number of players are currently in the game. This will
	use the MapSizes table for now and may be expanded in the future to add some randomness 
	inside each range, to spice things up a bit.
--]]
function Random:adjustMapSize( players )
	local size = MapSizes[#players]
	Map.max = Vector( size.x, Map.max.y, size.z )
end

--[[
	Place everyone around the world in their team groups.
--]]
function Random:placeAlliances( allies )
	--Start at a random point around a circle. We then add on bits based on how many teams and 
	--players there are.
	local twopi = math.pi * 2
	
	local startingAngle = math.random( 0, twopi )
	--Divide the circle into sectors. For each alliance, an extra sector is added.
	local sectorAngle = twopi / #allies
	
	local mapCentre = (Map.max - Map.min) * 0.5
	local distanceFromCentre = mapCentre.z - 1250
	
	function moveStartingUnits( team, pos )
		--Move the actual player and their stuff (should just be the starbase at this point)
		local ents = EntityFinder( TeamChecker(team) ):find()
		
		for _, ent in pairs(ents) do
			ent.position = pos
			self.avoidance:addEntry( pos, 1500 )
		end
		
		--Using our own information here - set starting location
		team.position = pos
		
		--Focus camera (how do we know if we are this player?)
		if( (Armada.localSlot + 1) == team.number ) then
			Camera.center( pos )
		end
	end
	
	for index, allyGroup in pairs(allies) do
		local playerCount = #allyGroup
		local perPlayerAngle = sectorAngle / (playerCount + 1)
		
		for playerIndex, team in pairs(allyGroup) do
			local theta = startingAngle + (index-1) * sectorAngle + perPlayerAngle * playerIndex
			local pos = mapCentre + Vector( math.sin(theta) * distanceFromCentre, 0, math.cos(theta) * distanceFromCentre )
			pos.y = 0
			moveStartingUnits( team, pos )
		end
	end
end

--[[
	Place resources and map objects (asteroids and nebulae)
--]]
function Random:createMapObjects( )
	self:createTerrain()
	self:createResources()
end

function Random:createTerrain( )
	for i = 0, math.random(5, 25) do self:createAsteroidBelt() end
	for i = 0, math.random(10, 30) do self:createNebula() end
end

function Random:createNebula() 
	--Asteroid fields and the like - chains
	function acquireStartPosition()
		for i = 0, 100 do
			local newPos = Vector( math.random(0,Map.max.x), 0, math.random(0, Map.max.z) )
			if self.avoidance:isClear( newPos ) then return newPos end
		end
	end
	
	local nebs = { "map_nebula_fluidset",
				   "map_nebula_mutaraset",
				   "map_nebula_nucleonset",
				   "map_nebula_tetrionset" }
				   --"map_nebula_organic" }
				   
	function createNebula( pos, neb )
		Entities.add( neb, 0, pos )
		Entities.add( "trigger_blocking_sml", 0, pos )
		self.avoidance:addEntry( pos, 1000 )
	end
	
	local positions = { }
	
	local previous = acquireStartPosition()
	if previous ~= nil then
		
		local lastAngle = math.random(math.pi * 2)
		local neb = nebs[math.random(1,#nebs)]
		
		for i = 1, math.random(1,10) do
			local nextAngle = lastAngle + math.random(-1.5, 1.5)
			local nextpos = previous + Matrix.createRotationY( nextAngle ) * Vector(0,0,600)
			if self.avoidance:isClear( nextpos ) then
				table.insert(positions, nextpos)
				lastAngle 	= nextAngle
				previous 	= nextpos
			end
		end
		for _, v in pairs(positions) do createNebula( v, neb ) end
	end
	
end

function Random:createAsteroidBelt()
	--Asteroid fields and the like - chains
	function acquireStartPosition()
		for i = 0, 100 do
			local newPos = Vector( math.random(0,Map.max.x), 0, math.random(0, Map.max.z) )
			if self.avoidance:isClear( newPos ) then return newPos end
		end
	end
	
	function createAsteroid( pos )
		Entities.add( "map_asteroidfield1", 0, pos )
		Entities.add( "trigger_blocking_sml", 0, pos )
		self.avoidance:addEntry( pos, 500 )
	end
	
	local positions = { }
	
	local previous = acquireStartPosition()
	if previous ~= nil then
		
		local lastAngle = math.random(math.pi * 2)
		
		for i = 1, math.random(3, 25) do
			local nextAngle = lastAngle + math.random(-1.0, 1.0)
			local nextpos = previous + Matrix.createRotationY( nextAngle ) * Vector(0,0,200)
			if self.avoidance:isClear( nextpos ) then
				table.insert(positions, nextpos)
				lastAngle 	= nextAngle
				previous 	= nextpos
			end
		end
		
		for _, v in pairs(positions) do createAsteroid( v ) end
		
	end
end

function Random:createResources( )
	--First we need to create the player's starting resource moons. They are near the starbase (and not too
	--far away from or close to the starbase). There should probably be some sort of map of places that we
	--avoid.
	
	--Initial moons do not check avoidance (because they need to be there)
	for _, player in pairs(self.players) do
		--Dil
		local moonDistance = 1000
		local unit = Vector(0,0,moonDistance)
		local diAngle = math.random( 0, math.pi * 2 )
		local triAngle = diAngle + math.pi + math.random( -0.4, 0.4 )
		local diMoonPos = Matrix.createRotationY( diAngle ) * unit
		local triMoonPos = Matrix.createRotationY( triAngle ) * unit
				
		Entities.add( "trigger_dilithium.odf", 0, player.position + diMoonPos )
		Entities.add( "trigger_tritanium.odf", 0, player.position + triMoonPos )		
	end
	
	function spawnMany( odf, radius, count )
		--Expansion moons
		for i = 1, count do 
			while( true ) do
				local newPos = Vector(math.random(2500, Map.max.x - 2500), 0, math.random(2500, Map.max.z - 2500))
				if self.avoidance:isClear( newPos ) then
					Entities.add( odf, 0, newPos ) 
					self.avoidance:addEntry( newPos, radius )
					break
				end
			end
		end	
	end
	
	spawnMany( "trigger_dilithium", 500, 6 )
	spawnMany( "trigger_tritanium", 500, 6 )
	
end

MMM.register( Random( ) )