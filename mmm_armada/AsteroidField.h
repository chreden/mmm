#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
    namespace types { struct AsteroidField; }

    class AsteroidField : public TerrainObject
    {
    public:
        static AsteroidFieldPtr create(types::Entity* entity);
        float getAsteroidBeltSpeedCoefficient() const;
        float getAsteroidBeltTime() const;
        float getBoundingRadius() const;
        float getSpeed() const;
        void setAsteroidBeltSpeedCoefficient(float value);
        void setAsteroidBeltTime(float value);
        void setBoundingRadius(float value);
        void setSpeed(float value);
    protected:
        explicit AsteroidField( types::AsteroidField* asteroid );
        virtual void allocateReplacement( luabind::detail::object_rep* object );
    private:
        types::AsteroidField* getAsteroidField() const;
    };

    void asteroidfield_register( lua_State* state );
}
