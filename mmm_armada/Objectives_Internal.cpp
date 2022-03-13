#include "Objectives_Internal.h"
#include "Type_ObjectivesText.h"
#include "Type_Objectives.h"
#include "Functions_ItemCache.h"
#include "ScriptErrors.h"
#include "Objective.h"

namespace mmm
{
	namespace
	{
		types::Objectives*
		getObjectives( )
		{
			return reinterpret_cast<types::Objectives*>( 0x007648a8 );
		}

		struct ObjectiveEntry
		{
			ObjectiveEntry( bool state, const std::string& objectiveText )
				: status( state ), text( objectiveText ) { }

			bool		status;
			std::string text;
		};


		std::vector<ObjectiveEntry> objectives_vec;

		//Builds the string that needs to be written to the objectives
		//file. This contains the title, objectives description and the
		//actual objectives.
		const std::string
		buildObjectiveFileString( const Objectives& objectives )
		{
			std::stringstream stringbuffer;

			stringbuffer << objectives.getObjectivesTitle() << '\n';

			stringbuffer << objectives.getObjectivesText() << '\n';

			const std::size_t Count = objectives_vec.size();
			for( std::size_t i = 0; i < Count; ++i )
			{
				stringbuffer << "*" << objectives_vec[i].text << '\n'; 
			}

			return stringbuffer.str();
		}

		void
		saveObjectivesFile( const Objectives& objectives )
		{
			DeleteFileA( "objectives/mmm_temp.txt" );

			std::ofstream outfile;
			outfile.open( "objectives/mmm_temp.txt", std::ios::binary | std::ios::out );

			outfile << buildObjectiveFileString(objectives);

			outfile.close();

			//This function inits the whole cache again, or at least that is what it sounds
			//like. This actually seems to be pretty fast, contrary to what you would think.
			functions::itemInitCache();

			getScriptInterface()->ObjectivesDisplay_Set_Text_From_File( "mmm_temp.txt", 1 );

			DeleteFileA( "objectives/mmm_temp.txt" );
		}

		void
		updateObjectives( Objectives& objectives )
		{
			//Set the values for the objectives since we have just reloaded everything.
			const std::size_t Count = objectives_vec.size();
			for( std::size_t o = 0; o < Count; ++o )
			{
				objectives.setObjectiveState( o, objectives_vec[o].status );
			}
		}

		//Right, we may have had something happen when we have reloaded the 
		//objectives from the file. So we have to check for changes and store
		//them so we have some idea what is going on.
		void
		synchroniseObjectives( const VectorAdapter<types::ObjectivesText*>& texts, 
								const VectorAdapter<bool>& states )
		{
			objectives_vec.clear();
			const std::size_t Count = texts.size();
			for( std::size_t o = 0; o < Count; ++o )
			{
				objectives_vec.push_back( ObjectiveEntry( states[o], texts[o]->get() ) );
			}
		}
	}

	Objectives::Objectives( )
	{

	}

	int
	Objectives::getCount() const
	{
		return getObjectives()->m_objectives.size();
	}

	const std::string 
	Objectives::getSummaryTitle() const
	{
		return getObjectives()->m_pSummaryTitle->get();
	}

	const std::string 
	Objectives::getObjectivesTitle() const
	{
		return getObjectives()->m_pObjectivesTitle->get();
	}

	const std::string 
	Objectives::getObjectivesText() const
	{
		return getObjectives()->m_pObjectivesText->get();
	}

	const std::string 
	Objectives::getObjectivesHeader() const
	{
		return getObjectives()->m_pObjectivesHeader->get();
	}

	void
	Objectives::setSummaryTitle( const std::string& text )
	{
		getObjectives()->m_pSummaryTitle->set( text );
	}
		
	void
	Objectives::setObjectivesTitle( const std::string& text )
	{
		getObjectives()->m_pObjectivesTitle->set( text );
	}

	void
	Objectives::setObjectivesText( const std::string& text )
	{
		getObjectives()->m_pObjectivesText->set( text );
	}

	void
	Objectives::setObjectivesHeader( const std::string& text )
	{
		getObjectives()->m_pObjectivesHeader->set( text );
	}

	void 
	Objectives::addObjective( const std::string& text )
	{
		objectives_vec.push_back( ObjectiveEntry( false, text ) );

		saveObjectivesFile(*this);

		updateObjectives(*this);

		synchroniseObjectives( getObjectives()->m_objectives,
								getObjectives()->m_objectiveFulfilled );
	}

	void 
	Objectives::removeObjective( int index )
	{
		if( index < 1 || index > objectives_vec.size() )
		{
			scriptError("Objective index out of range in Objectives:removeObjective" );
			return;
		}

		objectives_vec.erase( objectives_vec.begin() + (index-1) );
		saveObjectivesFile(*this);

		updateObjectives(*this);
	}

	bool
	Objectives::getObjectiveState( int index ) const
	{
		if( index < 1 || index > objectives_vec.size() )
		{
			scriptError("Objective index out of range in Objectives:getObjectiveState" );
			return false;
		}
		return objectives_vec[index-1].status;
	}

	const std::string
	Objectives::getObjective( int index ) const
	{
		if( index < 1 || index > objectives_vec.size() )
		{
			scriptError("Objective index out of range in Objectives:getObjective" );
			return false;
		}
		return objectives_vec[index-1].text;
	}

	void
	Objectives::setObjectiveState( int index, bool state )
	{
		if( index < 1 || index > objectives_vec.size() )
		{
			scriptError("Objective index out of range in Objectives:setObjectiveState" );
			return;
		}
		getScriptInterface()->ObjectivesDisplaySetObjectiveComplete( index-1, state );
		objectives_vec[index-1].status = state;
	}

	void
	Objectives::setObjective( int index, const std::string& text )
	{
		if( index < 1 || index > objectives_vec.size() )
		{
			scriptError("Objective index out of range in Objectives:setObjective" );
			return;
		}
		getObjectives()->m_objectives[index-1]->set( text );
		objectives_vec[index-1].text = text;
	}

	void 
	Objectives::load( const std::string& filename )
	{
		objectives_vec.clear();

		getScriptInterface()->ObjectivesDisplay_Set_Text_From_File( filename.c_str(), 1 );

		synchroniseObjectives( getObjectives()->m_objectives,
								getObjectives()->m_objectiveFulfilled );
	}
		
	bool
	Objectives::getShow() const
	{
		struct ObjectivesDisplay
		{
			char _padding_[0x16];
			bool isHidden;
			//More padding.
		};

		ObjectivesDisplay* g_objectivesDisplay = 
			reinterpret_cast<ObjectivesDisplay*>( 0x007648a8 );

		return !g_objectivesDisplay->isHidden;
		//0003:000788a8       ?g_objectivesDisplay@@3VObjectivesDisplay@@A 007648a8     ObjectivesDisplay.obj
	}

	void 
	Objectives::setShow( bool value )
	{
		getScriptInterface()->ObjectivesDisplay_Set_Visibility( value );
	}

	luabind::object 
	Objectives::getObjectiveValues() const
	{
		luabind::object results = luabind::newtable(common::Storage::instance().mainLuaVM);
		for( int i = 1; i <= getCount(); ++i )
		{
			results[i] = Objective(i);
		}
		return results;
	}
}
