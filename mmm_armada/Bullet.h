#pragma once
    
#include "Ordnance.h"

namespace mmm
{
    namespace types { struct Bullet; }

    class Bullet : public Ordnance
    {
    public:
        static BulletPtr create(types::Entity* entity);
        virtual	~Bullet(){};
        Vector3 getStartPosition() const;
        Vector3 getCurrentPosition() const;
        void setStartPosition(const Vector3& position);
        void setCurrentPosition(const Vector3& position);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Bullet(types::Bullet* bullet);
    private:
        types::Bullet* getBullet() const;
    };
}