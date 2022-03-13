include( "missions/Adventure.lua" )

Objectives = {  }

player 		= nil
scienceShip	= nil
parts		= nil
wormhole	= nil
newwormhole = nil

canpickupParts = false

Inventory = { }

adventureGame = nil

--The init function is called when the map is started, but not from a 
--savegame.
function init( )
	loadEntities( )
	
	player:setAlertStatus( Alert.Red )
	
	adventureGame = AdventureGame.new( )
	
	Mission.loadObjectives( "mmmadv1.txt" )
	
	registerCommands( )
	
	adventureGame:setCurrentCommandSet( "explore" )
	
	Mission.showObjectives( true )
	
end

function update( )
	if TextInput.isActive( ) then
		TextInput.setPrompt( "Enter Command : " )
	end
	
	Debug.test( player )
end

function createExploreCommandSet( )
	--Commands for moving the ship around
	local movementAmount = 300
	adventureGame:registerCommand( "explore", { "north", "n", "up" }, onMove, Vector.new( 0, 0, movementAmount ) )
	adventureGame:registerCommand( "explore", { "northeast", "ne", "upright" }, onMove, Vector.new( movementAmount, 0, movementAmount ) )
	adventureGame:registerCommand( "explore", { "east", "e", "right" }, onMove, Vector.new( movementAmount, 0, 0 ) )
	adventureGame:registerCommand( "explore", { "southeast", "se", "downright" }, onMove, Vector.new( movementAmount, 0, -movementAmount ) )
	adventureGame:registerCommand( "explore", { "south", "s", "down" }, onMove, Vector.new( 0, 0, -movementAmount ) )
	adventureGame:registerCommand( "explore", { "southwest", "sw", "downleft" }, onMove, Vector.new( -movementAmount, 0, -movementAmount ) )	
	adventureGame:registerCommand( "explore", { "west", "w", "left" }, onMove, Vector.new( -movementAmount, 0, 0 ) )
	adventureGame:registerCommand( "explore", { "northwest", "nw", "upleft" }, onMove, Vector.new( -movementAmount, 0, movementAmount ) )
	adventureGame:registerCommand( "explore", { "stop", "halt", "cancel" }, onStop, nil )
	
	adventureGame:registerCommand( "explore", "hail", onHail, nil )
	adventureGame:registerCommand( "explore", { "pickup", "take" }, onPickup, nil )
	
	adventureGame:registerCommand( "explore", { "use", "enter" }, onUse, nil )
end

function createHailCommandSets( )
	
	
	
end

function registerCommands( )
	createExploreCommandSet( )
	createHailCommandSets( )
end

function stringSplit( str )
		--Err, lets see what we can do here.
	local split = { }
	
	for w in string.gmatch( str, "%w+" ) do
		table.insert( split, string.lower( w ) )
	end
	
	return split
end

function onMove( str, arg )
	Armada.setTeamText( "Moving" )
	player:giveOrderPos( Order.Go, player:getPosition( ) + arg )
end

function onUse( str, arg )
	local split = stringSplit( str )
	
	if #split > 0 then
		if split[1] == "wormhole" then
			--Find the nearest wormhole to the ship, and if it is in range, we should use it. Only
			--use when wormhole is linked.
			if newwormhole ~= nil then
				if (newwormhole:getPosition( ) - player:getPosition( )):length( ) < 
				   (wormhole:getPosition( ) - player:getPosition( )):length( ) then
					player:giveOrderPos( Order.Go, newwormhole:getPosition( ) )
				else				
					player:giveOrderPos( Order.Go, wormhole:getPosition( ) )
				end
			end
		end
	end
	
end

function onStop( str, arg )
	Armada.setTeamText( "Stopping" )
	player:giveOrderPos( Order.Stop, player:getPosition( ) )
end

function onPickup( str, arg )
	local split = stringSplit( str )
	
	if #split > 0 then
		if split[1] == "parts" then
			if parts then
				if canpickupParts then
					Armada.setTeamText( "Picked up parts" )
					Objectives[ "findparts" ] = true
					Mission.setObjective( 1, true )
					Entities.remove( parts )
					parts = nil				
					Mission.showObjectives( true )
				else
					Armada.setTeamText( "Not close enough to pickup parts" )
				end
			else
				Armada.setTeamText( "We already have the parts" )
			end
		end
	else
		Armada.setTeamText( "Pickup what?" )
	end
end

function onHail( str, arg )
	--Check the distance between the player and the target ship.
	local split = stringSplit( str )
	
	if #split > 0 then
		if split[ 1 ] == "nebula" or split[ 1 ] == "pavlov" then
			if (player:getPosition( ) - scienceShip:getPosition( )):length( ) < 300 then
				if Objectives[ "findparts" ] == nil then
					Objectives[ "findparts" ] = false
					Objectives[ "deliverparts" ] = false
					UI.addMessage( 10, 75, 0, "USS Pavlov : We were attempting to reopen the nearby wormhole when we were attacked by Romulans.\
				\nWe can complete our mission if you can retrieve our engine components that we lost in the fight.", 0xff00ff00, false, 5, true )
					--Load the new objectives from the file.
					Mission.loadObjectives( "mmmadv2.txt" )
					Mission.setObjective( 0, true )
					--Create our checking timer.
					Timers.add( "prox", 1, nil, checkProximityToEngineParts, nil )
				else
					if not Objectives[ "deliverparts" ] then
						if Objectives[ "findparts" ] then
							UI.addMessage( 10, 75, 0, "USS Pavlov : At last, you have the vision to find our parts! Now we can reopen the wormhole\
							to allow you to continue.", 0xff00ff00, false, 5, true )
							Objectives[ "deliverparts" ] = true
							Timers.add( "fix", 1, nil, nebulaFixedMove, nil )
							Mission.setObjective( 2, true )
							Mission.showObjectives( true )
						else
							UI.addMessage( 10, 75, 0, "USS Pavlov : You should be able to follow the debris trail to find the parts", 0xff00ff00, false, 5, true )
						end
					else
						UI.addMessage( 10, 75, 0, "USS Pavlov : Go, with many blessings!", 0xff00ff00, false, 3, true )
					end
				end
			else
				Armada.setTeamText( "Not within hailing range" )
			end
		end
	end
end

function nebulaFixedMove( id, arg )
	--Creates a new wormhole and links them together with the old one
	newwormhole = Entities.add( "mwrmhole", 0, Vector.new( 1700, 0, 2300 ) )
	newwormhole:setWormholeLink( wormhole )
	wormhole:setWormholeLink( newwormhole )
	
	scienceShip:setSystemStatus( System.Engines, true )
	scienceShip:giveOrderPos( Order.Go, wormhole:getPosition( ) )
end

function checkProximityToEngineParts( id, arg )
	if parts == nil then return CallbackResult.Remove end
	--Check the distance between the ship and the parts. If close enough, 
	--we enable pickup of parts.
	canpickupParts = (player:getPosition( ) - parts:getPosition( )):length( ) < 250
	return CallbackResult.Repeat
end

function loadEntities( )
	player 			= Entities.get( GetEntity.Handle, "playership" )
	scienceShip 	= Entities.get( GetEntity.Handle, "sci_ship" )
	parts			= Entities.get( GetEntity.Handle, "parts" )
	wormhole		= Entities.get( GetEntity.Handle, "wormhole_1" )
	
	scienceShip:setSystemStatus( System.Engines, false )
end