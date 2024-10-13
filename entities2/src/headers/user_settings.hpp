// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file user_settings.hpp
 * \author norbcodes
 * \brief UserSettingsClass class.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <cstdint>
#include <string>
#include <filesystem>

#include "cmd_args.hpp"
#include "global_settings.hpp"

/**
 * \def ENTITIES2_USER_SAVE_VER_MAJOR
 * \brief Save format major version. (The 'x' in 'x.y.z')
 */
#define ENTITIES2_USER_SAVE_VER_MAJOR 1

/**
 * \def ENTITIES2_USER_SAVE_VER_MINOR
 * \brief Save format minor version. (The 'y' in 'x.y.z')
 */
#define ENTITIES2_USER_SAVE_VER_MINOR 0

/**
 * \def ENTITIES2_USER_SAVE_VER_PATCH
 * \brief Save format patch version. (The 'z' in 'x.y.z')
 */
#define ENTITIES2_USER_SAVE_VER_PATCH 0

/**
 * \def ENTITIES2_USER_SAVE_VER
 * \brief Quick macro to get the version.
 */
#define ENTITIES2_USER_SAVE_VER       ((ENTITIES2_USER_SAVE_VER_MAJOR * 10000000) + (ENTITIES2_USER_SAVE_VER_MINOR * 100000) + (ENTITIES2_USER_SAVE_VER_PATCH * 1000))

/**
 * \class UserSettingsClass
 * \brief UserSettingsClass class.
 * \details Contains variables of each user setting and stats, and getters to access them, and setters to change them.
 */
class UserSettingsClass
{
    public:
        UserSettingsClass(const GameArgs& game_args, const GlobalSettingsClass& global_settings);
        UserSettingsClass(const GameArgs& game_args, const std::string& username);  // for user creation within settings menu
        void Save(const GameArgs& game_args);
        void Load(const GameArgs& game_args, const std::string& path);
        // Getters
        uint32_t GetGamesWon() const;
        uint32_t GetGamesLost() const;
        uint32_t GetTotalGames() const;
        const std::string& GetUsername() const;
        std::string GetJsonPath() const;
        uint32_t GetSaveVer() const;
        // Setters
        void SetGamesWon(uint32_t num);
        void IncreaseGamesWon(uint32_t num);
        void SetGamesLost(uint32_t num);
        void IncreaseGamesLost(uint32_t num);
        void SetTotalGames(uint32_t num);
        void IncreaseTotalGames(uint32_t num);
        void SetUsername(const std::string& new_user);
    
    private:
        void _MakeDefault();
        // Yaaay :3
        // s_* are stats, v_* are settings

        /**
         * \var std::string _Path
         * \brief Used during saving.
         */
        std::string _Path;

        /**
         * \var uint32_t _Ver
         * \brief Internal variable.
         */
        uint32_t _Ver;

        /**
         * \var uint32_t s_GamesWon
         * \brief Number of games won.
         */
        uint32_t s_GamesWon;

        /**
         * \var uint32_t s_GamesLost
         * \brief Number of games lost.
         */
        uint32_t s_GamesLost;

        /**
         * \var uint32_t s_TotalGames
         * \brief Total number of games played.
         */
        uint32_t s_TotalGames;

        /**
         * \var std::string v_Username
         * \brief Username.
         */
        std::string v_Username;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0