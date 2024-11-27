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
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"

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
 * \param[in] GameTranslation Yes this is also localized
 */
void Credits(const TranslationEngine& GameTranslation)
{
    Div();
    fmt::print("{1}{2}{3}{0}\n\n", RESET, GOLD, ITALIC, GameTranslation.GetTranslated("credits.title1"));
    fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("credits.gameby")));
    fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("credits.writtenin")));
    fmt::print("{1}{3}{0}\n{2}{4}{0}\n", RESET, WHITE, DARK_GRAY, GameTranslation.GetTranslated("credits.moreinfo1"), GameTranslation.GetTranslated("credits.moreinfo2"));
    fmt::print("{1}{3} {2}rgbcolorcode.com{0}{1}! B){0}\n", RESET, BLUE, BOLD, GameTranslation.GetTranslated("credits.moreinfo3"));
    fmt::print("{1}{3} {2}github.com/norbcodes/entities{0}{1} :){0}\n\n", RESET, PURPLE, BOLD, GameTranslation.GetTranslated("credits.moreinfo4"));

    fmt::print("{1}{2}{0}\n", RESET, GOLD, GameTranslation.GetTranslated("credits.title2"));
    fmt::print("  {0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("credits.discordlib"), fmt::arg("name", "Discord")));
    fmt::print("  {0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("credits.fmtlib"), fmt::arg("name", "FMT")));
    fmt::print("  {0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("credits.pugilib"), fmt::arg("name", "Arseny Kapoulkine"), fmt::arg("name2", "Zeux")));
    fmt::print("  {0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("credits.arglib"), fmt::arg("name", "p-ranav")));
    fmt::print("  {0}\n\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("credits.jsonlib"), fmt::arg("name", "Nlohmann")));

    fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("credits.compiled")));
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