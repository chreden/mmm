#include "BlackHole_Internal.h"
#include "Type_BlackHoleClass.h"
#include "BlackHoleClass_Internal.h"
#include "Type_BlackHole.h"

namespace mmm
{
    BlackHolePtr BlackHole::create( types::Entity* entity )
    {
        return BlackHolePtr( new BlackHole( static_cast<types::BlackHole*>( entity ) ) );
    }

    BlackHole::BlackHole( types::BlackHole* type )
        : AreaEffectObject( type )
    {
    }

    std::shared_ptr<GameObjectClass> BlackHole::getClass() const
    {
        return std::shared_ptr<GameObjectClass>( new BlackHoleClass( static_cast<types::BlackHoleClass*>( getGameObject()->m_class ) ) );
    }
}
