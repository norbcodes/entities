// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file gameplay_loop.cpp
 * \author norbcodes
 * \brief The gameplay itself.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \hideincludegraph
 */

#include <cstdint>
#include <iostream>
#include <fmt/core.h>

#include "colors.hpp"
#include "entity_constants.hpp"
#include "entity.hpp"
#include "status_constants.hpp"
#include "status.hpp"
#include "energy_constants.hpp"
#include "energy.hpp"
#include "rng.hpp"
#include "utils.hpp"
#include "discord_rpc.hpp"
#include "sleep.hpp"
#include "keyboard.hpp"
#include "ai.hpp"
#include "pick_move.hpp"
#include "gen_moves.hpp"
#include "global_settings.hpp"
#include "user_settings.hpp"
#include "demo_system.hpp"
#include "cmd_args.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

static void GameOver(bool& picker_flag, bool& is_running, const std::string& username)
{
    fmt::print("{1}---<<< {3}{2}{5}{0} {1}dead. {4}{2}Enemy{0}{1} wins!!! >>>---{0}\n\n", RESET, WHITE, BOLD, BLUE, RED, username);
    fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
    fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Rematch!{0}\n", RESET, BOLD, GOLD, DARK_GRAY, HOT_PINK);
    EndDiv();

    uint32_t choice = WaitForNumkey();

    if (choice == 1)
    {
        picker_flag = false;
        is_running = false;
        return;
    }
    else if (choice == 2)
    {
        is_running = false;
        return;
    }
    else
    {
        picker_flag = false;
        is_running = false;
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

static void Victory(bool& picker_flag, bool& is_running, const std::string& username)
{
    fmt::print("{1}---<<< {4}{2}Enemy{0} {1}dead. {3}{2}{5}{0}{1} wins!!! >>>---{0}\n\n", RESET, WHITE, BOLD, BLUE, RED, username);
    fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
    fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Rematch!{0}\n", RESET, BOLD, GOLD, DARK_GRAY, HOT_PINK);
    EndDiv();

    uint32_t choice = WaitForNumkey();

    if (choice == 1)
    {
        picker_flag = false;
        is_running = false;
        return;
    }
    else if (choice == 2)
    {
        is_running = false;
        return;
    }
    else
    {
        picker_flag = false;
        is_running = false;
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

static void PlayerRound (
    bool& picker_flag, 
    bool& is_running, 
    bool& enemy_turn, 
    std::string& what_happened, 
    Entity* Enemy, 
    Entity* Player,
    uint8_t difficulty_scale,
    uint32_t* moves,
    uint32_t* move_types,
    double* energy_costs,
    UserSettingsClass& user_settings,
    uint8_t demo_mode,
    Demo* cur_demo
)
{
    ClearScreen();
    Div();

    if (Player->GetHealth() <= 0)
    {
        ///////////////////
        if (demo_mode == 1) { cur_demo->TimeEnd(); }
        ///////////////////
        if (demo_mode == 0 || demo_mode == 1)
        {
            GameOver(picker_flag, is_running, user_settings.GetUsername());
            user_settings.IncreaseGamesLost(1);
            user_settings.IncreaseTotalGames(1);
        }
        return;
    }

    fmt::print("{3}---<<< {1}{2}{4}'s{0} {3}turn! >>>---{0}\n", RESET, BLUE, BOLD, DARK_GRAY, user_settings.GetUsername());
    // Print history
    fmt::print("{2}What happened last round:{0}\n{1}{0}\n\n", RESET, what_happened, WHITE);
    what_happened = "";

    Player->UpdateStatuses(what_happened, false);

    // Print stats
    fmt::print("{1}{2}[{3}]{0}\n ", RESET, BLUE, BOLD, user_settings.GetUsername());
    PrintEntityStats(*Player);
    fmt::print("{1}{2}[ENEMY] {0}\n ", RESET, RED, BOLD);
    PrintEntityStats(*Enemy);
    fmt::print("\n");
    // Print energy bars
    PrintEnergyBar(*Player);
    PrintEnergyBar(*Enemy);
    fmt::print("\n");

    GenerateMoves(moves, move_types, energy_costs);
    fmt::print("{1}[{2}{3}5{0}{1}]{0} {1}[{5}{3} 10.0{0}{1}]{0}\t{4}Regenerate moves...{0}\n\n", RESET, DARK_GRAY, GOLD, BOLD, WHITE, BLUE);

    uint32_t picked_move;
    while (true)
    {
        fmt::print("{1}Choose your move. {2}{3}[1,2,3,4,5] (0 to exit)                                           {0}\n", RESET, WHITE, BOLD, GRAY);
        EndDiv();
        // Player
        ///////////////////
        if (demo_mode != 2)
        {
            picked_move = WaitForNumkey();
        }
        else
        {
            picked_move = cur_demo->GetMove();
            SleepMiliseconds(1500);
        }
        ///////////////////
        if (demo_mode == 1) { cur_demo->Capture(picked_move, false); }
        ///////////////////

        if (picked_move == 0)
        {
            fmt::print("{1}Do you really wanna end the battle? {2}{3}[y,n]                                                             {0}\n", RESET, RED, GRAY, BOLD);
            EndDiv();

            bool choice;

            if (demo_mode != 2)
            {
                choice = BinaryChoice();
            }
            else
            {
                uint32_t _m = cur_demo->GetMove();
                if (_m == 0x0f)
                {
                    choice = true;
                }
                else if (_m == 0x0e)
                {
                    choice = false;
                }
                SleepMiliseconds(1500);
            }

            if (choice)
            {
                is_running = false;
                picker_flag = false;
                ///////////////////
                if (demo_mode == 1) { cur_demo->Capture(0x0f, false); cur_demo->TimeEnd(); }
                ///////////////////
                break;
            }
            else
            {
                ///////////////////
                if (demo_mode == 1) { cur_demo->Capture(0x0e, false); }
                ///////////////////
                continue;
            }
        }

        picked_move--;
        
        if (picked_move > 4)
        {
            what_happened += fmt::format("{1}{2}{4}{0} {3}skipped the round.{0}", RESET, BLUE, BOLD, WHITE, user_settings.GetUsername());
            return;
        }

        // Check if Player has enough energy
        if (picked_move != 4)
        {
            if (energy_costs[picked_move] > Player->GetEnergy())
            {
                fmt::print("{1}Not enough energy!                                                            {0}\n", RESET, RED);
                continue;
            }

            break;
        }
        else
        {
            // reroll move
            if (Player->GetEnergy() >= REROLL_MOVE_COST)
            {
                Player->TakeEnergy(REROLL_MOVE_COST);
                what_happened = fmt::format("{1}{2}{4}{0}{3} rerolled their moves...{0}", RESET, BOLD, BLUE, WHITE, user_settings.GetUsername());
                PlayerRound(picker_flag, is_running, enemy_turn, what_happened, Enemy, Player, difficulty_scale, moves, move_types, energy_costs, user_settings, demo_mode, cur_demo);
                return;
            }
            else
            {
                fmt::print("{1}Not enough energy!                                                            {0}\n", RESET, RED);
                continue;
            }
        }
    }

    // if pick is not 0, 1, 2, 3, 4 = skip round
    if (picked_move > 4)
    {
        what_happened += fmt::format("{1}{2}{4}{0} {3}skipped the round.{0}", RESET, BLUE, BOLD, WHITE, user_settings.GetUsername());
        return;
    }

    PickMove(Player, Enemy, picked_move, moves, move_types, energy_costs, enemy_turn, what_happened, user_settings);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

static void EnemyRound (
    bool& picker_flag, 
    bool& is_running, 
    bool& enemy_turn, 
    std::string& what_happened, 
    Entity* Enemy, 
    Entity* Player,
    uint8_t difficulty_scale,
    uint32_t* moves,
    uint32_t* move_types,
    double* energy_costs,
    UserSettingsClass& user_settings,
    uint8_t demo_mode,
    Demo* cur_demo
)
{
    ClearScreen();
    Div();

    if (Enemy->GetHealth() <= 0)
    {
        ///////////////////
        if (demo_mode == 1) { cur_demo->TimeEnd(); }
        ///////////////////
        if (demo_mode == 0 || demo_mode == 1)
        {
            Victory(picker_flag, is_running, user_settings.GetUsername());
            user_settings.IncreaseGamesWon(1);
            user_settings.IncreaseTotalGames(1);
        }
        return;
    }

    fmt::print("{3}---<<< {1}{2}Enemy's{0} {3}turn! >>>---{0}\n", RESET, RED, BOLD, DARK_GRAY);
    // Print history
    fmt::print("{2}What happened last round:{0}\n{1}{0}\n\n", RESET, what_happened, WHITE);
    what_happened = "";

    Enemy->UpdateStatuses(what_happened, true);

    // Print stats
    fmt::print("{1}{2}[{3}]{0}\n ", RESET, BLUE, BOLD, user_settings.GetUsername());
    PrintEntityStats(*Player);
    fmt::print("{1}{2}[ENEMY] {0}\n ", RESET, RED, BOLD);
    PrintEntityStats(*Enemy);
    fmt::print("\n");
    // Print energy bars
    PrintEnergyBar(*Player);
    PrintEnergyBar(*Enemy);
    fmt::print("\n");

    GenerateMoves(moves, move_types, energy_costs);
    fmt::print("\n");

    uint32_t picked_move;

    if (demo_mode == 2)
    {
        picked_move = cur_demo->GetMove() - 1;
    }
    else
    {
        picked_move = AiChoose(moves, move_types, energy_costs, *Player, *Enemy, difficulty_scale);
    }
    
    ///////////////////
    if (demo_mode == 1) { cur_demo->Capture(picked_move + 1, true); }
    ///////////////////

    // Print random num
    // this bugs out completely on Linux
    #ifndef __linux__
    for (uint32_t i = 0; i != 20000; i++)
    {
        fmt::print("{1}{2}The AI is thinking... {3}{0}\n", RESET, GOLD, ITALIC, rng(1, 4));
        EndDivNoNewl();
    }
    #endif // __linux__

    fmt::print("{1}{2}The AI is thinking... {3}{0}\n", RESET, GOLD, ITALIC, picked_move + 1);
    EndDiv();
    SleepSeconds(2);

    // if pick is not 0, 1, 2, 3 or 9 = skip round
    if (picked_move > 3 && picked_move != 9)
    {
        what_happened += fmt::format("{2}{3}Enemy {1}skipped the round.{0}", RESET, WHITE, RED, BOLD);
        return;
    }

    PickMove(Enemy, Player, picked_move, moves, move_types, energy_costs, enemy_turn, what_happened, user_settings);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief The game loop.
 * \param[in] mode Difficulty.
 * \param[out] picker_flag External flag to break a loop inside DifficultyPicker()
 * \param[in] game_args Game CMD arguments.
 * \param[in] global_settings Global game settings.
 * \param[in] user_settings User settings.
 * \param[in] demo_mode 0 = No demo, proceed as normal; 1 = Recording
 */
void Game(uint32_t mode, bool& picker_flag, const GameArgs& game_args, const GlobalSettingsClass& global_settings, UserSettingsClass& user_settings, uint8_t demo_mode)
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

    // DEMO STUFF

    Demo* CurrentDemo = nullptr;

    if (demo_mode == 0)
    {
        SeedRNG();
    }
    else if (demo_mode == 1)
    {
        uint64_t _seed = static_cast<uint64_t>(rng(0, UINT32_MAX));
        SeedRNG(_seed);
        CurrentDemo = new Demo(_seed, user_settings.GetUsername(), mode);
    }
    // Create player and enemy
    // Heap alloc for funni
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
    std::string what_happened = fmt::format("{1}{2}The fights begins. Good luck {3}!{0}", RESET, RED, ITALIC, user_settings.GetUsername());

    ///////////////////
    if (demo_mode == 1) { CurrentDemo->TimeBegin(); }
    ///////////////////
    while (is_running)
    {
        if (global_settings.GetDiscordEnabled())
        {
            GameplayRPC(enemy_turn);
        }
        // Generate 4 options to choose from.
        // There are 4 types: Attack, Heal, Regen armor, Status
        uint32_t* moves = new uint32_t[4]{100, 100, 100, 100};
        uint32_t* move_types = new uint32_t[4]{100, 100, 100, 100};
        double* energy_costs = new double[4]{100.0, 100.0, 100.0, 100.0};

        if (enemy_turn)
        {
            EnemyRound(picker_flag, is_running, enemy_turn, what_happened, Enemy, Player, difficulty_scale, moves, move_types, energy_costs, user_settings, demo_mode, CurrentDemo);
        }
        else
        {
            PlayerRound(picker_flag, is_running, enemy_turn, what_happened, Enemy, Player, difficulty_scale, moves, move_types, energy_costs, user_settings, demo_mode, CurrentDemo);
        }

        // Increase energy
        Player->GiveEnergy(ENERGY_INC);
        Enemy->GiveEnergy(ENERGY_INC);

        enemy_turn = !enemy_turn;
        delete[] moves;
        delete[] move_types;
        delete[] energy_costs;
    }

    // Make sure to annihilate
    delete Player;
    delete Enemy;

    if (demo_mode == 1)
    {
        CurrentDemo->Save(MakeDemoName(game_args), game_args);
        delete CurrentDemo;
    }
}

/**
 * \brief The game loop, when playing back a demo.
 * \param[in] demo_path Path to a demo to playback.
 */
void DemoPlaybackGame(const std::string& demo_path)
{
    // The demo loads
    bool failbit = false;
    Demo* CurrentDemo = new Demo(demo_path, failbit);
    if (failbit)
    {
        return;
    }
    // Loaded properly
    // Seed RNG
    SeedRNG(CurrentDemo->GetSeed());
    // Wowie
    uint8_t difficulty_scale;
    if (CurrentDemo->GetDifficulty() == 1)
    {
        difficulty_scale = 0;
    }
    else if (CurrentDemo->GetDifficulty() == 2)
    {
        difficulty_scale = 2;
    }
    else if (CurrentDemo->GetDifficulty() == 3)
    {
        difficulty_scale = 4;
    }
    else if (CurrentDemo->GetDifficulty() == 4)
    {
        difficulty_scale = rng(0, 4);
    }

    // Copied all of it

    // Create player and enemy
    // Heap alloc for funni
    Entity* Player = new Entity(
        (CurrentDemo->GetDifficulty() == 4) ? rng(10, 200) : PLAYER_START_HP - difficulty_scale * HEALTH_F,
        (CurrentDemo->GetDifficulty() == 4) ? rng(10, 200) : PLAYER_START_AR - difficulty_scale * ARMOR_F
    );
    Entity* Enemy = new Entity(
        (CurrentDemo->GetDifficulty() == 4) ? rng(10, 200) : ENEMY_START_HP + difficulty_scale * HEALTH_F,
        (CurrentDemo->GetDifficulty() == 4) ? rng(10, 200) : ENEMY_START_AR + difficulty_scale * ARMOR_F
    );
    // Yes, it literally rigs the game against you

    // Gameplay loop
    bool is_running = true;
    bool enemy_turn = false;  // true = Enemy, false = Player
    std::string what_happened = fmt::format("{1}{2}The fights begins. Good luck {3}!{0}", RESET, RED, ITALIC, CurrentDemo->GetUsername());

    // Fake picker_flag
    bool picker_flag = true;
    // UserSettingsClass "husk", doesn't save, just exists so this can work
    UserSettingsClass* user_settings = new UserSettingsClass(CurrentDemo->GetUsername());

    while (is_running)
    {
        // Generate 4 options to choose from.
        // There are 4 types: Attack, Heal, Regen armor, Status
        uint32_t* moves = new uint32_t[4]{100, 100, 100, 100};
        uint32_t* move_types = new uint32_t[4]{100, 100, 100, 100};
        double* energy_costs = new double[4]{100.0, 100.0, 100.0, 100.0};

        if (enemy_turn)
        {
            EnemyRound(picker_flag, is_running, enemy_turn, what_happened, Enemy, Player, difficulty_scale, moves, move_types, energy_costs, *user_settings, 2, CurrentDemo);
        }
        else
        {
            PlayerRound(picker_flag, is_running, enemy_turn, what_happened, Enemy, Player, difficulty_scale, moves, move_types, energy_costs, *user_settings, 2, CurrentDemo);
        }

        // Increase energy
        Player->GiveEnergy(ENERGY_INC);
        Enemy->GiveEnergy(ENERGY_INC);

        enemy_turn = !enemy_turn;
        delete[] moves;
        delete[] move_types;
        delete[] energy_costs;
    }

    // Make sure to annihilate
    delete Player;
    delete Enemy;
    delete CurrentDemo;
    delete user_settings;

    fmt::print("\n\n\n{1}Press enter to continue.{0}", RESET, WHITE);
    BlockUntilEnter();
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0