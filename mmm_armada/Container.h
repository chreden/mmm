#pragma once

namespace mmm
{
	class Container
	{
	public:
		struct Callback
		{
			virtual ~Callback() = 0;
			virtual float get(eResource resource) const = 0;
			virtual void  set(eResource resource, float amount) = 0;
		};

		template < eResource Res >
		float getResource() const;

		template < eResource Res >
		void setResource(float value);

		explicit Container( std::shared_ptr<Callback> callback );
	private:
		std::shared_ptr<Callback> callback_;
	};

	void container_register( lua_State* state );
}

#include "Container.inl"
