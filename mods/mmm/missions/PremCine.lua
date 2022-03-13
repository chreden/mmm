--The premonition cineractive state just shows the Premonition coming through the time hole and getting
--attacked by some Borg ships.

include( "Borg.lua" )

class 'PremCine' (State)

function PremCine:__init( )
end

function PremCine:onEnter( machine )
	
	self.stateMachine = machine
	
	--Starting the cineractive is slightly complex - we have to make some wormholes so that
	--the ships can go through them. We link them together so they can travel, then turn on
	--Cineractive mode.
	Timer( "startCineractive", 4.0, Timer.State.Started ):hook( "startCineractive", self, 
		function()
			self.wormhole = Entity.add("map_wormhole.odf", 0, Vector( 1868, 0, 4800 ) )
			--Find the existing wormhole.
			self.wormholeSource = EntityFinder( function(e) return e:isType(Entity.Type.Wormhole) and e.label == "wh_source" end ):findOne()
			self.wormhole.link = self.wormholeSource
			--Delete both wormholes once the ships have all come through.
			self.wormhole.expireOnClose = true
			self.wormholeSource.expireOnClose = true
			--Actually start the cineractive now. Make it unskippable since it would be complex to recover
			--and is important.
			Cineractive.active = true
			Cineractive.skippable = false
			Cineractive:lookFrom( Vector( 1868, 0, 5600 ) )
			Cineractive:lookAt( self.wormhole )
		end, nil )
	
	--Make the USS Premonition and send it through the wormhole that we made in the previous timer hook. Give it a bit of a shield
	--boost so the player always has a chance to react.
	Timer( "makePremonition", 8.0, Timer.State.Started ):hook( "makePremonition", self,
		function( t, h )
			self.premonition = Entity.add("fed_premonition.odf", 1, Vector(420, 0, 250))
			self.premonition.name = "USS Premonition"
			self.premonition.shields = 2.0
			self.premonition:giveOrder(GameObject.Order.Go, self.wormholeSource)
		end, nil )		
	
	--Make the Borg ships that are pursuing the Premonition through the wormhole. Using probes because 2 spheres would be quite 
	--a challenge for players. We also disable the Premonition now that it has gone through the wormhole.
	Timer( "makeBorg", 9.0, Timer.State.Started ):hook( "makeBorg", self, 
		function()
			--Now that the Premonition has got through the wormhole, we can disable the engines and weapons and
			--engines of the Premonition.
			self.premonition.systems.engines.active = false
			self.premonition.systems.engines.permanentDisable = true		
			self.premonition.systems.weapons.active = false
			self.premonition.systems.weapons.permanentDisable = true
			--While we're here, set special energy to 0 so that you can't use the special.
			self.premonition.specialEnergy = 0
			self.premonition.maxSpecialEnergy = 0	
				
			Entity.add("bor_interceptor.odf", 2, Vector(420, 0, 250)):giveOrder( GameObject.Order.Go, self.wormholeSource )
			Entity.add("bor_interceptor.odf", 2, Vector(420, 0, 250)):giveOrder( GameObject.Order.Go, self.wormholeSource )
			
			Media:playMusic( "PremonitionsAppear.ogg" )
		end, nil )
	
	--Simple timer to play dialog where Picard says he recognises the Premonition.
	Timer( "picardRecognise", 13.0, Timer.State.Started ):hook( "picardRecognise", nil,
		function() 
			Media:playSound("PremonitionsRecognise.ogg") 
		end, nil )
	
	--Demming sends a distress call from the Premonition. This timer just plays that sound effect.
	Timer( "demmingDistress", 21.0, Timer.State.Started ):hook( "demmingDistress", nil,
		function() 
			Media:playSound("PremonitionsDistress.ogg") 
		end, nil )
	
	--Ends the cineractive mode after Demming has sent his distress call. 
	Timer( "endCineractive", 30.0, Timer.State.Started ):hook( "endCineractive", nil, 
		function ()
			Cineractive.active = false
		end, nil )
		
end

function PremCine:onCineractiveEnd( forced )
	--Plays the dialog where they lose the distress transmission.
	Media:playSound("PremonitionsLostTransmission.ogg")
	--Move to the Borg fighting state.
	self.stateMachine:setState( Borg() )
end
