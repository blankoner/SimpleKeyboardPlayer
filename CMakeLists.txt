cmake_minimum_required( VERSION 3.27.7 )

project( play )

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCES
  main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_mixer::SDL2_mixer)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
