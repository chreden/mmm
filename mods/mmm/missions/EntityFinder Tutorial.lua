class 'EntityFinderTutorial'

function EntityFinderTutorial:__init( )
	
end

function EntityFinderTutorial:setup( )

	--EntityFinder using two conditions in one function - could also 
	--pass two functions in a table.
	local finder = EntityFinder(
									function (e) return e:isType(Entity.Type.Craft) and
														e.maxCrew < 100 end
								)
								
	--Finds all matching entities - the returned value is a table of all entities.
	--0 length if no matches.
	local ents = finder:find()
	
	for _, v in pairs( ents ) do
		print( v.name )
	end
	
	Objectives:load( "EntityFinderTutorialObjectives.txt" )
	Objectives.visible = true	
end

MMM.register( EntityFinderTutorial( ) )
