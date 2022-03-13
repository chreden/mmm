class 'StateMachine'

function StateMachine:__init( initialState )
	self:setState( initialState )
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

function StateMachine:cineractiveEnd( forced )
	if self.currentState ~= nil then
		self.currentState:onCineractiveEnd( forced )
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