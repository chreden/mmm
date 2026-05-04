#pragma once

namespace mmm
{
    class Entity;
    class Team;
    class Entities
    {
    public:
        typedef bool (*FindComparator)(const std::shared_ptr<Entity>&, void*);
        static std::shared_ptr<Entity> add(const std::string& odf, int team, const Vector3& position);
        static std::shared_ptr<Entity> add(const std::string& odf, const std::shared_ptr<Team>& team, const Vector3& position);
        static void find(std::vector<std::shared_ptr<Entity>>& ents, FindComparator comparator, void* argument);
        static bool remove(const std::shared_ptr<Entity>& entity);
        static void getActiveEntities(std::vector<std::shared_ptr<Entity>>& results);
    };
}
