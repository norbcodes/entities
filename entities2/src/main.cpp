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

#include "constants.hpp"
#include "colors.hpp"
#include "entity.hpp"
#include "ai.hpp"
#include "utils.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void Game(const std::string& mode)
{
    uint8_t difficulty_scale;
    // Is easy?
    if (mode == "easy")
    {
        difficulty_scale = 0;
    }
    // Is medium?
    else if (mode == "medium")
    {
        difficulty_scale = 1;
    }
    // Is hard?
    else if (mode == "hard")
    {
        difficulty_scale = 2;
    }
    // or no
    else 
    {
        std::cerr << RED(BOLD_IN("WRONG DIFFICULTY!!!! Or maybe bad spelling or something")) << std::endl;
        return;
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
        ClearScreen();
        Div();
        // Generate 4 options to choose from.
        // There are 4 types: Attack, Heal, Regen armor, Status
        uint8_t* moves = new uint8_t[4];
        uint8_t* move_types = new uint8_t[4];

        if (Player->GetHealth() <= 0)
        {
            std::cout << WHITE("---<<< ") + BLUE(BOLD_IN("Player ")) + WHITE("dead. ") + RED(BOLD_IN("Enemy ")) + WHITE("wins!!! >>>---") << std::endl << std::endl;
            std::cout << GRAY("Press enter to exit") << std::endl << std::endl;
            Div();
            std::cout << "\x1b[2A";
            std::string garbage;
            std::cin >> garbage;
            is_running = false;
            goto END_GAME;
        }

        if (Enemy->GetHealth() <= 0)
        {
            std::cout << WHITE("---<<< ") + RED(BOLD_IN("Enemy ")) + WHITE("dead. ") + BLUE(BOLD_IN("Player ")) + WHITE("wins!!! >>>---") << std::endl << std::endl;
            std::cout << GRAY("Press enter to exit") << std::endl << std::endl;
            Div();
            std::cout << "\x1b[2A";
            std::string garbage;
            std::cin >> garbage;
            is_running = false;
        }

        // Print header
        std::cout << DARK_GRAY("---<<< ") << (turn ? RED(BOLD_IN("Enemy's")) : BLUE(BOLD_IN("Player's"))) << DARK_GRAY(" turn! >>>---") << std::endl;

        std::cout << WHITE("What happened:\n") << what_happened << std::endl << std::endl;
        what_happened = "";

        switch (turn)
        {
            case true:
                Enemy->UpdateStatuses(what_happened, true);
                break;
            case false:
                Player->UpdateStatuses(what_happened, false);
                break;
        }
        // random switch go brrrr

        // Print stats
        std::cout << BLUE(BOLD_IN("[Player]\t"));
        PrintEntityStats(*Player);
        std::cout << RED (BOLD_IN("[Enemy] \t"));
        PrintEntityStats(*Enemy);
        std::cout << std::endl;

        for (int i = 0; i != 4; i++)
        {
            uint32_t type = rng(4);  // 4 option types
            switch (type)
            {
                case ATTACK:
                    move_types[i] = ATTACK;
                    moves[i] = ATTACK_F * (rng(8) + 1);
                    std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + RED("Attack!") + WHITE(" Deal ") + PURPLE(std::to_string((int)moves[i]) ) + WHITE(" damage to opponent.") << std::endl;
                    break;
                case HEAL:
                    move_types[i] = HEAL;
                    moves[i] = HEAL_F * (rng(5) + 1);
                    std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + GREEN("Heal! ") + WHITE("Gives you ") + PURPLE("+" + std::to_string((int)moves[i])) + WHITE(" HP") << std::endl;
                    break;
                case ARMOR:
                    move_types[i] = ARMOR;
                    moves[i] = ARM_F * (rng(9) + 1);
                    std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + BLUE("Regen armor") + WHITE("! Give you ") + PURPLE("+" + std::to_string((int)moves[i])) + WHITE(" AR") << std::endl;
                    break;
                case STATUS:
                    move_types[i] = STATUS;
                    moves[i] = rng(STATUS_C);
                    
                    switch (moves[i])
                    {
                        case AUTO_HEAL:
                            std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + GREEN("AutoHeal ") + WHITE("status! Gives you ") + PURPLE("+5") + WHITE(" HP when it's your turn") << std::endl;
                            break;
                        case INCR_CRIT:
                            std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + RED("IncreasedCrit") + WHITE(" status! Increased chance to deal a ") + RED("critical attack") << std::endl;
                            break;
                        case INVIS:
                            std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + HOT_PINK("Invis ") + WHITE("status! Opponent has a chance to ") + HOT_PINK("miss") << std::endl;
                            break;
                    }

                    break;
                default:
                    std::cerr << RED(BOLD_IN("wtf")) << std::endl;
                    is_running = !is_running;
                    break;
            }
        }

        std::cout << std::endl;

        // Yay!
        // Ask for input...
        if (!turn)
        {
            POINT:
            std::cout << WHITE("Choose your move.") + BOLD(GRAY(" [1,2,3,4,9] (9 to exit)                                           ")) << std::endl << std::endl;
            Div();
            std::cout << "\x1b[2A";
            // Player
            uint32_t picked_move;
            std::cin >> picked_move;

            if (picked_move == 9)
            {
                std::cout << RED("Do you really wanna end the battle?") + BOLD(GRAY(" [y,n]                                                             ")) << std::endl << std::endl;
                Div();
                std::cout << "\x1b[2A";
                std::string option;
                std::cin >> option;
                if (option == "y")
                {
                    is_running = false;
                    goto END_GAME;
                }
                else
                {
                    goto POINT;
                }
            }

            // if pick is not 0, 1, 2, 3 or 9 = skip round
            if (picked_move != 1 && picked_move != 2 && picked_move != 3 && picked_move != 4 && picked_move != 9)
            {
                what_happened += BLUE(BOLD_IN("Player ")) + WHITE("skipped the round.");
                goto SKIP_ROUND;
            }

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
                Player->GiveStatus(moves[picked_move]);
                switch (moves[picked_move])
                {
                    case AUTO_HEAL:
                        what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + GREEN("AutoHeal") + WHITE(".");
                        break;
                    case INCR_CRIT:
                        what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + RED("IncreasedCrit") + WHITE(".");
                        break;
                    case INVIS:
                        what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + HOT_PINK("Invis") + WHITE(".");
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
                Enemy->GiveStatus(moves[picked_move]);
                switch (moves[picked_move])
                {
                    case AUTO_HEAL:
                        what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + GREEN("AutoHeal") + WHITE(".");
                        break;
                    case INCR_CRIT:
                        what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + RED("IncreasedCrit") + WHITE(".");
                        break;
                    case INVIS:
                        what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + HOT_PINK("Invis") + WHITE(".");
                        break;
                }
            }
        }

        SKIP_ROUND:
        END_GAME:
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

int main()
{
    // force 256 
    std::cout << "\x1b[=19h" << std::endl;
    while (true)
    {
        ClearScreen();
        Div();
        std::cout << WHITE("Welcome to ") + GOLD(ITALIC_IN("entities2.cpp")) + WHITE("!!!!\nPlease, pick a difficulty:\n") << std::endl;
        std::cout << BLUE("easy") << std::endl;
        std::cout << ORANGE("medium") << std::endl;
        std::cout << RED("hard") << std::endl;
        std::cout << DARK_GRAY("Or type 'quit' to quit") << std::endl << std::endl;
        Div();
        std::cout << "\x1b[2A";
        std::string option;
        std::cin >> option;

        if (option == "quit")
        {
            ClearScreen();
            Credits();
            SleepSeconds(1);
            break;
        }

        // do
        Game(option);
    }

    return 0;
}