class 'TextInputTutorial'

function TextInputTutorial:__init()
    
end

function TextInputTutorial:setup( )
	--Find the ship (the USS Test)
    local finder = EntityFinder( function (e) return e:isType(Entity.Type.Craft) and e.name == "USS Test" end )
    local ship = finder:findOne()

	--Hooking our commands. We use patterns for this. Since N, E, S, and W are all similar we map them
	--to one function and pass a direction argument in too.
    TextInput:hook( "stop", self, TextInputTutorial.onStop, ship, "^stop$" )
    TextInput:hook( "north", self, TextInputTutorial.onMove, { moveShip = ship, move = Vector(0,0,750) }, "^north$" )
    TextInput:hook( "east", self, TextInputTutorial.onMove, { moveShip = ship, move = Vector(750,0,0) }, "^east$" )    
    TextInput:hook( "south", self, TextInputTutorial.onMove, { moveShip = ship, move = Vector(0,0,-750) }, "^south$" )
    TextInput:hook( "west", self, TextInputTutorial.onMove, { moveShip = ship, move = Vector(-750,0,0) }, "^west$" )
	
	Objectives:load( "TextInputTutorialObjectives.txt" )
	Objectives.visible = true
end

function TextInputTutorial:onStop( text, hook )
    local ship = hook.argument
	if not ship.valid then return end
    ship:giveOrder( GameObject.Order.Stop )
end

function TextInputTutorial:onMove( text, hook )
    local ship = hook.argument.moveShip
    if not ship.valid then return end
    ship:giveOrder( GameObject.Order.Go, ship.position + hook.argument.move )
end

MMM.register( TextInputTutorial() )

