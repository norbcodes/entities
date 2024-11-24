// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file global_settings.hpp
 * \author norbcodes
 * \brief GlobalSettingsClass class.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <cstdint>
#include <string>

#include "cmd_args.hpp"
#include <nlohmann/json.hpp>

/**
 * \def ENTITIES2_GLOBAL_SAVE_VER_MAJOR
 * \brief Save format major version. (The 'x' in 'x.y.z')
 */
#define ENTITIES2_GLOBAL_SAVE_VER_MAJOR 1

/**
 * \def ENTITIES2_GLOBAL_SAVE_VER_MINOR
 * \brief Save format minor version. (The 'y' in 'x.y.z')
 */
#define ENTITIES2_GLOBAL_SAVE_VER_MINOR 0

/**
 * \def ENTITIES2_GLOBAL_SAVE_VER_PATCH
 * \brief Save format patch version. (The 'z' in 'x.y.z')
 */
#define ENTITIES2_GLOBAL_SAVE_VER_PATCH 0

/**
 * \def ENTITIES2_GLOBAL_SAVE_VER
 * \brief Quick macro to get the version.
 */
#define ENTITIES2_GLOBAL_SAVE_VER       ((ENTITIES2_GLOBAL_SAVE_VER_MAJOR * 1000000) + (ENTITIES2_GLOBAL_SAVE_VER_MINOR * 1000) + (ENTITIES2_GLOBAL_SAVE_VER_PATCH))

/**
 * \class GlobalSettingsClass
 * \brief GlobalSettingsClass class.
 * \details Contains variables that store values of each global setting, and getters to access them.
 */
class GlobalSettingsClass
{
    // I'm so fucking good at naming things
    public:
        GlobalSettingsClass(const GameArgs& game_args);
        void Save(const GameArgs& game_args) const;
        // Getters
        bool GetDiscordEnabled() const;
        uint32_t GetSaveVer() const;
        const std::string& GetLanguageId() const;
        // Setters
        void SetDiscordEnabled(bool o);
        void SetSaveVer(uint32_t o);
        void SetLanguageId(const std::string& lang);
    private:
        // SETTINGS

        /**
         * \var bool v_DiscordEnabled
         * \brief Boolean value, wheter Discord RPC is enabled.
         */
        bool v_DiscordEnabled;

        /**
         * \var std::string v_Language
         * \brief Saved language setting.
         */
        std::string v_Language;

        /**
         * \var uint32_t _Ver
         * \brief Save version.
         */
        uint32_t _Ver;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0