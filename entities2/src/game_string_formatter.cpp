// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file game_string_formatter.cpp
 * \author norbcodes
 * \brief Function for formatting strings inside Datapacks.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <string>
#include <fmt/format.h>

#include "colors.hpp"
#include "user_settings.hpp"

/**
 * \brief Format custom messages defined in Datapacks.
 * \param[in] str The string to format.
 * \param[in] user_settings User game settings.
 * \return Formatted string.
 */
std::string MsgFormatter(const std::string& str, const UserSettingsClass& user_settings)
{
    return fmt::format(
        str,
        fmt::arg("username", user_settings.GetUsername()),
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
        fmt::arg("brown", BROWN),
        fmt::arg("black", BLACK),
        fmt::arg("white_bg", WHITE_BACKGROUND)
    );
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0