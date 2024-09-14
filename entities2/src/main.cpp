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

#include "entity_constants.hpp"
#include "energy_constants.hpp"
#include "status_constants.hpp"
#include "move_constants.hpp"
#include "colors.hpp"
#include "entity.hpp"
#include "ai.hpp"
#include "utils.hpp"
#include "gen_moves.hpp"
#include "rng.hpp"
#include "exit_msg.hpp"
#include "sleep.hpp"
#include "energy.hpp"
#include "discord_rpc.hpp"
#include "pick_move.hpp"
#include "gameplay_info.hpp"
#include "keyboard.hpp"
#include "version.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief The game loop.
 * \param[in] mode Difficulty.
 * \param[out] picker_flag External flag to break a loop inside DifficultyPicker()
 */
void Game(uint32_t mode, uint32_t& picker_flag)
{
    // Wowie
    uint8_t difficulty_scale;
    if (mode == 1)
    {
        difficulty_scale = 0;
    }
    else if (mode == 2)
    {
        difficulty_scale = 2;
    }
    else if (mode == 3)
    {
        difficulty_scale = 4;
    }
    else if (mode == 4)
    {
        difficulty_scale = rng(0, 4);
    }

    // Create player and enemy
    // Heap alloc for funnidifficulty_scale
    Entity* Player = new Entity(
        (mode == 4) ? rng(10, 200) : PLAYER_START_HP - difficulty_scale * HEALTH_F, 
        (mode == 4) ? rng(10, 200) : PLAYER_START_AR - difficulty_scale * ARMOR_F
    );
    Entity* Enemy = new Entity(
        (mode == 4) ? rng(10, 200) : ENEMY_START_HP + difficulty_scale * HEALTH_F, 
        (mode == 4) ? rng(10, 200) : ENEMY_START_AR + difficulty_scale * ARMOR_F
    );
    // Yes, it literally rigs the game against you

    // Gameplay loop
    bool is_running = true;
    bool enemy_turn = false;  // true = Enemy, false = Player
    std::string what_happened = fmt::format("{1}{2}The fights begins.{0}", RESET, RED, ITALIC);

    while (is_running)
    {
        GameplayRPC(enemy_turn);
        // Generate 4 options to choose from.
        // There are 4 types: Attack, Heal, Regen armor, Status
        uint32_t* moves = new uint32_t[4]{100, 100, 100, 100};
        uint32_t* move_types = new uint32_t[4]{100, 100, 100, 100};
        double* energy_costs = new double[4]{100.0, 100.0, 100.0, 100.0};

        while (true)  // ALWAYS BREAK OUT OF THIS.
        {
            ClearScreen();
            Div();

            if (Player->GetHealth() <= 0)
            {
                fmt::print("{1}---<<< {3}{2}Player{0} {1}dead. {4}{2}Enemy{0}{1} wins!!! >>>---{0}\n\n", RESET, WHITE, BOLD, BLUE, RED);
                fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
                fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Rematch!{0}\n", RESET, BOLD, GOLD, DARK_GRAY, HOT_PINK);
                EndDiv();

                Keyguard();
                uint32_t choice = WaitForNumkey();

                if (choice == 1)
                {
                    picker_flag = false;
                    is_running = false;
                    break;
                }
                else if (choice == 2)
                {
                    is_running = false;
                    break;
                }
                else
                {
                    picker_flag = false;
                    is_running = false;
                    break;
                }
            }

            if (Enemy->GetHealth() <= 0)
            {
                fmt::print("{1}---<<< {4}{2}Enemy{0} {1}dead. {3}{2}Player{0}{1} wins!!! >>>---{0}\n\n", RESET, WHITE, BOLD, BLUE, RED);
                fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
                fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Rematch!{0}\n", RESET, BOLD, GOLD, DARK_GRAY, HOT_PINK);
                EndDiv();

                Keyguard();
                uint32_t choice = WaitForNumkey();

                if (choice == 1)
                {
                    picker_flag = false;
                    is_running = false;
                    break;
                }
                else if (choice == 2)
                {
                    is_running = false;
                    break;
                }
                else
                {
                    picker_flag = false;
                    is_running = false;
                    break;
                }
            }

            // Print header
            if (enemy_turn)
            {
                fmt::print("{3}---<<< {1}{2}Enemy's{0} {3}turn! >>>---{0}\n", RESET, RED, BOLD, DARK_GRAY);
                // Print history
                fmt::print("{2}What happened last round:{0}\n{1}{0}\n\n", RESET, what_happened, WHITE);
                what_happened = "";
                Enemy->UpdateStatuses(what_happened, true);
            }
            else
            {
                fmt::print("{3}---<<< {1}{2}Player's{0} {3}turn! >>>---{0}\n", RESET, BLUE, BOLD, DARK_GRAY);
                // Print history
                fmt::print("{2}What happened last round:{0}\n{1}{0}\n\n", RESET, what_happened, WHITE);
                what_happened = "";
                Player->UpdateStatuses(what_happened, false);
            }

            // Increase energy
            Player->GiveEnergy(ENERGY_INC);
            Enemy->GiveEnergy(ENERGY_INC);

            // Print stats
            fmt::print("{1}{2}[PLAYER]{0}\t", RESET, BLUE, BOLD);
            PrintEntityStats(*Player);
            fmt::print("{1}{2}[ENEMY] {0}\t", RESET, RED, BOLD);
            PrintEntityStats(*Enemy);
            fmt::print("\n");
            // Print energy bars
            PrintEnergyBar(*Player);
            PrintEnergyBar(*Enemy);
            fmt::print("\n");

            GenerateMoves(moves, move_types, energy_costs);

            std::cout << std::endl;

            // Yay!
            // Ask for input...
            if (!enemy_turn)
            {
                while (true)
                {
                    bool exit_flag = false;
                    uint32_t picked_move;
                    while (true)
                    {
                        fmt::print("{1}Choose your move. {2}{3}[0,1,2,3,4] (0 to exit)                                           {0}\n", RESET, WHITE, BOLD, GRAY);
                        EndDiv();
                        // Player
                        Keyguard();
                        picked_move = WaitForNumkey();

                        if (picked_move == 0)
                        {
                            fmt::print("{1}Do you really wanna end the battle? {2}{3}[y,n]                                                             {0}\n", RESET, RED, GRAY, BOLD);
                            EndDiv();
                            Keyguard();
                            if (BinaryChoice())
                            {
                                is_running = false;
                                picker_flag = false;
                                exit_flag = true;
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }

                        break;
                    }
                    

                    if (exit_flag)
                    {
                        break;
                    }

                    // if pick is not 0, 1, 2, 3 or 9 = skip round
                    if (picked_move != 1 && picked_move != 2 && picked_move != 3 && picked_move != 4 && picked_move != 0)
                    {
                        what_happened += fmt::format("{1}{2}Player{0} {3}skipped the round.{0}", RESET, BLUE, BOLD, WHITE);
                        break;
                    }

                    picked_move--;

                    // Check if Player has enough energy
                    if (energy_costs[picked_move] > Player->GetEnergy())
                    {
                        fmt::print("{1}Not enough energy!                                                            {0}\n", RESET, RED);
                        continue;
                    }

                    PickMove(Player, Enemy, picked_move, moves, move_types, energy_costs, enemy_turn, what_happened);

                    break;
                }
            }
            else
            {
                // bot
                uint32_t picked_move = AiChoose(moves, move_types, energy_costs, *Player, *Enemy, difficulty_scale);
                // Print random num
                for (int i = 0; i != 20000; i++)
                {
                    fmt::print("{1}{2}The AI is thinking... {3}{0}\n", RESET, GOLD, ITALIC, rng(1, 4));
                    EndDivNoNewl();
                }
                fmt::print("{1}{2}The AI is thinking... {3}{0}\n", RESET, GOLD, ITALIC, picked_move + 1);
                SleepSeconds(2);
                // Botttttt
                // if pick is not 0, 1, 2, 3 or 9 = skip round
                if (picked_move > 3 && picked_move != 9)
                {
                    what_happened += fmt::format("{2}{3}Enemy {1}skipped the round.{0}", RESET, WHITE, RED, BOLD);
                    break;
                }

                PickMove(Enemy, Player, picked_move, moves, move_types, energy_costs, enemy_turn, what_happened);

            }

            break;
        }

        enemy_turn = !enemy_turn;
        delete[] moves;
        delete[] move_types;
        delete[] energy_costs;
    }

    // Make sure to annihilate
    delete Player;
    delete Enemy;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Pick a difficulty...
 */
void DifficultyPicker()
{
    uint32_t picker_flag = true;
    while (picker_flag)
    {
        ClearScreen();
        Div();
        fmt::print("{1}Select your difficulty:{0}\n\n", RESET, WHITE);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}I kick Entities ass{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN);
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}I've seen worse{0}\n", RESET, BOLD, GOLD, DARK_GRAY, ORANGE);
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}Down with the Entities{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        fmt::print("{3}[{0}{2}{1}4{0}{3}]{0} {4}Random!{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER);
        fmt::print("{3}[{0}{2}{1}5{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        EndDiv();

        Keyguard();
        uint32_t choice = WaitForNumkey();

        if (choice == 5)
        {
            picker_flag = false;
            break;
        }
        else if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
        {
            Game(choice, picker_flag);
        }
        else
        {
            continue;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief The very entry point of the game, and the program as a whole.
 */
int main()
{
    #ifdef _WIN32
        // Create windows virtual cmd
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif

    InitializeRPC();

    #ifndef __ENTITIES2_DISABLE_UNSTABLE_WARNING__
        #if (ENTITIES2_VER_IS_DEV == 1)
            Div();
            fmt::print("{1}You are using a game build that is {2}still under Development!{0}\n", RESET, RED, BOLD);
            fmt::print("{1}Proceed with caution. {2}Do you still wanna play? [y,n]{0}\n", RESET, WHITE, RED);
            EndDiv();

            Keyguard();
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
        fmt::print("{1}Welcome to {2}{3}entities2.cpp{0}{1}!!!!{0}\n{1}Pick an option:{0}\n\n", RESET, WHITE, GOLD, ITALIC);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Play{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN);
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Gameplay Info{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER);
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}Quit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        EndDiv();

        Keyguard();
        uint32_t option = WaitForNumkey();

        if (option == 3)
        {
            ClearScreen();
            Div();
            fmt::print("{1}Confirm exit? [y,n]{0}\n\n", RESET, RED);
            std::cout << GetExitMsg() << std::endl;
            EndDiv();

            Keyguard();
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
        else
        {
            continue;
        }
    }

    DestroyRPC();

    return 0;
}