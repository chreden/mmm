#include "Bullet.h"
#include "Type_Bullet.h"
#include "LuaBinding.h"

namespace mmm
{
    BulletPtr Bullet::create(types::Entity* entity)
    {
        return BulletPtr(new Bullet(static_cast<types::Bullet*>(entity)));
    }

    Bullet::Bullet(types::Bullet* bullet)
        : Ordnance(bullet)
    {

    }

    types::Bullet* Bullet::getBullet() const
    {
        return static_cast<types::Bullet*>(getEntity());
    }

    Vector3 Bullet::getStartPosition() const
    {
        return getBullet()->startPos;
    }

    Vector3 Bullet::getCurrentPosition() const
    {
        return getBullet()->currentPos;
    }

    void Bullet::setStartPosition(const Vector3& position)
    {
        getBullet()->startPos = position;
    }

    void Bullet::setCurrentPosition(const Vector3& position)
    {
        getBullet()->currentPos = position;
    }

    int Bullet::index(lua_State* L, const std::string& key) const
    {
        if (key == "currentPosition")
        {
            return vector_new(L, getCurrentPosition());
        }
        else if (key == "startPosition")
        {
            return vector_new(L, getStartPosition());
        }
        return Ordnance::index(L, key);
    }

    int Bullet::newindex(lua_State* L, const std::string& key)
    {
        if (key == "currentPosition")
        {
            setCurrentPosition(get_userdata<Vector3>(L, 3));
            return 0;
        }
        return Ordnance::newindex(L, key);
    }
}
