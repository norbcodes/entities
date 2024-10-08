// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file global_settings.cpp
 * \author norbcodes
 * \brief Reading/Writing global settings :}
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <sys/stat.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "cmd_args.hpp"
#include "global_settings.hpp"

/**
 * \brief Constructor.
 * \param[in] game_args Game CMD arguments.
 */
GlobalSettingsClass::GlobalSettingsClass(const GameArgs& game_args)
{
    // Yay!
    // Check if the file exists
    struct stat sb;
    if (!stat(game_args.GlobalSettings().c_str(), &sb) == 0)
    {
        // global.json doesn't exist...
        #ifdef __ENTITIES2_DISCORD_RPC__
        // Discord stuff
        this->v_DiscordEnabled = true;
        #else //__ENTITIES2_DISCORD_RPC__
        this->v_DiscordEnabled = false;
        #endif //__ENTITIES2_DISCORD_RPC__

        // Save
        this->Save(game_args);
    }
    else
    {
        // Read
        std::ifstream Json(game_args.GlobalSettings().c_str());
        nlohmann::json JsonData = nlohmann::json::parse(Json);

        // LOAD EVERYTHING!
        this->v_DiscordEnabled = JsonData["Settings"]["DiscordEnabled"];

        // :3
        Json.close();
    }
}

/**
 * \brief Save to file.
 * \param[in] game_args Game CMD arguments.
 */
void GlobalSettingsClass::Save(const GameArgs& game_args) const
{
    // Write to json :3
    nlohmann::json JsonData;
    std::ofstream Json(game_args.GlobalSettings());

    // Stick it in
    JsonData["Settings"] = {{"DiscordEnabled", this->v_DiscordEnabled}};

    // Write
    Json << JsonData.dump(4);
    Json.close();
}

/**
 * \brief Getter for v_DiscordEnabled.
 * \return Boolean.
 */
bool GlobalSettingsClass::GetDiscordEnabled() const
{
    #ifdef __ENTITIES2_DISCORD_RPC__
    return (this->v_DiscordEnabled);
    #else //__ENTITIES2_DISCORD_RPC__
    return false;
    #endif //__ENTITIES2_DISCORD_RPC__
}

/**
 * \brief Setter for v_DiscordEnabled.
 * \param[in] o Boolean.
 */
void GlobalSettingsClass::SetDiscordEnabled(bool o)
{
    #ifdef __ENTITIES2_DISCORD_RPC__
    this->v_DiscordEnabled = o;
    #endif //__ENTITIES2_DISCORD_RPC__
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0