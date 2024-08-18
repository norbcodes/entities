// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <iostream>
#include <fmt/core.h>

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

void GameplayInfoSec()
{
    while (true)
    {
        ClearScreen();
        Div();
        fmt::print("{1}Gameplay Info!{0}\n\n", RESET, GOLD);
        // Print options
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}Tips and Tricks{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, PINK);
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}Exit{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED);
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
            break;
        }
        else
        {
            continue;
        }
    }
}