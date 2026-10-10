cmake_minimum_required (VERSION 4.0)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project ("WaterBox")


include (FetchContent)
FetchContent_Declare(   
	SDL 
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL"
)


set(SDL_SHARED OFF CACHE BOOL "Build SDL as static library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build SDL as static library" FORCE)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "Disable SDL installation" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "Disable SDL Examples" FORCE)
set(SDL_CAMERA OFF CACHE BOOL "Disable SDL Camera" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "Disable SDL Examples" FORCE)

FetchContent_MakeAvailable(SDL)



FetchContent_Declare(
    json
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/json"
)
FetchContent_MakeAvailable(json)
 
set(SDLTTF_HARFBUZZ OFF CACHE BOOL "Disable Harfbuzz text shaping" FORCE)
set(SDLTTF_PLUTOSVG OFF CACHE BOOL "Disable PlutoSVG color emoji support" FORCE)
set(SDLTTF_SAMPLES OFF CACHE BOOL "Disable SDL_ttf samples" FORCE)
set(SDLTTF_INSTALL OFF CACHE BOOL "Disable SDL_ttf installation" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build SDL_ttf as static library" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "Build SDL_ttf as static library" FORCE)

FetchContent_Declare(   
	SDL_ttf
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL_ttf"
)

set(SDLTTF_SAMPLES OFF CACHE BOOL "Disable SDL_ttf samples" FORCE)
set(SDLTTF_INSTALL OFF CACHE BOOL "Disable SDL_ttf installation" FORCE)

FetchContent_MakeAvailable(SDL_ttf)







set(SDLIMAGE_VENDORED ON CACHE BOOL "" FORCE)

set(SDLIMAGE_PNG ON CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG_LIBPNG ON CACHE BOOL "" FORCE)

set(SDLIMAGE_ANI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_GIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_LBM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PCX OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PNM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_QOI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_SVG OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TGA OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XCF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XPM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XV OFF CACHE BOOL "" FORCE)

set(SDLIMAGE_SAMPLES OFF CACHE BOOL "Disable SDL_image samples" FORCE)
set(SDLIMAGE_TESTS OFF CACHE BOOL "Disable SDL_image tests" FORCE)


FetchContent_Declare(
    SDL3_image
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL_img"
)

FetchContent_MakeAvailable(SDL3_image)


add_subdirectory ("WaterBox")


message(STATUS "========== SDL OPTIONS ==========")
message(STATUS "SDL_EXAMPLES       = ${SDL_EXAMPLES}")
message(STATUS "SDL_TESTS          = ${SDL_TESTS}")
message(STATUS "SDL_TEST_LIBRARY   = ${SDL_TEST_LIBRARY}")
message(STATUS "SDLTTF_SAMPLES     = ${SDLTTF_SAMPLES}")
message(STATUS "SDLIMAGE_SAMPLES   = ${SDLIMAGE_SAMPLES}")
message(STATUS "=================================")