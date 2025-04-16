// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file global_settings.cpp
 * \author norbcodes
 * \brief Reading/Writing global settings :}
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <sys/stat.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

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
        this->_SetDefault();
        // Save
        this->Save(game_args);
    }
    else
    {
        // Read
        std::ifstream Json(game_args.GlobalSettings().c_str());
        nlohmann::json JsonData = nlohmann::json::parse(Json);

        // Get version
        uint32_t version = JsonData["Meta"]["GSVer"];
        // Set all to default
        this->_SetDefault();

        // Aaaaaand load!
        switch (version)
        {
            default:
            case 1001000:
                this->v_DiscordEnabled = JsonData["Settings"]["DiscordEnabled"];
                this->v_Language = JsonData["Settings"]["Language"];
                this->v_ShowEndScreen = JsonData["Settings"]["ShowEndScreen"];
                break;
            case 1000000:
                this->v_DiscordEnabled = JsonData["Settings"]["DiscordEnabled"];
                this->v_Language = JsonData["Settings"]["Language"];
                break;
        }

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
    JsonData["Settings"] = {};
    JsonData["Settings"]["DiscordEnabled"] = this->v_DiscordEnabled;
    JsonData["Settings"]["Language"] = this->v_Language;
    JsonData["Settings"]["ShowEndScreen"] = this->v_ShowEndScreen;
    JsonData["Meta"] = {{"GSVer", this->_Ver}};

    // Write
    Json << JsonData.dump(4);
    Json.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void GlobalSettingsClass::_SetDefault()
{
    // Discord stuff
    #ifdef __ENTITIES2_DISCORD_RPC__
        this->v_DiscordEnabled = true;
    #else //__ENTITIES2_DISCORD_RPC__
        this->v_DiscordEnabled = false;
    #endif //__ENTITIES2_DISCORD_RPC__

    this->_Ver = ENTITIES2_GLOBAL_SAVE_VER;
    this->v_Language = "en-US";
    this->v_ShowEndScreen = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

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
 * \brief Getter for _Ver.
 * \return The version.
 */
uint32_t GlobalSettingsClass::GetSaveVer() const
{
    return (this->_Ver);
}

/**
 * \brief Getter for v_Language.
 * \return The language setting.
 */
const std::string& GlobalSettingsClass::GetLanguageId() const
{
    return (this->v_Language);
}

bool GlobalSettingsClass::GetShowEndScreenValue() const
{
    return (this->v_ShowEndScreen);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

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

/**
 * \brief Setter for _Ver.
 * \param[in] o Boolean.
 */
void GlobalSettingsClass::SetSaveVer(uint32_t o)
{
    this->_Ver = o;
}

/**
 * \brief Setter for v_Language.
 * \param[in] lang The language id to set the language setting to.
 */
void GlobalSettingsClass::SetLanguageId(const std::string& lang)
{
    this->v_Language = lang;
}

void GlobalSettingsClass::SetShowEndScreenValue(bool v)
{
    this->v_ShowEndScreen = v;
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0