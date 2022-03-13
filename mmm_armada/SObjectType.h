#pragma once

namespace mmm
{
	namespace types
	{
		struct SObject
		{
			virtual ~SObject() { };
			bool	bDontSave;
		};
	}
}
