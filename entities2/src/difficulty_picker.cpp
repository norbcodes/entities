// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file difficulty_picker.cpp
 * \author norbcodes
 * \brief Function for picking a difficulty.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <fmt/core.h>

#include "cmd_args.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "keyboard.hpp"
#include "gameplay_loop.hpp"
#include "global_settings.hpp"
#include "user_settings.hpp"

/**
 * \brief Pick a difficulty...
 * \param[in] global_settings Global game settings.
 * \param[in] user_settings User settings.
 * \param[in] game_args CMD arguments.
 */
void DifficultyPicker(const GlobalSettingsClass& global_settings, UserSettingsClass& user_settings, const GameArgs& game_args)
{
    bool picker_flag = true;
    bool record_demo = false;
    while (picker_flag)
    {
        ClearScreen();
        Div();
        fmt::print("{2}<{0} {1}Difficulty Selection{0}\n\n", RESET, RED, WHITE);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}I kick Entities ass{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN);
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}I've seen worse{0}\n", RESET, BOLD, GOLD, DARK_GRAY, ORANGE);
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}Down with the Entities{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        fmt::print("{3}[{0}{2}{1}4{0}{3}]{0} {4}Random!{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER);
        if (record_demo)
        {
            fmt::print("{3}[{0}{2}{1}9{0}{3}]{0} {4}Record demo: {5}ON{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, WHITE, GREEN);
        }
        else
        {
            fmt::print("{3}[{0}{2}{1}9{0}{3}]{0} {4}Record demo: {5}OFF{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, WHITE, RED);
        }
        fmt::print("{3}[{0}{2}{1}5{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        EndDiv();

        uint32_t choice = WaitForNumkey();

        if (choice == 5)
        {
            picker_flag = false;
            break;
        }
        else if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
        {
            Game(choice, picker_flag, game_args, global_settings, user_settings, record_demo ? 1 : 0);
        }
        else if (choice == 9)
        {
            record_demo = !record_demo;
        }
        else
        {
            continue;
        }
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0