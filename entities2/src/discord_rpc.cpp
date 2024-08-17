// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

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

#include <bits/stdc++.h>
#include <time.h>
#include <discord/discord_rpc.hpp>

namespace _DiscordStuff
{
    // I'm too lazy to do it any other way
    bool RegenMenuRPC = true;
    bool RegenGameplayTime = true;
    time_t GameplayTime;
}

void MainMenuRPC()
{
    #ifdef __ENTITIES2_DISCORD_RPC__

    // Thank god for the "Show Code" option <3
    if (_DiscordStuff::RegenMenuRPC)
    {
        _DiscordStuff::RegenGameplayTime = true;
        DiscordRichPresence presence;
        memset(&presence, 0, sizeof(presence));
        presence.details = "In Main Menu";
        presence.startTimestamp = time(NULL);
        presence.largeImageKey = "entities2_bigimage";
        presence.largeImageText = "entities2";
        Discord_UpdatePresence(&presence);
        _DiscordStuff::RegenMenuRPC = false;
    }

    #endif // __ENTITIES2_DISCORD_RPC__
}

void GameplayRPC(bool enemy_turn)
{
    #ifdef __ENTITIES2_DISCORD_RPC__

    _DiscordStuff::RegenMenuRPC = true;

    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));

    presence.state = (!enemy_turn) ? "Player Turn" : "Enemy Turn";
    presence.details = "In Battle";

    if (_DiscordStuff::RegenGameplayTime)
    {
        _DiscordStuff::GameplayTime = time(NULL);
        _DiscordStuff::RegenGameplayTime = false;
    }

    presence.startTimestamp = _DiscordStuff::GameplayTime;

    presence.largeImageKey = "entities2_bigimage";
    presence.largeImageText = "entities2";
    presence.smallImageKey = (!enemy_turn) ? "entities2_player" : "entities2_enemy";
    presence.smallImageText = (!enemy_turn) ? "Player Turn" : "Enemy Turn";
    Discord_UpdatePresence(&presence);

    #endif // __ENTITIES2_DISCORD_RPC__
}

void InitializeRPC()
{
    #ifdef __ENTITIES2_DISCORD_RPC__
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(__ENTITIES2_DISCORD_CLIENT_ID__, &handlers, 1, NULL);
    #endif // __ENTITIES2_DISCORD_RPC__
}

void DestroyRPC()
{
    #ifdef __ENTITIES2_DISCORD_RPC__
    Discord_Shutdown();
    #endif // __ENTITIES2_DISCORD_RPC__
}