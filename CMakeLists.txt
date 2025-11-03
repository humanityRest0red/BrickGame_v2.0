cmake_minimum_required(VERSION 3.14)
project(${PROJECT_NAME})

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Включение автоматического moc, rcc, uic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    gui/desktop/main.cc
    gui/desktop/main_window.cc
    gui/desktop/game_field.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/build/snake.a
    ${CMAKE_CURRENT_SOURCE_DIR}/build/tetris.a
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/brick_game
    ${CMAKE_CURRENT_SOURCE_DIR}/brick_game/snake
    ${CMAKE_CURRENT_SOURCE_DIR}/brick_game/tetris
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/desktop
)

# Связываем с библиотеками Qt
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)