include( "NameFinder.lua" )

class 'Chatting' (State)

function Chatting:__init( )
end

function Chatting:onEnter( machine )
	
	--Find the Enterprise and the Premonition - we'll be doing a lot of looking at them.
	local enterprise = EntityFinder( NameFinder( "USS Enterprise-E" ) ):findOne()
	local premonition = EntityFinder( NameFinder( "USS Premonition" ) ):findOne()
	
	--These two functions are used a lot for the back and forth conversation. We just look at who
	--is talking.
	
	--Looks at the Enterprise from a small offset.
	function picardFocus( monitor, hook )
		if enterprise.valid then
			Cineractive:lookFrom( enterprise.position + Vector( 100, 15, 100 ) )
			Cineractive:lookAt( enterprise )
		end
	end

	--Looks at the Premonition from a small offset.
	function demmingFocus( monitor, arg )
		if premonition.valid then
			Cineractive:lookFrom(  premonition.position + Vector( 100, 15, 100 ) )
			Cineractive:lookAt( premonition )
		end
	end
	
	--Enter cineractive mode.
	Cineractive.active = true
	
	--Initally we want to look at the Enterprise since they start off the dialog.
	picardFocus()	
	
	--Sound for hailing the Premonition
	Media:playSound( "PremonitionsHail.ogg" )
	
	--Premonition says something
	Timer( "demming1", 4.0, Timer.State.Started ):hook( "focusOnDemming", self, demmingFocus, nil )
	
	--The whole dialog sound file. We look back and forth at offsets measured from the
	--sound file.
	Timer( "dialog", 5.0, Timer.State.Started ):hook( "dialog", nil, 
		function() 
			Media:playSound("PremonitionsDemming.ogg") 
		end, nil )
	
	--Picard says something.
	Timer( "picard1", 8.2, Timer.State.Started ):hook( "focusOnPicard", self, picardFocus, nil )
	--Demming says something.
	Timer( "demming2", 14.0, Timer.State.Started ):hook( "focusOnDemming", self, demmingFocus, nil )
	--Picard says something else.
	Timer( "picard2", 23.5, Timer.State.Started ):hook( "focusOnPicard", self, picardFocus, nil )
	--Demming says something.
	Timer( "demming3", 30.0, Timer.State.Started ):hook( "focusOnDemming", self, demmingFocus, nil )
	--Picard accepts and leaves the area (we just make him move on a path vaguely back to where the ships 
	--started)
	Timer( "picard3", 55.0, Timer.State.Started ):hook( "picardLeave", nil,
		function()
			if enterprise.valid then
				Media:playSound("PremonitionsEnding.ogg") 
				Cineractive:lookFrom( enterprise.position + Vector( 100, 15, 100 ) )
				Cineractive:lookAt( enterprise )
				enterprise:giveOrder( GameObject.Order.Go, Path( "endpath" ) )
			end
		end, nil )
	
	--Fade the screen out once the dialog is over and the Enterprise has moved away a bit.
	Timer( "fadeOut", 68.0, Timer.State.Started ):hook( "fadeOut", nil, 
		function() 
			Cineractive:fadeOut( 2.0 ) 
		end, nil )	
	
	--Stop cineractive mode.
	Timer( "ending", 70.0, Timer.State.Started ):hook( "ending", nil, 
		function()
			Cineractive.active = false
		end, nil )
end

function Chatting:onCineractiveEnd( forced )
	--We finish the mission in here because the player may have
	--forced this finish.
	Mission:finish( true, 0 )
end
