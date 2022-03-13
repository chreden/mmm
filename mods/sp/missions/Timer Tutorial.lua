class 'TimerTutorial'

function TimerTutorial:__init( )
	
end

function TimerTutorial:setup( )
	
	--Find all of the Mandril class freighters that are placed
	--around the sensor station in the middle.
	local ents = EntityFinder( function(e) 
								return e:isType(EntityType.GameObject) 
									   and e.odf == "fed_mandril.odf" 
								end ):find()
	
	--Timer hook function that blows up a single ship and 
	--removes it from the list.
	function explodeShip( timer, hook )	
		--The table of ships is stored as the argument
		--in the hook - we take the first entry in the list
		local ship = hook.argument[1]
		if ship ~= nil and ship.valid then
			ship:explode()
		end
		
		--Remove the first ship from the results table 
		--so we don't explode it again
		table.remove( hook.argument, 1 )
		
		--Reduce the interval slightly each time to make it
		--more interesting
		timer.interval = timer.interval * 0.75
		
		--If we don't have any more ships to blow up
		--then we stop the timer from repeating.
		if #hook.argument == 0 then
			timer.repeats = false
		end
	end
	
	local newTimer = Timer( "explodeTimer", 5.0, Timer.State.Started )
	newTimer.repeats = true
	
	--Passing the entities we found earlier as the argument to the hook
	--function
	newTimer:hook( "explodeShip", nil, explodeShip, ents )
	
end

MMM.register( TimerTutorial( ) )
