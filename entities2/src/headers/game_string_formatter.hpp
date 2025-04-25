// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file game_string_formatter.hpp
 * \author norbcodes
 * \brief Functions for formatting game strings.
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
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
 * \brief A quick macro often repeated in the 3 formatter functions and 2 templated formatter functions.
 */
#define _body   fmt::arg("reset", RESET), \
                fmt::arg("end", RESET), \
                fmt::arg("blank", RESET), \
                fmt::arg("bold", BOLD), \
                fmt::arg("b", BOLD), \
                fmt::arg("faint", FAINT), \
                fmt::arg("f", ITALIC), \
                fmt::arg("italic", ITALIC), \
                fmt::arg("i", ITALIC), \
                fmt::arg("underline", UNDERLINE), \
                fmt::arg("u", UNDERLINE), \
                fmt::arg("blinking", BLINKING), \
                fmt::arg("bli", UNDERLINE), \
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
                fmt::arg("almond", ALMOND), \
                fmt::arg("crimson", CRIMSON), \
                fmt::arg("aqua", AQUA), \
                fmt::arg("dark_purple", DARK_PURPLE), \
                fmt::arg("onyx", ONYX), \
                fmt::arg("bg_red", BG_RED), \
                fmt::arg("bg_blue", BG_BLUE), \
                fmt::arg("bg_orange", BG_ORANGE), \
                fmt::arg("white_bg", BG_WHITE), \
                fmt::arg("bg_white", BG_WHITE), \
                fmt::arg("bg_hot_pink", BG_HOT_PINK), \
                fmt::arg("bg_gray", BG_GRAY), \
                fmt::arg("bg_dark_gray", BG_DARK_GRAY), \
                fmt::arg("bg_pink", BG_PINK), \
                fmt::arg("bg_gold", BG_GOLD), \
                fmt::arg("bg_green", BG_GREEN), \
                fmt::arg("bg_purple", BG_PURPLE), \
                fmt::arg("bg_dark_green", BG_DARK_GREEN), \
                fmt::arg("bg_lavender", BG_LAVENDER), \
                fmt::arg("bg_yellow", BG_YELLOW), \
                fmt::arg("bg_teal", BG_TEAL), \
                fmt::arg("bg_brown", BG_BROWN), \
                fmt::arg("bg_black", BG_BLACK), \
                fmt::arg("bg_light_blue", BG_LIGHT_BLUE), \
                fmt::arg("bg_almond", BG_ALMOND), \
                fmt::arg("bg_crimson", BG_CRIMSON), \
                fmt::arg("bg_aqua", BG_AQUA), \
                fmt::arg("bg_dark_purple", BG_DARK_PURPLE), \
                fmt::arg("bg_onyx", BG_ONYX)

/**
 * \def _extra
 * \hideinitializer
 * \brief A quick macro for non-color format arguments.
 */
#define _extra  fmt::arg("entities2_ver", ENTITIES2_VER), \
                fmt::arg("nl", '\n'), \
                fmt::arg("compile_time", __TIME__), \
                fmt::arg("compile_date", __DATE__)

std::string MsgFormatter(const std::string& str, const UserSettingsClass& user_settings);
std::string MsgFormatterNoUser(const std::string& str);
std::string MsgFormatterColorsOnly(const std::string& str);

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
        _extra,
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
        _extra,
        std::forward<format_args>(f_args)...
    );
}

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0