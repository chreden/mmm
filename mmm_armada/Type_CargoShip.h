#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct CargoShip
			: public Craft
		{
			struct cGoods
			{
				float			m_amtGoods;				//Done
				eResource		m_resource;				//Done
				CargoDesc*		m_pCargoDesc;			//Done
				int				m_stationHandle;		//Ignore
				Vector3			m_stationLocation;		//Ignore
				bool			m_full;					//Done
			};

			int			  m_startStation;				//Done
			int			  m_goalStation;				//Done
			bool		  m_isTrading;					//Done
			float		  m_maxCargo;					//Done
			eResource	  m_nextCargoType;				//Done
			cGoods*		  m_pGoods;						//Done
		};
	}
}
