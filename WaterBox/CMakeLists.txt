
file(GLOB_RECURSE WATERBOX_SOURCES 
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)


# Цель 1: С консолью
add_executable(WaterBoxConsole ${WATERBOX_SOURCES})
target_link_libraries(WaterBoxConsole PRIVATE SDL3::SDL3)
target_compile_definitions (WaterBoxConsole PRIVATE ENABLE_CONSOLE)

# Цель 2: Без консоли
add_executable(WaterBox WIN32 ${WATERBOX_SOURCES})
target_link_libraries(WaterBox PRIVATE SDL3::SDL3)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WaterBox PROPERTY CXX_STANDARD 20)
  set_property(TARGET WaterBoxConsole PROPERTY CXX_STANDARD 20)
endif()
