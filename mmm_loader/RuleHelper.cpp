#include "RuleHelper.h"

#include "../mmm_armada/ScriptInterface.h"
#include "../mmm_armada/Types.h"

namespace mmm
{
    namespace
    {
	    const std::size_t Address_WorldCharacter		 = 0x007349c8;
	    const std::size_t Function_GetIIIE				 = 0x00403250;
	    const std::size_t Function_CreateRule			 = 0x00405fd0;
	    const std::size_t Function_AddDependentRule		 = 0x004055e0;
	    const std::size_t Function_AddRuleToAffectedList = 0x00405a00;
	    const std::size_t Function_TrashRule			 = 0x004061d0;

	    Rule* CurrentRule;

	    //Maps the callback to the actual rule - when the rule is activated it becomes the active rule.
	    int
	    ruleSatisfiedCallback( )
	    {
		    if( nullptr == CurrentRule )
		    {
			    return 0;
		    }
		    return CurrentRule->isSatisfied() ? 0 : 1;
	    }
    }

	Rule::Rule( const std::string& name )
		: name_( name ), satisfied_( false ), int_( 0 ), internal_(0)
	{
	}

	Rule::~Rule( )
	{
		if( CurrentRule == this )
		{
			CurrentRule = nullptr;
		}

		getScriptInterface()->ScriptDestroy_hot_int( int_ );

		//We have to destroy the rule otherwise the game will crash when we start another game 
		//(if we actually used the rule, that is).
		character* world = reinterpret_cast<character*>( Address_WorldCharacter );
		IIIE& iiie = (world->*memory_function< IIIE& (character::*)( ) >( Function_GetIIIE ))( );

		(iiie.*memory_function< rule* (IIIE::*)( rule* ) >( Function_TrashRule ))
			( internal_ );
	}

	bool	 
	Rule::isSatisfied() const
	{
		return satisfied_;
	}

	void	 
	Rule::satisfy( )
	{
		satisfied_ = true;
	}

	void	 
	Rule::activate( RuleCallbackFunction callbackFunction )
	{
		ScriptInterface* scriptInterface = getScriptInterface();

		//A whole bunch of constants. Yes, I have to call 4 functions to get the silly rule
		//working. Oh well.	
		typedef int (*fun2)();

		character* world = reinterpret_cast<character*>( Address_WorldCharacter );

		IIIE& iiie = (world->*memory_function< IIIE& (character::*)( ) >( Function_GetIIIE ))( );

		internal_ = (iiie.*memory_function< rule* (IIIE::*)(fun2, RuleCallbackFunction, char*) >( Function_CreateRule ))
			( ruleSatisfiedCallback, callbackFunction, const_cast<char*>( name_.c_str() ) );

		//The "Hot Int" is something used in Armada as some sort of watch thing, I think. Not sure. Doesn't really matter
		//as for the purposes of making callbacks work it is irrelevant.
		int_ = scriptInterface->ScriptCreate_hot_int( const_cast<char*>( name_.c_str() ) );

		(int_->*memory_function< void (hot_int::*)(rule*) >( Function_AddDependentRule ))
			( internal_ );

		(iiie.*memory_function< void (IIIE::*)(rule*) >( Function_AddRuleToAffectedList ))
			( internal_ );

		CurrentRule = this;
	}
}
