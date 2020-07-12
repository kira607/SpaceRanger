cmake_minimum_required(VERSION 3.16)
project(LCW)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(LCW main.cpp
        spaceship.cpp
        spaceship.h
        constants.h
        bullet.cpp
        bullet.h
        kamikaze.cpp
        kamikaze.h
        rand.cpp
        rand.h
        shooter.cpp
        shooter.h
        rotate_vector.cpp
        rotate_vector.h
        shooter_bullet.cpp
        shooter_bullet.h
        button.cpp
        button.h
        colors.h
        health_orb.h
        health_orb.cpp
        main_menu.cpp main_menu.h mouse_cursor_in.cpp mouse_cursor_in.h game_status.h main_menu_signal.h leader_board.cpp leader_board.h leader_board_line.cpp leader_board_line.h pause_menu.cpp pause_menu.h pause_menu_signal.h game_over.cpp game_over.h input_box.cpp input_box.h inside_window.cpp inside_window.h intersect.cpp intersect.h)


target_link_libraries(LCW sfml-graphics sfml-audio)

