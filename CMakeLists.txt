cmake_minimum_required(VERSION 3.16)
project(LCW)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(
        LCW 
        src/main.cpp
        src/spaceship.cpp
        src/spaceship.h
        src/constants.h
        src/bullet.cpp
        src/bullet.h
        src/kamikaze.cpp
        src/kamikaze.h
        src/rand.cpp
        src/rand.h
        src/shooter.cpp
        src/shooter.h
        src/rotate_vector.cpp
        src/rotate_vector.h
        src/shooter_bullet.cpp
        src/shooter_bullet.h
        src/button.cpp
        src/button.h
        src/colors.h
        src/health_orb.h
        src/health_orb.cpp
        src/main_menu.cpp 
        src/main_menu.h 
        src/mouse_cursor_in.cpp 
        src/mouse_cursor_in.h 
        src/game_status.h 
        src/main_menu_signal.h 
        src/leader_board.cpp 
        src/leader_board.h 
        src/leader_board_line.cpp 
        src/leader_board_line.h 
        src/pause_menu.cpp 
        src/pause_menu.h 
        src/pause_menu_signal.h 
        src/game_over.cpp 
        src/game_over.h 
        src/input_box.cpp 
        src/input_box.h 
        src/inside_window.cpp 
        src/inside_window.h 
        src/intersect.cpp 
        src/intersect.h
)


target_link_libraries(LCW sfml-graphics sfml-audio)

