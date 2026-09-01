cmake_minimum_required(VERSION 3.22)
project(WaterBoxAndroid LANGUAGES C CXX)

set(SDL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party/SDL")
set(JSON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party/json")

set(WATERBOX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../WaterBox")

if(NOT EXISTS "${SDL_PATH}/CMakeLists.txt")
    message(FATAL_ERROR "SDL не найден! Проверьте путь: ${SDL_PATH}")
endif()
if(NOT EXISTS "${WATERBOX_PATH}")
    message(FATAL_ERROR "Папка с исходниками не найдена: ${WATERBOX_PATH}")
endif()
if(NOT EXISTS "${JSON_PATH}")
    message(FATAL_ERROR "Папка с исходниками не найдена: ${WATERBOX_PATH}")
endif()

set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(${SDL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL)


file(GLOB_RECURSE WATERBOX_SOURCES
        CONFIGURE_DEPENDS
        "${WATERBOX_PATH}/*.cpp"
        "${WATERBOX_PATH}/*.h"
)

add_library(main SHARED ${WATERBOX_SOURCES})
target_compile_definitions (main PRIVATE GlobalPathPrefix="")


add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE "${JSON_PATH}/include")

target_link_libraries(main
        SDL3::SDL3
        nlohmann_json
        log        # Библиотека логирования Android
        android    # Нативные API Android
)

# Настройки компилятора
set_target_properties(main PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_include_directories(main PRIVATE "${WATERBOX_PATH}")

target_compile_definitions(main PRIVATE
        __ANDROID__
        APP_VERSION="1.0.0"
)