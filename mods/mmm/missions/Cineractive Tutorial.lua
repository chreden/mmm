class 'CineractiveTutorial'

function CineractiveTutorial:__init( )
	
end

function CineractiveTutorial:setup( )
	
	Cineractive.active = true
	Cineractive.skippable = false
	
	--Screen will fade in over two seconds
	Cineractive:fadeIn( 2.0 )
	--Add the title at coordinates 50, 50. It will fade in, stay and fade out over four seconds
	UI:addTitle( "Cineractive Tutorial", 50, 50, 4.0, true )
	--Add subtitle below the title. It will stay the same amount of time as the title
	UI:addSubtitle( "The Flyby", 50, 75, 4.0, true )   
	
	--Search for entities that have the "sfc" label. Since there is only one
	--we will get the station
	local sfc = EntityFinder( function(e) 
								return e:isType(Entity.Type.GameObject) 
									   and e.label == "sfc" 
								end ):findOne()
	
	Cineractive:lookFrom( sfc )
	--200, 100, 0 is slightly above and to the right of the station
	Cineractive:setCameraOffset( Vector( 200, 100, 0 ) )
	
	--Search for entities that have the "fedship" label. Since there is only one
	--we will get the ship
	local ship = EntityFinder( function(e)
									return e:isType(Entity.Type.GameObject)
										   and e.label == "fedship"
							   end ):findOne()
										
	Cineractive:lookAt( ship )
	ship:giveOrder( GameObject.Order.Go, sfc )

	--This timer will go off in 23 seconds (about the time it takes for the
	--ship to reach the station).
	local fadeTimer = Timer( "fadeTimer", 23, Timer.State.Started )
	--Hook function will fade the screen out over two seconds
	fadeTimer:hook( "fadeOut", nil, function(timer, hook) 
										Cineractive:fadeOut( 2.0 ) 
									end, nil )
	
	--This time will go off in 26 seconds (this will be after the screen has faded
	--out)
	local endCineractiveTimer = Timer( "endTimer", 26, Timer.State.Started )
	--Hook function will end the Cineractive and focus the camera on the station
	endCineractiveTimer:hook( "endCineractive", nil, function(timer, hook) 
														Cineractive.active = false
														Camera:center( sfc )
														Objectives:load( "CineractiveTutorialObjectives.txt" )
														Objectives.visible = true
													end, nil )		
end

MMM.register( CineractiveTutorial( ) )
