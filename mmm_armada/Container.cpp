#include "Container.h"

namespace mmm
{
	Container::Callback::~Callback()
	{

	}

	Container::Container( std::shared_ptr<Callback> callback )
		: callback_( callback )
	{

	}

	void
	container_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<Container>( "Resources" )
				//Stock resources
				.property( "crew", &Container::getResource<RESOURCE_CREW>, &Container::setResource<RESOURCE_CREW> )
				.property( "officers", &Container::getResource<RESOURCE_OFFICERS>, &Container::setResource<RESOURCE_OFFICERS> )
				.property( "dilithium", &Container::getResource<RESOURCE_DILITHIUM>, &Container::setResource<RESOURCE_DILITHIUM> )
				.property( "latinum", &Container::getResource<RESOURCE_LATINUM>, &Container::setResource<RESOURCE_LATINUM> )
				.property( "metal", &Container::getResource<RESOURCE_METAL>, &Container::setResource<RESOURCE_METAL> )
				.property( "biomatter", &Container::getResource<RESOURCE_BIOMATTER>, &Container::setResource<RESOURCE_BIOMATTER> )
				//Fleet Operations
				.property( "tritanium", &Container::getResource<RESOURCE_LATINUM>, &Container::setResource<RESOURCE_LATINUM> )
				.property( "supply", &Container::getResource<RESOURCE_BIOMATTER>, &Container::setResource<RESOURCE_BIOMATTER> )
				.property( "collectiveConnections", &Container::getResource<RESOURCE_METAL>, &Container::setResource<RESOURCE_METAL> )
				.scope
				[
					class_<eResource>("Type")
						.enum_("constants")
						[
							value("Crew", RESOURCE_CREW),
							value("Officers", RESOURCE_OFFICERS),
							value("Dilithium", RESOURCE_DILITHIUM),
							value("Latinum", RESOURCE_LATINUM),
							value("Metal", RESOURCE_METAL),
							value("Biomatter", RESOURCE_BIOMATTER),
							value("Tritanium", RESOURCE_LATINUM),
							value("Supply", RESOURCE_BIOMATTER),
							value("CollectiveConnections", RESOURCE_METAL)
						]
				]
		];
	}
}