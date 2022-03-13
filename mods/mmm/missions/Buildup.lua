include( "Dominion.lua" )
include( "ShipDies.lua" )

class 'Buildup' (State)

function Buildup:__init( )

end

function Buildup:onEnter( machine )
		
	--Set up hooks on the enterprise death, so you can fail the mission.
	setupShipDeathHook( EntityFinder( NameFinder("USS Enterprise-E") ):findOne(),
						"The Enterprise",
						machine )
					
	--Same with the constructor.
	setupShipDeathHook( EntityFinder( NameFinder("USS Podlech") ):findOne(),
						"The construction ship",
						machine )						
	
	--Get the music playing and load and show the objectives.
	Media:playMusic( "PremonitionsBackgroundMusic.ogg" )
	Objectives:load( "PremonitionsBuildupObjectives.txt" )
	Objectives.visible = true

	--One of the objectives is to build an outpost, so we check to see if there are
	--any starbases that belong to player 1.
	function checkStarbaseDone( monitor, arg )
		return EntityFinder( function(e) 
								return e:isType(Entity.Type.Starbase) and 
									   e.odf == "fed_outpostya.odf" and 
									   e.player.number == 1 
								end ):findOne() ~= nil
	end
	
	--Complete a specific objective. The objective number to complete is stored
	--in the argument field of the hook. Also shows the Objectives screen.
	function completeObjective( monitor, hook )
		Objectives.objectives[hook.argument].state = true
		Objectives.visible = true
	end
	
	--The monitor uses the starbase condition function. When completed it will complete one of the
	--objectives (the argument of 1 tells the completeObjective function which objective to set to
	--completed.
	Monitor( "starbaseDone", false, nil, checkStarbaseDone, nil ):hook( "onStarbaseDone", MonitorHook.Type.OnTrue, nil, completeObjective, 1 )
	
	--Another objective is to build a mining station. Much like the starbase objective
	--we just check to see that there is a mining station belonging to player 1.
	function checkMiningDone( monitor, arg )
		return EntityFinder( function(e) 
								return e:isType(Entity.Type.MiningStation) and 
									   e.odf == "fed_storage_dock.odf" and
									   e.player.number == 1
 							    end ):findOne() ~= nil
	end
	
	--The monitor uses the mining station condition function, much like the starbase one. When it
	--completes, the completeObjective function will be called setting objective number 2 to
	--completed.
	Monitor( "miningDone", false, nil, checkMiningDone, nil ):hook( "onMiningDone", MonitorHook.Type.OnTrue, nil, completeObjective, 2 )
	
	--Checks the state of both of the objectives that we care about. When they are both true the condition
	--will be true.
	function checkObjectivesDone( monitor, arg )
		return Objectives.objectives[1].state and
			   Objectives.objectives[2].state
	end
	
	--This monitor checks to see that all of the tasks are completed.
	function onObjectivesDone( monitor, hook )
		--Clear hooks from the construction ship.
		local podlech = EntityFinder( NameFinder( "USS Podlech" ) ):findOne()
		if podlech and podlech.valid and podlech:isType(Entity.Type.ConstructionRig) then
			for _, h in pairs(podlech.hooks) do podlech:unhook(h) end
		end
		--Activate the Dominion fight state.
		machine:setState( Dominion() )
	end
	
	--This monitor checks if the objectives are both complete. If they are, we move on to the 
	--next stage of the mission.
	Monitor( "buildObjectivesDone", false, nil, checkObjectivesDone, nil ):hook( "onBuildObjectivesDone", MonitorHook.Type.OnTrue, self, onObjectivesDone, nil )
	
	--This final monitor will check to see if the player has seen any of the dominion ships. It will live beyond the end
	--of this state.
	function canSeeDominion( monitor, arg )
		for _, v in pairs(arg) do
			if v.valid and v:canPlayerSee( Player(1) ) then
				return true 
			end
		end
		return false
	end
	
	--Plays a sound when we first see a dominion ship.
	Monitor( "canSeeDominion", false, nil, canSeeDominion, EntityFinder( function(e) 
																			return e:isType(Entity.Type.Craft) and 
																				   e.player.number == 2 
																		 end ):find() ):hook( "onDominionSeen", MonitorHook.Type.OnTrue, nil,
		function(monitor, hoook)
			Media:playSound("PremonitionsWeapons.ogg" )
			monitor:stop()
		end, nil )
	
	
end
