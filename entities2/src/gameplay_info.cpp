// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <iostream>
#include <fmt/core.h>

#include "status_constants.hpp"
#include "colors.hpp"
#include "utils.hpp"

static void TipsNTricks()
{
    ClearScreen();
    Div();
    fmt::print("{1}{2}Coming soon! :){0}\n", RESET, GOLD, BOLD);
    EndDiv();
    std::string g;
    std::cin >> g;
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
    EndDiv();
    std::string g;
    std::cin >> g;
}

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
        std::string option;
        std::cin >> option;
        // Yay
        if (option == "1")
        {
            TipsNTricks();
        }
        else if (option == "2")
        {
            Statuses();
        }
        else if (option == "3")
        {
            break;
        }
        else
        {
            continue;
        }
    }
}