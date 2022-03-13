#pragma once

#include "Producer.h"

namespace mmm
{
	namespace types
	{
		struct Evolver;
	}

	class Evolver
		: public Producer
	{
	public:
		static EvolverPtr create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;

		float	getEvolutionProgress() const;
		void	setEvolutionProgress( float value );

	protected:
		explicit	 Evolver( types::Evolver* evolver );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::Evolver* getEvolver() const;
	};

	void evolver_register( lua_State* state );
}
