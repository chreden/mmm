#pragma once

namespace mmm
{
    class Team;
    class Map
    {
    public:
        enum eVisibility
        {
            Shrouded = 0,
            Fogged,
            Visible
        };
        
        Vector3 getMin();
        Vector3 getMax();
        eVisibility getVisibility(const Vector3& position, const std::shared_ptr<Team>& player) const;
        void setMin(const Vector3& vec);
        void setMax(const Vector3& vec);
        static void resize(float x, float y);
        void loadStarfield(const std::string& sod, const std::string& odf);
    private:
        static void updateMapSize();
    };

    void map_register(lua_State* L);
}
