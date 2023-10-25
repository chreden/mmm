#include "Camera_Internal.h"
#include "Path_Internal.h"

namespace mmm
{
    namespace
    {
        Camera camera;
    }

    void camera_register(lua_State* state)
    {
        using namespace luabind;

        module(state)
        [
            class_<Camera>("_Camera")
                .def("center", (void(Camera::*)(EntityPtr)) &Camera::center)
                .def("center", (void(Camera::*)(const Path&, int)) &Camera::center)
                .def("center", (void(Camera::*)(const Vector3&)) &Camera::center)
                .def("zoom", &Camera::zoom)
                .def("project", &Camera::project)
                .property("target", &Camera::getTarget, (void(Camera::*)(const Vector3&)) & Camera::center)
        ];

        globals(state)["Camera"] = &camera;
    }
}
