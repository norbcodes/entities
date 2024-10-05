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

#ifdef _WIN32
    #include "windows.h"
#endif

#include "colors.hpp"
#include "difficulty_picker.hpp"
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

/**
 * \brief The very entry point of the game, and the program as a whole.
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

    // Arg parsing
    GameArgs* GameArguments = new GameArgs(argc, argv);

    // Global settings
    GlobalSettingsClass* GlobalSettings = new GlobalSettingsClass(*GameArguments);

    // B)
    DatapackEngine* Datapacks = new DatapackEngine(*GameArguments);
    Datapacks->LoadAll(*GameArguments);

    // Add this as well.
    AddExitMsg(fmt::format("{1}Did you know? Each of these message has a {3}{2:.2f}%{1} chance to appear.{0}", RESET, WHITE, (1.0 / (double)GetExitMsgCount()) * 100, PURPLE));

    InitializeRPC();

    #ifndef __ENTITIES2_DISABLE_UNSTABLE_WARNING__
        #if (ENTITIES2_VER_IS_DEV == 1)
            Div();
            fmt::print("{1}You are using a game build that is {2}still under Development!{0}\n", RESET, RED, BOLD);
            fmt::print("{1}Proceed with caution. {2}Do you still wanna play? [y,n]{0}\n", RESET, WHITE, RED);
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
        MainMenuRPC();
        ClearScreen();
        Div();
        fmt::print("{1}{2}              __  _ __  _          ___ {0}\n", RESET, LAVENDER, BOLD);
        fmt::print("{1}{2}  ___  ____  / /_(_) /_(_)__  ____|__ \\{0}\n", RESET, LAVENDER, BOLD);
        fmt::print("{1}{2} / _ \\/ __ \\/ __/ / __/ / _ \\/ ___/_/ /{0}\n", RESET, LAVENDER, BOLD);
        fmt::print("{1}{2}/  __/ / / / /_/ / /_/ /  __(__  ) __/ {0}\n", RESET, LAVENDER, BOLD);
        fmt::print("{1}{2}\\___/_/ /_/\\__/_/\\__/_/\\___/____/____/ {0}\n", RESET, LAVENDER, BOLD);
        fmt::print("{1}                  A game by norbcodes.{0}\n\n", RESET, DARK_GRAY);
        fmt::print("{1}Pick an option:{0}\n\n", RESET, WHITE);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Play{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN);
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Gameplay Info{0}\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER);
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}Datapacks{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, PINK);
        fmt::print("{3}[{0}{2}{1}4{0}{3}]{0} {4}Quit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        EndDiv();

        uint32_t option = WaitForNumkey();

        if (option == 4)
        {
            ClearScreen();
            Div();
            fmt::print("{1}Confirm exit? [y,n]{0}\n\n", RESET, RED);
            std::cout << GetExitMsg() << std::endl;
            EndDiv();

            if (BinaryChoice())
            {
                ClearScreen();
                Credits();
                SleepSeconds(2);
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
            DifficultyPicker();
        }
        // INFO SECTION
        else if (option == 2)
        {
            GameplayInfoSec();
        }
        // DATAPACK VIEW
        else if (option == 3)
        {
            DatapackViewer(*Datapacks);
        }
        else
        {
            continue;
        }
    }

    DestroyRPC();
    GlobalSettings->Save(*GameArguments);

    return 0;
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0