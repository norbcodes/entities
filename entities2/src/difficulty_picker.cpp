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
#include "translation_engine.hpp"

/**
 * \brief Pick a difficulty...
 * \param[in] global_settings Global game settings.
 * \param[in] user_settings User settings.
 * \param[in] game_args CMD arguments.
 * \param[in] GameTranslation Game translation system, for localized strings.
 */
void DifficultyPicker(const GlobalSettingsClass& global_settings, UserSettingsClass& user_settings, const GameArgs& game_args, const TranslationEngine& GameTranslation)
{
    bool picker_flag = true;
    bool record_demo = false;
    while (picker_flag)
    {
        ClearScreen();
        Div();
        fmt::print("{2}<{0} {1}{3}{0}\n\n", RESET, RED, WHITE, GameTranslation.GetTranslated("menu.diffpicker.title"));
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN, GameTranslation.GetTranslated("menu.diffpicker.easy"));
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, ORANGE, GameTranslation.GetTranslated("menu.diffpicker.medium"));
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED, GameTranslation.GetTranslated("menu.diffpicker.hard"));
        fmt::print("{3}[{0}{2}{1}4{0}{3}]{0} {4}{5}{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER, GameTranslation.GetTranslated("menu.diffpicker.random"));
        if (record_demo)
        {
            fmt::print("{3}[{0}{2}{1}9{0}{3}]{0} {4}{6}: {5}{7}{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, WHITE, GREEN, GameTranslation.GetTranslated("menu.diffpicker.record"), GameTranslation.GetTranslated("general.on"));
        }
        else
        {
            fmt::print("{3}[{0}{2}{1}9{0}{3}]{0} {4}{6}: {5}{7}{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, WHITE, RED, GameTranslation.GetTranslated("menu.diffpicker.record"), GameTranslation.GetTranslated("general.off"));
        }
        fmt::print("{3}[{0}{2}{1}5{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED, GameTranslation.GetTranslated("general.exit"));
        EndDiv();

        uint32_t choice = WaitForNumkey();

        if (choice == 5)
        {
            picker_flag = false;
            break;
        }
        else if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
        {
            Game(choice, picker_flag, game_args, global_settings, user_settings, record_demo ? 1 : 0, GameTranslation);
            user_settings.Save(game_args);
            global_settings.Save(game_args);
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