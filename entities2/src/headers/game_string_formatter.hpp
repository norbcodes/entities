// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file game_string_formatter.hpp
 * \author norbcodes
 * \brief Functions for formatting game strings.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <string>
#include <fmt/format.h>

#include "colors.hpp"
#include "version.hpp"
#include "user_settings.hpp"

/**
 * \def _body
 * \hideinitializer
 * \brief A quick macro often repeated in the 2 formatter functions and 2 templated formatter functions.
 */
#define _body   fmt::arg("entities2_ver", ENTITIES2_VER), \
                fmt::arg("nl", '\n'), \
                fmt::arg("compile_time", __TIME__), \
                fmt::arg("compile_date", __DATE__), \
                fmt::arg("reset", RESET), \
                fmt::arg("bold", BOLD), \
                fmt::arg("faint", FAINT), \
                fmt::arg("italic", ITALIC), \
                fmt::arg("underline", UNDERLINE), \
                fmt::arg("blinking", BLINKING), \
                fmt::arg("red", RED), \
                fmt::arg("blue", BLUE), \
                fmt::arg("orange", ORANGE), \
                fmt::arg("white", WHITE), \
                fmt::arg("hot_pink", HOT_PINK), \
                fmt::arg("gray", GRAY), \
                fmt::arg("dark_gray", DARK_GRAY), \
                fmt::arg("pink", PINK), \
                fmt::arg("gold", GOLD), \
                fmt::arg("green", GREEN), \
                fmt::arg("purple", PURPLE), \
                fmt::arg("dark_green", DARK_GREEN), \
                fmt::arg("lavender", LAVENDER), \
                fmt::arg("yellow", YELLOW), \
                fmt::arg("teal", TEAL), \
                fmt::arg("brown", BROWN), \
                fmt::arg("black", BLACK), \
                fmt::arg("light_blue", LIGHT_BLUE), \
                fmt::arg("white_bg", WHITE_BACKGROUND)

std::string MsgFormatter(const std::string& str, const UserSettingsClass& user_settings);
std::string MsgFormatterNoUser(const std::string& str);

/**
 * \brief A custom string formatter.
 * \tparam format_args Custom formatting arguments. (fmt::arg objects, automatically deducted from f_args)
 * \param[in] str The string to format.
 * \param[in] user_settings User settings (for username)
 * \param[in] f_args Custom formatting arguments.
 * \return Formatted string.
 */
template<typename... format_args>
std::string CustomMsgFormatter(const std::string& str, const UserSettingsClass& user_settings, format_args... f_args)
{
    return fmt::format(
        str,
        fmt::arg("username", user_settings.GetUsername()),
        _body,
        std::forward<format_args>(f_args)...
    );
}

/**
 * \brief A custom string formatter (with no username).
 * \tparam format_args Custom formatting arguments. (fmt::arg objects, automatically deducted from f_args)
 * \param[in] str The string to format.
 * \param[in] f_args Custom formatting arguments.
 * \return Formatted string.
 */
template<typename... format_args>
std::string CustomMsgFormatterNoUser(const std::string& str, format_args... f_args)
{
    return fmt::format(
        str,
        _body,
        std::forward<format_args>(f_args)...
    );
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0