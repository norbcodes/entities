// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file gameplay_info.cpp
 * \author norbcodes
 * \brief Info... About the game.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \details Provides a neat function that can interactively<br>
 *          display information, guides, tips and tricks, and so on.
 */

#include <iostream>
#include <fmt/core.h>

#include "status_constants.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "keyboard.hpp"

static void TipsNTricks()
{
    ClearScreen();
    Div();
    fmt::print("{1}{2}TIPS 'N' TRICKS{0}\n\n", RESET, GOLD, BOLD);
    fmt::print("{1}- You can use skip a round by choosing neither 0, 1, 2, 3 or 4.{0}\n", RESET, WHITE);
    fmt::print("{1}- If need be, you can skip a round to recharge your energy.{0}\n", RESET, WHITE);
    fmt::print("{1}- The AI will try to attack if it has more than 60 HP.{0}\n", RESET, WHITE);
    EndDiv();
    BlockUntilEnter();
}

static void Statuses()
{
    ClearScreen();
    Div();
    fmt::print("{1}{2}STATUSES{0} {4}{3}and what they do...{0}\n\n", RESET, GOLD, BOLD, ITALIC, BLUE);
    fmt::print("{2}{3}AutoHeal{0}\n   {4}At the start of a {5}new round{0}, the entity that{0}\n   {4}has {5}their turn will recieve {6}{3}+{1}HP of health.{0}\n", RESET, AUTO_HEAL_AMOUNT, GREEN, BOLD, WHITE, UNDERLINE, PURPLE);
    fmt::print("{2}{1}IncreasedCrit{0}\n   {3}When an entity has this status, it has {4}about {5}~30%{0}\n   {3}of dealing a {4}critical attack{0}{3}, which deals{0}\n   {3}significantly {4}more damage.{0}\n", RESET, BOLD, RED, WHITE, UNDERLINE, PURPLE);
    fmt::print("{2}{1}Invis{0}\n   {3}When an entity has this status, there's{0}\n   {3}a {5}{4}~20%{0} {3}chance of an attacker {5}missing{0}\n   {3}{5}the attack when attacking this entity.{0}\n", RESET, BOLD, HOT_PINK, WHITE, PURPLE, UNDERLINE);
    fmt::print("{3}{2}Poison{0}\n   {4}At the start of a {5}new round{0}, the entity that{0}\n   {4}has {5}their turn will recieve {6}{3}-{1}HP of damage.{0}\n", RESET, POISON_AMOUNT, DARK_GREEN, BOLD, WHITE, UNDERLINE, PURPLE);
    fmt::print("{2}{1}Thorns{0}\n   {3}When an entity with this status is{0}\n   {3}attacked, {4}50% of the damage{0}{3} goes back to the {4}attacker.{0}\n", RESET, BOLD, TEAL, WHITE, UNDERLINE);
    fmt::print("{2}{1}Weakness{0}\n   {3}A weakened enemy has their HP and AR {4}{5}capped at 60 only.{0}\n   {3}Their energy replenishes {4}{5}75% less per round{0}{3}, too.{0}\n   {3}They also {4}{5}attack less{0}{3}. This status only lasts {6} rounds.{0}", RESET, BOLD, BROWN, WHITE, UNDERLINE, PURPLE, WEAKNESS_TIME_LEFT);
    EndDiv();
    BlockUntilEnter();
}

/**
 * \brief The gameplay info function.
 * \details An interactive menu that you can navigate to learn more about this game<br>
 *          how it plays, neat tips and trick, and more!
 */
void GameplayInfoSec()
{
    while (true)
    {
        ClearScreen();
        Div();
        fmt::print("{1}Gameplay Info!{0}\n\n", RESET, GOLD);
        // Print options
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Tips and Tricks{0}\n", RESET, BOLD, GOLD, DARK_GRAY, PINK);
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Statuses and what they do{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER);
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
        EndDiv();
        // Get optionnn
        Keyguard();
        uint32_t option = WaitForNumkey();
        // Yay
        if (option == 1)
        {
            TipsNTricks();
        }
        else if (option == 2)
        {
            Statuses();
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            continue;
        }
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0