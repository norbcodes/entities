// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file datapack_viewer.cpp
 * \author norbcodes
 * \brief Functions for viewing installed datapacks :3
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <fmt/core.h>

#include "colors.hpp"
#include "utils.hpp"
#include "keyboard.hpp"
#include "datapacks.hpp"
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"

/** 
 * \def MAX_RENDER_COUNT
 * \brief Amount of Datapacks listed at max.
 */
#define MAX_RENDER_COUNT 8

static void DatapackView(const Datapack& datapack, const TranslationEngine& GameTranslation)
{
    ClearScreen();
    Div();

    fmt::print("{1}< {2}{4}{3}{0}\n\n", RESET, WHITE, PINK, GameTranslation.GetTranslated("menu.datapacks.title2"), UNDERLINE);
    fmt::print("{1}{2}{0}\n", RESET, ORANGE, GameTranslation.GetTranslated("menu.datapacks.subtitle"));
    fmt::print("{1}   {3: <16} {2}{0}\n", RESET, WHITE, datapack.GetName(), GameTranslation.GetTranslated("menu.datapacks.name"));
    fmt::print("{1}   {3: <16} {2}{0}\n", RESET, WHITE, datapack.GetAuthor(), GameTranslation.GetTranslated("menu.datapacks.author"));
    fmt::print("{1}   {3: <16} {2}{0}\n", RESET, WHITE, datapack.GetDatapackId(), GameTranslation.GetTranslated("menu.datapacks.id"));
    fmt::print("{1}   {3: <16} {2}{0}\n\n", RESET, WHITE, datapack.GetDesc(), GameTranslation.GetTranslated("menu.datapacks.desc"));
    fmt::print("{1}{2} {3}{0}\n\n", RESET, WHITE, GameTranslation.GetTranslated("menu.datapacks.size"), datapack.GetFilesizeFormatted(GameTranslation));
    fmt::print("{1}{2}{0}\n", RESET, WHITE, GameTranslation.GetTranslated("general.enter_to_exit"));
    EndDiv();
    EndDiv();

    BlockUntilEnter();
}

/** 
 * \brief Datapack Viewer!
 * \param[in] datapacks An instance of DatapackEngine class, in const reference mode.
 * \param[in] GameTranslation Game Translation System, for localized strings.
 */
void DatapackViewer(const DatapackEngine& datapacks, const TranslationEngine& GameTranslation)
{
    ClearScreen();
    int16_t selection = 0;
    int16_t scroll = 0;
    const int16_t scroll_max = datapacks.DatapackCount() - MAX_RENDER_COUNT;
    const bool scrollable = datapacks.DatapackCount() > MAX_RENDER_COUNT;
    
    while (true)
    {
        ResetCursor();
        Div();
        // Print stuff
        fmt::print("{1}<{0} {2}{3}{4}{0}\n\n", RESET, WHITE, PINK, UNDERLINE, GameTranslation.GetTranslated("menu.datapacks.title"));
        fmt::print("{0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.datapacks.loaded"), fmt::arg("datapack_count", datapacks.DatapackCount())));
        fmt::print("{1}{2}{0}\n\n", RESET, WHITE, GameTranslation.GetTranslated("menu.datapacks.help1"));

        // Now comes the fun part!
        fmt::print("{1}:: :: :: :: :: :: :: :: :: :: :: :: :: ::{0}\n", RESET, DARK_GRAY);
        for (uint32_t i = 0; i != datapacks.DatapackCount() && i != MAX_RENDER_COUNT; i++)
        {
            // Print datapack info
            const Datapack& obj = datapacks.GetConstDatapackRef(i + scroll);
            if (!obj.LoadSuccessful())
            {
                fmt::print("{1}   {3} \"{2}\"{0}\n", RESET, RED, obj.GetPath(), GameTranslation.GetTranslated(obj.GetFailReason()));
                continue;
            }
            if (i == static_cast<uint32_t>(selection))
            {
                fmt::print("{1}{4}   {2: <10} {5} {3: <8}{0}\n", RESET, BG_WHITE, obj.GetName(), obj.GetAuthor(), BLACK, GameTranslation.GetTranslated("general.by"));
            }
            else
            {
                fmt::print("{1}   {2: <10} {4}{6}{0}{1}{5} {3: <8}{0}\n", RESET, WHITE, obj.GetName(), obj.GetAuthor(), DARK_GRAY, BOLD, GameTranslation.GetTranslated("general.by"));
            }
        }
        if (datapacks.DatapackCount() == 0)
        {
            fmt::print("{1}   {2}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.datapacks.empty"));
        }
        fmt::print("{1}:: :: :: :: :: :: :: :: :: :: :: :: :: ::{0}\n\n", RESET, DARK_GRAY);
        fmt::print("{1}{2}{0}\n", RESET, WHITE, MsgFormatterNoUser(GameTranslation.GetTranslated("menu.datapacks.info")));
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
                if (static_cast<uint32_t>(selection + 1) == datapacks.DatapackCount())
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
        else if (option == RIGHT_KEY && datapacks.DatapackCount() > 0)
        {
            if (datapacks.GetConstDatapackRef(selection + scroll).LoadSuccessful())
            {
                DatapackView(datapacks.GetConstDatapackRef(selection + scroll), GameTranslation);
            }
            ClearScreen();
        }
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0