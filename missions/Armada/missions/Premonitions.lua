--Quick state machine implementation - to make things easier to manage without 
--world of ifelseif.

--A state is the base 'class' for any mission state. Is used with state machine.
State = { }
initMetatable( State )

function State.new( )
	return setmetatable( { }, State.mt )
end

function State:onUpdate( )
	--print("Base Update")
end

function State:onCineractiveBegin( )
	--print("Base Cine Begin")
end

function State:onCineractiveEnd( )
	--print("Base Cine End")
end

function State:onCineractiveUpdate( )
	--print("Base Cine Update")
end

function State:onEnter( )
	--print("Base Enter")
end

function State:onExit( )
	--print("Base Exit")
end

--Different states here.
--########################################################################
--						CINERACTIVE INTRO STATE					

Intro = { }
initMetatable( Intro )
inherit( Intro, State )

function Intro.new( )
	local newIntro = State.new( )
	
	setmetatable( newIntro, Intro.mt )
	
	newIntro.stateMachine = nil
	
	return newIntro
end

function Intro:onEnter( machine )
	self.stateMachine = machine

	Cineractive.start( )
	if( false ) then
		Timers.add( "endcine", 1.0, self, Intro.endCine, nil )
	else
		--Music playlist
		Timers.add( "music", 0.0, self, Intro.playIntroSound, "premintro.wav" )
		Timers.add( "picard", 22.0, self, Intro.playIntroSound, "prempic1.wav" )
		Timers.add( "trans", 48.0, self, Intro.playIntroSound, "premtrans.wav" )
		Timers.add( "endcine", 55.0, self, Intro.endCine, nil )
		--Text display
		Timers.add( "text", 1.0, self, Intro.showTitle, nil )
	end
end


function Intro:setupCinematic()
	
	function planetFocus(id, arg)
		Cineractive.lookFromPosition( Vector.new(5100, 125, 150) )
		Cineractive.lookAtPosition( Vector.new(4250, -850, 1500) )
		return CallbackResult.Remove
	end
		
	function initMove(id, arg)
		Entities.get( GetEntity.Name, "USS Templar" ):giveOrderPath( Order.Go, Paths.find("path_3") )
		Entities.get( GetEntity.Name, "USS Enterprise-E" ):giveOrderPath( Order.Go, Paths.find("path_1") )
		Entities.get( GetEntity.Name, "USS Kursk" ):giveOrderPath( Order.Go, Paths.find("path_2") )
		Entities.get( GetEntity.Name, "USS Podlech" ):giveOrderPath( Order.Go, Paths.find("path_4") )
		return CallbackResult.Remove
	end
	
	function swingShip(id, arg)
		Cineractive.lookFromPath( "path_8", 0.525 )
		Cineractive.lookAtGameObject(Entities.get( GetEntity.Name, "USS Enterprise-E" ) )
		return CallbackResult.Remove
	end
	
	Timers.add( "planetfocus", 0.0, self, planetFocus, nil )
	Timers.add( "initMove", 4.0, self, initMove, nil )
	Timers.add( "swingship", 20.0, self, swingShip, nil )
end

function Intro:showTitle( id, arg )
	UI.addMessage( 50, 50, 0, "Premonitions", 0xff0080ff, true, 8.5, true )
	return CallbackResult.Remove
end

function Intro:playIntroSound( id, name )
	Media.playSound(name)
	return CallbackResult.Remove
end

function Intro:playIntroMusic( id, name )
	Media.playMusic(name)
	return CallbackResult.Remove
end

function Intro:endCine( id, arg )
	Cineractive.finish( )
	self.stateMachine:setState( Buildup.new( ) )
	return CallbackResult.Remove
end

function Intro:onCineractiveBegin( )
	if( true ) then
		self:setupCinematic()
	end
end

--########################################################################


Buildup = { }
initMetatable( Buildup )
inherit( Buildup, State )

function Buildup.new( )
	local newBuildup = State.new( )
	
	setmetatable( newBuildup, Buildup.mt )
	
	newBuildup.stateMachine = nil
	
	return newBuildup
end

function Buildup:onEnter( machine )
	self.stateMachine = machine
	
	self.starbaseDone = false
	self.miningDone = false
	
	Mission.loadObjectives( "Premonitions.txt" )
	Mission.showObjectives( true )	
end

function Buildup:onUpdate( )
	--Check for starbase.
	self:checkStarbase()
	self:checkMining()
	if( self.starbaseDone ) then Mission.setObjective( 0, true ) end
	if( self.miningDone ) then Mission.setObjective( 1, true ) end
	
	if(  self.starbaseDone and self.miningDone  ) then
		--Complete! Next state.
		--Enter next state
		self.stateMachine:setState( Dominion.new() )
	end
end

function Buildup:checkStarbase( )
	if self.starbaseDone then return true end
	
	local ents = Team.new(1):getEntities()
	for _, v in pairs(ents) do
		if v:getOdfName() == "fed_outpostya.odf" then
			self.starbaseDone = true
			Mission.setObjective( 0, true )
			Mission.showObjectives( true )
			return true
		end
	end	
	
	return false
end

function Buildup:checkMining( )
	if self.miningDone then return true end
	
	local ents = Team.new(1):getEntities()
	for _, v in pairs(ents) do
		if v:getOdfName() == "fed_storage_dock.odf" then
			self.miningDone = true
			Mission.setObjective( 1, true )
			Mission.showObjectives( true )
			return true
		end
	end	
	
	return false
end

--########################################################################

Dominion = { }
initMetatable( Dominion )
inherit( Dominion, State )

function Dominion.new( )
	local newDom = State.new( )
	
	setmetatable( newDom, Dominion.mt )
	
	newDom.stateMachine = nil
	
	return newDom
end

function Dominion:onEnter( machine )
	self.stateMachine = machine
	
	self.shipsKilled = false
		
	Media.playSound( "premdom.wav" )
	Mission.loadObjectives( "Premonitions1.txt" )
	Mission.showObjectives( true )	
end

function Dominion:onUpdate( )
	--Check for starbase.
	if( self:checkShips() ) then
		--Complete! Next state.
		--Enter next state
		self.stateMachine:setState( PremCine.new( ) )
	end
end

function Dominion:checkShips( )
	if self.shipsKilled then return true end
	
	local ents = Team.new(2):getEntities()
	if #ents == 0 then 
		Mission.setObjective( 0, true )
		Mission.showObjectives( true )
		return true 
	end
	
	return false
end

--########################################################################

PremCine = { }
initMetatable( PremCine )
inherit( PremCine, State )

function PremCine.new( )
	local newIntro = State.new( )
	
	setmetatable( newIntro, PremCine.mt )
	
	newIntro.stateMachine = nil
	
	return newIntro
end

function PremCine:onEnter( machine )
	self.stateMachine = machine

	Media.playSound( "premsec.wav" )
	
	
	--Music playlist
	Timers.add( "startCine", 4.0, self, PremCine.startCine, nil )
	Timers.add( "makeprem", 8.0, self, PremCine.makePrem, nil )
	Timers.add( "makeborg", 9.0, self, PremCine.makeBorg, nil )
	Timers.add( "picard", 13.0, self, PremCine.playIntroSound, "prempic2.wav" )
	Timers.add( "dem", 21.0, self, PremCine.playIntroSound, "premdem.wav" )	
	Timers.add( "endcine", 30.0, self, PremCine.endCine, nil )
end


function PremCine:startCine(id,arg )
	--add wormhole here too at 1868 0 5219
	self.wormhole = Entities.add("map_wormhole.odf", 0, Vector.new( 1868, 0, 4800 ) )
	self.wormhole:setWormholeLink( Entities.get(GetEntity.Handle, "wh_source") )
	
	Cineractive.start( )	
end

function PremCine:makePrem( )
	self.premonition = Entities.add("fed_premonition.odf", 1, Vector.new(420, 0, 250))
	self.premonition:setName("USS Premonition")
	self.premonition:setShields(2.0)
	self.premonition:giveOrderEntity(Order.Go, Entities.get(GetEntity.Handle, "wh_source"))
	return CallbackResult.Remove
end

function PremCine:makeBorg( )
	self.premonition:setSystemStatus(System.Engines, false )
	self.premonition:setSystemStatus(System.Weapons, false )
		
	self.b1 = Entities.add("bor_interceptor.odf", 2, Vector.new(420, 0, 250))
	self.b2 = Entities.add("bor_interceptor.odf", 2, Vector.new(420, 0, 250))
	
	self.b1:giveOrderEntity(Order.Go, Entities.get(GetEntity.Handle, "wh_source"))
	self.b2:giveOrderEntity(Order.Go, Entities.get(GetEntity.Handle, "wh_source"))
	return CallbackResult.Remove
end

function PremCine:setupCinematic()
	Cineractive.lookFromPosition( Vector.new( 1868, 0, 5600 ) )
	Cineractive.lookAtGameObject( self.wormhole )
end

function PremCine:playIntroSound( id, name )
	Media.playSound(name)
	return CallbackResult.Remove
end

function PremCine:playIntroMusic( id, name )
	Media.playMusic(name)
	return CallbackResult.Remove
end

function PremCine:endCine( id, arg )
	Cineractive.finish( )
	Media.playSound("premtrans2.wav")
	self.stateMachine:setState( Borg.new() )
	return CallbackResult.Remove
end

function PremCine:onCineractiveBegin( )
	self:setupCinematic()
end

function PremCine:onExit( )
	Entities.remove( self.wormhole )
end

--########################################################################

Borg = { }
initMetatable( Borg )
inherit( Borg, State )

function Borg.new( )
	local newBorg = State.new( )
	
	setmetatable( newBorg, Borg.mt )
	
	newBorg.stateMachine = nil
	
	return newBorg
end

function Borg:onEnter( machine )
	self.stateMachine = machine
	
	self.shipsKilled = false
		
	Mission.loadObjectives( "Premonitions2.txt" )
	Mission.showObjectives( true )	
end

function Borg:onUpdate( )
	--Check for starbase.
	if( self:checkShips() ) then
		--Complete! Next state.
		--Enter next state
		self.stateMachine:setState( Chatting.new() )
		Media.playSound( "premhail.wav" )
	end
end

function Borg:checkShips( )
	if self.shipsKilled then return true end
	
	local ents = Team.new(2):getEntities()
	if #ents == 0 then 
		Mission.setObjective( 0, true )
		return true 
	end
	
	return false
end

--########################################################################

Chatting = { }
initMetatable( Chatting )
inherit( Chatting, State )

function Chatting.new( )
	local newIntro = State.new( )
	
	setmetatable( newIntro, Chatting.mt )
	
	newIntro.stateMachine = nil
	
	return newIntro
end

function Chatting:onEnter( machine )
	self.stateMachine = machine

	Cineractive.start( )
	
	--Music playlist
	Timers.add( "dialog", 5.0, self, Chatting.playIntroSound, "premdem2.wav" )
	Timers.add( "FINE", 55.0, self, Chatting.playIntroSound, "prempic3.wav" )
	Timers.add( "ending", 70.0, self, Chatting.endCine, nil )
	
end


function Chatting:setupCinematic()
	
	function picardFocus(id, arg)
		local ent = Entities.get( GetEntity.Name, "USS Enterprise-E" )
		Cineractive.lookFromPosition(  ent:getPosition() + Vector.new( 100, 15, 100 ) )
		Cineractive.lookAtGameObject( ent )
		return CallbackResult.Remove
	end
	
	picardFocus(nil, nil)
	
	function picardLeave(id, arg)
		local ent = Entities.get( GetEntity.Name, "USS Enterprise-E" )
		Cineractive.lookFromPosition(  ent:getPosition() + Vector.new( 100, 15, 100 ) )
		Cineractive.lookAtGameObject( ent )
		ent:giveOrderPath( Order.Go, Paths.find( "endpath" ) )
		return CallbackResult.Remove
	end
	
	function demmingFocus(id, arg)
		local prem = Entities.get( GetEntity.Name, "USS Premonition" )
		Cineractive.lookFromPosition(  prem:getPosition() + Vector.new( 100, 15, 100 ) )
		Cineractive.lookAtGameObject( prem )
		return CallbackResult.Remove
	end
			
	Timers.add( "dem1", 4.0, self, demmingFocus, nil )
	Timers.add( "pic1", 8.2, self, picardFocus, nil )
	Timers.add( "dem2", 14.0, self, demmingFocus, nil )
	Timers.add( "pic2", 23.5,  self, picardFocus, nil )
	Timers.add( "dem3", 30.0,  self, demmingFocus, nil )
	Timers.add( "pic3", 55.0,  self, picardLeave, nil )
end

function Chatting:playIntroSound( id, name )
	Media.playSound(name)
	return CallbackResult.Remove
end

function Chatting:endCine( id, arg )
	Cineractive.finish( )
	--End the mission here.
	Mission.finish( true, 0 )
	
	return CallbackResult.Remove
end

function Chatting:onCineractiveBegin( )
	self:setupCinematic()
end

--########################################################################

StateMachine = { }
initMetatable( StateMachine )

function StateMachine.new( initialState )
	local newMachine = { }
	setmetatable( newMachine, StateMachine.mt )
	
	--Some setup here?
	newMachine:setState( initialState )
	
	return newMachine
end

function StateMachine:update( isCine )
	if self.currentState ~= nil then
		if not isCine then
			self.currentState:onUpdate()
		else
			self.currentState:onCineractiveUpdate()
		end
	end
end

function StateMachine:cineractiveBegin( )
	if self.currentState ~= nil then
		self.currentState:onCineractiveBegin()
	end
end

function StateMachine:cineractiveEnd( )
	if self.currentState ~= nil then
		self.currentState:onCineractiveEnd()
	end
end

function StateMachine:setState( newState )
	
	if self.currentState ~= nil then
		self.currentState:onExit( )
	end
	
	self.currentState = newState
	
	if self.currentState ~= nil then
		self.currentState:onEnter( self )
	end
	
end


--This part creates the table we will use for the mission
--an initialises the metatable, allowing it to work properly
--with MMMApp
Premonitions = { }
initMetatable( Premonitions )
inherit( Premonitions, MMMApp )

--Spawn : fed_premonition.odf
--Spawn : bor_interceptor.odf
--Starbase : fed_outposty.odf
--Mission.loadObjectives( "premonitions.txt" )
--Mission.showObjectives( true )

function Premonitions.new( )
	local newMission = { }
	setmetatable( newMission, Premonitions.mt )
	
	--Right-o, lets get going!
	newMission.stateMachine = StateMachine.new( Intro.new() )
		
	return newMission
end

--Called once when the mission is first started. Ideal place to set up the variables and structures
--needed for the mission.
function Premonitions:init( )
	
end

--Called when the mission is loaded from a save game. You should load any data that was saved in this
--function and prepare for the mission to carry on.
function Premonitions:resume( )

end

--This is called some time after you tell MMM to start a cineractive - you can set up the cineractive that
--is going to be played and prepare the game world for cineractive mode.
function Premonitions:cineractiveBegin( )
	self.stateMachine:cineractiveBegin()
end

--This is called every update while a cineractive is running. You should check for conditions you require for
--the end of the cineractive and end it if needed. You can also change the running cineractive, to focus on another
--ship for example.
function Premonitions:cineractiveUpdate( )
	self.stateMachine:update( true )
end

--The is called some time after you tell MMM to end the cineractive. This is where you prepare the game world for
--game mode again.
function Premonitions:cineractiveFinish( )
	self.stateMachine:cineractiveEnd()
end

--This is called every time MMM updates. This frequency can change based on the value specified to Armada.setUpdateTime.
function Premonitions:update( )
	self.stateMachine:update( false )
end

--This line registers the App with MMM. This makes it MMM call the app's functions.
MMMApp.register( Premonitions.new( ) )