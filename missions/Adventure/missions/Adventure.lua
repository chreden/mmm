--[[
	Lua file for the adventure game framework. This contains code to allow
	the user to interact with the game via text.
--]]

AdventureGame = { }
AdventureGame.mt = { }
AdventureGame.mt.__index = AdventureGame

function AdventureGame.new( )
	local newGame = { }
	setmetatable( newGame, AdventureGame.mt )
	--Initialises the new adventure with the things that it
	--needs to do its job.
	newGame.commandSets = { }
	newGame.currentCommandSet = nil
	--Sets up the callback so we get told about text.
	TextInput.hook( newGame, AdventureGame.onTextEntered )	
	return newGame
end

--[[
	This is used to register a command with the adventure game. You can 
	specify either a table or a string for commmands - if a table is given, 
	every entry will be linked to the callback.
	
	The command set indicates what set you want the command registered in.
--]]
function AdventureGame:registerCommand( set, commands, func, arg )
	--First we find the command set. This may or may not exist already, so 
	--we might have to create it.
	local commandSet = self.commandSets[ set ]
	if commandSet == nil then
		self.commandSets[ set ] = { }
		commandSet = self.commandSets[ set ]
	end
	
	if type(commands) == "string"  then
		if commandSet[ commands ] == nil then
			commandSet[ commands ] = { }
		end
		table.insert( commandSet[ commands ], { func, arg } )
	elseif type(commandSet) == "table" then
		for _, v in pairs(commands) do
			if commandSet[ v ] == nil then
				commandSet[ v ] = { }
			end
			table.insert( commandSet[ v ], { func, arg } )
		end
	end
end

--[[ 
	This function will be where we handle the user input. The user will enter text
	which we will then parse. We then tell object to do certain commands.
--]]
function AdventureGame:onTextEntered( text )
	--Find the current command set. If it isn't there, we just abort.
	local commandSet = self.commandSets[ self.currentCommandSet ]
	if commandSet == nil then return end
	
	--Get the command. This is the text up to the first whitespace character.
	local split = { }
	
	for w in string.gmatch( text, "%w+" ) do
		table.insert( split, string.lower( w ) )
	end
	
	if #split > 0 then
		if commandSet[split[1]] then
			for _, v in pairs(commandSet[split[1]]) do
				v[1]( table.concat( split, ' ', 2 ), v[2] )
			end
		else
			Armada.setTeamText( "I don't know how to "..split[1] )
		end
	end
end

--[[
	This is used to choose what command set is being used at the minute. This
	is useful for disabling movement during a conversation or something.
--]]
function AdventureGame:setCurrentCommandSet( set )
	self.currentCommandSet = set
end



