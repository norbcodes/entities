// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <string>
#include <ctime>
#include <fmt/format.h>

#include "colors.hpp"
#include "user_settings.hpp"
#include "rng.hpp"

#define MORNING_START       4
#define MORNING_END         11
#define AFTERNOON_START     12
#define AFTERNOON_END       17
#define EVENING_START       18
#define EVENING_END         22
#define EARLY_NIGHT_START   23
#define EARLY_NIGHT_END     2

const std::string GetGreeting(const UserSettingsClass& user_settings)
{
    std::time_t now = std::time(0);
    std::tm* local_time = std::localtime(&now);
    // Yay
    // Check
    if (MORNING_START <= local_time->tm_hour && local_time->tm_hour <= MORNING_END)
    {
        // Mowning
        switch (rng(0,2))
        {
            case 0:
                return fmt::format("{1}Good morning, {3}{4}{2}{0}{1}. Ready to kill?{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 1:
                return fmt::format("{1}Good morning, {3}{4}{2}{0}{1}. Grab a coffee and crush some entities.{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 2:
                return fmt::format("{1}Good morning, {3}{4}{2}{0}{1}. Rise and shine!{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
        }
    }
    else if (AFTERNOON_START <= local_time->tm_hour && local_time->tm_hour <= AFTERNOON_END)
    {
        switch (rng(0,2))
        {
            case 0:
                return fmt::format("{1}Good afternoon, {3}{4}{2}{0}{1}. Back for more blood.{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 1:
                return fmt::format("{1}Good afternoon, {3}{4}{2}{0}{1}. Today's lunch: Entities{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 2:
                return fmt::format("{1}Good afternoon, {3}{4}{2}{0}{1}. I would really go for a nap now...{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
        }
    }
    else if (EVENING_START <= local_time->tm_hour && local_time->tm_hour <= EVENING_END)
    {
        switch (rng(0,2))
        {
            case 0:
                return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. 5 minutes until bedtime.{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 1:
                return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. Entities are sleepy now, surprise attack!{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 2:
                return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. *{5}Yawn{0}{1}*{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD, ITALIC);
        }
    }
    else if (EARLY_NIGHT_START <= local_time->tm_hour && local_time->tm_hour <= EARLY_NIGHT_END)
    {
        return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. Can't sleep yet?{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
    }
    else if (local_time->tm_hour == 3)
    {
        switch (rng(0,2))
        {
            case 0:
                return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. Spooky time!{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 1:
                return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. The line between mortal and the other side blurs...{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
            case 2:
                return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. Something feels off..{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD);
        }
    }
    // Make the compiler shut up
    // This will never show up sooooooo
    return fmt::format("{1}Good evening, {3}{4}{2}{0}{1}. ################{5}{0}", RESET, WHITE, user_settings.GetUsername(), BLUE, BOLD, local_time->tm_hour);
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0