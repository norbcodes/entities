// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file settings_view.cpp
 * \author norbcodes
 * \brief Settings menu!
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <iostream>
#include <string>
#include <cstdint>
#include <fmt/core.h>

#include "colors.hpp"
#include "utils.hpp"
#include "global_settings.hpp"
#include "user_settings.hpp"
#include "keyboard.hpp"
#include "cmd_args.hpp"

static void UserCreationScreen(const GameArgs& game_args)
{
    // Here we create a new user.
    ClearScreen();
    Div();
    fmt::print("{1}Enter your username: {0}\n\n", RESET, WHITE);
    EndDivNoNewl();
    // get
    std::string name;
    std::cin >> name;
    // Create new user and delete
    UserSettingsClass* new_user = new UserSettingsClass(game_args, name);
    new_user->Save(game_args);
    delete new_user;
}

static void NewUsername(UserSettingsClass& user_settings)
{
    ClearScreen();
    Div();
    fmt::print("{1}Enter your username: {0}\n\n", RESET, WHITE);
    EndDivNoNewl();
    // yessss
    std::string name;
    std::cin >> name;
    // mmmmmm
    user_settings.SetUsername(name);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Settings menu.
 * \param[in] game_args Game CMD arguments.
 * \param[in] global_settings Global game settings.
 * \param[in] user_settings User settings.
 */
void SettingsView(const GameArgs& game_args, GlobalSettingsClass& global_settings, UserSettingsClass& user_settings)
{
    int32_t selection = 0;
    bool edit_mode = false;
    bool in_settings = true;
    while (in_settings)
    {
        ClearScreen();
        if (edit_mode)
        {
            Div();
            fmt::print("{1}> {2}Settings{0}\n\n", RESET, WHITE, BLUE);
            // Nice
            fmt::print("{1}......... 1 DISCORD SETTINGS ..........{0}\n", RESET, DARK_GRAY);

            if (global_settings.GetDiscordEnabled())
            {
                if (selection == 0)
                {
                    fmt::print("{1}{2}1   Discord RPC:     ON{0}\n", RESET, WHITE_BACKGROUND, BLACK);
                }
                else
                {
                    fmt::print("{1}1   Discord RPC:     {0}{2}ON{0}\n", RESET, WHITE, GREEN);
                }
            }
            else
            {
                if (selection == 0)
                {
                    fmt::print("{1}{2}1   Discord RPC:     OFF{0}\n", RESET, WHITE_BACKGROUND, BLACK);
                }
                else
                {
                    fmt::print("{1}1   Discord RPC:     {0}{2}OFF{0}\n", RESET, WHITE, RED);
                }
            }

            fmt::print("{1}.......................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{1}.......... 2 USER SETTINGS ............{0}\n", RESET, DARK_GRAY);
            fmt::print("{1}:: Logged in as {2}{3}{0}\n", RESET, WHITE, BOLD, user_settings.GetUsername());

            if (selection == 1)
            {
                fmt::print("{1}{2}2   Create new user...{0}\n", RESET, WHITE_BACKGROUND, BLACK);
            }
            else
            {
                fmt::print("{1}2   Create new user...{0}\n", RESET, WHITE);
            }

            if (selection == 2)
            {
                fmt::print("{1}{2}3   Change username...{0}\n", RESET, WHITE_BACKGROUND, BLACK);
            }
            else
            {
                fmt::print("{1}3   Change username...{0}\n", RESET, WHITE);
            }

            fmt::print("{1}.......................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{1}Press {2}left arrow{1} to exit {2}Edit{1} mode.{0}\n", RESET, WHITE, RED);
            fmt::print("{1}Use {2}up and down arrows{1} to {2}move{1}.{0}\n", RESET, WHITE, PURPLE);
            fmt::print("{1}Press {2}right arrow{1} to {2}change a setting{1}.{0}\n", RESET, WHITE, YELLOW);
            EndDiv();

            // Get arrow keys instead
            uint16_t arrow = GetArrowKey();
            switch (arrow)
            {
                case LEFT_KEY:
                    edit_mode = false;
                    selection = 0;
                    break;
                case DOWN_KEY:
                    if (selection + 1 <= 2)
                    {
                        selection++;
                    }
                    break;
                case UP_KEY:
                    if (selection - 1 >= 0)
                    {
                        selection--;
                    }
                    break;
                case RIGHT_KEY:
                    switch (selection)
                    {
                        // Yes, nested switch
                        case 0:
                            global_settings.SetDiscordEnabled(!global_settings.GetDiscordEnabled());
                            break;
                        case 1:
                            UserCreationScreen(game_args);
                            break;
                        case 2:
                            NewUsername(user_settings);
                            break;
                    }
            }
        }
        else
        {
            Div();
            fmt::print("{1}> {2}Settings{0}\n\n", RESET, WHITE, BLUE);
            // Nice
            fmt::print("{1}......... 1 DISCORD SETTINGS ..........{0}\n", RESET, DARK_GRAY);
            if (global_settings.GetDiscordEnabled())
            {
                fmt::print("{1}>   Discord RPC:     {0}{2}ON{0}\n", RESET, WHITE, GREEN);
            }
            else
            {
                fmt::print("{1}>   Discord RPC:     {0}{2}OFF{0}\n", RESET, WHITE, RED);
            }
            fmt::print("{1}.......................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{1}.......... 2 USER SETTINGS ............{0}\n", RESET, DARK_GRAY);
            fmt::print("{1}:: Logged in as {2}{3}{0}\n", RESET, WHITE, BOLD, user_settings.GetUsername());
            fmt::print("{1}>   Create new user...{0}\n", RESET, WHITE);
            fmt::print("{1}>   Change username...{0}\n", RESET, WHITE);
            fmt::print("{1}.......................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{1}Press {2}1{1} to enter {2}Edit{1} mode. Press {3}9{1} to {3}go back to main menu{1}.{0}\n", RESET, WHITE, GREEN, RED);
            EndDiv();

            // Yay :3
            uint32_t option = WaitForNumkey();
            switch (option)
            {
                case 1:
                    edit_mode = true;
                    break;
                case 9:
                    in_settings = false;
                    break;
            }
        }
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0