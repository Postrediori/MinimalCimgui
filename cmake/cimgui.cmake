set(CIMGUI_DIR ${CMAKE_SOURCE_DIR}/3rdparty/cimgui)
set(CIMGUI_IMGUI ${CIMGUI_DIR}/imgui)
set(CIMGUI_IMGUI_IMPL ${CIMGUI_IMGUI}/backends)
set(CIMGUI_INCLUDE_DIRS
    ${CIMGUI_DIR}
    ${CIMGUI_DIR}/generator/output
    ${CIMGUI_IMGUI}
    ${CIMGUI_IMGUI_IMPL}
    )

file(GLOB CIMGUI_FILES
    ${CIMGUI_DIR}/*.cpp
    ${CIMGUI_IMGUI}/*.cpp
    ${CIMGUI_IMGUI_IMPL}/imgui_impl_glfw.cpp
    ${CIMGUI_IMGUI_IMPL}/imgui_impl_opengl3.cpp
    )

add_library(cimgui ${CIMGUI_FILES})

target_include_directories(cimgui PUBLIC
    ${CIMGUI_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    )

target_link_libraries(cimgui
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
    )

target_compile_definitions(cimgui PRIVATE
    IMGUI_IMPL_API=extern\ \"C\"
    IMGUI_IMPL_LOADER_GLAD
    IMGUI_IMPL_OPENGL_LOADER_GLAD
    )

set_target_properties(cimgui PROPERTIES FOLDER 3rdparty)

set(CIMGUI_LIBRARY cimgui)
