class 'NameFinder'

function NameFinder:__init( name )
	self.targetName = name
end

function NameFinder:evaluate( e )
	return e.name == self.targetName		   
end