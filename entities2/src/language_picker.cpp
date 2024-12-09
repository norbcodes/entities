// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file language_picker.cpp
 * \author norbcodes
 * \brief Smol function for changing language in the settings.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fmt/core.h>

#include "colors.hpp"
#include "utils.hpp"
#include "game_string_formatter.hpp"
#include "translation_engine.hpp"
#include "keyboard.hpp"

/**
 * \def MAX_RENDER_COUNT
 * \brief Amount of languages to display before needing to scroll.
 */
#define MAX_RENDER_COUNT    8

/**
 * \brief Under the hood, returns a language id that is chosen in this fancy user menu.
 * \param[in] GameTranslation Game translation system.
 * \return Language id.
 */
const std::string PickLanguage(const TranslationEngine& GameTranslation)
{
    ClearScreen();
    Div();
    fmt::print("{1}{2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.lang.loading"));
    EndDiv();

    std::vector<std::string> LangList;
    LangList.reserve(16);

    for (std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator i = GameTranslation.LangIteratorBegin(); i != GameTranslation.LangIteratorEnd(); i++)
    {
        LangList.emplace_back(i->first);
    }

    bool in_menu = true;
    int16_t selection = 0;
    int16_t scroll = 0;
    const int16_t lang_count = LangList.size();
    const int16_t scroll_max = lang_count - MAX_RENDER_COUNT;
    const bool scrollable = lang_count > MAX_RENDER_COUNT;

    while (in_menu)
    {
        ClearScreen();
        Div();
        fmt::print("{1}> {3}{4}{2}{0}\n\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.lang.select"), TEAL, UNDERLINE);
        fmt::print("{1}{2}{0}\n", RESET, WHITE, CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.options.lang.line1"), fmt::arg("lang", GameTranslation.GetTranslated("lang.name"))));
        fmt::print("{1}{2}{0}\n", RESET, WHITE, CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.options.lang.line2"), fmt::arg("lang_count", lang_count)));
        fmt::print("{1}{2}{0}\n\n", RESET, WHITE, GameTranslation.GetTranslated("menu.options.lang.line3"));
        fmt::print("{1}:: :: :: :: :: :: :: :: :: :: :: :: :: ::{0}\n", RESET, DARK_GRAY);
        // Yay now we print stuff
        // The compiler, for the first time since development and using this very same comparison elsewhere,
        // is COMPLAINING.                      THIS. WHY.
        for (int16_t i = 0; static_cast<size_t>(i) != LangList.size(); i++)
        {
            if (selection == i)
            {
                fmt::print("{1}{2}{3} ({4}){0}\n", RESET, WHITE_BACKGROUND, BLACK, GameTranslation.GetTranslated("lang.name", LangList[i]), GameTranslation.GetTranslated("lang.id", LangList[i]));
            }
            else
            {
                fmt::print("{1}{2} {3}({4}{5}{6}{0}{3}){0}\n", RESET, WHITE, GameTranslation.GetTranslated("lang.name", LangList[i]), DARK_GRAY, GOLD, BOLD, GameTranslation.GetTranslated("lang.id", LangList[i]));
            }
        }
        fmt::print("{1}:: :: :: :: :: :: :: :: :: :: :: :: :: ::{0}\n", RESET, DARK_GRAY);
        EndDiv();

        uint32_t option = GetArrowKey();

        if (option == LEFT_KEY)
        {
            break;
        }
        else if (option == UP_KEY)
        {
            if (selection - 1 < 0)
            {
                if (scroll - 1 < 0)
                {
                    continue;
                }
                scroll -= 1;
                continue;
            }
            selection -= 1;
        }
        else if (option == DOWN_KEY)
        {
            if (!scrollable)
            {
                if (selection + 1 == lang_count)
                {
                    continue;
                }
                selection += 1;
                continue;
            }
            if (selection + 1 > (MAX_RENDER_COUNT - 1))
            {
                if (scroll + 1 > scroll_max)
                {
                    continue;
                }
                scroll += 1;
                continue;
            }
            selection += 1;
        }
        else if (option == RIGHT_KEY)
        {
            return LangList[selection + scroll];
        }
    }

    return GameTranslation.GetCurrentLangId();
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0