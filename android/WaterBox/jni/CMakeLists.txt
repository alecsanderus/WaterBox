cmake_minimum_required(VERSION 3.22)
project(WaterBoxAndroid LANGUAGES C CXX)

set(THIRD_PARTY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party")
set(WATERBOX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../WaterBox")


if(NOT EXISTS "${THIRD_PARTY_PATH}/SDL/CMakeLists.txt")
    message(FATAL_ERROR "SDL не найден! Проверьте путь: ${THIRD_PARTY_PATH}/SDL")
endif()
if(NOT EXISTS "${THIRD_PARTY_PATH}/SDL_ttf/CMakeLists.txt")
    message(FATAL_ERROR "SDL_ttf не найден! Проверьте путь: ${THIRD_PARTY_PATH}/SDL_ttf")
endif()
if(NOT EXISTS "${THIRD_PARTY_PATH}/json/CMakeLists.txt")
    message(FATAL_ERROR "json не найден! Проверьте путь: ${THIRD_PARTY_PATH}/json")
endif()
if(NOT EXISTS "${WATERBOX_PATH}")
    message(FATAL_ERROR "Папка с исходниками не найдена: ${WATERBOX_PATH}")
endif()



set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_CAMERA OFF CACHE BOOL "" FORCE)

set(SDLTTF_HARFBUZZ OFF CACHE BOOL "Disable Harfbuzz text shaping" FORCE)
set(SDLTTF_PLUTOSVG OFF CACHE BOOL "Disable PlutoSVG color emoji support" FORCE)
set(SDLTTF_SAMPLES OFF CACHE BOOL "Disable SDL_ttf samples" FORCE)
set(SDLTTF_INSTALL OFF CACHE BOOL "Disable SDL_ttf installation" FORCE)

add_subdirectory("${THIRD_PARTY_PATH}/SDL " ${CMAKE_CURRENT_BINARY_DIR}/SDL)
add_subdirectory("${THIRD_PARTY_PATH}/SDL_ttf " ${CMAKE_CURRENT_BINARY_DIR}/SDL_ttf)


file(GLOB_RECURSE WATERBOX_SOURCES
        CONFIGURE_DEPENDS
        "${WATERBOX_PATH}/*.cpp"
        "${WATERBOX_PATH}/*.h"
)

add_library(main SHARED ${WATERBOX_SOURCES})
target_compile_definitions (main PRIVATE GlobalPathPrefix="")


add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE "${THIRD_PARTY_PATH}/json/include")

target_link_libraries(main
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
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
        GlobalPathPrefix=""
)