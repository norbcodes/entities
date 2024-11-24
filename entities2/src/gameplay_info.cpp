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
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"

static void TipsNTricks(const TranslationEngine& GameTranslation)
{
    ClearScreen();
    Div();
    fmt::print("{3}<{0} {1}{2}{4}{0}\n\n", RESET, GOLD, BOLD, WHITE, GameTranslation.GetTranslated("menu.ginfo.tiptitle"));
    fmt::print("{1}- {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.ginfo.tip1"));
    fmt::print("{1}- {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.ginfo.tip2"));
    fmt::print("{1}- {2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.ginfo.tip3"));
    EndDiv();
    BlockUntilEnter();
}

static void Statuses(const TranslationEngine& GameTranslation)
{
    ClearScreen();
    Div();
    fmt::print("{5}<{0} {1}{2}{6}{0} {4}{3}{7}{0}\n\n", RESET, GOLD, BOLD, ITALIC, BLUE, WHITE, GameTranslation.GetTranslated("menu.ginfo.statustitle1"), GameTranslation.GetTranslated("menu.ginfo.statustitle2"));
    fmt::print("{1}{2}{3}{0}\n   {4}\n", RESET, GREEN, BOLD, GameTranslation.GetTranslated("menu.ginfo.autoheal"), CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.ginfo.autoheal.info"), fmt::arg("autoheal_amount", AUTO_HEAL_AMOUNT)));
    fmt::print("{1}{2}{3}{0}\n   {4}\n", RESET, RED, BOLD, GameTranslation.GetTranslated("menu.ginfo.increasedcrit"), MsgFormatterNoUser(GameTranslation.GetTranslated("menu.ginfo.icrit.info")));
    fmt::print("{1}{2}{3}{0}\n   {4}\n", RESET, HOT_PINK, BOLD, GameTranslation.GetTranslated("menu.ginfo.invis"), MsgFormatterNoUser(GameTranslation.GetTranslated("menu.ginfo.invis.info")));
    fmt::print("{1}{2}{3}{0}\n   {4}\n", RESET, DARK_GREEN, BOLD, GameTranslation.GetTranslated("menu.ginfo.poison"), CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.ginfo.poison.info"), fmt::arg("poison_amount", POISON_AMOUNT)));
    fmt::print("{1}{2}{3}{0}\n   {4}\n", RESET, TEAL, BOLD, GameTranslation.GetTranslated("menu.ginfo.thorns"), MsgFormatterNoUser(GameTranslation.GetTranslated("menu.ginfo.thorns.info")));
    fmt::print("{1}{2}{3}{0}\n   {4}\n", RESET, BROWN, BOLD, GameTranslation.GetTranslated("menu.ginfo.weak"), CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.ginfo.weak.info"), fmt::arg("weakness_time", WEAKNESS_TIME_LEFT)));
    
    EndDiv();
    BlockUntilEnter();
}

/**
 * \brief The gameplay info function.
 * \details An interactive menu that you can navigate to learn more about this game<br>
 *          how it plays, neat tips and trick, and more!
 * \param[in] GameTranslation Game translation system, for localized strings.
 */
void GameplayInfoSec(const TranslationEngine& GameTranslation)
{
    while (true)
    {
        ClearScreen();
        Div();
        fmt::print("{2}<{0} {1}{3}{0}\n\n", RESET, GOLD, WHITE, GameTranslation.GetTranslated("menu.ginfo.title"));
        // Print options
        fmt::print("{3}[{0}{2}{1}1{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, PINK, GameTranslation.GetTranslated("menu.ginfo.tips"));
        fmt::print("{3}[{0}{2}{1}2{0}{3}]{0} {4}{5}{0}\n\n", RESET, BOLD, GOLD, DARK_GRAY, LAVENDER, GameTranslation.GetTranslated("menu.ginfo.status"));
        fmt::print("{3}[{0}{2}{1}3{0}{3}]{0} {4}{5}{0}\n", RESET, BOLD, GOLD, DARK_GRAY, RED, GameTranslation.GetTranslated("general.exit"));
        EndDiv();
        // Get optionnn
        uint32_t option = WaitForNumkey();
        // Yay
        if (option == 1)
        {
            TipsNTricks(GameTranslation);
        }
        else if (option == 2)
        {
            Statuses(GameTranslation);
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