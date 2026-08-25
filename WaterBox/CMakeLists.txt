
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


file(GLOB GAME_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../GameFiles/*")


function(copy_game_files TARGET_NAME)
  foreach(GAME_FILE ${GAME_FILES})
    if(NOT IS_DIRECTORY ${GAME_FILE})
        add_custom_command(
                TARGET ${TARGET_NAME} POST_BUILD
                # Создаем папку GameFiles рядом с EXE этого таргета
                COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${TARGET_NAME}>/GameFiles"
                # Копируем файл
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${GAME_FILE}"
                "$<TARGET_FILE_DIR:${TARGET_NAME}>/GameFiles/"
            )
        endif()
    endforeach()
endfunction()



# Цель 1: С консолью
add_executable(WaterBoxConsole ${WATERBOX_SOURCES})
target_link_libraries(WaterBoxConsole PRIVATE SDL3::SDL3 nlohmann_json::nlohmann_json)
target_include_directories(WaterBoxConsole PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
copy_game_files (WaterBoxConsole)

target_compile_definitions (WaterBoxConsole PRIVATE ENABLE_CONSOLE)

# Цель 2: Без консоли
add_executable(WaterBox WIN32 ${WATERBOX_SOURCES})
target_link_libraries(WaterBox PRIVATE SDL3::SDL3 nlohmann_json::nlohmann_json)
target_include_directories(WaterBox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
copy_game_files (WaterBox)




if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WaterBox PROPERTY CXX_STANDARD 20)
  set_property(TARGET WaterBoxConsole PROPERTY CXX_STANDARD 20)
endif()








