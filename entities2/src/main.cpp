// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

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

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void Game(const std::string& mode, uint32_t& picker_flag)
{
    // Wowie
    uint8_t difficulty_scale;
    if (mode == "1")
    {
        difficulty_scale = 0;
    }
    else if (mode == "2")
    {
        difficulty_scale = 2;
    }
    else if (mode == "3")
    {
        difficulty_scale = 4;
    }

    // Create player and enemy
    // Heap alloc for funnidifficulty_scale
    Entity* Player = new Entity(
        (mode == "4") ? rng(10, 200) : PLAYER_START_HP - difficulty_scale * HEALTH_F, 
        (mode == "4") ? rng(10, 200) : PLAYER_START_AR - difficulty_scale * ARMOR_F
    );
    Entity* Enemy = new Entity(
        (mode == "4") ? rng(10, 200) : ENEMY_START_HP + difficulty_scale * HEALTH_F, 
        (mode == "4") ? rng(10, 200) : ENEMY_START_AR + difficulty_scale * ARMOR_F
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

                uint32_t choice;
                std::cin >> choice;

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

                uint32_t choice;
                std::cin >> choice;

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
            }
            else
            {
                fmt::print("{3}---<<< {1}{2}Player's{0} {3}turn! >>>---{0}\n", RESET, BLUE, BOLD, DARK_GRAY);
            }

            // Print history
            fmt::print("{2}What happened last round:{0}\n{1}{0}\n\n", RESET, what_happened, WHITE);
            what_happened = "";

            if (enemy_turn)  // if enemy turn
            {
                Enemy->UpdateStatuses(what_happened, true);
            }
            else  // if player turn turn
            {
                Player->UpdateStatuses(what_happened, false);
            }
            // random switch go brrrr

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
                    std::string _picked_move;
                    while (true)
                    {
                        fmt::print("{1}Choose your move. {2}{3}[1,2,3,4,9] (9 to exit)                                           {0}\n", RESET, WHITE, BOLD, GRAY);
                        EndDiv();
                        // Player
                        std::cin >> _picked_move;

                        if (_picked_move == "9")
                        {
                            fmt::print("{1}Do you really wanna end the battle? {2}{3}[y,n]                                                             {0}\n", RESET, RED, GRAY, BOLD);
                            EndDiv();
                            std::string option;
                            std::cin >> option;
                            if (option == "y")
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
                    if (_picked_move != "1" && _picked_move != "2" && _picked_move != "3" && _picked_move != "4" && _picked_move != "9")
                    {
                        what_happened += fmt::format("{1}{2}Player{0} {3}skipped the round.{0}", RESET, BLUE, BOLD, WHITE);
                        break;
                    }

                    // The above checks should capture any garbage like ~2, fd, 5021qa
                    // So we can safely convert to int
                    uint32_t picked_move = std::stoi(_picked_move);

                    picked_move--;

                    // Check if Player has enough energy
                    if (energy_costs[picked_move] > Player->GetEnergy())
                    {
                        fmt::print("{1}Not enough energy!                                                            {0}\n", RESET, RED);
                        continue;
                    }

                    if (move_types[picked_move] == ATTACK)
                    {
                        EntityAttack(*Player, *Enemy, moves[picked_move], what_happened, enemy_turn);
                        Player->TakeEnergy(energy_costs[picked_move]);
                    }
                    else if (move_types[picked_move] == HEAL)
                    {
                        Player->Heal(moves[picked_move]);
                        what_happened += fmt::format("{2}{3}Player {4}healed {5}+{1}HP{0}", RESET, moves[picked_move], BLUE, BOLD, WHITE, PURPLE);
                        Player->TakeEnergy(energy_costs[picked_move]);
                    }
                    else if (move_types[picked_move] == ARMOR)
                    {
                        Player->RegenArmor(moves[picked_move]);
                        what_happened += fmt::format("{2}{3}Player {4}regen'd {5}+{1}AR{0}", RESET, moves[picked_move], BLUE, BOLD, WHITE, PURPLE);
                        Player->TakeEnergy(energy_costs[picked_move]);
                    }
                    else if (move_types[picked_move] == STATUS)
                    {
                        switch (moves[picked_move])
                        {
                            case AUTO_HEAL:
                                Player->GiveStatus(moves[picked_move]);
                                what_happened += fmt::format("{3}{4}Player{0} {1}has applied {2}Autoheal{1}.{0}", RESET, WHITE, GREEN, BLUE, BOLD);
                                Player->TakeEnergy(energy_costs[picked_move]);
                                break;
                            case INCR_CRIT:
                                Player->GiveStatus(moves[picked_move]);
                                what_happened += fmt::format("{3}{4}Player{0} {1}has applied {2}IncreasedCrit{1}.{0}", RESET, WHITE, RED, BLUE, BOLD);
                                Player->TakeEnergy(energy_costs[picked_move]);
                                break;
                            case INVIS:
                                Player->GiveStatus(moves[picked_move]);
                                what_happened += fmt::format("{3}{4}Player{0} {1}has applied {2}Invis{1}.{0}", RESET, WHITE, HOT_PINK, BLUE, BOLD);
                                Player->TakeEnergy(energy_costs[picked_move]);
                                break;
                            case POISON:
                                Enemy->GiveStatus(moves[picked_move]);
                                what_happened += fmt::format("{3}{4}Player{0} {1}has given {2}Poison{1} to {5}{4}Enemy{0}{1}.{0}", RESET, WHITE, DARK_GREEN, BLUE, BOLD, RED);
                                Player->TakeEnergy(energy_costs[picked_move]);
                                break;
                        }
                    }
                    break;
                }
            }
            else
            {
                fmt::print("{1}{2}The AI is thinking...{0}\n", RESET, GOLD, ITALIC);
                EndDiv();
                // bot
                uint32_t picked_move = AiChoose(moves, move_types, energy_costs, *Player, *Enemy);
                // Print random num
                for (int i = 0; i != 19000; i++)
                {
                    std::cout << rng(1, 4);
                    std::cout << "\x1B[1D";
                }
                std::cout << picked_move + 1;
                SleepSeconds(2);
                // Botttttt
                // if pick is not 0, 1, 2, 3 or 9 = skip round
                if (picked_move > 3 && picked_move != 9)
                {
                    what_happened += fmt::format("{2}{3}Enemy {1}skipped the round.{0}", RESET, WHITE, RED, BOLD);
                    break;
                }

                if (move_types[picked_move] == ATTACK)
                {
                    EntityAttack(*Enemy, *Player, moves[picked_move], what_happened, enemy_turn);
                    Enemy->TakeEnergy(energy_costs[picked_move]);
                }
                else if (move_types[picked_move] == HEAL)
                {
                    Enemy->Heal(moves[picked_move]);
                    what_happened += fmt::format("{2}{3}Enemy {4}healed {5}+{1}HP{0}", RESET, moves[picked_move], RED, BOLD, WHITE, PURPLE);
                    Enemy->TakeEnergy(energy_costs[picked_move]);
                }
                else if (move_types[picked_move] == ARMOR)
                {
                    Enemy->RegenArmor(moves[picked_move]);
                    what_happened += fmt::format("{2}{3}Enemy {4}regen'd {5}+{1}AR{0}", RESET, moves[picked_move], RED, BOLD, WHITE, PURPLE);
                    Enemy->TakeEnergy(energy_costs[picked_move]);
                }
                else if (move_types[picked_move] == STATUS)
                {
                    switch (moves[picked_move])
                    {
                        case AUTO_HEAL:
                            Enemy->GiveStatus(moves[picked_move]);
                            what_happened += fmt::format("{3}{4}Enemy{0} {1}has applied {2}Autoheal{1}.{0}", RESET, WHITE, GREEN, RED, BOLD);
                            Enemy->TakeEnergy(energy_costs[picked_move]);
                            break;
                        case INCR_CRIT:
                            Enemy->GiveStatus(moves[picked_move]);
                            what_happened += fmt::format("{3}{4}Enemy{0} {1}has applied {2}IncreasedCrit{1}.{0}", RESET, WHITE, RED, RED, BOLD);
                            Enemy->TakeEnergy(energy_costs[picked_move]);
                            break;
                        case INVIS:
                            Enemy->GiveStatus(moves[picked_move]);
                            what_happened += fmt::format("{3}{4}Enemy{0} {1}has applied {2}Invis{1}.{0}", RESET, WHITE, HOT_PINK, RED, BOLD);
                            Enemy->TakeEnergy(energy_costs[picked_move]);
                            break;
                        case POISON:
                            Player->GiveStatus(moves[picked_move]);
                            what_happened += fmt::format("{5}{4}Enemy{0} {1}has given {2}Poison{1} to {3}{4}Player{0}{1}.{0}", RESET, WHITE, DARK_GREEN, BLUE, BOLD, RED);
                            Enemy->TakeEnergy(energy_costs[picked_move]);
                            break;
                    }
                }
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

void DifficultyPicker()
{
    uint32_t picker_flag = true;
    while (picker_flag)
    {
        ClearScreen();
        Div();
        fmt::print("{1}Select your difficulty:{0}\n\n", RESET, WHITE);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}I kick Entities ass{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}I've seen worse{0}\n", RESET, BOLD, GOLD, DARK_GRAY, ORANGE);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Down with the Entities{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Random!{0}\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER);
        EndDiv();

        std::string choice;
        std::cin >> choice;

        if (choice == "1" || choice == "2" || choice == "3" || choice == "4")
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

    while (true)
    {
        MainMenuRPC();
        ClearScreen();
        Div();
        fmt::print("{1}Welcome to {2}{3}entities2.cpp{0}{1}!!!!{0}\n{1}Pick an option:{0}\n\n", RESET, WHITE, GOLD, ITALIC);
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Play{0}\n", RESET, BOLD, GOLD, DARK_GRAY, GREEN);
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Quit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        EndDiv();

        std::string option;
        std::cin >> option;

        if (option == "2")
        {
            ClearScreen();
            Div();
            fmt::print("{1}Confirm exit? [y,n]{0}\n\n", RESET, RED);
            std::cout << GetExitMsg() << std::endl;
            EndDiv();
            std::string confirm;
            std::cin >> confirm;

            if (confirm == "y")
            {
                ClearScreen();
                Credits();
                SleepSeconds(1);
                break;
            }
            else
            {
                continue;
            }
        }
        else if (option == "1")
        {
            // do
            DifficultyPicker();
        }
        else
        {
            continue;
        }
    }

    DestroyRPC();

    return 0;
}
