BaseState = {}
initMetatable( BaseState )

function BaseState.new( )
	local state = { }
	setmetatable( state, BaseState.mt )
	return state
end

function BaseState:onEnter( stack )
	self.stack = stack
end

function BaseState:onPause( )
	
end

function BaseState:onResume( )
	
end

function BaseState:onExit( )
	
end

function BaseState:onUpdate( )
	
end

