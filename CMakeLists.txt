cmake_minimum_required(VERSION 3.27.9)

project(SDL2Chess LANGUAGES C)

add_executable(SDL2Chess)

set_property(TARGET SDL2Chess PROPERTY C_STANDARD 17)
set_property(TARGET SDL2Chess PROPERTY C_STANDARD_REQUIRED TRUE)

find_package(SDL2 REQUIRED)

target_sources(SDL2Chess PRIVATE
  ${CMAKE_SOURCE_DIR}/src/main.c
  ${CMAKE_SOURCE_DIR}/src/engine.c
  ${CMAKE_SOURCE_DIR}/src/events.c
  ${CMAKE_SOURCE_DIR}/src/keyboard.c
  ${CMAKE_SOURCE_DIR}/src/render.c
  ${CMAKE_SOURCE_DIR}/src/update.c
)

target_include_directories(SDL2Chess PRIVATE
  ${SDL2_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(SDL2Chess PRIVATE
  ${SDL2_LIBRARIES}
)