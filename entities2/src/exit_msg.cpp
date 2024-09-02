// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file exit_msg.cpp
 * \author norbcodes
 * \brief Exit messages! :D
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \details Code for those little whiny messages you see when you try to exit.
 */

// Yep

#include <fmt/core.h>

#include "colors.hpp"
#include "rng.hpp"

/**
 * \def EXIT_MSG_COUNT
 * \brief The number of exit messages.
 */
#define EXIT_MSG_COUNT 17

/**
 * \namespace E2_ExitMsg
 * \brief E2_ExitMsg game namespace.
 * \details Internal game namespace, stores a fixed length array of std::string's:<br>
 *          The actual exit messages. These also change depending on the platform<br>
 *          they were compiled on.<br><br>
 *          Variables inside of this namespace should not be used outside of this file (exit_msg.cpp)<br>
 */
namespace E2_ExitMsg
{
    static const std::string exit_msg[EXIT_MSG_COUNT] = {
        fmt::format("{1}Noooooo don't leave yet :<{0}", RESET, WHITE),

        #ifdef _WIN32
        fmt::format("{1}Are you sure? {2}Windows is much worse...{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}Of course, as if Windows is more fun!{0}", RESET, WHITE),
        fmt::format("{1}You know that Bill Gates approves of this game, right?{0}", RESET, WHITE),
        #endif // _WIN32

        #ifdef __APPLE__
        fmt::format("{1}Are you sure? {2}Mac is much worse...{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}Of course, as if Mac is more fun!{0}", RESET, WHITE),
        fmt::format("{1}You know that Steve Jobs approved of this game, right?{0}", RESET, WHITE),
        #endif // __APPLE__

        #ifdef __linux__
        fmt::format("{1}Are you sure? {2}Linux is much worse...{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}Of course, as if Linux is more fun!{0}", RESET, WHITE),
        fmt::format("{1}You know that Linus Torvalds approves of this game, right?{0}", RESET, WHITE),
        #endif // __linux__

        fmt::format("{1}The enemy still has 6 hp left!{0}", RESET, WHITE),
        fmt::format("{1}._.{0}", RESET, WHITE),
        fmt::format("{1}Huh? Why?{0}", RESET, WHITE),
        fmt::format("{1}You leave now, you forfeit your kill count!{0}", RESET, WHITE),
        fmt::format("{1}Atleast you tried, can't argue with that.{0}", RESET, WHITE),
        fmt::format("{1}Don't go yet!{0}", RESET, WHITE),
        fmt::format("{1}Pssst, i'll give you 3 free powerups if you stay... ;){0}", RESET, WHITE),
        fmt::format("{1}Are you sure? It's dangerous outside...{0}", RESET, WHITE),
        fmt::format("{1}Tch, just go. Unworthy.{0}", RESET, WHITE),
        fmt::format("{1}Ok{0}", RESET, WHITE),
        fmt::format("{1}Honey are you cheating on me with Java games?{0}", RESET, WHITE),
        // BFMV reference ;)
        fmt::format("{3}\"{1}{2}This is how it's been, how it always be...{0}{3}\"{0}", RESET, GOLD, BOLD, DARK_GRAY),
        // Prodigy reference ;)
        fmt::format("{1}\"{2}{3}We live, forevah! The time! Has come! We live, forevah!{0}{1}\"{0}", RESET, DARK_GRAY, LAVENDER, BOLD)
    };
}

/**
 * \brief Function that retrieves an exit message.
 * \return A constant reference to std::string, the actual exit message.
 */
const std::string& GetExitMsg()
{
    return E2_ExitMsg::exit_msg[ rng(0, EXIT_MSG_COUNT - 1) ];
}