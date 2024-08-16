// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <iostream>
#include <cstdint>
#include <random>

#include "colors.hpp"
#include "version.hpp"

void ClearScreen()
{
    // Funky
    std::cout << "\x1b[2J\x1b[1;1H";
}

void Div()
{
    std::cout << DARK_GRAY(BOLD_IN("------------------------------------------------------------------------")) << std::endl;
}

void Credits()
{
    Div();
    std::cout << GOLD(ITALIC_IN("DEM CREDITS!!!!")) << std::endl << std::endl;
    std::cout << GOLD(BOLD_IN("Game")) + WHITE(" by ") + BLUE(BOLD_IN("Norb")) << std::endl;
    std::cout << HOT_PINK(BOLD_IN("Coded")) + WHITE(" in ") + GREEN(BOLD_IN("C++")) << std::endl;
    std::cout << WHITE("v1.0 coded in about 2 days.\n") + DARK_GRAY("(As of writting the credits, Discord says I spent 6 hours on VScode)") << std::endl;
    std::cout << BLUE("These fine colors picked out using ") + BLUE(BOLD_IN("rgbcolorcode.com")) + BLUE("! B)") << std::endl;
    std::cout << PURPLE("Check out entity1 and the homepage at ") + PURPLE(BOLD_IN("github.com/norbcodes/entities")) << std::endl;
    std::cout << std::endl << DARK_GRAY("entities2.cpp version ") + DARK_GRAY(ENTITIES2_VER) + DARK_GRAY(" compiled at ") + DARK_GRAY(__DATE__) + " " + DARK_GRAY(__TIME__) + " ;)" << std::endl;
    Div();
}