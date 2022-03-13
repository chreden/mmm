class 'NameFinder'

function ODFFinder:__init( odf )
	self.targetOdf = odf
end

function ODFFinder:evaluate( e )
	return e.odf == self.targetOdf
end