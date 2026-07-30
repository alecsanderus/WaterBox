cmake_minimum_required(VERSION 3.22)
project(WaterBoxAndroid LANGUAGES C CXX)

# === 1. ПРАВИЛЬНЫЕ ПУТИ (всего 3 уровня вверх: ../../../) ===
set(SDL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party/SDL")
set(WATERBOX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../WaterBox")

# Проверка, что папки существуют (чтобы не было молчаливых ошибок)
if(NOT EXISTS "${SDL_PATH}/CMakeLists.txt")
    message(FATAL_ERROR "SDL не найден! Проверьте путь: ${SDL_PATH}")
endif()
if(NOT EXISTS "${WATERBOX_PATH}")
    message(FATAL_ERROR "Папка с исходниками не найдена: ${WATERBOX_PATH}")
endif()

# === 2. Настройка SDL для Android ===
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(${SDL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL)

# === 3. Сборка ваших исходников ===
file(GLOB_RECURSE WATERBOX_SOURCES
        CONFIGURE_DEPENDS
        "${WATERBOX_PATH}/*.cpp"
        "${WATERBOX_PATH}/*.h"
)

# ВАЖНО: Библиотека ДОЛЖНА называться "main" для SDL Android
add_library(main SHARED ${WATERBOX_SOURCES})

# Подключаем зависимости
target_link_libraries(main
        SDL3::SDL3
        log        # Библиотека логирования Android
        android    # Нативные API Android
)

# Настройки компилятора
set_target_properties(main PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_include_directories(main PRIVATE "${WATERBOX_PATH}")

target_compile_definitions(main PRIVATE
        __ANDROID__
        APP_VERSION="1.0.0"
)