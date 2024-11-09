// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file greetings.cpp
 * \author norbcodes
 * \brief Greetings stranger
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

// I don't like this file.

#include <ctime>
#include <vector>
#include <string>
#include <cstdint>
#include <fmt/format.h>

#include "greetings.hpp"
#include "colors.hpp"
#include "user_settings.hpp"
#include "rng.hpp"

/** 
 * \def MORNING_START
 * \brief Morning start hour.
 */
#define MORNING_START       4

/** 
 * \def MORNING_END
 * \brief Morning end hour.
 */
#define MORNING_END         11

/** 
 * \def AFTERNOON_START
 * \brief Afternoon start hour.
 */
#define AFTERNOON_START     12

/** 
 * \def AFTERNOON_END
 * \brief Afternoon end hour.
 */
#define AFTERNOON_END       17

/** 
 * \def EVENING_START
 * \brief Evening start hour.
 */
#define EVENING_START       18

/** 
 * \def EVENING_END
 * \brief Evening end hour.
 */
#define EVENING_END         22

/** 
 * \def EARLY_NIGHT_START
 * \brief Early night start hour.
 */
#define EARLY_NIGHT_START   23

/** 
 * \def EARLY_NIGHT_END
 * \brief Early night end hour.
 */
#define EARLY_NIGHT_END     2

/**
 * \namespace E2_Greets
 * \brief E2_Greets game namespace.
 * \details Internal game namespace, stores a fixed length array of std::string's:<br>
 *          The actual greeting messages.
 *          Variables inside of this namespace should not be used outside of this file (greetings.cpp)<br>
 */
namespace E2_Greets
{
    /**
     * \var std::vector<std::string> MorningGreets
     * \brief A dynamic array of morning greetings.
     */
    std::vector<std::string> MorningGreets;

    /**
     * \var std::vector<std::string> AfternoonGreets
     * \brief A dynamic array of afternoon greetings.
     */
    std::vector<std::string> AfternoonGreets;

    /**
     * \var std::vector<std::string> EveningGreets
     * \brief A dynamic array of evening greetings.
     */
    std::vector<std::string> EveningGreets;

    /**
     * \var std::vector<std::string> EarlyNightGreets
     * \brief A dynamic array of early night greetings.
     */
    std::vector<std::string> EarlyNightGreets;

    /**
     * \var std::vector<std::string> ThreeAmGreets
     * \brief A dynamic array of 3 am greetings.
     */
    std::vector<std::string> ThreeAmGreets;
};

/**
 * \brief Initializer for the greetings system.
 * \param[in] user_settings User game settings.
 */
void InitializeGreets(const UserSettingsClass& user_settings)
{
    // Morning
    E2_Greets::MorningGreets.emplace_back(fmt::format("{1}Good morning, {2}. Ready to kill?{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::MorningGreets.emplace_back(fmt::format("{1}Good morning, {2}. Grab a coffee and crush some entities.{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::MorningGreets.emplace_back(fmt::format("{1}Good morning, {2}. Rise and shine!{0}", RESET, WHITE, user_settings.GetUsername()));
    // Afternoon
    E2_Greets::AfternoonGreets.emplace_back(fmt::format("{1}Good afternoon, {2}. Back for more blood.{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::AfternoonGreets.emplace_back(fmt::format("{1}Good afternoon, {2}. Today's lunch: Entities{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::AfternoonGreets.emplace_back(fmt::format("{1}Good afternoon, {2}. I would really go for a nap now...{0}", RESET, WHITE, user_settings.GetUsername()));
    // Evening
    E2_Greets::EveningGreets.emplace_back(fmt::format("{1}Good evening, {2}. 5 minutes until bedtime.{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::EveningGreets.emplace_back(fmt::format("{1}Good evening, {2}. Entities are sleepy now, surprise attack!{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::EveningGreets.emplace_back(fmt::format("{1}Good evening, {3}. *{2}Yawn{0}{1}*{0}", RESET, WHITE, ITALIC, user_settings.GetUsername()));
    // Early Night
    E2_Greets::EarlyNightGreets.emplace_back(fmt::format("{1}Good evening, {2}. Can't sleep yet?{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::EarlyNightGreets.emplace_back(fmt::format("{1}Good evening, {2}. Was dinner yummy?{0}", RESET, WHITE, user_settings.GetUsername()));
    // 3 AM greets
    E2_Greets::ThreeAmGreets.emplace_back(fmt::format("{1}Good evening, {2}. Spooky time!{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::ThreeAmGreets.emplace_back(fmt::format("{1}Good evening, {2}. The line between mortal and the other side blurs...{0}", RESET, WHITE, user_settings.GetUsername()));
    E2_Greets::ThreeAmGreets.emplace_back(fmt::format("{1}Good evening, {2}. Something feels off..{0}", RESET, WHITE, user_settings.GetUsername()));
}

/**
 * \brief Return a greeting.
 * \return The greeting.
 */
const std::string GetGreeting()
{
    std::time_t now = std::time(0);
    std::tm* local_time = std::localtime(&now);
    // Yay
    // Check
    ///////////////////////////////////////////////////////////////////////////////////////////
    if (MORNING_START <= local_time->tm_hour && local_time->tm_hour <= MORNING_END)
    {
        return E2_Greets::MorningGreets[ rng(0, E2_Greets::MorningGreets.size() - 1) ];
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    else if (AFTERNOON_START <= local_time->tm_hour && local_time->tm_hour <= AFTERNOON_END)
    {
        return E2_Greets::AfternoonGreets[ rng(0, E2_Greets::AfternoonGreets.size() - 1) ];
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    else if (EVENING_START <= local_time->tm_hour && local_time->tm_hour <= EVENING_END)
    {
        return E2_Greets::EveningGreets[ rng(0, E2_Greets::EveningGreets.size() - 1) ];
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    else if (EARLY_NIGHT_START <= local_time->tm_hour || local_time->tm_hour <= EARLY_NIGHT_END)
    {
        // fixed this
        return E2_Greets::EarlyNightGreets[ rng(0, E2_Greets::EarlyNightGreets.size() - 1) ];
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    else if (local_time->tm_hour == 3)
    {
        return E2_Greets::ThreeAmGreets[ rng(0, E2_Greets::ThreeAmGreets.size() - 1) ];
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Make the compiler shut up
    // This will never show up sooooooo
    return fmt::format("{1}Uh...... {2}?{0}", RESET, WHITE, local_time->tm_hour);
}

/**
 * \brief Adds a greeting to one of the arrays.
 * \param[in] str The string.
 * \param[in] where The array.
 */
void AddGreetMsg(const std::string& str, uint32_t where)
{
    switch (where)
    {
        case G_MORNING:
            E2_Greets::MorningGreets.emplace_back(str);
            break;
        case G_AFTERNOON:
            E2_Greets::AfternoonGreets.emplace_back(str);
            break;
        case G_EVENING:
            E2_Greets::EveningGreets.emplace_back(str);
            break;
        case G_ENIGHT:
            E2_Greets::EarlyNightGreets.emplace_back(str);
            break;
        case G_3AM:
            E2_Greets::ThreeAmGreets.emplace_back(str);
            break;
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0