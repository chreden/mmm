#pragma once

namespace mmm
{
	namespace types
	{
		struct Objectives
		{
			char				   _padding_[36];
			void*				   m_pObjectivesCursor; //Sprite
			types::ObjectivesText* m_pSummaryTitle;
			types::ObjectivesText* m_pObjectivesTitle;
			types::ObjectivesText* m_pObjectivesText;
			types::ObjectivesText* m_pObjectivesHeader;

			VectorAdapter<types::ObjectivesText*> m_objectives;
			VectorAdapter<types::ObjectivesText*> m_objectiveTickBox;
			VectorAdapter<bool> m_objectiveFulfilled;
		};
	}
}
