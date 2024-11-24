// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file settings_viewer.cpp
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
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"
#include "language_picker.hpp"

static void UserCreationScreen(const GameArgs& game_args, const TranslationEngine& GameTranslation)
{
    // Here we create a new user.
    ClearScreen();
    Div();
    while (true)
    {
        fmt::print("{1}{2} {0}\n\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.enteruser"));
        EndDivNoNewl();
        // get
        std::string name;
        std::getline(std::cin, name);
        // mmmmmm
        // Check for spaces
        bool rewind = false;
        for (uint32_t i = 0; i != name.size(); i++)
        {
            if (name[i] == ' ')
            {
                rewind = true;
            }
        }
        // Oopsie daisy
        if (rewind)
        {
            fmt::print("{1}{2: <90}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.options.usererror"));
            continue;
        }
        // Create new user and delete
        UserSettingsClass* new_user = new UserSettingsClass(game_args, name);
        new_user->Save(game_args);
        delete new_user;
        break;
    }
}

static void NewUsername(UserSettingsClass& user_settings, const TranslationEngine& GameTranslation)
{
    ClearScreen();
    Div();
    while (true)
    {
        fmt::print("{1}{2} {0}\n\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.enteruser"));
        EndDivNoNewl();
        // yessss
        std::string name;
        std::getline(std::cin, name);
        // mmmmmm
        // Check for spaces
        bool rewind = false;
        for (uint32_t i = 0; i != name.size(); i++)
        {
            if (name[i] == ' ')
            {
                rewind = true;
            }
        }
        // uwu
        if (rewind)
        {
            fmt::print("{1}{2: <90}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.options.usererror"));
            continue;
        }

        user_settings.SetUsername(name);
        break;
    }
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
 * \param[in] GameTranslation Game translation system.
 */
void SettingsView(const GameArgs& game_args, GlobalSettingsClass& global_settings, UserSettingsClass& user_settings, TranslationEngine& GameTranslation)
{
    int32_t selection = 0;
    const int32_t selection_count = 4;
    bool edit_mode = false;
    bool in_settings = true;
    while (in_settings)
    {
        ClearScreen();
        if (edit_mode)
        {
            Div();
            fmt::print("{1}> {2}{3}{0}\n\n", RESET, WHITE, BLUE, GameTranslation.GetTranslated("menu.options.title"));
            // Nice
            fmt::print("{1}{2:.^40}{0}\n", RESET, DARK_GRAY, GameTranslation.GetTranslated("menu.options.cat1"));

            if (global_settings.GetDiscordEnabled())
            {
                if (selection == 0)
                {
                    fmt::print("{1}{2}1   {3: <20} {4}{0}\n", RESET, WHITE_BACKGROUND, BLACK, GameTranslation.GetTranslated("menu.options.c1o1"), GameTranslation.GetTranslated("general.on"));
                }
                else
                {
                    fmt::print("{1}1   {3: <20}  {0}{2}{4}{0}\n", RESET, WHITE, GREEN, GameTranslation.GetTranslated("menu.options.c1o1"), GameTranslation.GetTranslated("general.on"));
                }
            }
            else
            {
                if (selection == 0)
                {
                    fmt::print("{1}{2}1   {3: <20} {4}{0}\n", RESET, WHITE_BACKGROUND, BLACK, GameTranslation.GetTranslated("menu.options.c1o1"), GameTranslation.GetTranslated("general.off"));
                }
                else
                {
                    fmt::print("{1}1   {3: <20} {0}{2}{4}{0}\n", RESET, WHITE, RED, GameTranslation.GetTranslated("menu.options.c1o1"), GameTranslation.GetTranslated("general.off"));
                }
            }
            ////////////////////////////////////
            // LANGUAGE
            fmt::print("{1}........................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{1}{2:.^40}{0}\n", RESET, DARK_GRAY, GameTranslation.GetTranslated("menu.options.cat2"));
            fmt::print("{1}:: {2} {3}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.currlang"), GameTranslation.GetTranslated("lang.name"));
            
            if (selection == 1)
            {
                fmt::print("{1}{2}2   {3}{0}\n", RESET, WHITE_BACKGROUND, BLACK, GameTranslation.GetTranslated("menu.options.changelang"));
            }
            else
            {
                fmt::print("{1}2   {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.changelang"));
            }

            fmt::print("{1}........................................{0}\n\n", RESET, DARK_GRAY);
            ////////////////////////////////////
            // USER
            fmt::print("{1}{2:.^40}{0}\n", RESET, DARK_GRAY, GameTranslation.GetTranslated("menu.options.cat3"));
            fmt::print("{1}:: {4} {2}{3}{0}\n", RESET, WHITE, BOLD, user_settings.GetUsername(), GameTranslation.GetTranslated("menu.options.login"));

            if (selection == 2)
            {
                fmt::print("{1}{2}3   {3}{0}\n", RESET, WHITE_BACKGROUND, BLACK, GameTranslation.GetTranslated("menu.options.newuser"));
            }
            else
            {
                fmt::print("{1}3   {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.newuser"));
            }

            if (selection == 3)
            {
                fmt::print("{1}{2}4   {3}{0}\n", RESET, WHITE_BACKGROUND, BLACK, GameTranslation.GetTranslated("menu.options.changename"));
            }
            else
            {
                fmt::print("{1}4   {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.changename"));
            }

            fmt::print("{1}........................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("menu.options.help2")));
            fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("menu.options.help3")));
            fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("menu.options.help4")));
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
                    if (selection + 1 <= (selection_count - 1))
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
                            GameTranslation.SetLang( PickLanguage(GameTranslation, global_settings) );
                            break;
                        case 2:
                            UserCreationScreen(game_args, GameTranslation);
                            break;
                        case 3:
                            NewUsername(user_settings, GameTranslation);
                            break;
                    }
            }
        }
        else
        {
            Div();
            fmt::print("{1}> {2}{3}{0}\n\n", RESET, WHITE, BLUE, GameTranslation.GetTranslated("menu.options.title"));
            // Nice
            fmt::print("{1}{2:.^40}{0}\n", RESET, DARK_GRAY, GameTranslation.GetTranslated("menu.options.cat1"));
            if (global_settings.GetDiscordEnabled())
            {
                fmt::print("{1}>   {3: <20} {0}{2}{4}{0}\n", RESET, WHITE, GREEN, GameTranslation.GetTranslated("menu.options.c1o1"), GameTranslation.GetTranslated("general.on"));
            }
            else
            {
                fmt::print("{1}>   {3: <20} {0}{2}{4}{0}\n", RESET, WHITE, RED, GameTranslation.GetTranslated("menu.options.c1o1"), GameTranslation.GetTranslated("general.off"));
            }
            fmt::print("{1}........................................{0}\n\n", RESET, DARK_GRAY);
            ////////////////////////////////////
            // LANGUAGE
            fmt::print("{1}{2:.^40}{0}\n", RESET, DARK_GRAY, GameTranslation.GetTranslated("menu.options.cat2"));
            fmt::print("{1}:: {2} {3}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.currlang"), GameTranslation.GetTranslated("lang.name"));
            fmt::print("{1}>   {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.changelang"));
            ////////////////////////////////////
            fmt::print("{1}........................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{1}{2:.^40}{0}\n", RESET, DARK_GRAY, GameTranslation.GetTranslated("menu.options.cat3"));
            fmt::print("{1}:: {4} {2}{3}{0}\n", RESET, WHITE, BOLD, user_settings.GetUsername(), GameTranslation.GetTranslated("menu.options.login"));
            fmt::print("{1}>   {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.newuser"));
            fmt::print("{1}>   {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.changename"));
            fmt::print("{1}........................................{0}\n\n", RESET, DARK_GRAY);
            fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("menu.options.help1")));
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