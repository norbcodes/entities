// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file global_settings.hpp
 * \author norbcodes
 * \brief GlobalSettingsClass class.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include "cmd_args.hpp"
#include <nlohmann/json.hpp>

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
        void Save(const GameArgs& game_args);
        // Getters
        bool GetDiscordEnabled() const;
        // Setters
        void SetDiscordEnabled(bool o);
    
    private:
        // SETTINGS

        /**
         * \var bool v_DiscordEnabled
         * \brief Boolean value, wheter Discord RPC is enabled.
         */
        bool v_DiscordEnabled;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0