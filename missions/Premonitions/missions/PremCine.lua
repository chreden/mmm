--########################################################################

class 'PremCine' (State)

function PremCine:__init( )
end

function PremCine:onEnter( machine )

	function startCineractive( )
		self.wormhole = Entity.add("map_wormhole.odf", 0, Vector( 1868, 0, 4800 ) )
		--Find the existing wormhole.
		self.wormholeSource = EntityFinder( function(e) return e:isType(EntityType.Wormhole) and e.label == "wh_source" end ):findOne()
		self.wormhole.link = self.wormholeSource
		--Delete both wormholes once the ships have all come through.
		self.wormhole.expireOnClose = true
		self.wormholeSource.expireOnClose = true
		
		Cineractive.active = true
		Cineractive:lookFrom( Vector( 1868, 0, 5600 ) )
		Cineractive:lookAt( self.wormhole )
		
		return CallbackResult.Remove
	end	
	
	function makePremonition( )
		self.premonition = Entity.add("fed_premonition.odf", 1, Vector(420, 0, 250))
		self.premonition.name = "USS Premonition"
		self.premonition.shields = 2.0
		self.premonition:giveOrder(Order.Go, self.wormholeSource)
		return CallbackResult.Remove
	end
	
	function makeBorg( )
		self.premonition.systems.engines.active = false
		self.premonition.systems.engines.permanentDisable = true		
		self.premonition.systems.weapons.active = false
		self.premonition.systems.weapons.permanentDisable = true
			
		Entity.add("bor_interceptor.odf", 2, Vector(420, 0, 250)):giveOrder( Order.Go, self.wormholeSource )
		Entity.add("bor_interceptor.odf", 2, Vector(420, 0, 250)):giveOrder( Order.Go, self.wormholeSource )
		
		return CallbackResult.Remove
	end
	
	function endCineractive( )
		Cineractive.active = false
		Media.playSound("premtrans2.wav")
		machine:setState( Borg() )
		return CallbackResult.Remove
	end
	
	Media.playSound( "premsec.wav" )

	Timer.add( "startCine", 4.0, self, startCineractive, nil )
	Timer.add( "makeprem", 8.0, self, makePremonition, nil )
	Timer.add( "makeborg", 9.0, self, makeBorg, nil )
	Timer.add( "picard", 13.0, self, function() Media.playSound("prempic2.wav") return CallbackResult.Remove end, nil )
	Timer.add( "dem", 21.0, self, function() Media.playSound("premdem.wav") return CallbackResult.Remove end, nil )
	Timer.add( "endcine", 30.0, self, endCineractive, nil )
end
