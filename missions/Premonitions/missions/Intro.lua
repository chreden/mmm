--########################################################################
--						CINERACTIVE INTRO STATE					

include( "NameFinder.lua" )

class 'Intro' (State)

function Intro:__init( )

end

function Intro:onEnter( machine )

	Armada.gameSpeed = 25
	
	--Looks at the planet from a point that is sort of like the view from the original 
	--Premonitions mission - the ships will do a close fly-by on their way to their objectives.
	function planetFocus(id, arg)
		Cineractive:lookFrom( Vector(5100, 125, 150) )
		Cineractive:lookAt( Vector(4250, -850, 1500) )
		return CallbackResult.Remove
	end
		
	--Tells the 4 starting ships to move to the moon pair where JLP will explain the mission.
	function initMove(id, arg)
		EntityFinder( NameFinder( "USS Templar" ) ):findOne():giveOrder( Order.Go, Path("path_3") )
		EntityFinder( NameFinder( "USS Enterprise-E" ) ):findOne():giveOrder( Order.Go, Path("path_1") )
		EntityFinder( NameFinder( "USS Kursk" ) ):findOne():giveOrder( Order.Go, Path("path_2") )
		EntityFinder( NameFinder( "USS Podlech" ) ):findOne():giveOrder( Order.Go, Path("path_4") )
		return CallbackResult.Remove
	end
	
	--Shot that moves around the Enterprise while JLP does his chat about what goes on.
	function swingShip(id, arg)	
		Cineractive:lookFrom( Path("path_9"), 0.525 )
		Cineractive:lookAt(EntityFinder( NameFinder("USS Enterprise-E")):findOne())
		return CallbackResult.Remove
	end
	
	--Ends the cinematic and moves on to the build-up stage of the mission.
	function endCinematic( id, arg )
		Cineractive.active = false
		machine:setState( Buildup( ) )
		return CallbackResult.Remove
	end

	Cineractive.active = true
	Cineractive:fadeIn( 2.0 )
	UI:addTitle( 50, 50, "Premonitions", 9.5, true )
	
	--Play the music straight away (background music for the intro part)
	Media.playMusic( "premintro.wav" )
	
	Timer.add( "planetfocus", 0.0, self, planetFocus, nil )
	Timer.add( "initMove", 4.0, self, initMove, nil )
	Timer.add( "swingship", 20.0, self, swingShip, nil )
	Timer.add( "picard", 22.0, self, function() Media.playSound("prempic1.wav") return CallbackResult.Remove end, nil )
	Timer.add( "stopIntroMusic", 24.0, nil, function() Media.stopMusic() return CallbackResult.Remove end, nil )
	Timer.add( "trans", 48.0, self, function() Media.playSound("premtrans.wav") return CallbackResult.Remove end, nil )
	Timer.add( "endcine", 55.0, self, endCinematic, nil )	
end

