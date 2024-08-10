// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

// Yep

#include "rng.hpp"

#define EXIT_MSG_COUNT 7

const char* exit_msg[EXIT_MSG_COUNT] = {
    "Noooooo don't leave yet :<",
    #ifdef _WIN32
    "Are you sure? Windows is much worse...",
    #endif
    #ifdef __linux__
    "Are you sure? Linux is much worse...",
    #endif
    "The enemy still has 6 hp left!",
    "You leave now, you forfeit your kill count!",
    "Atleast you tried, can't argue with that.",
    "Don't go yet!",
    "Pssst, i'll give you 3 free powerups if you stay... ;)"
};

const char* GetExitMsg()
{
    return exit_msg[ rng(EXIT_MSG_COUNT) ];
}