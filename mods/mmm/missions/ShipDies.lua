--The ShipDies state is used when a hero ship is destroyed. It shows a cineractive and 
--some text while zooming in on where the ship died.

class 'ShipDies' (State)

function ShipDies:__init( shipPosition, displayName )
	self.position = shipPosition
	self.displayName = displayName
end

function ShipDies:onEnter( machine )
	
	--Stop existing monitor hooks, if there are any, so they don't interfere
	--with the cutscene.
	Monitor.stopAll( )
	Timer.stopAll( )
		
	--Stops the existing music, which would have been playing in the previous
	--state.
	Media:stopMusic( )
	
	--Play transition as a sound effect, as we don't want it to loop.
	Media:playSound( "PremonitionsTransition.ogg" )
	
	--Go into cineractive mode - this one is unskippable though.
	Cineractive.active = true	
	Cineractive.skippable = false
	
	--Quick message to tell the player what's going on.
	UI:addMessage( self.displayName .. " has been destroyed", 800, 900, UI.Justify.Center, Color(1,1,1), true, 4 )

	--Generate a path to fly towards the ship as it blows up.
	local rotationMatrix = Matrix.rotationY( math.random() * math.pi * 2 )
	local startPoint = rotationMatrix * Vector(0, 50, 750)
	
	local approachPath = Path("DeathPath:" .. self.displayName)
	approachPath:append( self.position + startPoint )
	approachPath:append( self.position )
	
	Cineractive:lookFrom( approachPath, 0.1 )
	Cineractive:lookAt( self.position )
	
	--The end cineractive timer will fade the screen out and end the mission after a short
	--amount of time.
	Timer( "endCineractive", 5.0, Timer.State.Started ):hook( "endCineractive", nil,
		function()
			Cineractive:fadeOut( 1.5 )
			Mission:finish( false, 2.0 )
		end, nil )
	
end

function setupShipDeathHook( ship, displayName, machine )
	
	local shipData = { position = ship.position }
	
	--Timer to get the position of the ship every half second, so we can do the 
	--death cineractive if it dies.
	local trackerTimer = Timer( "shipTracker:" .. ship.name, 0.5, Timer.State.Started )
	trackerTimer.repeats = true
	trackerTimer:hook("tracker", nil, 
		function(t, h) 
			if( ship.valid ) then 
				shipData.position = ship.position
			else
				t:stop( )
			end
		end, nil )
	
	ship:hook( "onDeath", EntityHook.Type.OnDestroy, nil, 
			  function(e, h)
				--Fail the mission (set it to the ship failure state)
				machine:setState( ShipDies( shipData.position, displayName ) )
			  end, nil )	
end
