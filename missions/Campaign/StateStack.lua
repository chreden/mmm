--[[
	The state stack will allow for the different campaign states
	to be managed easily.
--]]

include( "BaseState.lua" )

StateStack = {}
initMetatable( StateStack )

function StateStack.new( )
	local stack = { }
	setmetatable( stack, StateStack.mt )
	stack.stack = { }
	return stack
end

function StateStack:pop( )
	if #self.stack == 0 then return end
	self.stack[#self.stack]:onExit()
	table.remove( #self.stack )
	if #self.stack == 0 then return end
	self.stack[#self.stack]:onResume()
end

function StateStack:push( state )
	if #self.stack ~= 0 then
		self.stack[#self.stack]:onPause()
	end
	table.insert( self.stack, state )
	state:onEnter()
end

function StateStack:update( )
	if #self.stack == 0 then return end
	self.stack[#self.stack]:onUpdate()
end
