#pragma once

namespace mmm
{
    class Entity;
    class EntityFinderFilter
    {
    public:
        virtual ~EntityFinderFilter( );
        virtual bool call(const std::shared_ptr<Entity>& entity) = 0;
    };
}
