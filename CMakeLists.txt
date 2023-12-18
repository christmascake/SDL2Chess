cmake_minimum_required(VERSION 3.27.9)

project(SDL2Chess LANGUAGES C)

add_executable(SDL2Chess)

set_property(TARGET SDL2Chess PROPERTY C_STANDARD 17)
set_property(TARGET SDL2Chess PROPERTY C_STANDARD_REQUIRED TRUE)

find_package(SDL2 REQUIRED)

target_sources(SDL2Chess PRIVATE
  ${CMAKE_SOURCE_DIR}/src/main.c
  ${CMAKE_SOURCE_DIR}/src/game/chess.c
  ${CMAKE_SOURCE_DIR}/src/game/piece.c
  ${CMAKE_SOURCE_DIR}/src/game/pawn.c
  ${CMAKE_SOURCE_DIR}/src/game/knight.c
  ${CMAKE_SOURCE_DIR}/src/engine/engine.c
  ${CMAKE_SOURCE_DIR}/src/engine/events.c
  ${CMAKE_SOURCE_DIR}/src/engine/keyboard.c
  ${CMAKE_SOURCE_DIR}/src/engine/mouse.c
  ${CMAKE_SOURCE_DIR}/src/engine/render.c
  ${CMAKE_SOURCE_DIR}/src/engine/update.c
)

target_include_directories(SDL2Chess PRIVATE
  ${SDL2_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/engine
  ${CMAKE_SOURCE_DIR}/include/assets
  ${CMAKE_SOURCE_DIR}/include/game
)

target_link_libraries(SDL2Chess PRIVATE
  ${SDL2_LIBRARIES}
)