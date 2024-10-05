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
#include <fmt/core.h>

#include "colors.hpp"
#include "rng.hpp"

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
    /**
     * \var std::vector<std::string> exit_msg
     * \brief A dynamic array of exit messages. You can add more via Datapacks.
     */
    std::vector<std::string> exit_msg = {
        fmt::format("{1}Noooooo don't leave yet :<{0}", RESET, WHITE),

        #ifdef _WIN32
        fmt::format("{1}Are you sure? {2}Windows is much worse...{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}Of course, as if Windows is more fun!{0}", RESET, WHITE),
        fmt::format("{1}You know that Bill Gates approves of this game, right?{0}", RESET, WHITE),
        fmt::format("{1}Right right, don't forget to close the windows on the way out.{0}", RESET, WHITE),
        #endif // _WIN32

        #ifdef __APPLE__
        fmt::format("{1}Are you sure? {2}Mac is much worse...{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}Of course, as if Mac is more fun!{0}", RESET, WHITE),
        fmt::format("{1}You know that Steve Jobs approved of this game, right?{0}", RESET, WHITE),
        fmt::format("{1}An Apple a day keeps the wallet away.{0}", RESET, WHITE),
        #endif // __APPLE__

        #ifdef __linux__
        fmt::format("{1}Are you sure? {2}Linux is much worse...{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}Of course, as if Linux is more fun!{0}", RESET, WHITE),
        fmt::format("{1}You know that Linus Torvalds approves of this game, right?{0}", RESET, WHITE),
        fmt::format("{1}Linuwux{0}", RESET, WHITE),
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
        fmt::format("{1}\"{2}{3}We live, forevah! The time! Has come! We live, forevah!{0}{1}\"{0}", RESET, DARK_GRAY, LAVENDER, BOLD),
        fmt::format("{1}The prophecy says you'll continue playing. You dare break the prophecy?{0}", RESET, WHITE),
        // Tally Hall reference :)
        fmt::format("{3}\"{0}{1}{2}Do you like how I walk, do you like how I talk?\nDo you like how my face disintigrates into chalk?{0}{3}\"{0}", RESET, TEAL, BOLD, DARK_GRAY),
        fmt::format("{1}Thank you for downloading our malware :3{0}", RESET, WHITE),
        fmt::format("{1}Press 'y', and in your coffin you will lay!{0}", RESET, WHITE),
        fmt::format("{1}Don't be silly! Stay a while longer!{0}", RESET, WHITE),
        fmt::format("{1}The entities live in your walls{0}", RESET, WHITE),
        fmt::format("{1}I, norbcodes, live rent free in your ceiling{0}", RESET, WHITE),
        fmt::format("{1}Really?{0}", RESET, WHITE),
        fmt::format("{1}For reals?{0}", RESET, WHITE),
        fmt::format("{1}Babeeee! No!{0}", RESET, WHITE),
        fmt::format("{1}Is your fridge running...?{0}", RESET, WHITE),
        fmt::format("{1}Is your stove turned off...?{0}", RESET, WHITE),
        fmt::format("{1}What? Heap memory allocs scared you away?{0}", RESET, WHITE),
        fmt::format("{1}There's a chance a neutrino particle is\npassing through your skull right now.{0}", RESET, WHITE),
        fmt::format("{1}Let that sink in.{0}", RESET, WHITE),
        fmt::format("{1}Oh no! Your 'y' button just broke!{0}", RESET, WHITE),
        fmt::format("{1}LMFAOOOOO{0}", RESET, WHITE),
        fmt::format("{1}The outside is not real. Wake up. Wake up.{0}", RESET, WHITE),
        fmt::format("{1}Original entities more fun?{0}", RESET, WHITE),
        fmt::format("{1}:C{0}", RESET, WHITE),
        fmt::format("{1}I, norbcodes, do not approve!!! >:({0}", RESET, WHITE),
        fmt::format("{1}Maybe i'll break your keyboard then{0}", RESET, WHITE),
        fmt::format("{1}Come back soon. We're gonna be having a pizza party.{0}", RESET, WHITE),
        fmt::format("{1}Goodbye :3{0}", RESET, WHITE),
        fmt::format("{1}QwQ{0}", RESET, WHITE),
        // Dethklok reference :3
        fmt::format("{3}\"{0}{1}{2}Awaken, Awaken, Mustakrakish, rise!{0}{3}\"{0}", RESET, RED, BOLD, DARK_GRAY),
        fmt::format("{1}*{2}insert exit message here{0}{1}*{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}>:p{0}", RESET, WHITE),
        fmt::format("{1}Dude, just choose a lower difficulty. No need for drastic measures.{0}", RESET, WHITE),
        fmt::format("{1}*{2}insert threatening exit message here{0}{1}*{0}", RESET, WHITE, ITALIC),
        fmt::format("{1}Fine, get out of my face.{0}", RESET, WHITE),
        fmt::format("{1}Nuuuuu pwease staay :({0}", RESET, WHITE),
        fmt::format("{1}><>     <---- fish{0}", RESET, WHITE),
        fmt::format("{1}exit{0}{2}(){0}", RESET, RED, WHITE),
        fmt::format("{1}No syntax highlighting for you!!!{0}", RESET, WHITE),
        std::string("{red}{bold}Damn, my formatting broke{reset}"),
        // Metallica reference :O
        fmt::format("{3}\"{0}{1}{2}I'm the pain when you can't feel! Sad but true!{0}{3}\"{0}", RESET, PURPLE, BOLD, DARK_GRAY),
        fmt::format("{1}Do\n  not\n     exit,\n          PLEASE{0}", RESET, WHITE),
        fmt::format("{1}I hate you >:({0}", RESET, WHITE),
        fmt::format("{1}You KNOW that this is the best game ever made, right?{0}", RESET, WHITE),
        fmt::format("{1}Classic, just give up when you fail once.{0}", RESET, WHITE),
        fmt::format("{1};-;{0}", RESET, WHITE),
        fmt::format("{1}Go f##k yourself :) jkjk{0}", RESET, WHITE),
        fmt::format("{1}I will report your Github account if you leave >:({0}", RESET, WHITE)
    };
}

/**
 * \brief Function that retrieves an exit message.
 * \return A constant reference to std::string, the actual exit message.
 */
const std::string& GetExitMsg()
{
    return E2_ExitMsg::exit_msg[ rng(0, E2_ExitMsg::exit_msg.size() - 1) ];
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
 * \return The totala amount of exit messages.
 */
uint32_t GetExitMsgCount()
{
    return E2_ExitMsg::exit_msg.size();
}

/**
 * \brief Format custom exit messages defined in Datapacks.
 * \param[in] str The string to format.
 * \return Formatted string.
 */
std::string ExitMsgFormatter(const std::string& str)
{
    return fmt::format(
        str,
        fmt::arg("reset", RESET),
        fmt::arg("bold", BOLD),
        fmt::arg("faint", FAINT),
        fmt::arg("italic", ITALIC),
        fmt::arg("underline", UNDERLINE),
        fmt::arg("blinking", BLINKING),
        fmt::arg("red", RED),
        fmt::arg("blue", BLUE),
        fmt::arg("orange", ORANGE),
        fmt::arg("white", WHITE),
        fmt::arg("hot_pink", HOT_PINK),
        fmt::arg("gray", GRAY),
        fmt::arg("dark_gray", DARK_GRAY),
        fmt::arg("pink", PINK),
        fmt::arg("gold", GOLD),
        fmt::arg("green", GREEN),
        fmt::arg("purple", PURPLE),
        fmt::arg("dark_green", DARK_GREEN),
        fmt::arg("lavender", LAVENDER),
        fmt::arg("yellow", YELLOW),
        fmt::arg("teal", TEAL),
        fmt::arg("brown", BROWN)
    );
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0