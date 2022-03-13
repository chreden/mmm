--Quick state machine implementation - to make things easier to manage without 
--world of ifelseif.

include( "StateMachine.lua" )
include( "State.lua" )
include( "Intro.lua" )

--This part creates the table we will use for the mission
--an initialises the metatable, allowing it to work properly
--with MMM
class 'Premonitions'

function Premonitions:__init( )
	self.stateMachine = StateMachine( Intro( ) )
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
function Premonitions:cineractiveFinish( forced )
	self.stateMachine:cineractiveEnd( forced )
end

--This is called every time MMM updates. This frequency can change based on the value specified to Armada.setUpdateTime.
function Premonitions:update( )
	self.stateMachine:update( false )
end

--This line registers the App with MMM. This makes it MMM call the app's functions.
MMM.register( Premonitions( ) )