--The Intro state is used for the Cineractive when the ships move to the start point. Picard does the
--captain's log.

include( "NameFinder.lua" )
include( "ZoomOut.lua" )

class 'Intro' (State)

function Intro:__init( )

end

function Intro:onEnter( machine )

	self.stateMachine = machine

	--Gets the Cineractive started, fades in the screen and shows
	--the title.
	Cineractive.active = true
	Cineractive:fadeIn( 2.0 )
	UI:addTitle( "Premonitions", 50, 50, 9.5, true )
	 
	--Play the music straight away (background music for the intro part)
	Media:playMusic( "PremonitionsIntroMusic.ogg" )
	
	--Looks at the planet from a point that is sort of like the view from the original 
	--Premonitions mission - the ships will do a close fly-by on their way to their objectives.
	Timer( "lookAtPlanet", 0.0, Timer.State.Started ):hook( "lookAtPlanet", nil, 
		function()
			Cineractive:lookFrom( Vector(5150, 125, 200) )
			Cineractive:lookAt( Vector(4250, -850, 1500) )			
		end, nil )
	
	--Gives the ships the initial move order. They will move across the screen and eventually stop
	--at the destination point (near the moons).
	Timer( "moveShips", 4.0, Timer.State.Started ):hook( "moveShips", nil, 
		function()
			EntityFinder( NameFinder( "USS Enterprise-E" ) ):findOne():giveOrder( GameObject.Order.Go, Path("path_1") )
			EntityFinder( NameFinder( "USS Kursk" ) ):findOne():giveOrder( GameObject.Order.Go, Path("path_2") )
			EntityFinder( NameFinder( "USS Templar" ) ):findOne():giveOrder( GameObject.Order.Go, Path("path_3") )
			EntityFinder( NameFinder( "USS Podlech" ) ):findOne():giveOrder( GameObject.Order.Go, Path("path_4") )
		end, nil )
	
	--Cineractive shot that moves around the Enterprise while Picard does the captain's
	--log speech.
	Timer( "moveAroundEnterprise", 20.0, Timer.State.Started ):hook( "moveAroundEnterprise", nil,
		function()
			Cineractive:lookFrom( Path("path_9"), 0.525 )
			Cineractive:lookAt(EntityFinder( NameFinder("USS Enterprise-E")):findOne())
		end, nil )
	
	--Play the Captain's Log while we circle around the ships.
	Timer( "captainsLog", 22.0, Timer.State.Started ):hook( "captainsLog", nil, 
		function() 
			Media:playSound("PremonitionsCaptainsLog.ogg") 
		end, nil )
	
	--The introduction music needs to be stopped at around 24 seconds in, so we
	--set a timer for that too.
	Timer( "stopIntroMusic", 24.0, Timer.State.Started ):hook( "stopIntroMusic", nil, 
		function() 
			Media:stopMusic() 
		end, nil )

	--Transition - while the camera zooms out a bit, we play the transition music.
	Timer( "fadeOut", 46.0, Timer.State.Started ):hook( "fadeOut", nil,
		function() 
			Cineractive:fadeOut( 2.0 )
		end, nil )		
		
	--Transition - while the camera zooms out a bit, we play the transition music.
	Timer( "changeState", 48.0, Timer.State.Started ):hook( "changeState", nil,
		function() 
			machine:setState( ZoomOut() )
		end, nil )

end

--Calculate where the ships should be when they reach the end of the path.
function Intro:calculateShipDestinations( )
	
	--Get a ship by name.
	function getShip( name )
		return EntityFinder( NameFinder( name ) ):findOne()
	end
	
	--Get the last vector entry in the path points.
	function getLastPathPoint( name )
		local p = Path(name)
		return p.points[p.count]
	end
	
	local results = { }
	
	results[ getShip("USS Enterprise-E") ] = getLastPathPoint("path_1")
	results[ getShip("USS Kursk") ] =  getLastPathPoint("path_2")
	results[ getShip("USS Templar") ] = getLastPathPoint("path_3")
	results[ getShip("USS Podlech") ] = getLastPathPoint("path_4")
	
	return results
end

function Intro:onCineractiveEnd( forced )
	
	--Cineractive may have been ended by the user, so we have to make sure that
	--the mission is in the right state.
	if( forced ) then
		--Stop all audio messages that may be playing, since the cineractive 
		--was force ended.	
		Media:stopSounds( )
		
		--Stop all timers too since they would mess up things if we left them going.
		Timer.stopAll( )
		
		--Move ships to their destinations, as we can't assume that they got to where
		--they were going.
		for ship, pos in pairs(self:calculateShipDestinations( )) do
			--Move to the end of the path
			ship.position = pos
			--Since the ships may be moving along the path, we have to stop them
			--otherwise they will go back to try and follow the path from
			--the start.
			ship:giveOrder( GameObject.Order.Stop )
		end
		
		--Move into the buildup state now that we are done
		self.stateMachine:setState( ZoomOut( ) )
		
	end

end
