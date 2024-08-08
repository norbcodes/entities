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

#ifdef _WIN32
#include "windows.h"
#endif

#include "constants.hpp"
#include "colors.hpp"
#include "entity.hpp"
#include "ai.hpp"
#include "utils.hpp"
#include "gen_moves.hpp"
#include "rng.hpp"

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
        difficulty_scale = 1;
    }
    else if (mode == "3")
    {
        difficulty_scale = 2;
    }

    // Create player and enemy
    // Heap alloc for funnidifficulty_scale
    Entity* Player = new Entity(PLAYER_START_HP - difficulty_scale * HEALTH_F, PLAYER_START_AR - difficulty_scale * ARMOR_F);
    Entity* Enemy = new Entity(ENEMY_START_HP + difficulty_scale * HEALTH_F, ENEMY_START_AR + difficulty_scale * ARMOR_F);
    // Yes, it literally rigs the game against you

    // Gameplay loop
    bool is_running = true;
    bool turn = false;  // true = Enemy, false = Player
    std::string what_happened = RED(ITALIC_IN("The fight begins."));

    while (is_running)
    {
        // Generate 4 options to choose from.
        // There are 4 types: Attack, Heal, Regen armor, Status
        uint32_t* moves = new uint32_t[4]{100, 100, 100, 100};
        uint32_t* move_types = new uint32_t[4]{100, 100, 100, 100};

        while (true)  // ALWAYS BREAK OUT OF THIS.
        {
            ClearScreen();
            Div();

            if (Player->GetHealth() <= 0)
            {
                std::cout << WHITE("---<<< ") + BLUE(BOLD_IN("Player ")) + WHITE("dead. ") + RED(BOLD_IN("Enemy ")) + WHITE("wins!!! >>>---") << std::endl << std::endl;
                std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("1")) + DARK_GRAY("]") + RED(" Exit") << std::endl;
                std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("2")) + DARK_GRAY("]") + HOT_PINK(" Rematch!") << std::endl;
                std::cout << std::endl;
                Div();
                std::cout << "\x1b[2A";

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
                std::cout << WHITE("---<<< ") + RED(BOLD_IN("Enemy ")) + WHITE("dead. ") + BLUE(BOLD_IN("Player ")) + WHITE("wins!!! >>>---") << std::endl << std::endl;
                std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("1")) + DARK_GRAY("]") + RED(" Exit") << std::endl;
                std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("2")) + DARK_GRAY("]") + HOT_PINK(" Rematch!") << std::endl;
                std::cout << std::endl;
                Div();
                std::cout << "\x1b[2A";

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
            std::cout << DARK_GRAY("---<<< ") << (turn ? RED(BOLD_IN("Enemy's")) : BLUE(BOLD_IN("Player's"))) << DARK_GRAY(" turn! >>>---") << std::endl;

            std::cout << WHITE("What happened in the previous round:\n") << what_happened << std::endl << std::endl;
            what_happened = "";

            if (turn)  // if enemy turn
            {
                Enemy->UpdateStatuses(what_happened, true);
            }
            else  // if player turn turn
            {
                Player->UpdateStatuses(what_happened, false);
            }
            // random switch go brrrr

            // Print stats
            std::cout << BLUE(BOLD_IN("[Player]\t"));
            PrintEntityStats(*Player);
            std::cout << RED (BOLD_IN("[Enemy] \t"));
            PrintEntityStats(*Enemy);
            std::cout << std::endl;

            GenerateMoves(moves, move_types);

            std::cout << std::endl;

            // Yay!
            // Ask for input...
            if (!turn)
            {
                bool exit_flag = false;
                std::string _picked_move;
                while (true)
                {
                    std::cout << WHITE("Choose your move.") + BOLD(GRAY(" [1,2,3,4,9] (9 to exit)                                           ")) << std::endl << std::endl;
                    Div();
                    std::cout << "\x1b[2A";
                    // Player
                    std::cin >> _picked_move;

                    if (_picked_move == "9")
                    {
                        std::cout << RED("Do you really wanna end the battle?") + BOLD(GRAY(" [y,n]                                                             ")) << std::endl << std::endl;
                        Div();
                        std::cout << "\x1b[2A";
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
                    what_happened += BLUE(BOLD_IN("Player ")) + WHITE("skipped the round.");
                    break;
                }

                // The above checks should capture any garbage like ~2, fd, 5021qa
                // So we can safely convert to int
                uint32_t picked_move = std::stoi(_picked_move);

                picked_move--;

                if (move_types[picked_move] == ATTACK)
                {
                    EntityAttack(*Player, *Enemy, moves[picked_move], what_happened, turn);
                }
                else if (move_types[picked_move] == HEAL)
                {
                    Player->Heal(moves[picked_move]);
                    what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has healed ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" health.");
                }
                else if (move_types[picked_move] == ARMOR)
                {
                    Player->RegenArmor(moves[picked_move]);
                    what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has regen'd ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" armor.");
                }
                else if (move_types[picked_move] == STATUS)
                {
                    switch (moves[picked_move])
                    {
                        case AUTO_HEAL:
                            Player->GiveStatus(moves[picked_move]);
                            what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + GREEN("AutoHeal") + WHITE(".");
                            break;
                        case INCR_CRIT:
                            Player->GiveStatus(moves[picked_move]);
                            what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + RED("IncreasedCrit") + WHITE(".");
                            break;
                        case INVIS:
                            Player->GiveStatus(moves[picked_move]);
                            what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + HOT_PINK("Invis") + WHITE(".");
                            break;
                        case POISON:
                            Enemy->GiveStatus(moves[picked_move]);
                            what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has given ") + DARK_GREEN("Poison") + WHITE(" to ") + RED(BOLD_IN("Enemy")) + WHITE(".");
                            break;
                    }
                }
            }
            else
            {
                std::cout << GOLD(ITALIC_IN("The AI is thinking...")) << std::endl << std::endl;
                Div();
                std::cout << "\x1b[2A";
                // bot
                uint32_t picked_move = AiChoose(moves, move_types, *Player, *Enemy);
                // Print random num
                for (int i = 0; i != 19000; i++)
                {
                    std::cout << rng(3) + 1;
                    std::cout << "\x1B[1D";
                }
                std::cout << picked_move + 1;
                SleepSeconds(2);
                // Botttttt
                if (move_types[picked_move] == ATTACK)
                {
                    EntityAttack(*Enemy, *Player, moves[picked_move], what_happened, turn);
                }
                else if (move_types[picked_move] == HEAL)
                {
                    Enemy->Heal(moves[picked_move]);
                    what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has healed ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" health.");
                }
                else if (move_types[picked_move] == ARMOR)
                {
                    Enemy->RegenArmor(moves[picked_move]);
                    what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has regen'd ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" armor.");
                }
                else if (move_types[picked_move] == STATUS)
                {
                    switch (moves[picked_move])
                    {
                        case AUTO_HEAL:
                            Enemy->GiveStatus(moves[picked_move]);
                            what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + GREEN("AutoHeal") + WHITE(".");
                            break;
                        case INCR_CRIT:
                            Enemy->GiveStatus(moves[picked_move]);
                            what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + RED("IncreasedCrit") + WHITE(".");
                            break;
                        case INVIS:
                            Enemy->GiveStatus(moves[picked_move]);
                            what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + HOT_PINK("Invis") + WHITE(".");
                            break;
                        case POISON:
                            Player->GiveStatus(moves[picked_move]);
                            what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has given ") + DARK_GREEN("Poison") + WHITE(" to ") + BLUE(BOLD_IN("Player")) + WHITE(".");
                            break;
                    }
                }
            }

            break;
        }

        turn = !turn;
        delete[] moves;
        delete[] move_types;
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
        std::cout << WHITE("Select your difficulty:") << std::endl << std::endl;
        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("1")) + DARK_GRAY("]") + GREEN(" Easy") << std::endl;
        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("2")) + DARK_GRAY("]") + ORANGE(" Medium") << std::endl;
        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("3")) + DARK_GRAY("]") + RED(" Hard") << std::endl;
        std::cout << std::endl;
        Div();
        std::cout << "\x1b[2A";

        std::string choice;
        std::cin >> choice;

        if (choice == "1" || choice == "2" || choice == "3")
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
    
    while (true)
    {
        ClearScreen();
        Div();
        std::cout << WHITE("Welcome to ") + GOLD(ITALIC_IN("entities2.cpp")) + WHITE("!!!!\nPick an option:\n") << std::endl;
        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("1")) + DARK_GRAY("]") + GREEN(" Play") << std::endl;
        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN("2")) + DARK_GRAY("]") + RED(" Quit") << std::endl;
        std::cout << std::endl;
        Div();
        std::cout << "\x1b[2A";
        std::string option;
        std::cin >> option;

        if (option == "2")
        {
            ClearScreen();
            Credits();
            SleepSeconds(1);
            break;
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

    return 0;
}