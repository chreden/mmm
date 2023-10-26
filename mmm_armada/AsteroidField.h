#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
    namespace types { struct AsteroidField; }

    class AsteroidField : public TerrainObject
    {
    public:
        static AsteroidFieldPtr create(types::Entity* entity);
        float getBoundingRadius() const;
        float getAsteroidBeltTime() const;
        void setBoundingRadius(float value);
        void setAsteroidBeltTime(float value);
    protected:
        explicit AsteroidField( types::AsteroidField* asteroid );
        virtual void allocateReplacement( luabind::detail::object_rep* object );
    private:
        types::AsteroidField* getAsteroidField() const;
    };

    void asteroidfield_register( lua_State* state );
}
