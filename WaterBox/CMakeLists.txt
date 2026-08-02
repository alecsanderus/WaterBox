
file(GLOB_RECURSE WATERBOX_SOURCES 
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

if(MSVC)
    string(REPLACE "/EHsc" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    # На всякий случай убираем и /EHs, если он где-то проскочил
    string(REPLACE "/EHs" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Цель 1: С консолью
add_executable(WaterBoxConsole ${WATERBOX_SOURCES})
target_link_libraries(WaterBoxConsole PRIVATE SDL3::SDL3)
target_include_directories(WaterBoxConsole PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions (WaterBoxConsole PRIVATE ENABLE_CONSOLE)

# Цель 2: Без консоли
add_executable(WaterBox WIN32 ${WATERBOX_SOURCES})
target_link_libraries(WaterBox PRIVATE SDL3::SDL3)
target_include_directories(WaterBox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WaterBox PROPERTY CXX_STANDARD 20)
  set_property(TARGET WaterBoxConsole PROPERTY CXX_STANDARD 20)
endif()
