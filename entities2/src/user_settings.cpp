// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file user_settings.cpp
 * \author norbcodes
 * \brief Reading/Writing user settings :}
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>
#include <fmt/core.h>
#include <nlohmann/json.hpp>

#include "colors.hpp"
#include "cmd_args.hpp"
#include "user_settings.hpp"
#include "global_settings.hpp"
#include "utils.hpp"
#include "rng.hpp"

/**
 * \def MAX_LINE_CHARS
 * \brief Used for login screen.
 */
#define MAX_LINE_CHARS 35

static std::string GetSaveName(const GameArgs& game_args)
{
    // Yeeeeeee
    // Start with "save0.json", if exists, increment number in it
    uint32_t num = 0;
    struct stat sb;
    // Loop
    while (true)
    {
        std::string file_name = fmt::format("{0}save{1}.json", game_args.UserFolder(), num);
        if (!stat(file_name.c_str(), &sb) == 0)
        {
            return file_name;
        }
        num++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Constructor of UserSettingsClass.
 */
UserSettingsClass::UserSettingsClass(const GameArgs& game_args, const GlobalSettingsClass& global_settings)
{
    // So we check two things...
    // One, if users folder exists
    struct stat sb;
    if (!stat(game_args.UserFolder().c_str(), &sb) == 0)
    {
        // User folder not exist :weary:
        std::filesystem::create_directory(game_args.UserFolder());
    }
    // Two, if there's atleast any user save files yet
    if (std::filesystem::is_empty(game_args.UserFolder()))
    {
        this->_MakeDefault();
        // Save
        this->Save(game_args);
    }
    else
    {
        // Count files and store inside a map
        std::map<std::string, std::filesystem::path> idk_what_to_name_this;
        uint32_t file_count = 0;
        for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator(game_args.UserFolder()))
        {
            // Increment this
            file_count++;
            // Now, quick read for the username
            std::ifstream JsonFile(file.path());
            nlohmann::json JsonData = nlohmann::json::parse(JsonFile);
            // Get username...
            // and store
            idk_what_to_name_this[JsonData["Settings"]["Username"]] = file.path();
        }

        // Two things can happen here
        if (file_count == 1)
        {
            // Only one found, so we load that
            this->Load(game_args, idk_what_to_name_this.begin()->second.string());
        }
        else
        {
            // Multiple found, ask the user...
            // This is tedious but whatevs
            ClearScreen();
            Div();
            fmt::print("{1}{2}Multiple users detected! Who's playing?{0}\n\n", RESET, WHITE, ITALIC);
            // Now print out all the names
            uint32_t line_length = 0;
            for (std::map<std::string, std::filesystem::path>::iterator i = idk_what_to_name_this.begin(); i != idk_what_to_name_this.end(); i++)
            {
                // :skull:
                switch (rng(0, 3))
                {
                    case 0:
                        fmt::print("{1}{2}{0} ", RESET, BLUE, i->first);
                        break;
                    case 1:
                        fmt::print("{1}{2}{0} ", RESET, WHITE, i->first);
                        break;
                    case 2:
                        fmt::print("{1}{2}{0} ", RESET, GREEN, i->first);
                        break;
                    case 3:
                        fmt::print("{1}{2}{0} ", RESET, PURPLE, i->first);
                        break;
                    default:
                        fmt::print("{1}{2}{0} ", RESET, BROWN, i->first);
                        break;
                }
                // lmao
                line_length += sizeof((i->first).c_str()) / sizeof(char);
                if (line_length > MAX_LINE_CHARS)
                {
                    fmt::print("\n");
                }
            }
            fmt::print("\n\n");
            // NOW
            // NOW
            // ASK THE USER
            while (true)
            {
                EndDivNoNewl();
                fmt::print("{1}>{0} ", RESET, WHITE);
                std::string option;
                std::cin >> option;
                // yay
                // Error proof
                try
                {
                    idk_what_to_name_this.at(option);
                }
                catch (const std::out_of_range& ex)
                {
                    fmt::print("{1}No user like that found.{0}                                                          \n\n", RESET, RED);
                    continue;
                }
                // Load
                this->Load(game_args, idk_what_to_name_this[option].string());
                break;
            }
        }
    }
}

/**
 * \brief Constructor with only game args and an username. Used during user creation within settings menu.
 * \param[in] game_args Game CMD arguments.
 * \param[in] username Username.
 */
UserSettingsClass::UserSettingsClass(const GameArgs& game_args, const std::string& username)
{
    this->_MakeDefault();
    this->v_Username = username;
    // Save
    this->Save(game_args);
}

/**
 * \brief Initialized settins with default values.
 */
void UserSettingsClass::_MakeDefault()
{
    // Folder empty, create brand new user save file
    this->_Path = "";
    this->_Ver = ENTITIES2_USER_SAVE_VER;
    this->v_Username = "Player";
    this->s_GamesWon = 0;
    this->s_GamesLost = 0;
    this->s_TotalGames = 0;
}

/**
 * \brief Saves user settings into a json file.
 * \param[in] game_args Game arguments.
 */
void UserSettingsClass::Save(const GameArgs& game_args)
{
    // YEAAAAAA
    nlohmann::json JsonData;
    // Stats
    JsonData["Stats"] = nlohmann::json::object();
    JsonData["Stats"]["GamesWon"] = this->s_GamesWon;
    JsonData["Stats"]["GamesLost"] = this->s_GamesLost;
    JsonData["Stats"]["TotalGames"] = this->s_TotalGames;
    // Settings
    JsonData["Settings"] = {{"Username", this->v_Username}};
    // Meta
    JsonData["Meta"]["USVer"] = this->_Ver;
    // Save
    if (this->_Path == "")
    {
        std::string save_name = GetSaveName(game_args);
        std::ofstream Json(save_name);
        this->_Path = save_name;
        Json << JsonData.dump(4);
        Json.close();
    }
    else
    {
        std::ofstream Json(this->_Path);
        Json << JsonData.dump(4);
        Json.close();
    }
}

/**
 * \brief Load user settings from a json file.
 * \param[in] game_args Game arguments.
 * \param[in] path Path to the json file.
 */
void UserSettingsClass::Load(const GameArgs& game_args, const std::string& path)
{
    // Reverse of "save" method
    std::ifstream Json(path);
    nlohmann::json JsonData = nlohmann::json::parse(Json);
    this->_Path = path;
    // Stats
    this->s_GamesWon = JsonData["Stats"]["GamesWon"];
    this->s_GamesLost = JsonData["Stats"]["GamesLost"];
    this->s_TotalGames = JsonData["Stats"]["TotalGames"];
    // Settings
    this->v_Username = JsonData["Settings"]["Username"];
    // Meta
    this->_Ver = JsonData["Meta"]["USVer"];
    Json.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Getter for s_GamesWon
 * \return Number of games won.
 */
uint32_t UserSettingsClass::GetGamesWon() const
{
    return (this->s_GamesWon);
}

/**
 * \brief Getter for s_GamesLost
 * \return Number of games lost.
 */
uint32_t UserSettingsClass::GetGamesLost() const
{
    return (this->s_GamesLost);
}

/**
 * \brief Getter for s_TotalGames
 * \return Number of games played.
 */
uint32_t UserSettingsClass::GetTotalGames() const
{
    return (this->s_TotalGames);
}

/**
 * \brief Getter for v_Username
 * \return Username of our player.
 */
const std::string& UserSettingsClass::GetUsername() const
{
    return (this->v_Username);
}

/**
 * \brief Getter for _Path
 * \return Get the save format version.
 */
std::string UserSettingsClass::GetJsonPath() const
{
    return (this->_Path);
}

/**
 * \brief Getter for _Ver
 * \return Get the save format version.
 */
uint32_t UserSettingsClass::GetSaveVer() const
{
    return (this->_Ver);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Setter for s_GamesWon.
 * \param[in] num Number to set the variable to.
 */
void UserSettingsClass::SetGamesWon(uint32_t num)
{
    this->s_GamesWon = num;
}

/**
 * \brief Setter for s_GamesWon.
 * \param[in] num Number to add to the variable.
 */
void UserSettingsClass::IncreaseGamesWon(uint32_t num)
{
    this->s_GamesWon += num;
}

/**
 * \brief Setter for s_GamesLost.
 * \param[in] num Number to set the variable to.
 */
void UserSettingsClass::SetGamesLost(uint32_t num)
{
    this->s_GamesLost = num;
}

/**
 * \brief Setter for s_GamesLost.
 * \param[in] num Number to add to the variable.
 */
void UserSettingsClass::IncreaseGamesLost(uint32_t num)
{
    this->s_GamesLost += num;
}

/**
 * \brief Setter for s_TotalGames.
 * \param[in] num Number to set the variable to.
 */
void UserSettingsClass::SetTotalGames(uint32_t num)
{
    this->s_TotalGames = num;
}

/**
 * \brief Setter for s_TotalGames.
 * \param[in] num Number to add to the variable.
 */
void UserSettingsClass::IncreaseTotalGames(uint32_t num)
{
    this->s_TotalGames += num;
}

/**
 * \brief Setter for v_Username.
 * \param[in] new_user New username.
 */
void UserSettingsClass::SetUsername(const std::string& new_user)
{
    this->v_Username = new_user;
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0