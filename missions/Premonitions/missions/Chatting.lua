class 'Chatting' (State)

function Chatting:__init( )
end

function Chatting:onEnter( machine )
	
	local enterprise = EntityFinder( function (e) return e:isType(EntityType.Craft) and e.name == "USS Enterprise-E" end ):findOne()
	local premonition = EntityFinder( function (e) return e:isType(EntityType.Craft) and e.name == "USS Premonition" end ):findOne()
	
	function picardFocus(id, arg)
		if enterprise.valid then
			Cineractive:lookFrom( enterprise.position + Vector( 100, 15, 100 ) )
			Cineractive:lookAt( enterprise )
		end
		return CallbackResult.Remove
	end

	function picardLeave(id, arg)
		if enterprise.valid then
			Cineractive:lookFrom( enterprise.position + Vector( 100, 15, 100 ) )
			Cineractive:lookAt( enterprise )
			enterprise:giveOrder( Order.Go, Path( "endpath" ) )
		end
		return CallbackResult.Remove
	end
	
	function demmingFocus(id, arg)
		if premonition.valid then
			Cineractive:lookFrom(  premonition.position + Vector( 100, 15, 100 ) )
			Cineractive:lookAt( premonition )
		end
		return CallbackResult.Remove
	end
	
	function endCineractive( id, arg )
		Cineractive.active = false
		--End the mission here.
		Mission.finish( true, 0 )
		return CallbackResult.Remove
	end
	
	Cineractive.active = true
	picardFocus(self, nil, nil)	
	Media.playSound( "premhail.wav" )
	Timer.add( "dem1", 4.0, self, demmingFocus, nil )
	Timer.add( "dialog", 5.0, self, function() Media.playSound("premdem2.wav") return CallbackResult.Remove end, "premdem2.wav" )
	Timer.add( "pic1", 8.2, self, picardFocus, nil )
	Timer.add( "dem2", 14.0, self, demmingFocus, nil )
	Timer.add( "pic2", 23.5,  self, picardFocus, nil )
	Timer.add( "dem3", 30.0,  self, demmingFocus, nil )
	Timer.add( "pic3", 55.0,  self, picardLeave, nil )
	Timer.add( "FINE", 55.0, self, function() Media.playSound("prempic3.wav") return CallbackResult.Remove end, "prempic3.wav" )
	Timer.add( "fadeOut", 68.0, self, function() Cineractive:fadeOut( 2.0 ) return CallbackResult.Remove end, nil )
	Timer.add( "ending", 70.0, self, endCineractive, nil )
end
