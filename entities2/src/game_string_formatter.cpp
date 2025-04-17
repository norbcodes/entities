// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file game_string_formatter.cpp
 * \author norbcodes
 * \brief Function for formatting strings inside Datapacks.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <string>
#include <fmt/format.h>

#include "game_string_formatter.hpp"
#include "colors.hpp"
#include "user_settings.hpp"
#include "version.hpp"

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
        _body,
        _extra
    );
}

/**
 * \brief Format custom messages defined in Datapacks, now without using User Settings.
 * \param[in] str The string to format.
 * \return Formatted string.
 */
std::string MsgFormatterNoUser(const std::string& str)
{
    return fmt::format(
        str,
        _body,
        _extra
    );
}

/**
 * \brief Format custom messages defined in Datapacks, with only colors.
 * \param[in] str The string to format.
 * \return Formatted string.
 */
std::string MsgFormatterColorsOnly(const std::string& str)
{
    return fmt::format(
        str,
        _body
    );
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0