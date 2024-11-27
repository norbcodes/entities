// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file exit_msg.cpp
 * \author norbcodes
 * \brief Exit messages! :D
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \details Code for those little whiny messages you see when you try to exit.
 */

// Yep

#include <vector>
#include <string>
#include <fmt/core.h>

#include "colors.hpp"
#include "rng.hpp"
#include "translation_engine.hpp"

/**
 * \namespace E2_ExitMsg
 * \brief E2_ExitMsg game namespace.
 * \details Internal game namespace, stores a dynamic length array of std::string's:<br>
 *          The actual exit messages. These also change depending on the platform<br>
 *          they were compiled on.<br><br>
 *          Variables inside of this namespace should not be used outside of this file (exit_msg.cpp)<br>
 */
namespace E2_ExitMsg
{
    /**
     * \var std::vector<std::string> exit_msg
     * \brief A dynamic array of exit messages. You can add more via Datapacks.
     */
    std::vector<std::string> exit_msg = {
        "exit.message.1",

        #ifdef _WIN32
        "exit.message.win2",
        "exit.message.win3",
        "exit.message.win4",
        "exit.message.win5",
        #endif // _WIN32

        #ifdef __APPLE__
        "exit.message.mac2",
        "exit.message.mac3",
        "exit.message.mac4",
        "exit.message.mac5",
        #endif // __APPLE__

        #ifdef __linux__
        "exit.message.lix2",
        "exit.message.lix3",
        "exit.message.lix4",
        "exit.message.lix5",
        #endif // __linux__

        "exit.message.6",
        fmt::format("{1}._.{0}", RESET, WHITE),
        "exit.message.8",
        "exit.message.9",
        "exit.message.10",
        "exit.message.11",
        "exit.message.12",
        "exit.message.13",
        "exit.message.14",
        "exit.message.15",
        "exit.message.16",
        // BFMV reference ;)
        fmt::format("{1}\"{2}{3}This is how it's been, how it always be...{0}{1}\"{0}", RESET, DARK_GRAY, ORANGE, BOLD),
        // Prodigy reference ;)
        fmt::format("{1}\"{2}{3}We live, forevah! The time! Has come! We live, forevah!{0}{1}\"{0}", RESET, DARK_GRAY, LAVENDER, BOLD),
        "exit.message.19",
        // Tally Hall reference :)
        fmt::format("{1}\"{2}{3}Do you like how I walk, do you like how I talk?{4}Do you like how my face disintigrates into chalk?{0}{1}\"{0}", RESET, DARK_GRAY, TEAL, BOLD, '\n'),
        "exit.message.21",
        "exit.message.22",
        "exit.message.23",
        "exit.message.24",
        "exit.message.25",
        "exit.message.26",
        "exit.message.27",
        "exit.message.28",
        "exit.message.29",
        "exit.message.30",
        "exit.message.31",
        "exit.message.32",
        "exit.message.33",
        "exit.message.34",
        "exit.message.35",
        "exit.message.36",
        "exit.message.37",
        fmt::format("{1}:C{0}", RESET, WHITE),
        "exit.message.39",
        "exit.message.40",
        "exit.message.41",
        "exit.message.42",
        fmt::format("{1}QwQ{0}", RESET, WHITE),
        // Dethklok reference :3
        fmt::format("{1}\"{2}{3}Awaken, Awaken, Mustakrakish, rise!{0}{1}\"{0}", RESET, DARK_GRAY, RED, BOLD),
        "exit.message.45",
        fmt::format("{1}>:p{0}", RESET, WHITE),
        "exit.message.47",
        "exit.message.48",
        "exit.message.49",
        "exit.message.50",
        "exit.message.51",
        "exit.message.52",
        "exit.message.53",
        "exit.message.54",
        // Metallica reference :O
        fmt::format("{1}\"{2}{3}I'm the pain when you can't feel! Sad but true!{0}{1}\"{0}", RESET, DARK_GRAY, PURPLE, BOLD),
        "exit.message.56",
        "exit.message.57",
        "exit.message.58",
        "exit.message.59",
        fmt::format("{1};-;{0}", RESET, WHITE),
        "exit.message.61",
        "exit.message.62",
        fmt::format("{1}Blerp{0}", RESET, WHITE),
        "exit.message.64",
        "exit.message.65",
        fmt::format("{1}@_@{0}", RESET, WHITE),
        "exit.message.67",
        fmt::format("{1}AAAAAAAAAAAAAAAA{0}", RESET, WHITE),
        "", // 69th message. Nice.
        "exit.message.70",
        "exit.message.special"
    };
}

/**
 * \brief Function that retrieves an exit message.
 * \param[in] GameTranslation Game translation system, for localized strings.
 * \param[out] Was_Translated Assigned to 'true' if the returned string was translated.
 * \return A constant reference to std::string, the actual exit message.
 */
const std::string GetExitMsg(const TranslationEngine& GameTranslation, bool& Was_Translated)
{
    std::string random_pick = E2_ExitMsg::exit_msg[ rng(0, E2_ExitMsg::exit_msg.size() - 1) ];
    // Check if the exit message can be found in language registry
    if (GameTranslation.TranslationStringExists(random_pick))
    {
        Was_Translated = true;
        return GameTranslation.GetTranslated(random_pick);
    }
    else
    {
        Was_Translated = false;
        return random_pick;
    }
}

/**
 * \brief Add a new exit message! :3
 * \param[in] str The exit message to add.
 */
void AddExitMsg(const std::string& str)
{
    E2_ExitMsg::exit_msg.emplace_back(str);
}

/**
 * \brief Get the total amount of exit messages.
 * \return The total amount of exit messages.
 */
uint32_t GetExitMsgCount()
{
    return E2_ExitMsg::exit_msg.size();
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0