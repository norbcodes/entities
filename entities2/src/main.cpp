// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file main.cpp
 * \author norbcodes
 * \brief Entry point to the program.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

/*
MADE BY NORB
https://github.com/norbcodes
https://github.com/norbcodes/entities

The long awaited... entities2!!!!
*/

#include <cstdint>
#include <string>
#include <iostream>
#include <fmt/core.h>
#include <array>

#ifdef _WIN32
    #include "windows.h"
#endif

#include "colors.hpp"
#include "difficulty_picker.hpp"
#include "gameplay_loop.hpp"
#include "discord_rpc.hpp"
#include "utils.hpp"
#include "keyboard.hpp"
#include "exit_msg.hpp"
#include "gameplay_info.hpp"
#include "sleep.hpp"
#include "datapacks.hpp"
#include "datapack_viewer.hpp"
#include "cmd_args.hpp"
#include "global_settings.hpp"
#include "user_settings.hpp"
#include "settings_viewer.hpp"
#include "rng.hpp"
#include "greetings.hpp"
#include "version.hpp"
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"

/**
 * \brief The very entry point of the game, and the program as a whole.
 * \param[in] argc CMD argument count.
 * \param[in] argv Arguments.
 * \return Exit code.
 */
int main(int argc, char* argv[])
{
    #ifdef _WIN32
        // Create windows virtual cmd
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif

    // LOAD ESSENTIAL SYSTEMS.
    // Arg parsing
    GameArgs* GameArguments = new GameArgs(argc, argv);
    // Translations
    TranslationEngine* GameTranslation = new TranslationEngine;
    GameTranslation->LoadEnglish();

    #ifdef __ENTITIES2_BAKED_IN_SLOVAK__
    GameTranslation->LoadSlovak();
    #endif

    #ifdef __ENTITIES2_BAKED_IN_RUSSIAN__
    GameTranslation->LoadRussian();
    #endif

    #ifdef __ENTITIES2_BAKED_IN_TAGALOG__
    GameTranslation->LoadTagalog();
    #endif

    #ifdef __ENTITIES2_BAKED_IN_PORTUGUESE__
    GameTranslation->LoadPortuguese();
    #endif

    // Global settings
    GlobalSettingsClass* GlobalSettings = new GlobalSettingsClass(*GameArguments);
    // Now set language, hehe
    if (GameArguments->LanguageOverride() != std::string(""))
    {
        if (GameTranslation->LangIdExists(GameArguments->LanguageOverride()))
        {
            GameTranslation->SetLang(GameArguments->LanguageOverride(), *GlobalSettings);
        }
        else
        {
            GameTranslation->SetLang("EN-US", *GlobalSettings);
        }
    }
    else
    {
        GameTranslation->SetLang(GlobalSettings->GetLanguageId(), *GlobalSettings);
    }
    // User settings
    UserSettingsClass* UserSettings = new UserSettingsClass(*GameArguments);
    // B)
    DatapackEngine* Datapacks = new DatapackEngine(*GameArguments);

    if (!GameArguments->NoDatapacks())
    {
        Datapacks->LoadAll(*GameArguments, *UserSettings, *GameTranslation);
    }

    if (GlobalSettings->GetDiscordEnabled())
    {
        InitializeRPC();
    }

    #ifndef __ENTITIES2_DISABLE_UNSTABLE_WARNING__
        #if (ENTITIES2_VER_IS_DEV == 1)
            Div();
            fmt::print("{0}\n", MsgFormatter(GameTranslation->GetTranslated("menu.unstable"), *UserSettings));
            EndDiv();

            if (!BinaryChoice())
            {
                std::cout << std::endl;
                return 0;
            }
        #endif
    #endif // __ENTITIES2_DISABLE_UNSTABLE_WARNING__

    while (true)
    {
        if (GlobalSettings->GetDiscordEnabled())
        {
            MainMenuRPC();
        }
        ClearScreen();
        Div();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #ifndef __ENTITIES2_4_BIT_COLORS__

        if (rng(0, 5) != 0)
        {
            uint8_t r = 50;
            uint8_t g = 50;
            uint8_t b = 50;
            const uint32_t loops = rng(0, 50);
            for (uint32_t i = 0; i != loops; i++)
            {
                r += rng(1, 58);
                g += rng(1, 58);
                b += rng(1, 58);
                // basically it will just overflow so no need to check if over 256
            }
            std::string title_col = fmt::format("\x1b[38;2;{0};{1};{2}m", r, g, b);
            // I love when ascii art looks like this :)
            fmt::print("{1}{2}              __  _ __  _          ___ {0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2}  ___  ____  / /_(_) /_(_)__  ____|__ \\{0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2} / _ \\/ __ \\/ __/ / __/ / _ \\/ ___/_/ /{0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2}/  __/ / / / /_/ / /_/ /  __(__  ) __/ {0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2}\\___/_/ /_/\\__/_/\\__/_/\\___/____/____/ {0}\n", RESET, title_col, BOLD);
        }
        else
        {
            // Oh boy, now we do each line different color
            // Weeee
            uint8_t r = 50;
            uint8_t g = 50;
            uint8_t b = 50;
            const uint32_t loops = rng(0, 50);
            std::string title_col;
            // First row
            for (uint32_t i = 0; i != loops; i++)
            {
                r += rng(1, 58);
                g += rng(1, 58);
                b += rng(1, 58);
            }
            title_col = fmt::format("\x1b[38;2;{0};{1};{2}m", r, g, b);
            fmt::print("{1}{2}              __  _ __  _          ___ {0}\n", RESET, title_col, BOLD);
            // Second line
                        for (uint32_t i = 0; i != loops; i++)
            {
                r += rng(1, 58);
                g += rng(1, 58);
                b += rng(1, 58);
            }
            title_col = fmt::format("\x1b[38;2;{0};{1};{2}m", r, g, b);
            fmt::print("{1}{2}  ___  ____  / /_(_) /_(_)__  ____|__ \\{0}\n", RESET, title_col, BOLD);
            // Third row
            for (uint32_t i = 0; i != loops; i++)
            {
                r += rng(1, 58);
                g += rng(1, 58);
                b += rng(1, 58);
            }
            title_col = fmt::format("\x1b[38;2;{0};{1};{2}m", r, g, b);
            fmt::print("{1}{2} / _ \\/ __ \\/ __/ / __/ / _ \\/ ___/_/ /{0}\n", RESET, title_col, BOLD);
            // Fourth line
                        for (uint32_t i = 0; i != loops; i++)
            {
                r += rng(1, 58);
                g += rng(1, 58);
                b += rng(1, 58);
            }
            title_col = fmt::format("\x1b[38;2;{0};{1};{2}m", r, g, b);
            fmt::print("{1}{2}/  __/ / / / /_/ / /_/ /  __(__  ) __/ {0}\n", RESET, title_col, BOLD);
            // Fifth line
            for (uint32_t i = 0; i != loops; i++)
            {
                r += rng(1, 58);
                g += rng(1, 58);
                b += rng(1, 58);
            }
            title_col = fmt::format("\x1b[38;2;{0};{1};{2}m", r, g, b);
            fmt::print("{1}{2}\\___/_/ /_/\\__/_/\\__/_/\\___/____/____/ {0}\n", RESET, title_col, BOLD);
        }

        #else // __ENTITIES2_4_BIT_COLORS__
        
        std::array<const char*, 7> color_array = {RED, BLUE, ORANGE, WHITE, HOT_PINK, DARK_GRAY, GOLD};
        if (rng(0, 5) != 0)
        {
            std::string title_col = color_array[rng(0, 6)];
            fmt::print("{1}{2}              __  _ __  _          ___ {0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2}  ___  ____  / /_(_) /_(_)__  ____|__ \\{0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2} / _ \\/ __ \\/ __/ / __/ / _ \\/ ___/_/ /{0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2}/  __/ / / / /_/ / /_/ /  __(__  ) __/ {0}\n", RESET, title_col, BOLD);
            fmt::print("{1}{2}\\___/_/ /_/\\__/_/\\__/_/\\___/____/____/ {0}\n", RESET, title_col, BOLD);
        }
        else
        {
            std::string title_col = color_array[rng(0, 6)];
            fmt::print("{1}{2}              __  _ __  _          ___ {0}\n", RESET, title_col, BOLD);
            title_col = color_array[rng(0, 6)];
            fmt::print("{1}{2}  ___  ____  / /_(_) /_(_)__  ____|__ \\{0}\n", RESET, title_col, BOLD);
            title_col = color_array[rng(0, 6)];
            fmt::print("{1}{2} / _ \\/ __ \\/ __/ / __/ / _ \\/ ___/_/ /{0}\n", RESET, title_col, BOLD);
            title_col = color_array[rng(0, 6)];
            fmt::print("{1}{2}/  __/ / / / /_/ / /_/ /  __(__  ) __/ {0}\n", RESET, title_col, BOLD);
            title_col = color_array[rng(0, 6)];
            fmt::print("{1}{2}\\___/_/ /_/\\__/_/\\__/_/\\___/____/____/ {0}\n", RESET, title_col, BOLD);
        }

        #endif

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        fmt::print("{2}{5}{3: <8}{0}              {5}{1}{4}{0}", RESET, DARK_GRAY, GREEN, ENTITIES2_VER, GameTranslation->GetTranslated("menu.main.subtitle"), UNDERLINE);
        fmt::print("\n\n");
        ////////////////////////////////////////
        // Greet
        bool Was_Translated_Greet;
        std::string greet = GetGreeting(*GameTranslation, Was_Translated_Greet);
        if (Was_Translated_Greet)
        {
            greet = MsgFormatter(greet, *UserSettings);
        }
        fmt::print("{0}", greet);
        ////////////////////////////////////////
        fmt::print("\n\n");
        fmt::print("{1}{2}{0}", RESET, WHITE, MsgFormatter(GameTranslation->GetTranslated("menu.main.optionpick"), *UserSettings));
        fmt::print("\n\n");
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN, GameTranslation->GetTranslated("menu.main.play"));
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER, GameTranslation->GetTranslated("menu.main.ginfo"));
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, PINK, GameTranslation->GetTranslated("menu.main.datapacks"));
        fmt::print("{3}[{0}{2}{1}4{0}{3}]{0} {4}{5}{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, BROWN, GameTranslation->GetTranslated("menu.main.settings"));
        fmt::print("{3}[{0}{2}{1}5{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED, GameTranslation->GetTranslated("general.quit"));
        EndDiv();

        uint32_t option = WaitForNumkey();

        if (option == 5)
        {
            ClearScreen();
            Div();
            fmt::print("{1}{2} [y,n]{0}\n\n", RESET, RED, GameTranslation->GetTranslated("menu.exit.confirm"));
            bool Was_Translated_Exit;
            std::string exit_msg = GetExitMsg(*GameTranslation, Was_Translated_Exit);
            if (Was_Translated_Exit)
            {
                exit_msg = CustomMsgFormatter(exit_msg, *UserSettings, fmt::arg("perc", (1.0 / (double)GetExitMsgCount()) * 100));
            }
            fmt::print("{0}\n", exit_msg);
            EndDiv();

            if (BinaryChoice())
            {
                ClearScreen();
                if (GlobalSettings->GetShowEndScreenValue())
                {
                    Credits(*GameTranslation);
                    SleepSeconds(1);
                }
                break;
            }
            else
            {
                continue;
            }
        }
        // MAIN GAME
        else if (option == 1)
        {
            // do
            DifficultyPicker(*GlobalSettings, *UserSettings, *GameArguments, *GameTranslation);
        }
        // INFO SECTION
        else if (option == 2)
        {
            GameplayInfoSec(*GameTranslation);
        }
        // DATAPACK VIEW
        else if (option == 3)
        {
            DatapackViewer(*Datapacks, *GameTranslation);
        }
        else if (option == 4)
        {
            SettingsView(*GameArguments, *GlobalSettings, *UserSettings, *GameTranslation);
        }
        else
        {
            continue;
        }
    }

    if (GlobalSettings->GetDiscordEnabled())
    {
        DestroyRPC();
    }
    GlobalSettings->Save(*GameArguments);
    UserSettings->Save(*GameArguments);

    delete GameArguments;
    delete GlobalSettings;
    delete UserSettings;
    delete Datapacks;

    return 0;
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0