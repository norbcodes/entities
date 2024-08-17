// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

// Yep

#include <fmt/core.h>

#include "colors.hpp"
#include "rng.hpp"

#define EXIT_MSG_COUNT 10

namespace EntitiesExitMsg
{
    const std::string exit_msg[EXIT_MSG_COUNT] = {
        fmt::format("{1}Noooooo don't leave yet :<{0}", RESET, WHITE),
        #ifdef _WIN32
        fmt::format("{1}Are you sure? {2}Windows is much worse...{0}", RESET, WHITE, ITALIC),
        #endif
        #ifdef __linux__
        fmt::format("{1}Are you sure? {2}Linux is much worse...{0}", RESET, WHITE, ITALIC),
        #endif
        fmt::format("{1}The enemy still has 6 hp left!{0}", RESET, WHITE),
        fmt::format("{1}You leave now, you forfeit your kill count!{0}", RESET, WHITE),
        fmt::format("{1}Atleast you tried, can't argue with that.{0}", RESET, WHITE),
        fmt::format("{1}Don't go yet!{0}", RESET, WHITE),
        fmt::format("{1}Pssst, i'll give you 3 free powerups if you stay... ;){0}", RESET, WHITE),
        fmt::format("{1}Are you sure? It's dangerous outside...{0}", RESET, WHITE),
        fmt::format("{1}Tch, just go. Unworthy.{0}", RESET, WHITE),
        fmt::format("{1}Ok{0}", RESET, WHITE)
    };
}

const std::string& GetExitMsg()
{
    return EntitiesExitMsg::exit_msg[ rng(0, EXIT_MSG_COUNT - 1) ];
}