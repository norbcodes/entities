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

/** 
 * \def MAX_RENDER_COUNT
 * \brief Amount of Datapacks listed at max.
 */
#define MAX_RENDER_COUNT 8

static void DatapackView(const Datapack& datapack)
{
    ClearScreen();
    Div();

    fmt::print("{1}< {2}DATAPACK VIEW{0}\n\n", RESET, WHITE, PINK);
    fmt::print("{1}Metadata:{0}\n", RESET, ORANGE);
    fmt::print("{1}   Name:        {2}{0}\n", RESET, WHITE, datapack.GetName());
    fmt::print("{1}   Author:      {2}{0}\n", RESET, WHITE, datapack.GetAuthor());
    fmt::print("{1}   Description: {2}{0}\n", RESET, WHITE, datapack.GetDesc());

    EndDiv();

    BlockUntilEnter();
}

/** 
 * \brief Datapack Viewer!
 * \param[in] datapacks An instance of DatapackEngine class, in const reference mode.
 */
void DatapackViewer(const DatapackEngine& datapacks)
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
        fmt::print("{1}<{0} {2}{3}DATAPACKS{0}\n\n", RESET, WHITE, PINK, BOLD);
        fmt::print("{1}Currently loaded {2}{3}{0}{1} datapacks.{0}\n{1}Use up,down arrows to scroll.{0}\n\n", RESET, WHITE, PURPLE, datapacks.DatapackCount());

        // Now comes the fun part!
        fmt::print("{1}:: :: :: :: :: :: :: :: :: :: :: :: :: ::{0}\n", RESET, DARK_GRAY);
        for (uint32_t i = 0; i != datapacks.DatapackCount() && i != MAX_RENDER_COUNT; i++)
        {
            // Print datapack info
            const Datapack& obj = datapacks.GetConstDatapackRef(i + scroll);
            if (!obj.LoadSuccessful())
            {
                fmt::print("{1}   Failed to load: \"{2}\"{0}\n", RESET, RED, obj.GetPath());
                continue;
            }
            if (i == static_cast<uint32_t>(selection))
            {
                fmt::print("{1}{4}   {2: <10} by {3: <8}{0}\n", RESET, WHITE_BACKGROUND, obj.GetName(), obj.GetAuthor(), BLACK);
            }
            else
            {
                fmt::print("{1}   {2: <10} {4}by{0}{1}{5} {3: <8}{0}\n", RESET, WHITE, obj.GetName(), obj.GetAuthor(), DARK_GRAY, BOLD);
            }
        }
        if (datapacks.DatapackCount() == 0)
        {
            fmt::print("{1}   No datapacks!{0}\n", RESET, RED);
        }
        fmt::print("{1}:: :: :: :: :: :: :: :: :: :: :: :: :: ::{0}\n\n", RESET, DARK_GRAY);
        fmt::print("{1}Press left arrow to go back. Press right arrow to view a datapacks' info.{0}\n", RESET, WHITE);
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
        else if (option == RIGHT_KEY)
        {
            if (datapacks.GetConstDatapackRef(selection + scroll).LoadSuccessful())
            {
                DatapackView(datapacks.GetConstDatapackRef(selection + scroll));
            }
            ClearScreen();
        }
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0