 --[[
		Graph class for the MMM Multi AAS gamemode. This represents
		the tree structure.
 --]]
 
 Node = { }
 Node.mt = { }
 Node.mt.__index = Node
 
 --Utility function to see if a table contains a value
 function tableContains( tab, val )
	for _, v in pairs(tab) do
		if v == val then
			return true
		end
	end
	return false
 end
  
 --Creates a new graph node.
 function Node.new( 
						team, --The team number that is in control.
						position
				   )
	local newnode = { }
	
	--Set up properties.
	newnode.links = { }
	
	newnode.team = team
	newnode.position = position
	
	return setmetatable( newnode, Node.mt )
 end
 
 function Node:link( other, bidirectional )
	--Add to our links, if not already there.
	if not tableContains( self.links, other ) then
		table.insert( self.links, other )
	end
	
	if bidirectional then
		--If bd, then we add to the other
		other:link( self, false )
	end
 end
 
  