//The rule helper file makes it somewhat easier to make rule callbacks so that the saving/loading
//and cineractive functionality can be implemented a bit easier.

#ifndef _MMM_MMMLOADER_RULEHELPER_H
#define _MMM_MMMLOADER_RULEHELPER_H

#include "../mmm_armada/Types.h"

namespace mmm
{
	typedef void (*RuleCallbackFunction)();

	//The Rule class can be used when there is no other means of having an update being called - 
	//Armada does not call update for example when Cineractives are being played, so the Rule is 
	//required there.
	class Rule
	{
	public:
		explicit Rule( const std::string& name );
				 ~Rule( );
		bool	 isSatisfied() const;
		void	 satisfy( ); 
		void	 activate( RuleCallbackFunction callbackFunction );
	private:
		Rule( const Rule& ){};
		Rule& operator=( const Rule& ) { return *this; };

		std::string			 name_;
		bool				 satisfied_;
		rule*				 internal_;
		hot_int*	 int_;
	};
}

#endif
