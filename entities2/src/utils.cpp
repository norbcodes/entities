// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file utils.cpp
 * \author norbcodes
 * \brief Utility functions, for easier work.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <iostream>
#include <cstdint>
#include <random>
#include <fmt/core.h>

#include "colors.hpp"
#include "version.hpp"

/**
 * \brief Clear screen.
 */
void ClearScreen()
{
    // Funky
    fmt::print("\x1b[2J\x1b[1;1H");
}

/**
 * \brief Move cursor to the very upper left corner.
 */
void ResetCursor()
{
    fmt::print("\x1b[1;1H");
}

/**
 * \brief Visual divisor.
 */
void Div()
{
    fmt::print("{1}{2}────────────────────────────────────────────────────────────────────────{0}\n", RESET, DARK_GRAY, BOLD);
}

/**
 * \brief Visual divisor, usually at the bottom of the screen.
 */
void EndDiv()
{
    fmt::print("{1}{2}────────────────────────────────────────────────────────────────────────{0}\n\x1b[1F", RESET, DARK_GRAY, BOLD);
    // \x1b[1F moves cursor up by one line.
}

/**
 * \brief Same as EndDiv, except no newline.
 */
void EndDivNoNewl()
{
    fmt::print("{1}{2}────────────────────────────────────────────────────────────────────────{0}\x1b[1F", RESET, DARK_GRAY, BOLD);
}

/**
 * \brief Display credits.
 */
void Credits()
{
    Div();
    fmt::print("{1}{2}DEM CREDITS!!!!{0}\n\n", RESET, GOLD, ITALIC);
    fmt::print("{2}{3}Game{0} {1}by{0} {4}{3}Norb{0}\n", RESET, WHITE, GOLD, BOLD, BLUE);
    fmt::print("{1}{2}Coded{0} {3}in{0} {4}{2}C++{0}\n", RESET, HOT_PINK, BOLD, WHITE, GREEN);
    fmt::print("{1}v1.0 coded in about 2 days.{0}\n{2}(As of writting the credits, Discord says I spent 6 hours on VScode){0}\n", RESET, WHITE, DARK_GRAY);
    fmt::print("{1}These fine colors picked out using {2}rgbcolorcode.com{0}{1}! B){0}\n", RESET, BLUE, BOLD);
    fmt::print("{1}Check out entity1 and the homepage at {2}github.com/norbcodes/entities{0}{1} :){0}\n\n", RESET, PURPLE, BOLD);

    fmt::print("{1}{2}EXTERNAL LIBRARIES USED:{0}\n  {3}{4}discord-rpc{0} {5}:: {6}{2}Thanks to Discord :){0}\n", RESET, GOLD, ITALIC, BLUE, BOLD, DARK_GRAY, LAVENDER);
    fmt::print("  {1}{2}{{{3}f{4}m{5}t{6}}}{0} {7}::{0} {8}{9}Thanks to the entire FMT lib team!! :P{0}\n", RESET, BOLD, RED, ORANGE, YELLOW, GREEN, BLUE, DARK_GRAY, ITALIC, HOT_PINK);
    fmt::print("  {1}{2}pugi{0}{3}{2}xml{0} {4}::{0} {5}{6}Thanks to Arseny Kapoulkine (a.k.a Zeux on github)!! :3{0}\n\n", RESET, WHITE, BOLD, BROWN, DARK_GRAY, PINK, ITALIC);

    fmt::print("{4}entities2.cpp version {1} compiled at {2} {3} ;){0}\n", RESET, ENTITIES2_VER, __DATE__, __TIME__, DARK_GRAY);
    Div();
}

/**
 * \brief Terminal bell.
 */
void TerminalBell()
{
    #ifdef __ENTITIES2_TERMINAL_BELL__
    // ¯\_(ツ)_/¯
    fmt::print("\a");
    #endif // __ENTITIES2_TERMINAL_BELL__
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0