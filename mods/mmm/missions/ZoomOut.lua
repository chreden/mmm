--The ZoomOut state is used for the Cineractive when the ships have moved to the start point. 

include( "NameFinder.lua" )
include( "Buildup.lua" )

class 'ZoomOut' (State)

function ZoomOut:__init( )

end

function ZoomOut:onEnter( machine )

	self.stateMachine = machine

	Cineractive.active = true
	Cineractive.skippable = false
	
	Cineractive:fadeIn( 2.0 )
	Cineractive:lookFrom( Path( "zoomout" ), 0.18 )
	Cineractive:lookAt(EntityFinder( NameFinder("USS Enterprise-E")):findOne())
	Media:playSound("PremonitionsTransition.ogg") 
	
	--After about 7 seconds we want to end the Cineractive mode. We just pass a function here because
	--it's a pretty simple one. Cineractive finish will get called by MMM where we set up the next state.
	Timer( "endCineractive", 7.0, Timer.State.Started ):hook( "endCineractive", nil, 
		function(t,h) 
			Cineractive.active = false 
		end, nil )	

end

function ZoomOut:onCineractiveEnd( forced )
	--Move into the buildup state now that we are done
	self.stateMachine:setState( Buildup( ) )
end
