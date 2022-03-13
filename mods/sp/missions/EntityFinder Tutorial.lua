class 'EntityFinderTutorial'

function EntityFinderTutorial:__init( )
	
end

function EntityFinderTutorial:setup( )

	--We can extend the current one as well
	local finder = EntityFinder(
									function (e) return e:isType(EntityType.Craft) and
														e.maxCrew < 100 end
								)
								
	--Finds all matching entities - the returned value is a table of all entities.
	--0 length if no matches.
	local ents = finder:find()
	
	for _, v in pairs( ents ) do
		print( v.name )
	end
	
end

MMM.register( EntityFinderTutorial( ) )
