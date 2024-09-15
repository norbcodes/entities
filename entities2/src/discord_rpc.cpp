// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file discord_rpc.cpp
 * \author norbcodes
 * \brief Discord RPC Code.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \details Contains code for working with the Discord RPC library.<br>
 *          This is where the game keeps functions for updating the RPC.
 */

/*
yeaaaah
This is another story about dogs
For the dog that don't pee on trees, is a bitch
So says Snoop Dogg, get your pooper scooper
Cause the n****'s talkin shit
Aroof!

Also "We deprecated discord-rpc" I don't give a shit
If it works, it works, and it works better than the under-documented SDK :)
*/

#include <cstring>
#include <time.h>
#include <discord/discord_rpc.hpp>

/**
 * \namespace E2_Discord
 * \brief E2_Discord game namespace.
 * \details Internal game namespace, used to store variables without cluttering the global scope.<br>
 *          Variables inside of this namespace should not be used outside of this file (discord_rpc.cpp)<br>
 *          They are static anyway.
 */
namespace E2_Discord
{
    // I'm too lazy to do it any other way
    // So enjoy these static variables
    // I DARE you to fight me right now
    static bool RegenMenuRPC = true;
    static bool RegenGameplayTime = true;
    static time_t GameplayTime;
}

/**
 * \brief Update RPC to show the player is in main menu.
 * \details This function will set the RPC to show that the player is in the main menu.<br>
 *          and shows the approriate time.
 */
void MainMenuRPC()
{
    #ifdef __ENTITIES2_DISCORD_RPC__

    // Thank god for the "Show Code" option <3
    if (E2_Discord::RegenMenuRPC)
    {
        // Set data
        E2_Discord::RegenGameplayTime = true;
        DiscordRichPresence presence;
        memset(&presence, 0, sizeof(presence));
        presence.details = "In Main Menu";
        presence.startTimestamp = time(NULL);
        presence.largeImageKey = "entities2_bigimage";
        presence.largeImageText = "entities2";
        // Send update
        Discord_UpdatePresence(&presence);
        E2_Discord::RegenMenuRPC = false;
    }

    #endif // __ENTITIES2_DISCORD_RPC__
}

/**
 * \brief Update RPC to show the player is in battle.
 * \details This function will set the RPC to show that the player is in a battle<br>
 *          and shows the approriate time.
 * \param[in] enemy_turn Controls which image and text to display<br>
 *                       1 = Enemy data and image, 0 = Player data and image.
 */
void GameplayRPC(bool enemy_turn)
{
    #ifdef __ENTITIES2_DISCORD_RPC__

    // This switch below controls whetever we reset main menu time
    // or not
    E2_Discord::RegenMenuRPC = true;

    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));

    // Add details
    presence.state = (!enemy_turn) ? "Player Turn" : "Enemy Turn";
    presence.details = "In Battle";

    if (E2_Discord::RegenGameplayTime)
    {
        E2_Discord::GameplayTime = time(NULL);
        E2_Discord::RegenGameplayTime = false;
    }

    presence.startTimestamp = E2_Discord::GameplayTime;
    presence.largeImageKey = "entities2_bigimage";
    presence.largeImageText = "entities2";
    presence.smallImageKey = (!enemy_turn) ? "entities2_player" : "entities2_enemy";
    presence.smallImageText = (!enemy_turn) ? "Player Turn" : "Enemy Turn";

    // Send update
    Discord_UpdatePresence(&presence);

    #endif // __ENTITIES2_DISCORD_RPC__
}

/**
 * \brief Initialize RPC.
 * \details Run this function to initialize Discord RPC.<br>
 *          Will use custom client_id if supplied.
 */
void InitializeRPC()
{
    #ifdef __ENTITIES2_DISCORD_RPC__
    // Initialize discord rpc
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    //                  CUSTOM ID HERE IF WANTED
    Discord_Initialize(__ENTITIES2_DISCORD_CLIENT_ID__, &handlers, 1, NULL);
    #endif // __ENTITIES2_DISCORD_RPC__
}

/**
 * \brief Destroy RPC.
 * \details Run this function to destroy Discord RPC.<br>
 *          :(
 */
void DestroyRPC()
{
    #ifdef __ENTITIES2_DISCORD_RPC__
    // DESTROY
    Discord_Shutdown();
    #endif // __ENTITIES2_DISCORD_RPC__
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0