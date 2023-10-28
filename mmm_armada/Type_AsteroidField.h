#pragma once

#include "Type_TerrainObject.h"

namespace mmm
{
	namespace types
	{
		//Move this at some point.
		struct BBOX
		{
			Vector3 min;
			Vector3 max;
		};

		struct AsteroidInfo
		{
			Vector3		vel;
			Vector3		accel;
			float		mass;
			float		radius;
			Vector3		omega;
			Matrix34	transform;
		};

		struct AsteroidField
			: public TerrainObject
		{
			BBOX			m_bounding_box;
			float			m_bounding_radius;
			float			m_rotation_speed;
			double			m_speed;
			double			m_repulsion_distance;
			double			m_maximum_distance_sqr;
			const double	m_forcefield_strength;
			int				m_number_of_asteroids;
			float			m_total_energy;
			AsteroidInfo*	m_asteroids;
			char*			m_asteroid_belt_label;
			Vector3			m_closest_offset;
			float			m_closest_t_on_path;
			float			m_asteroid_belt_time;
			float			m_asteroid_belt_speed_coefficient;
			AiPath*			m_asteroid_belt;
		};
	}
}
