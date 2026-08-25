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

FetchContent_MakeAvailable(SDL)



FetchContent_Declare(
    json
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/json"
)
FetchContent_MakeAvailable(json)
 

add_subdirectory ("WaterBox")