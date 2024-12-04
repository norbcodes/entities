// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file translation_engine.cpp
 * \author norbcodes
 * \brief Entities2 localization system! Also includes base languages.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <string>
#include <stdexcept>
#include <map>
#include <unordered_map>

#include "translation_engine.hpp"
#include "game_string_formatter.hpp"
#include "global_settings.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Constructor.
 */
TranslationEngine::TranslationEngine() {}

/**
 * \brief Set/change language.
 * \param[in] id The language id to switch to.
 * \param[out] global_settings Apply language change and save in global settings too.
 */
void TranslationEngine::SetLang(const std::string& id, GlobalSettingsClass& global_settings)
{
    global_settings.SetLanguageId(id);
    this->CurrentLangId = id;
}

/**
 * \brief Add translation string.
 * \param[in] lang_id The language of the string.
 * \param[in] trans_id The id of the translation string.
 * \param[in] str The translation string.
 */
void TranslationEngine::AddTranslation(const std::string& lang_id, const std::string& trans_id, const std::string& str)
{
    this->Register[lang_id][trans_id] = str;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Return the current set language id.
 * \return The id.
 */
const std::string& TranslationEngine::GetCurrentLangId() const
{
    return (this->CurrentLangId);
}

/**
 * \brief Get translated string.
 * \param[in] str The string to translate.
 * \return Translated string.
 */
const std::string& TranslationEngine::GetTranslated(const std::string& str) const
{
    try
    {
        return this->Register.at(this->CurrentLangId).at(str);
    }
    catch (const std::out_of_range& E)
    {
        #ifdef __ENTITIES2_TRANSLATION_OLD_BEHAVIOR__
        return str;
        #else // __ENTITIES2_TRANSLATION_OLD_BEHAVIOR__
        if (str == "lang.name" || str == "lang.id")
        {
            return str;
        }
        else
        {
            try
            {
                // As Artezon said, "returning translation key would confuse normal people aka non-programmers"
                return this->Register.at("en-US").at(str);
            }
            catch (const std::out_of_range& E2)
            {
                return str;
            }
        }
        #endif // __ENTITIES2_TRANSLATION_OLD_BEHAVIOR__
    }
}

/**
 * \brief Get translated string, with explicitely set target language.
 * \param[in] str The string to translate.
 * \param[in] lang_id The language to translate to.
 * \return Translated string.
 */
const std::string& TranslationEngine::GetTranslated(const std::string& str, const std::string& lang_id) const
{
    try
    {
        return this->Register.at(lang_id).at(str);
    }
    catch (const std::out_of_range& E)
    {
        #ifdef __ENTITIES2_TRANSLATION_OLD_BEHAVIOR__
        return str;
        #else // __ENTITIES2_TRANSLATION_OLD_BEHAVIOR__
        if (str == "lang.name" || str == "lang.id")
        {
            return str;
        }
        else
        {
            try
            {
                return this->Register.at("en-US").at(str);
            }
            catch (const std::out_of_range& E2)
            {
                return str;
            }
        }
        #endif // __ENTITIES2_TRANSLATION_OLD_BEHAVIOR__
    }
}

/**
 * \brief Check if a given translation string exists.
 * \param[in] what The string.
 * \return 'true' if the string exists.
 */
bool TranslationEngine::TranslationStringExists(const std::string& what) const
{
    try
    {
        std::string _garbage = this->Register.at(this->GetCurrentLangId()).at(what);
        return true;
    }
    catch (const std::out_of_range& E)
    {
        return false;
    }
}

/**
 * \brief Check if a given language exists.
 * \param[in] what The language.
 * \return 'true' if the language exists.
 */
bool TranslationEngine::LangIdExists(const std::string& what) const
{
    try
    {
        std::unordered_map<std::string, std::string> _garbage = this->Register.at(what);
        return true;
    }
    catch (const std::out_of_range& E)
    {
        return false;
    }
}

/**
 * \brief An iterator of the internal std::map.
 * \return std::map<...>::const_iterator
 */
std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator TranslationEngine::LangIteratorBegin() const
{
    return (this->Register.begin());
}

/**
 * \brief An iterator of the internal std::map.
 * \return std::map<...>::const_iterator
 */
std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator TranslationEngine::LangIteratorEnd() const
{
    return (this->Register.end());
}

/**
 * \brief An iterator of a language's translation keys.
 * \param[in] id ID of the language to iterate through.
 * \return std::unordered_map<...>::const_iterator
 */
std::unordered_map<std::string, std::string>::const_iterator TranslationEngine::TranslationIteratorBegin(const std::string& id) const
{
    return (this->Register.at(id).begin());
}

/**
 * \brief An iterator of a language's translation keys.
 * \param[in] id ID of the language to iterate through.
 * \return std::unordered_map<...>::const_iterator
 */
std::unordered_map<std::string, std::string>::const_iterator TranslationEngine::TranslationIteratorEnd(const std::string& id) const
{
    return (this->Register.at(id).end());
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Load all of English translation.
 * \note This is always loaded.
 */
void TranslationEngine::LoadEnglish()
{
    // IS ALWAYS CALLED.
    // THE BASE LANGUAGE.
    // Strings are in raw form
    // They are formatted where they are needed

    // Language specific strings
    this->Register["en-US"]["lang.name"]                    = "English (USA)";
    this->Register["en-US"]["lang.id"]                      = "en-US";

    // General texts
    this->Register["en-US"]["general.quit"]                 = "Quit";
    this->Register["en-US"]["general.exit"]                 = "Exit";
    this->Register["en-US"]["general.on"]                   = "ON";
    this->Register["en-US"]["general.off"]                  = "OFF";
    this->Register["en-US"]["general.by"]                   = "by";
    this->Register["en-US"]["general.enter_to_exit"]        = "Press enter to continue.";
    this->Register["en-US"]["general.healed"]               = "healed";
    this->Register["en-US"]["general.regenerated"]          = "regenerated";
    this->Register["en-US"]["general.enemy"]                = "Enemy";

    // Main menu texts
    this->Register["en-US"]["menu.main.subtitle"]           = "A game by norbcodes.";
    this->Register["en-US"]["menu.main.optionpick"]         = "Pick an option:";
    this->Register["en-US"]["menu.main.play"]               = "Play";
    this->Register["en-US"]["menu.main.ginfo"]              = "Gameplay Info";
    this->Register["en-US"]["menu.main.datapacks"]          = "Datapacks";
    this->Register["en-US"]["menu.main.settings"]           = "Settings";
    this->Register["en-US"]["menu.exit.confirm"]            = "Confirm exit?";
    this->Register["en-US"]["menu.unstable"]                = "{red}You are using a game build that is {bold}still under Development!{reset}{nl}{white}Proceed with caution. {red}Do you still wanna play? [y,n]{reset}";

    // Difficulty picker texts
    this->Register["en-US"]["menu.diffpicker.title"]        = "Difficulty Selection";
    this->Register["en-US"]["menu.diffpicker.easy"]         = "I kick Entities ass";
    this->Register["en-US"]["menu.diffpicker.medium"]       = "I've seen worse";
    this->Register["en-US"]["menu.diffpicker.hard"]         = "Down with the Entities";
    this->Register["en-US"]["menu.diffpicker.random"]       = "Random!";
    this->Register["en-US"]["menu.diffpicker.record"]       = "Record demo";

    // Datapack viewer stuff
    this->Register["en-US"]["menu.datapacks.title"]         = "Datapacks";
    this->Register["en-US"]["menu.datapacks.loaded"]        = "{white}Currently loaded {purple}{datapack_count}{reset}{white} datapacks.{reset}";
    this->Register["en-US"]["menu.datapacks.help1"]         = "Use up, down arrows to scroll.";
    this->Register["en-US"]["menu.datapacks.empty"]         = "No datapacks!";
    this->Register["en-US"]["menu.datapacks.info"]          = "Press left arrow to go back. Press right arrow to view a datapacks' info.";
    this->Register["en-US"]["menu.datapacks.title2"]        = "Datapack Info";
    this->Register["en-US"]["menu.datapacks.subtitle"]      = "Metadata:";
    this->Register["en-US"]["menu.datapacks.name"]          = "Name:";
    this->Register["en-US"]["menu.datapacks.author"]        = "Author:";
    this->Register["en-US"]["menu.datapacks.id"]            = "Datapack id:";
    this->Register["en-US"]["menu.datapacks.desc"]          = "Description:";
    this->Register["en-US"]["menu.datapacks.size"]          = "Size on disk:";
    this->Register["en-US"]["menu.datapacks.veryhuge"]      = "Bigger than Jupiter";
    this->Register["en-US"]["menu.datapacks.error1"]        = "Main \"Datapack\" block missing!";
    this->Register["en-US"]["menu.datapacks.error2"]        = "Main \"Meta\" block missing!";
    this->Register["en-US"]["menu.datapacks.error3"]        = "Main \"Data\" block missing!";
    this->Register["en-US"]["menu.datapacks.error4"]        = "Datapack name missing!";
    this->Register["en-US"]["menu.datapacks.error5"]        = "Datapack author missing!";
    this->Register["en-US"]["menu.datapacks.error6"]        = "Datapack identificator missing!";
    this->Register["en-US"]["menu.datapacks.error7"]        = "Broken translations!";
    this->Register["en-US"]["menu.datapacks.error8"]        = "Greeting has no time specified!";
    this->Register["en-US"]["menu.datapacks.error9"]        = "Empty greeting!";
    this->Register["en-US"]["menu.datapacks.error10"]       = "Empty exit message!";

    // Gameplay info
    this->Register["en-US"]["menu.ginfo.title"]             = "Gameplay Info!";
    this->Register["en-US"]["menu.ginfo.tips"]              = "Tips and Tricks";
    this->Register["en-US"]["menu.ginfo.status"]            = "Statuses and what they do";
    this->Register["en-US"]["menu.ginfo.tiptitle"]          = "TIPS 'N' TRICKS";
    this->Register["en-US"]["menu.ginfo.tip1"]              = "You can use skip a round by choosing neither 0, 1, 2, 3 or 4.";
    this->Register["en-US"]["menu.ginfo.tip2"]              = "If need be, you can skip a round to recharge your energy.";
    this->Register["en-US"]["menu.ginfo.tip3"]              = "The AI will try to attack if it has more than 60 HP.";
    this->Register["en-US"]["menu.ginfo.statustitle1"]      = "STATUSES";
    this->Register["en-US"]["menu.ginfo.statustitle2"]      = "and what they do...";
    this->Register["en-US"]["menu.ginfo.autoheal"]          = "AutoHeal";
    this->Register["en-US"]["menu.ginfo.autoheal.info"]     = "{white}At the start of a {underline}new round{reset}{white}, the entity that{reset}{nl}   {white}has {underline}their turn will recieve {purple}{bold}+{autoheal_amount}HP of health.{reset}";
    this->Register["en-US"]["menu.ginfo.icrit"]             = "IncreasedCrit";
    this->Register["en-US"]["menu.ginfo.icrit.info"]        = "{white}When an entity has this status, it has {underline}about {purple}~30%{reset}{nl}   {white}of dealing a {underline}critical attack{reset}{white}, which deals{reset}{nl}   {white}significantly {underline}more damage.{reset}";
    this->Register["en-US"]["menu.ginfo.invis"]             = "Invisibility";
    this->Register["en-US"]["menu.ginfo.invis.info"]        = "{white}When an entity has this status, there's{reset}{nl}   {white}a {underline}{purple}~20%{reset} {white}chance of an attacker {underline}missing{reset}{nl}   {white}{underline}the attack when attacking this entity.{reset}";
    this->Register["en-US"]["menu.ginfo.poison"]            = "Poison";
    this->Register["en-US"]["menu.ginfo.poison.info"]       = "{white}At the start of a {underline}new round{reset}, the entity that{reset}{nl}   {white}has {underline}their turn will recieve {purple}{bold}-{poison_amount}HP of damage.{reset}";
    this->Register["en-US"]["menu.ginfo.thorns"]            = "Thorns";
    this->Register["en-US"]["menu.ginfo.thorns.info"]       = "{white}When an entity with this status is{reset}{nl}   {white}attacked, {underline}50% of the damage{reset}{white} goes back to the {underline}attacker.{reset}";
    this->Register["en-US"]["menu.ginfo.weak"]              = "Weakness";
    this->Register["en-US"]["menu.ginfo.weak.info"]         = "{white}A weakened enemy has their HP and AR {underline}{purple}capped at 60 only.{reset}{nl}   {white}Their energy replenishes {underline}{purple}75% less per round{reset}{white}, too.{reset}{nl}   {white}They also {underline}{purple}attack less{reset}{white}. This status only lasts {weakness_time} rounds.{reset}";

    // Settings texts
    this->Register["en-US"]["menu.options.title"]           = "Settings";
    this->Register["en-US"]["menu.options.cat1"]            = " 1 DISCORD SETTINGS ";
    this->Register["en-US"]["menu.options.cat2"]            = " 2 LANGUAGE SETTINGS ";
    this->Register["en-US"]["menu.options.cat3"]            = " 3 USER SETTINGS ";
    this->Register["en-US"]["menu.options.c1o1"]            = "Discord RPC:";
    this->Register["en-US"]["menu.options.login"]           = "Logged in as";
    this->Register["en-US"]["menu.options.currlang"]        = "Current language:";
    this->Register["en-US"]["menu.options.changelang"]      = "Change language...";
    this->Register["en-US"]["menu.options.langutils"]       = "Language utilities...";
    this->Register["en-US"]["menu.options.export1"]         = "Export language to Datapack (xml)...";
    this->Register["en-US"]["menu.options.export2"]         = "Export language as Text (txt)...";
    this->Register["en-US"]["menu.options.export3"]         = "Convert TXT to Datapack (xml)...";
    this->Register["en-US"]["menu.options.newuser"]         = "Create new user...";
    this->Register["en-US"]["menu.options.changename"]      = "Change username...";
    this->Register["en-US"]["menu.options.help1"]           = "{white}Press {green}1{white} to enter {green}Edit{white} mode. Press {red}9{white} to {red}go back to main menu{white}.{reset}";
    this->Register["en-US"]["menu.options.help2"]           = "{white}Press {red}left arrow{white} to exit {red}Edit{white} mode.{reset}";
    this->Register["en-US"]["menu.options.help3"]           = "{white}Use {purple}up and down arrows{white} to {purple}move{white}.{reset}";
    this->Register["en-US"]["menu.options.help4"]           = "{white}Press {yellow}right arrow{white} to {yellow}change a setting{white}.{reset}";
    this->Register["en-US"]["menu.options.enteruser"]       = "Enter your username:";
    this->Register["en-US"]["menu.options.usererror"]       = "Username cannot have spaces!";
    this->Register["en-US"]["menu.options.lang.select"]     = "Language Selection";
    this->Register["en-US"]["menu.options.lang.loading"]    = "Loading...";
    this->Register["en-US"]["menu.options.lang.line1"]      = "Current language: {lang}";
    this->Register["en-US"]["menu.options.lang.line2"]      = "There are {lang_count} languages loaded.";
    this->Register["en-US"]["menu.options.lang.line3"]      = "Up/down arrows to move, right to select language and left to leave.";

    // Language utilities texts
    this->Register["en-US"]["menu.langutils.success"]       = "Successfully exported language {lang_id}!";
    this->Register["en-US"]["menu.langutils.fail"]          = "Something bad happened during exporting...";
    this->Register["en-US"]["menu.langutils.getpath"]       = "Please input the path to the TXT:";
    this->Register["en-US"]["menu.langutils.pathfail"]      = "Path doesn't exist!";
    this->Register["en-US"]["menu.langutils.notfile"]       = "Path does not lead to a file!";

    // Greet texts
    this->Register["en-US"]["greet.morning.1"]              = "{white}Good morning, {username}. Ready to kill?{reset}";
    this->Register["en-US"]["greet.morning.2"]              = "{white}Good morning, {username}. Grab a coffee and crush some entities.{reset}";
    this->Register["en-US"]["greet.morning.3"]              = "{white}Good morning, {username}. Rise and shine!{reset}";
    this->Register["en-US"]["greet.afternoon.1"]            = "{white}Good afternoon, {username}. Back for more blood?{reset}";
    this->Register["en-US"]["greet.afternoon.2"]            = "{white}Good afternoon, {username}. Today's lunch: Entities{reset}";
    this->Register["en-US"]["greet.afternoon.3"]            = "{white}Good afternoon, {username}. I would really go for a nap now...{reset}";
    this->Register["en-US"]["greet.evening.1"]              = "{white}Good evening, {username}. 5 minutes until bedtime.{reset}";
    this->Register["en-US"]["greet.evening.2"]              = "{white}Good evening, {username}. Entities are sleepy now, surprise attack!{reset}";
    this->Register["en-US"]["greet.evening.3"]              = "{white}Good evening, {username}. *{italic}Yawn{reset}{white}*{reset}";
    this->Register["en-US"]["greet.earlynight.1"]           = "{white}Good night, {username}. Can't sleep yet?{reset}";
    this->Register["en-US"]["greet.earlynight.2"]           = "{white}Good night, {username}. Was dinner yummy?{reset}";
    this->Register["en-US"]["greet.threeam.1"]              = "{white}Good night, {username}. Spooky time!{reset}";
    this->Register["en-US"]["greet.threeam.2"]              = "{white}Good night, {username}. The line between mortal and the other side blurs...{reset}";
    this->Register["en-US"]["greet.threeam.3"]              = "{white}Good night, {username}. Something feels off..{reset}";

    // Gameplay strings
    this->Register["en-US"]["game.battle.announce"]         = "{red}{italic}The fights begins. Good luck {username}!{reset}";
    this->Register["en-US"]["game.battle.what_happened"]    = "{white}What happened last round:{reset}{nl}{what_happened}{reset}";
    this->Register["en-US"]["game.battle.ply_header"]       = "{dark_gray}---<<< {blue}{bold}{username}'s{reset} {dark_gray}turn! >>>---{reset}";
    this->Register["en-US"]["game.battle.ene_header"]       = "{dark_gray}---<<< {red}{bold}Enemy's{reset} {dark_gray}turn! >>>---{reset}";
    this->Register["en-US"]["game.battle.enemy"]            = "ENEMY";
    this->Register["en-US"]["game.battle.regen_moves"]      = "Regenerate moves...";
    this->Register["en-US"]["game.battle.move_choose"]      = "{white}Choose your move. {dark_gray}{bold}[1,2,3,4,5] (0 to exit){reset}";
    this->Register["en-US"]["game.battle.exit"]             = "Do you really wanna end the battle?";
    this->Register["en-US"]["game.battle.skip"]             = "skipped the round.";
    this->Register["en-US"]["game.battle.enemy_skip"]       = "{red}{bold}Enemy{reset} {white}skipped the round.{reset}";
    this->Register["en-US"]["game.battle.no_energy"]        = "Not enough energy!";
    this->Register["en-US"]["game.battle.rerolled"]         = "{blue}{bold}{username}{reset}{white} rerolled their moves...{reset}";
    this->Register["en-US"]["game.battle.ai_think"]         = "The AI is thinking...";
    this->Register["en-US"]["game.moves.attack"]            = "{red}Attack! {white}Deal {purple}{value}{white} damage to opponent.{reset}";
    this->Register["en-US"]["game.moves.heal"]              = "{green}Heal! {white}Gives you {purple}+{value}{white} HP{reset}";
    this->Register["en-US"]["game.moves.regen"]             = "{blue}Regen armor{white}! Gives you {purple}+{value}{white} AR{reset}";
    this->Register["en-US"]["game.moves.autoheal"]          = "{white}Apply {green}AutoHeal {white}status! Gives you {purple}{value} {white}HP when it's your turn{reset}";
    this->Register["en-US"]["game.moves.icrit"]             = "{white}Apply {red}IncreasedCrit {white}status! Increased {red}critical attack chance{reset}";
    this->Register["en-US"]["game.moves.invis"]             = "{white}Apply {hot_pink}Invis {white}status! Opponent has a chance to {hot_pink}miss{reset}";
    this->Register["en-US"]["game.moves.poison"]            = "{white}Give opponent {dark_green}Poison {white}status! Deals {purple}{value}{white} poison damage{reset}";
    this->Register["en-US"]["game.moves.thorns"]            = "{white}Apply {teal}Thorns {white}status! Opponent will {bold}take damage too on attack{reset}";
    this->Register["en-US"]["game.moves.weakness"]          = "{white}Give opponent {brown}Weakness {white}status! Opponent will be weakened...{reset}";
    this->Register["en-US"]["game.moves.gameover"]          = "{white}---<<< {blue}{bold}{username}{reset} {white}dead. {red}{bold}Enemy{reset}{white} wins!!! >>>---{reset}";
    this->Register["en-US"]["game.moves.victory"]           = "{white}---<<< {red}{bold}Enemy{reset} {white}dead. {blue}{bold}{username}{reset}{white} wins!!! >>>---{reset}";
    this->Register["en-US"]["game.moves.rematch"]           = "Rematch!";
    this->Register["en-US"]["game.applied.autoheal"]        = "{white}has applied {green}Autoheal{white}.";
    this->Register["en-US"]["game.applied.incr_crit"]       = "{white}has applied {red}IncreasedCrit{white}.";
    this->Register["en-US"]["game.applied.invis"]           = "{white}has applied {hot_pink}Invis{white}.";
    this->Register["en-US"]["game.applied.poison"]          = "{who} {white}has given {dark_green}Poison{white} to {who2}{white}.{reset}";
    this->Register["en-US"]["game.applied.thorns"]          = "{white}has applied {teal}Thorns{white}.";
    this->Register["en-US"]["game.applied.weakness"]        = "{who} {white}has given {brown}Weakness{white} to {who2}{white}.{reset}";

    // Entity attack texts
    this->Register["en-US"]["entity.attack.ply_missed"]     = "{blue}{bold}{username}{reset} {white}tried to attack, but {italic}missed{reset}{white}!{reset}";
    this->Register["en-US"]["entity.attack.ene_missed"]     = "{red}{bold}Enemy{reset} {white}tried to attack, but {italic}missed{reset}{white}!{reset}";
    this->Register["en-US"]["entity.attack.ply_normal"]     = "{blue}{bold}{username}{reset} {white}has attacked {red}{bold}Enemy{reset}{white}! {red}{bold}Enemy{reset} {purple}-{dmg}HP{reset}";
    this->Register["en-US"]["entity.attack.ply_crit"]       = "{blue}{bold}{username}{reset} {white}has attacked {red}{bold}Enemy{reset}{white}! {gold}{italic}CRITICAL HIT{reset}{white}! {red}{bold}Enemy{reset} {purple}-{dmg}HP{reset}";
    this->Register["en-US"]["entity.attack.ene_normal"]     = "{red}{bold}Enemy{reset} {white}has attacked {blue}{bold}{username}{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";
    this->Register["en-US"]["entity.attack.ene_crit"]       = "{red}{bold}Enemy{reset} {white}has attacked {blue}{bold}{username}{reset}{white}! {gold}{italic}CRITICAL HIT{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";

    // Exit messages :3
    this->Register["en-US"]["exit.message.1"]               = "{white}Noooooo don't leave yet :<{reset}";
    this->Register["en-US"]["exit.message.win2"]            = "{white}Are you sure? {italic}Windows is much worse...{reset}";
    this->Register["en-US"]["exit.message.win3"]            = "{white}Of course, as if Windows is more fun!{reset}";
    this->Register["en-US"]["exit.message.win4"]            = "{white}You know that Bill Gates approves of this game, right?{reset}";
    this->Register["en-US"]["exit.message.win5"]            = "{white}Right right, don't forget to close the windows on the way out.{reset}";
    this->Register["en-US"]["exit.message.mac2"]            = "{white}Are you sure? {italic}Mac is much worse...{reset}";
    this->Register["en-US"]["exit.message.mac3"]            = "{white}Of course, as if Mac is more fun!{reset}";
    this->Register["en-US"]["exit.message.mac4"]            = "{white}You know that Steve Jobs approved of this game, right?{reset}";
    this->Register["en-US"]["exit.message.mac5"]            = "{white}An Apple a day keeps the wallet away.{reset}";
    this->Register["en-US"]["exit.message.lix2"]            = "{white}Are you sure? {italic}Linux is much worse...{reset}";
    this->Register["en-US"]["exit.message.lix3"]            = "{white}Of course, as if Linux is more fun!{reset}";
    this->Register["en-US"]["exit.message.lix4"]            = "{white}You know that Linus Torvalds approves of this game, right?{reset}";
    this->Register["en-US"]["exit.message.lix5"]            = "{white}Linuwux{reset}";
    this->Register["en-US"]["exit.message.6"]               = "{white}The enemy still has 6 hp left!{reset}";
    this->Register["en-US"]["exit.message.8"]               = "{white}Huh? Why?{reset}";
    this->Register["en-US"]["exit.message.9"]               = "{white}You leave now, you forfeit your kill count!{reset}";
    this->Register["en-US"]["exit.message.10"]              = "{white}Atleast you tried, can't argue with that.{reset}";
    this->Register["en-US"]["exit.message.11"]              = "{white}Don't go yet!{reset}";
    this->Register["en-US"]["exit.message.12"]              = "{white}Pssst, i'll give you 3 free powerups if you stay... ;){reset}";
    this->Register["en-US"]["exit.message.13"]              = "{white}Are you sure? It's dangerous outside...{reset}";
    this->Register["en-US"]["exit.message.14"]              = "{white}Tch, just go. Unworthy.{reset}";
    this->Register["en-US"]["exit.message.15"]              = "{white}Ok{reset}";
    this->Register["en-US"]["exit.message.16"]              = "{white}Honey are you cheating on me with Java games?{reset}";
    this->Register["en-US"]["exit.message.19"]              = "{white}The prophecy says you'll continue playing. You dare break the prophecy?{reset}";
    this->Register["en-US"]["exit.message.21"]              = "{white}Thank you for downloading our malware :3{reset}";
    this->Register["en-US"]["exit.message.22"]              = "{white}Press 'y', and in your coffin you will lay!{reset}";
    this->Register["en-US"]["exit.message.23"]              = "{white}Don't be silly! Stay a while longer!{reset}";
    this->Register["en-US"]["exit.message.24"]              = "{white}The entities live in your walls{reset}";
    this->Register["en-US"]["exit.message.25"]              = "{white}I, norbcodes, live rent free in your ceiling{reset}";
    this->Register["en-US"]["exit.message.26"]              = "{white}Really?{reset}";
    this->Register["en-US"]["exit.message.27"]              = "{white}For reals?{reset}";
    this->Register["en-US"]["exit.message.28"]              = "{white}Babeeee! No!{reset}";
    this->Register["en-US"]["exit.message.29"]              = "{white}Is your fridge running...?{reset}";
    this->Register["en-US"]["exit.message.30"]              = "{white}Is your stove turned off...?{reset}";
    this->Register["en-US"]["exit.message.31"]              = "{white}What? Heap memory allocs scared you away?{reset}";
    this->Register["en-US"]["exit.message.32"]              = "{white}There's a chance a neutrino particle is{nl}passing through your skull right now.{reset}";
    this->Register["en-US"]["exit.message.33"]              = "{white}Let that sink in.{reset}";
    this->Register["en-US"]["exit.message.34"]              = "{white}Oh no! Your 'y' button just broke!{reset}";
    this->Register["en-US"]["exit.message.35"]              = "{white}LMFAOOOOO{reset}";
    this->Register["en-US"]["exit.message.36"]              = "{white}The outside is not real. Wake up. Wake up.{reset}";
    this->Register["en-US"]["exit.message.37"]              = "{white}Original entities more fun?{reset}";
    this->Register["en-US"]["exit.message.39"]              = "{white}I, norbcodes, do not approve!!! >:({reset}";
    this->Register["en-US"]["exit.message.40"]              = "{white}Maybe i'll break your keyboard then{reset}";
    this->Register["en-US"]["exit.message.41"]              = "{white}Come back soon. We're gonna be having a pizza party.{reset}";
    this->Register["en-US"]["exit.message.42"]              = "{white}Goodbye :3{reset}";
    this->Register["en-US"]["exit.message.45"]              = "{white}*{italic}insert exit message here{reset}{white}*{reset}";
    this->Register["en-US"]["exit.message.47"]              = "{white}Dude, just choose a lower difficulty. No need for drastic measures.{reset}";
    this->Register["en-US"]["exit.message.48"]              = "{white}*{italic}insert threatening exit message here{reset}{white}*{reset}";
    this->Register["en-US"]["exit.message.49"]              = "{white}Fine, get out of my face.{reset}";
    this->Register["en-US"]["exit.message.50"]              = "{white}Nuuuuu pwease staay :({reset}";
    this->Register["en-US"]["exit.message.51"]              = "{white}><>     <---- fish{reset}";
    this->Register["en-US"]["exit.message.52"]              = "{red}exit{reset}{white}(){reset}";
    this->Register["en-US"]["exit.message.53"]              = "{white}No syntax highlighting for you!!!{reset}";
    this->Register["en-US"]["exit.message.54"]              = "{{red}}{{bold}}Damn, my formatting broke{{reset}}";
    this->Register["en-US"]["exit.message.56"]              = "{white}Do{nl}  not{nl}     exit,{nl}          PLEASE{reset}";
    this->Register["en-US"]["exit.message.57"]              = "{white}I hate you >:({reset}";
    this->Register["en-US"]["exit.message.58"]              = "{white}You KNOW that this is the best game ever made, right?{reset}";
    this->Register["en-US"]["exit.message.59"]              = "{white}Classic, just give up when you fail once.{reset}";
    this->Register["en-US"]["exit.message.61"]              = "{white}I will report your Github account if you leave >:({reset}";
    this->Register["en-US"]["exit.message.62"]              = "{white}Meow meerpppp :3{reset}";
    this->Register["en-US"]["exit.message.64"]              = "{white}And the \"Best Player\" award goes to...{reset}";
    this->Register["en-US"]["exit.message.65"]              = "{white}no balls :>{reset}";
    this->Register["en-US"]["exit.message.67"]              = "{white}Yeah go play your Valorant or whatever you kids play nowadays{reset}";
    this->Register["en-US"]["exit.message.70"]              = "{white}When's your birthday?{reset}";
    this->Register["en-US"]["exit.message.special"]         = "{white}Did you know? Each of these message has a {purple}{perc:.2f}%{white} chance to appear.{reset}";

    // Credits :3
    this->Register["en-US"]["credits.title1"]               = "DEM CREDITS!!!!";
    this->Register["en-US"]["credits.gameby"]               = "{gold}{bold}Game{reset} {white}by{reset} {blue}{bold}Norb{reset}";
    this->Register["en-US"]["credits.writtenin"]            = "{hot_pink}{bold}Written{reset} {white}in{reset} {green}{bold}C++{reset}";
    this->Register["en-US"]["credits.moreinfo1"]            = "v1.0 coded in about 2 days.";
    this->Register["en-US"]["credits.moreinfo2"]            = "(As of writting the credits, Discord says I spent 6 hours on VScode)";
    this->Register["en-US"]["credits.moreinfo3"]            = "These fine colors picked out using";
    this->Register["en-US"]["credits.moreinfo4"]            = "Check out entity1 and the homepage at";
    this->Register["en-US"]["credits.title2"]               = "EXTERNAL LIBRARIES USED:";
    this->Register["en-US"]["credits.discordlib"]           = "{blue}{bold}discord-rpc{reset} {dark_gray}:: {lavender}{italic}Thanks to {name} :){reset}";
    this->Register["en-US"]["credits.fmtlib"]               = "{bold}{red}{{{orange}f{yellow}m{green}t{blue}}}{reset} {dark_gray}::{reset} {hot_pink}{italic}Thanks to the entire {name} lib team!! :P{reset}";
    this->Register["en-US"]["credits.pugilib"]              = "{white}{bold}pugi{reset}{brown}{bold}xml{reset} {dark_gray}::{reset} {pink}{italic}Thanks to {name} (a.k.a {name2} on github)!! :3{reset}";
    this->Register["en-US"]["credits.arglib"]               = "{orange}{bold}arg{gold}parse{reset} {dark_gray}::{reset} {green}{italic}Thanks to {name} {dark_green}for this cool lib :>{reset}";
    this->Register["en-US"]["credits.jsonlib"]              = "{blue}{bold}{italic}json{reset} {dark_gray}::{reset} {teal}{italic}Thanks to {name} for this epic lib!!{reset}";
    this->Register["en-US"]["credits.compiled"]             = "{dark_gray}entities2.cpp version {entities2_ver} compiled at {compile_date} {compile_time} ;){reset}";
    this->Register["en-US"]["credits.title3"]               = "SPECIAL THANKS TO THE TRANSLATORS:";
    this->Register["en-US"]["credits.slovak"]               = "{blue}{bold}{name}{reset} {dark_gray}::{reset} {white}{bold}English{reset}{white} (base game lang) and {bold}Slovak{reset}";
    this->Register["en-US"]["credits.russian"]              = "{purple}{bold}{name}{reset} {dark_gray}::{reset} {white}Translated to {bold}Russian{reset}";
    this->Register["en-US"]["credits.portuguese"]           = "{yellow}{bold}{name}{reset} {dark_gray}::{reset} {white}Translated to {bold}Portuguese{reset}";
    this->Register["en-US"]["credits.tagalog"]              = "{light_blue}{bold}{name}{reset} {dark_gray}::{reset} {white}Translated to {bold}Tagalog{reset}";
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Load all of Slovak translation.
 * \note Needs to be enabled when cmake is invoked...
 */
void TranslationEngine::LoadSlovak()
{
    #ifdef __ENTITIES2_BAKED_IN_SLOVAK__
    
    // Language specific strings
    this->Register["sk-SK"]["lang.name"]                    = "Slovenčina (Slovensko)";
    this->Register["sk-SK"]["lang.id"]                      = "sk-SK";

    // General texts
    this->Register["sk-SK"]["general.quit"]                 = "Odísť z hry";
    this->Register["sk-SK"]["general.exit"]                 = "Späť";
    this->Register["sk-SK"]["general.on"]                   = "Áno";
    this->Register["sk-SK"]["general.off"]                  = "Nie";
    this->Register["sk-SK"]["general.by"]                   = "od";
    this->Register["sk-SK"]["general.enter_to_exit"]        = "Enterom naspäť.";
    this->Register["sk-SK"]["general.healed"]               = "si uzdravil";
    this->Register["sk-SK"]["general.regenerated"]          = "si regeneroval";
    this->Register["sk-SK"]["general.enemy"]                = "Nepriateľ";

    // Main menu texts
    this->Register["sk-SK"]["menu.main.subtitle"]           = "Hra vytvorená vývorajom norbcodes.";
    this->Register["sk-SK"]["menu.main.optionpick"]         = "Zvolte možnosť:";
    this->Register["sk-SK"]["menu.main.play"]               = "Hrať!";
    this->Register["sk-SK"]["menu.main.ginfo"]              = "Poučenie o hre";
    this->Register["sk-SK"]["menu.main.datapacks"]          = "Dátové balíky";
    this->Register["sk-SK"]["menu.main.settings"]           = "Nastavenia";
    this->Register["sk-SK"]["menu.exit.confirm"]            = "Naozaj chceš odísť?";
    this->Register["sk-SK"]["menu.unstable"]                = "{red}Hraješ na verzii ktorá je ešte stále{bold} pod vývojom!{reset}{nl}{white}Pokračuj s opatrnosťou. {red}Si si istý že chceš hrať? [y,n]{reset}";

    // Difficulty picker texts
    this->Register["sk-SK"]["menu.diffpicker.title"]        = "Výber náročnosti";
    this->Register["sk-SK"]["menu.diffpicker.easy"]         = "Nakopem entitám prdel!";
    this->Register["sk-SK"]["menu.diffpicker.medium"]       = "Videl som aj horšie";
    this->Register["sk-SK"]["menu.diffpicker.hard"]         = "Dolu s entitami...";
    this->Register["sk-SK"]["menu.diffpicker.random"]       = "Náhodne!";
    this->Register["sk-SK"]["menu.diffpicker.record"]       = "Zachytiť Demo záznam";

    // Datapack viewer stuff
    this->Register["sk-SK"]["menu.datapacks.title"]         = "Dátové balíky";
    this->Register["sk-SK"]["menu.datapacks.loaded"]        = "{white}Práve teraz nainštalovaných {purple}{datapack_count}{reset}{white} dátových balíkov.{reset}";
    this->Register["sk-SK"]["menu.datapacks.help1"]         = "Použi šipky hore a dole na skrolovanie.";
    this->Register["sk-SK"]["menu.datapacks.empty"]         = "Neboli nájdené žiadne dátové balíky!";
    this->Register["sk-SK"]["menu.datapacks.info"]          = "Šipkou doľava sa vrátiš späť. Šipkou doprava sa ti zobrazí info of dátovom balíku.";
    this->Register["sk-SK"]["menu.datapacks.title2"]        = "Informácie o dátovom balíku";
    this->Register["sk-SK"]["menu.datapacks.subtitle"]      = "Metadáta:";
    this->Register["sk-SK"]["menu.datapacks.name"]          = "Meno:";
    this->Register["sk-SK"]["menu.datapacks.author"]        = "Autor:";
    this->Register["sk-SK"]["menu.datapacks.id"]            = "Identifikátor:";
    this->Register["sk-SK"]["menu.datapacks.desc"]          = "Popis:";
    this->Register["sk-SK"]["menu.datapacks.size"]          = "Veľkosť na disku:";
    this->Register["sk-SK"]["menu.datapacks.veryhuge"]      = "Väčší ako Jupiter";
    this->Register["sk-SK"]["menu.datapacks.error1"]        = "XML sekcia \"Datapack\" neexistuje!";
    this->Register["sk-SK"]["menu.datapacks.error2"]        = "XML sekcia \"Meta\" neexistuje!";
    this->Register["sk-SK"]["menu.datapacks.error3"]        = "XML sekcia \"Data\" neexistuje!";
    this->Register["sk-SK"]["menu.datapacks.error4"]        = "Dátový balík nemá meno!";
    this->Register["sk-SK"]["menu.datapacks.error5"]        = "Dátový balík nemá autora!";
    this->Register["sk-SK"]["menu.datapacks.error6"]        = "Dátový balík nemá identifikátor!";
    this->Register["sk-SK"]["menu.datapacks.error7"]        = "Chybné preklady!";
    this->Register["sk-SK"]["menu.datapacks.error8"]        = "Pozdrav nemá zadaný čas!";
    this->Register["sk-SK"]["menu.datapacks.error9"]        = "Prázdny podzdrav!";
    this->Register["sk-SK"]["menu.datapacks.error10"]       = "Prázdna exitová správa!";

    // Gameplay info
    this->Register["sk-SK"]["menu.ginfo.title"]             = "Poučenie o hre";
    this->Register["sk-SK"]["menu.ginfo.tips"]              = "Tipy a finty";
    this->Register["sk-SK"]["menu.ginfo.status"]            = "Efekty a čo robia";
    this->Register["sk-SK"]["menu.ginfo.tiptitle"]          = "TIPY A FINTY";
    this->Register["sk-SK"]["menu.ginfo.tip1"]              = "Môžeš preskočiť svoj ťah s iným klávesom ako 0, 1, 2, 3 alebo 4.";
    this->Register["sk-SK"]["menu.ginfo.tip2"]              = "Ak potrebuješ, môžeš preskočiť svoj ťah aby si si obnovil energiu.";
    this->Register["sk-SK"]["menu.ginfo.tip3"]              = "Oponent bude chcieť vyskúšať útok ak má viac ako 60 HP.";
    this->Register["sk-SK"]["menu.ginfo.statustitle1"]      = "EFEKTY";
    this->Register["sk-SK"]["menu.ginfo.statustitle2"]      = "a ako fungujú...";
    this->Register["sk-SK"]["menu.ginfo.autoheal"]          = "AutoHeal";
    this->Register["sk-SK"]["menu.ginfo.autoheal.info"]     = "{white}Na začiatku {underline}dalšieho ťahu{reset}{white}, tá entita, ktorá{reset}{nl}   {white}je na ťahu {underline}dostane {purple}{bold}+{autoheal_amount}HP života.{reset}";
    this->Register["sk-SK"]["menu.ginfo.icrit"]             = "Kritický útok";
    this->Register["sk-SK"]["menu.ginfo.icrit.info"]        = "{white}Ak má entita tento efekt, má {underline}približne {purple}30%{reset}{nl}   {white}šancu na {underline}kritický útok{reset}{white}, ktorý uberá{reset}{nl}   {white}oveľa {underline}viac života (HP).{reset}";
    this->Register["sk-SK"]["menu.ginfo.invis"]             = "Neviditelnosť";
    this->Register["sk-SK"]["menu.ginfo.invis.info"]        = "{white}Ak má entita tento efekt, má{reset}{nl}   {underline}{purple}~20%{reset} {white}šancu že sa oponent {underline}netrafí{reset}{nl}   {white}{underline}pri útoku na túto entitu.{reset}";
    this->Register["sk-SK"]["menu.ginfo.poison"]            = "Jed";
    this->Register["sk-SK"]["menu.ginfo.poison.info"]       = "{white}Na začiatku daľšieho ťahu, tá entita ktorá má tento efekt{reset}{nl}   {white}odobere sa im {underline}{purple}{bold}-{poison_amount}HP života.{reset}";
    this->Register["sk-SK"]["menu.ginfo.thorns"]            = "Tŕnie";
    this->Register["sk-SK"]["menu.ginfo.thorns.info"]       = "{white}Ak niekto na entitu s týmto efektom{reset}{nl}   {white}zaútočí, {underline}50% útoku{reset}{white} ide späť do {underline}útočníka.{reset}";
    this->Register["sk-SK"]["menu.ginfo.weak"]              = "Slabosť";
    this->Register["sk-SK"]["menu.ginfo.weak.info"]         = "{white}Oslabená entita má svoje HP a AR {underline}{purple}obmedzené iba na 60.{reset}{nl}   {white}Ich energia sa dobíja {underline}{purple}75% menej za ťah{reset}{white}.{reset}{nl}   {white}Tak tiež majú {underline}{purple}menší útok{reset}{white}. Tento efekt trvá iba {weakness_time} ťahy.{reset}";

    // Settings texts
    this->Register["sk-SK"]["menu.options.title"]           = "Nastavenia";
    this->Register["sk-SK"]["menu.options.cat1"]            = " 1 NASTAVENIA DISCORDU ";
    this->Register["sk-SK"]["menu.options.cat2"]            = " 2 NASTAVENIA JAZYKOV ";
    this->Register["sk-SK"]["menu.options.cat3"]            = " 3 POUŽÍVATEĽSKÉ NASTAVENIA ";
    this->Register["sk-SK"]["menu.options.c1o1"]            = "Discord RPC:";
    this->Register["sk-SK"]["menu.options.login"]           = "Prihlásení ako";
    this->Register["sk-SK"]["menu.options.currlang"]        = "Nastavený jazyk:";
    this->Register["sk-SK"]["menu.options.changelang"]      = "Zmeniť jazyk...";
    this->Register["sk-SK"]["menu.options.langutils"]       = "Jazykové funkcie...";
    this->Register["sk-SK"]["menu.options.export1"]         = "Exportovať jazyk ako dátový balík (xml)...";
    this->Register["sk-SK"]["menu.options.export2"]         = "Exportovať jazyk ako text (txt)...";
    this->Register["sk-SK"]["menu.options.export3"]         = "Previesť text (TXT) na dátový balík (xml)...";
    this->Register["sk-SK"]["menu.options.newuser"]         = "Vytvoriť nového používatela...";
    this->Register["sk-SK"]["menu.options.changename"]      = "Zmeniť používatelské meno...";
    this->Register["sk-SK"]["menu.options.help1"]           = "{white}Stlač {green}1{white} pre {green}Editačný{white} mód. Stlač {red}9 aby si sa vrátil do hlavného menu{white}.{reset}";
    this->Register["sk-SK"]["menu.options.help2"]           = "{red}Šipka doľava{white} aby si odišiel z {red}Editačného{white} módu.{reset}";
    this->Register["sk-SK"]["menu.options.help3"]           = "{purple}Šipky hore a dole{white} na {purple}skrolovanie{white}.{reset}";
    this->Register["sk-SK"]["menu.options.help4"]           = "{yellow}Šipka doprava{white} na {yellow}zmenenie nastavenia{white}.{reset}";
    this->Register["sk-SK"]["menu.options.enteruser"]       = "Napíš svoje používatelské meno:";
    this->Register["sk-SK"]["menu.options.usererror"]       = "Meno nemôže mať medzeri!";
    this->Register["sk-SK"]["menu.options.lang.select"]     = "Výber jazyka";
    this->Register["sk-SK"]["menu.options.lang.loading"]    = "Načítavanie...";
    this->Register["sk-SK"]["menu.options.lang.line1"]      = "Nastavený jazyk: {lang}";
    this->Register["sk-SK"]["menu.options.lang.line2"]      = "Sú nainštalované {lang_count} jazyky.";
    this->Register["sk-SK"]["menu.options.lang.line3"]      = "Šipky hore a dole na skrolovanie, doprava na výber jazyka a doľava naspäť.";

    // Language utilities texts
    this->Register["sk-SK"]["menu.langutils.success"]       = "Správne sa exportoval jazyk {lang_id}!";
    this->Register["sk-SK"]["menu.langutils.fail"]          = "Nastala chyba pri exporte...";
    this->Register["sk-SK"]["menu.langutils.getpath"]       = "Zadaj adresu súbora:";
    this->Register["sk-SK"]["menu.langutils.pathfail"]      = "Adresa nieje platná!";
    this->Register["sk-SK"]["menu.langutils.notfile"]       = "Adresa nevedie k súboru!";

    // Greet texts
    this->Register["sk-SK"]["greet.morning.1"]              = "{white}Dobré ráno, {username}. Pripravený na lov?{reset}";
    this->Register["sk-SK"]["greet.morning.2"]              = "{white}Dobré ráno, {username}. Sprav si kávu a zadup niake entity do zeme.{reset}";
    this->Register["sk-SK"]["greet.morning.3"]              = "{white}Dobré ránko, {username}. Stávaj!{reset}";
    this->Register["sk-SK"]["greet.afternoon.1"]            = "{white}Dobrý deň, {username}. Späť k lovu?{reset}";
    this->Register["sk-SK"]["greet.afternoon.2"]            = "{white}Dobrý deň, {username}. Dnešné menu: entity{reset}";
    this->Register["sk-SK"]["greet.afternoon.3"]            = "{white}Dobrý deň, {username}. Chce sa mi spať...{reset}";
    this->Register["sk-SK"]["greet.evening.1"]              = "{white}Dobrý večer, {username}. Ešte 5 minút a šup do postele.{reset}";
    this->Register["sk-SK"]["greet.evening.2"]              = "{white}Dobrý večer, {username}. Entitám sa che teraz spať, prekvap ich!{reset}";
    this->Register["sk-SK"]["greet.evening.3"]              = "{white}Dobrý večer, {username}. Pardón, zíva sa mi...{reset}";
    this->Register["sk-SK"]["greet.earlynight.1"]           = "{white}Dobrý večer, {username}. Nechce sa ti spať?{reset}";
    this->Register["sk-SK"]["greet.earlynight.2"]           = "{white}Dobrý večer, {username}. Chutila ti večera?{reset}";
    this->Register["sk-SK"]["greet.threeam.1"]              = "{white}{username}, nie je niak neskoro? Čas na horor!{reset}";
    this->Register["sk-SK"]["greet.threeam.2"]              = "{white}{username}, nie je niak neskoro? Hranica s podsvetím sa rozmazáva...{reset}";
    this->Register["sk-SK"]["greet.threeam.3"]              = "{white}{username}, nie je niak neskoro? Niečo mi tu nehraje..{reset}";

    // Gameplay strings
    this->Register["sk-SK"]["game.battle.announce"]         = "{red}{italic}Boj sa začal. Veľa šťastia {username}!{reset}";
    this->Register["sk-SK"]["game.battle.what_happened"]    = "{white}Čo sa stalo minulý ťah:{reset}{nl}{what_happened}{reset}";
    this->Register["sk-SK"]["game.battle.ply_header"]       = "{dark_gray}---<<< {blue}{bold}{username}{reset} {dark_gray}na ťahu! >>>---{reset}";
    this->Register["sk-SK"]["game.battle.ene_header"]       = "{dark_gray}---<<< {red}{bold}Nepriateľ{reset} {dark_gray}na ťahu! >>>---{reset}";
    this->Register["sk-SK"]["game.battle.enemy"]            = "NEPRIATEĽ";
    this->Register["sk-SK"]["game.battle.regen_moves"]      = "Vymeniť ťahy...";
    this->Register["sk-SK"]["game.battle.move_choose"]      = "{white}Vyber si svoj ťah. {dark_gray}{bold}[1,2,3,4,5] (0 odídeš z boja){reset}";
    this->Register["sk-SK"]["game.battle.exit"]             = "Naozaj sa chceš vzdať?";
    this->Register["sk-SK"]["game.battle.skip"]             = "preskočil ťah.";
    this->Register["sk-SK"]["game.battle.enemy_skip"]       = "{red}{bold}Nepriateľ{reset} {white}preskočil ťah.{reset}";
    this->Register["sk-SK"]["game.battle.no_energy"]        = "Nedostatok energie!";
    this->Register["sk-SK"]["game.battle.rerolled"]         = "{white}Hráč {blue}{bold}{username}{reset}{white} si vymenil ťahy...{reset}";
    this->Register["sk-SK"]["game.battle.ai_think"]         = "Umelá inteligencia rozmýšľa...";
    this->Register["sk-SK"]["game.moves.attack"]            = "{red}Zaútočiť! {white}Uber oponentovi {purple}{value}{white} HP života.{reset}";
    this->Register["sk-SK"]["game.moves.heal"]              = "{green}Oživ sa! {white}Oživíš si {purple}+{value}{white} HP života{reset}";
    this->Register["sk-SK"]["game.moves.regen"]             = "{blue}Regenerácia brnenia{white}! Vráti sa ti {purple}+{value}{white} AR brnenia{reset}";
    this->Register["sk-SK"]["game.moves.autoheal"]          = "{white}Aplikuj si {green}AutoHeal{white}! Oživí ti {purple}{value}{white} HP života každý tvoj ťah{reset}";
    this->Register["sk-SK"]["game.moves.icrit"]             = "{white}Aplikuj si {red}Kritický útok{white}! Zvýšená šanca na {red}kritický zásah pri útoku{reset}";
    this->Register["sk-SK"]["game.moves.invis"]             = "{white}Aplikuj si {hot_pink}Neviditelnosť{white}! Oponent má šancu {hot_pink}sa netrafiť pri útoku{reset}";
    this->Register["sk-SK"]["game.moves.poison"]            = "{white}Daj oponentovi {dark_green}Otravu{white}! Uberá {purple}{value}{white} HP života každý ťah{reset}";
    this->Register["sk-SK"]["game.moves.thorns"]            = "{white}Aplikuj si {teal}Tŕnie{white}! Oponent {bold}bude dostávať útok späť{reset}";
    this->Register["sk-SK"]["game.moves.weakness"]          = "{white}Pridaj oponentovy {brown}Slabosť{white}! Oponent bude mať problém...{reset}";
    this->Register["sk-SK"]["game.moves.gameover"]          = "{white}---<<< Hráč {blue}{bold}{username}{reset} {white}je mŕtvy. {red}{bold}Nepriateľ{reset}{white} vyhral!!! >>>---{reset}";
    this->Register["sk-SK"]["game.moves.victory"]           = "{white}---<<< {red}{bold}Nepriateľ{reset} {white}je mŕtvy. Hráč {blue}{bold}{username}{reset}{white} vyhral!!! >>>---{reset}";
    this->Register["sk-SK"]["game.moves.rematch"]           = "Odveta!";
    this->Register["sk-SK"]["game.applied.autoheal"]        = "{white}si aplikoval {green}Autoheal{white}.";
    this->Register["sk-SK"]["game.applied.incr_crit"]       = "{white}si aplikoval {red}IncreasedCrit{white}.";
    this->Register["sk-SK"]["game.applied.invis"]           = "{white}si aplikoval {hot_pink}Neviditelnosť{white}.";
    this->Register["sk-SK"]["game.applied.poison"]          = "\"{who}\" {white}dal {dark_green}Otravu{white} \"{who2}\"-ovi{white}.{reset}";
    this->Register["sk-SK"]["game.applied.thorns"]          = "{white}si aplikoval {teal}Tŕnie{white}.";
    this->Register["sk-SK"]["game.applied.weakness"]        = "\"{who}\" {white}dal {brown}Slabosť{white} \"{who2}\"-ovi{white}.{reset}";

    // Entity attack texts
    this->Register["sk-SK"]["entity.attack.ply_missed"]     = "{blue}{bold}{username}{reset} {white}chceľ zaútočiť, ale sa {italic}netrafil{reset}{white}!{reset}";
    this->Register["sk-SK"]["entity.attack.ene_missed"]     = "{red}{bold}Nepriateľ{reset} {white}chceľ zaútočiť, ale sa {italic}netrafil{reset}{white}!{reset}";
    this->Register["sk-SK"]["entity.attack.ply_normal"]     = "{blue}{bold}{username}{reset} {white}zauútočil na {red}{bold}nepriateľa{reset}{white}! {red}{bold}Nepriateľ{reset} {purple}-{dmg}HP{reset}";
    this->Register["sk-SK"]["entity.attack.ply_crit"]       = "{blue}{bold}{username}{reset} {white}zauútočil na {red}{bold}nepriateľa{reset}{white}! {gold}{italic}KRITICKÝ ZÁSAH{reset}{white}! {red}{bold}Nepriateľ{reset} {purple}-{dmg}HP{reset}";
    this->Register["sk-SK"]["entity.attack.ene_normal"]     = "{red}{bold}Nepriateľ{reset} {white}zauútočil na hráča {blue}{bold}{username}{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";
    this->Register["sk-SK"]["entity.attack.ene_crit"]       = "{red}{bold}Nepriateľ{reset} {white}zauútočil na hráča {blue}{bold}{username}{reset}{white}! {gold}{italic}KRITICKÝ ZÁSAH{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";

    // Exit messages :3
    this->Register["sk-SK"]["exit.message.1"]               = "{white}Nieeeeee, neodchádzaj :<{reset}";
    this->Register["sk-SK"]["exit.message.win2"]            = "{white}Si si istý? {italic}Windows je oveľa horší...{reset}";
    this->Register["sk-SK"]["exit.message.win3"]            = "{white}Samozrejme, určite je Windows vačšia zábava!{reset}";
    this->Register["sk-SK"]["exit.message.win4"]            = "{white}Však vieš že Bill Gates hráva túto hru?{reset}";
    this->Register["sk-SK"]["exit.message.win5"]            = "{white}Nezabudni po sebe zavrieť okná.{reset}";
    this->Register["sk-SK"]["exit.message.mac2"]            = "{white}Si si istý? {italic}Mac je ešte horší...{reset}";
    this->Register["sk-SK"]["exit.message.mac3"]            = "{white}Samozrejme, ako keby Mac je vačšia sranda!{reset}";
    this->Register["sk-SK"]["exit.message.mac4"]            = "{white}Vedeľ si že Steve Jobs hrával túto hru?{reset}";
    this->Register["sk-SK"]["exit.message.mac5"]            = "{white}Koľko si dal za svoj iphone?{reset}";
    this->Register["sk-SK"]["exit.message.lix2"]            = "{white}Si si istý? {italic}Linux je oveľa horší...{reset}";
    this->Register["sk-SK"]["exit.message.lix3"]            = "{white}Samozrejme, ako keby Linux je zábavnejší!{reset}";
    this->Register["sk-SK"]["exit.message.lix4"]            = "{white}Vieš o tom že Linus Torvalds hráva túto hru, však?{reset}";
    this->Register["sk-SK"]["exit.message.lix5"]            = "{white}Linuwux{reset}";
    this->Register["sk-SK"]["exit.message.6"]               = "{white}Nepriateľovi ostali ešte 6 HP!{reset}";
    this->Register["sk-SK"]["exit.message.8"]               = "{white}Hm? Prečo?{reset}";
    this->Register["sk-SK"]["exit.message.9"]               = "{white}Odídeš a vynuluje sa ti kill count!{reset}";
    this->Register["sk-SK"]["exit.message.10"]              = "{white}Aspoň si to vyskúšal, s tým sa nedá arguovať.{reset}";
    this->Register["sk-SK"]["exit.message.11"]              = "{white}Neodchádzaj!{reset}";
    this->Register["sk-SK"]["exit.message.12"]              = "{white}Pssst, dám ti zadarmo 3 powerupky keď budeš ďalej hrať... ;){reset}";
    this->Register["sk-SK"]["exit.message.13"]              = "{white}Si si naozaj istý? Tam vonku je to dosť nebezpečné...{reset}";
    this->Register["sk-SK"]["exit.message.14"]              = "{white}Zmizni.{reset}";
    this->Register["sk-SK"]["exit.message.15"]              = "{white}Okej{reset}";
    this->Register["sk-SK"]["exit.message.16"]              = "{white}Zlatko, podvádzaš ma s Java hrámi?{reset}";
    this->Register["sk-SK"]["exit.message.19"]              = "{white}Proroctvo hovorí že zostaneš a budeš hrať dalej. Naozaj chceš porušiť proroctvo?{reset}";
    this->Register["sk-SK"]["exit.message.21"]              = "{white}Ďakujem že si si nainštaloval môj malware :3{reset}";
    this->Register["sk-SK"]["exit.message.22"]              = "{white}Stlač 'y', a priprav sa na svoj pohreb.{reset}";
    this->Register["sk-SK"]["exit.message.23"]              = "{white}Nebuď hlúpy! Zostaň trochu dlhšie!{reset}";
    this->Register["sk-SK"]["exit.message.24"]              = "{white}Entity bývajú v tvojich stenách...{reset}";
    this->Register["sk-SK"]["exit.message.25"]              = "{white}Ja, norbcodes, žijem v tvojej povale, ani neplatím nájom.{reset}";
    this->Register["sk-SK"]["exit.message.26"]              = "{white}Naozaj?{reset}";
    this->Register["sk-SK"]["exit.message.27"]              = "{white}Akože, naozaj?{reset}";
    this->Register["sk-SK"]["exit.message.28"]              = "{white}Zlatko! Nie!{reset}";
    this->Register["sk-SK"]["exit.message.29"]              = "{white}Je tvoja chladnička funkčná...?{reset}";
    this->Register["sk-SK"]["exit.message.30"]              = "{white}Je tvoj sporák vypnutý...?{reset}";
    this->Register["sk-SK"]["exit.message.31"]              = "{white}Čože? Manuálna správa pamäte ťa vystrašila?{reset}";
    this->Register["sk-SK"]["exit.message.32"]              = "{white}Je malá šanca, že v tomto momente, neutrino častica{nl}prechádza cez tvoju lebku.{reset}";
    this->Register["sk-SK"]["exit.message.33"]              = "{white}Premysli si to.{reset}";
    this->Register["sk-SK"]["exit.message.34"]              = "{white}Ale nie! Tvoja 'y' klávesa sa pokazila!{reset}";
    this->Register["sk-SK"]["exit.message.35"]              = "{white}HAHAHAHAHAHAHAHAHAHAHAHA{reset}";
    this->Register["sk-SK"]["exit.message.36"]              = "{white}Vonok neexistuje. Preber sa. Preber sa.{reset}";
    this->Register["sk-SK"]["exit.message.37"]              = "{white}Predošlá hra je zábavnejšia?{reset}";
    this->Register["sk-SK"]["exit.message.39"]              = "{white}Ja, norbcodes, toto neschvalujem!!! >:({reset}";
    this->Register["sk-SK"]["exit.message.40"]              = "{white}Možno ti teda zničím klávesnicu.{reset}";
    this->Register["sk-SK"]["exit.message.41"]              = "{white}Vrát sa o pár hodín. Budeme mať pizza party.{reset}";
    this->Register["sk-SK"]["exit.message.42"]              = "{white}Dovidenia :3{reset}";
    this->Register["sk-SK"]["exit.message.45"]              = "{white}*{italic}sem vlož exitovú správu{reset}{white}*{reset}";
    this->Register["sk-SK"]["exit.message.47"]              = "{white}Kámo, proste si zníž obtiažnosť. Neni potreba pre drastické zákroky.{reset}";
    this->Register["sk-SK"]["exit.message.48"]              = "{white}*{italic}sem vlož exitovú hrozbu{reset}{white}*{reset}";
    this->Register["sk-SK"]["exit.message.49"]              = "{white}Fajn, zmizni mi z očí.{reset}";
    this->Register["sk-SK"]["exit.message.50"]              = "{white}Nieeee prosííííím neodchádzaj :({reset}";
    this->Register["sk-SK"]["exit.message.51"]              = "{white}><>     <---- ryba{reset}";
    this->Register["sk-SK"]["exit.message.52"]              = "{red}exit{reset}{white}(){reset}";
    this->Register["sk-SK"]["exit.message.53"]              = "{white}Žiadne syntax zvýraznovanie pre teba!!!{reset}";
    this->Register["sk-SK"]["exit.message.54"]              = "{{red}}{{bold}}Aj, pokazilo sa mi formátovanie{{reset}}";
    this->Register["sk-SK"]["exit.message.56"]              = "{white}Neodchádzaj{nl}           PROSÍM{reset}";
    this->Register["sk-SK"]["exit.message.57"]              = "{white}Neznášam ťa >:({reset}";
    this->Register["sk-SK"]["exit.message.58"]              = "{white}VIEŠ že toto je najlepšia hra na celom svete, však?{reset}";
    this->Register["sk-SK"]["exit.message.59"]              = "{white}Samozrejme, hneď sa zdávaš keď sa ti nedarí.{reset}";
    this->Register["sk-SK"]["exit.message.61"]              = "{white}Nahlásim tvoj Github účet keď odídeš >:({reset}";
    this->Register["sk-SK"]["exit.message.62"]              = "{white}Mňau mrrrrrr :3{reset}";
    this->Register["sk-SK"]["exit.message.64"]              = "{white}A ocenenie za \"Najlepšieho hráča\" patrí...{reset}";
    this->Register["sk-SK"]["exit.message.65"]              = "{white}Bojko :>{reset}";
    this->Register["sk-SK"]["exit.message.67"]              = "{white}Áno áno, choj si zahrať ten tvoj Valorant alebo čo to teraz deti hrávaju{reset}";
    this->Register["sk-SK"]["exit.message.70"]              = "{white}Kedy máš narodky?{reset}";
    this->Register["sk-SK"]["exit.message.special"]         = "{white}Vedel si o tom, že každá z týchto správ má {purple}{perc:.2f}%{white} šancu, že sa tu objavý?{reset}";

    // Credits :3
    this->Register["sk-SK"]["credits.title1"]               = "DÔLEŽITÉ ZMIENKY!!!!!";
    this->Register["sk-SK"]["credits.gameby"]               = "{gold}{bold}Hru{reset} {white}vytvoril{reset} {blue}{bold}Norb{reset}";
    this->Register["sk-SK"]["credits.writtenin"]            = "{hot_pink}{bold}Napísana{reset} {white}jazykom{reset} {green}{bold}C++{reset}";
    this->Register["sk-SK"]["credits.moreinfo1"]            = "Verzia 1.0 napísana v približne 2 dňoch.";
    this->Register["sk-SK"]["credits.moreinfo2"]            = "(Pri písaní, Discord hovorí že už programujem 6 hodín v kuse)";
    this->Register["sk-SK"]["credits.moreinfo3"]            = "Tieto pekné farby boli vybraté pomocou";
    this->Register["sk-SK"]["credits.moreinfo4"]            = "Omrkni entity1 a hlavnú stránku na";
    this->Register["sk-SK"]["credits.title2"]               = "POUŽITÉ KNIŽNICE:";
    this->Register["sk-SK"]["credits.discordlib"]           = "{blue}{bold}discord-rpc{reset} {dark_gray}:: {lavender}{italic}Vďaka, {name} :){reset}";
    this->Register["sk-SK"]["credits.fmtlib"]               = "{bold}{red}{{{orange}f{yellow}m{green}t{blue}}}{reset} {dark_gray}::{reset} {hot_pink}{italic} Veľké poďakovanie celému {name} tímu!! :P{reset}";
    this->Register["sk-SK"]["credits.pugilib"]              = "{white}{bold}pugi{reset}{brown}{bold}xml{reset} {dark_gray}::{reset} {pink}{italic}Vďaka {name} (a.k.a {name2} na github)!! :3{reset}";
    this->Register["sk-SK"]["credits.arglib"]               = "{orange}{bold}arg{gold}parse{reset} {dark_gray}::{reset} {green}{italic}Ďakujem ti, {name}, {dark_green}za túto knižnicu :>{reset}";
    this->Register["sk-SK"]["credits.jsonlib"]              = "{blue}{bold}{italic}json{reset} {dark_gray}::{reset} {teal}{italic}Díky {name} za túto knižnicu!!{reset}";
    this->Register["sk-SK"]["credits.compiled"]             = "{dark_gray}entities2.cpp verzia {entities2_ver} skompilovaná {compile_date} {compile_time} ;){reset}";
    this->Register["sk-SK"]["credits.title3"]               = "ŠPECIALNE PODAKOVANIE TLMOČNÍKOM:";
    this->Register["sk-SK"]["credits.slovak"]               = "{blue}{bold}{name}{reset} {dark_gray}::{reset} {white}{bold}Angličtina{reset}{white} (hlavný jazyk hry) a {bold}slovenčina{reset}";
    this->Register["sk-SK"]["credits.russian"]              = "{purple}{bold}{name}{reset} {dark_gray}::{reset} {white}Preložil do {bold}ruštiny{reset}";
    this->Register["sk-SK"]["credits.portuguese"]           = "{yellow}{bold}{name}{reset} {dark_gray}::{reset} {white}Preložil do {bold}portugalčiny{reset}";
    this->Register["sk-SK"]["credits.tagalog"]              = "{light_blue}{bold}{name}{reset} {dark_gray}::{reset} {white}Preložil do jazyka {bold}tagalóg{reset}";
    
    #endif // __ENTITIES2_BAKED_IN_SLOVAK__
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Load all of Russian translation.
 * \note Needs to be enabled when cmake is invoked...
 */
void TranslationEngine::LoadRussian()
{
    #ifdef __ENTITIES2_BAKED_IN_RUSSIAN__
    
    // Language specific strings
    this->Register["ru-RU"]["lang.name"]                    = "Русский (Россия)";
    this->Register["ru-RU"]["lang.id"]                      = "ru-RU";

    // General texts
    this->Register["ru-RU"]["general.quit"]                 = "Выйти из игры";
    this->Register["ru-RU"]["general.exit"]                 = "Назад";
    this->Register["ru-RU"]["general.on"]                   = "Вкл.";
    this->Register["ru-RU"]["general.off"]                  = "Выкл.";
    this->Register["ru-RU"]["general.by"]                   = "от";
    this->Register["ru-RU"]["general.enter_to_exit"]        = "Нажмите Enter, чтобы продолжить.";
    this->Register["ru-RU"]["general.healed"]               = "восстановил";
    this->Register["ru-RU"]["general.regenerated"]          = "восстановил";
    this->Register["ru-RU"]["general.enemy"]                = "Противник";

    // Main menu texts
    this->Register["ru-RU"]["menu.main.subtitle"]           = "Игра от norbcodes.";
    this->Register["ru-RU"]["menu.main.optionpick"]         = "Выберите вариант:";
    this->Register["ru-RU"]["menu.main.play"]               = "Играть";
    this->Register["ru-RU"]["menu.main.ginfo"]              = "Информация об игре";
    this->Register["ru-RU"]["menu.main.datapacks"]          = "Датапаки";
    this->Register["ru-RU"]["menu.main.settings"]           = "Настройки";
    this->Register["ru-RU"]["menu.exit.confirm"]            = "Точно хотите выйти?";
    this->Register["ru-RU"]["menu.unstable"]                = "{red}Вы используете сборку игры, которая {bold}находится в разработке!{reset}{nl}{white}Используйте с осторожностью. {red}Вы хотите продолжить? [y,n]{reset}";

    // Difficulty picker texts
    this->Register["ru-RU"]["menu.diffpicker.title"]        = "Выбор уровня сложности";
    this->Register["ru-RU"]["menu.diffpicker.easy"]         = "Надираю сущностям задницу";
    this->Register["ru-RU"]["menu.diffpicker.medium"]       = "Бывало и похуже";
    this->Register["ru-RU"]["menu.diffpicker.hard"]         = "Долой этих сущностей";
    this->Register["ru-RU"]["menu.diffpicker.random"]       = "Случайная сложность!";
    this->Register["ru-RU"]["menu.diffpicker.record"]       = "Запись игры";

    // Datapack viewer stuff
    this->Register["ru-RU"]["menu.datapacks.title"]         = "Датапаки";
    this->Register["ru-RU"]["menu.datapacks.loaded"]        = "{white}Загружено датапаков: {purple}{datapack_count}{reset}{white}.{reset}";
    this->Register["ru-RU"]["menu.datapacks.help1"]         = "Используйте стрелки вверх/вниз для перелистывания.";
    this->Register["ru-RU"]["menu.datapacks.empty"]         = "Нет датапаков!";
    this->Register["ru-RU"]["menu.datapacks.info"]          = "Нажмите стрелку влево, чтобы вернуться назад.{nl}Нажмите стрелку вправо, чтобы просмотреть информацию о датапаке.";
    this->Register["ru-RU"]["menu.datapacks.title2"]        = "Информация о датапаке";
    this->Register["ru-RU"]["menu.datapacks.subtitle"]      = "Метаданные:";
    this->Register["ru-RU"]["menu.datapacks.name"]          = "Название:";
    this->Register["ru-RU"]["menu.datapacks.author"]        = "Автор:";
    this->Register["ru-RU"]["menu.datapacks.id"]            = "ID датапака:";
    this->Register["ru-RU"]["menu.datapacks.desc"]          = "Описание:";
    this->Register["ru-RU"]["menu.datapacks.size"]          = "Размер на диске:";
    this->Register["ru-RU"]["menu.datapacks.veryhuge"]      = "Больше Юпитера";
    this->Register["ru-RU"]["menu.datapacks.error1"]        = "Отсутствует основной раздел \"Datapack\"!";
    this->Register["ru-RU"]["menu.datapacks.error2"]        = "Отсутствует основной раздел \"Meta\"!";
    this->Register["ru-RU"]["menu.datapacks.error3"]        = "Отсутствует основной раздел \"Data\"!";
    this->Register["ru-RU"]["menu.datapacks.error4"]        = "Отсутствует название датапака!";
    this->Register["ru-RU"]["menu.datapacks.error5"]        = "Отсутствует автор датапака!";
    this->Register["ru-RU"]["menu.datapacks.error6"]        = "Отсутствует идентификатор датапака!";
    this->Register["ru-RU"]["menu.datapacks.error7"]        = "Неполный перевод!";
    this->Register["ru-RU"]["menu.datapacks.error8"]        = "Время приветствия не указано!";
    this->Register["ru-RU"]["menu.datapacks.error9"]        = "Пустое приветствие!";
    this->Register["ru-RU"]["menu.datapacks.error10"]       = "Пустое сообщение о выходе!";

    // Gameplay info
    this->Register["ru-RU"]["menu.ginfo.title"]             = "Информация об игре!";
    this->Register["ru-RU"]["menu.ginfo.tips"]              = "Советы и подсказки";
    this->Register["ru-RU"]["menu.ginfo.status"]            = "Статусы и их описание";
    this->Register["ru-RU"]["menu.ginfo.tiptitle"]          = "СОВЕТЫ И ПОДСКАЗКИ";
    this->Register["ru-RU"]["menu.ginfo.tip1"]              = "Вы можете пропустить ход, выбрав номер, отличный от 0, 1, 2, 3 и 4.";
    this->Register["ru-RU"]["menu.ginfo.tip2"]              = "При необходимости вы можете пропустить ход, чтобы восстановить энергию.";
    this->Register["ru-RU"]["menu.ginfo.tip3"]              = "ИИ будет пытаться атаковать вас, если у него больше 60 очков здоровья (HP).";
    this->Register["ru-RU"]["menu.ginfo.statustitle1"]      = "СТАТУСЫ";
    this->Register["ru-RU"]["menu.ginfo.statustitle2"]      = "и как они работают...";
    this->Register["ru-RU"]["menu.ginfo.autoheal"]          = "Регенерация";
    this->Register["ru-RU"]["menu.ginfo.autoheal.info"]     = "{white}{underline}В начале раунда{reset}{white} тот, до кого {reset}{white}дошла {underline}очередь{reset}{white},{nl}   будет получать {purple}{bold}+{autoheal_amount} очков здоровья (HP){reset}{white}.{reset}";
    this->Register["ru-RU"]["menu.ginfo.icrit"]             = "Повышение крит. шанса";
    this->Register["ru-RU"]["menu.ginfo.icrit.info"]        = "{white}При атаке сущность, обладающая данным статусом,{nl}   с вероятностью {underline}около {purple}~30%{reset}{white} наносит {underline}критический удар{reset}{white},{nl}   {white}который наносит значительно {underline}больше урона{reset}{white}.{reset}";
    this->Register["ru-RU"]["menu.ginfo.invis"]             = "Невидимка";
    this->Register["ru-RU"]["menu.ginfo.invis.info"]        = "{white}Когда сущность обладает данным статусом, атакующий{nl}   её противник может {underline}промахнуться{reset} с вероятностью{reset} {white}{underline}{purple}~20%{reset}{white}.{reset}";
    this->Register["ru-RU"]["menu.ginfo.poison"]            = "Яд";
    this->Register["ru-RU"]["menu.ginfo.poison.info"]       = "{white}{underline}В начале раунда{reset}{white} тот, до кого {reset}{white}дошла {underline}очередь{reset}{white},{nl}   будет получать урон {purple}{bold}-{poison_amount} HP{reset}{white}.{reset}";
    this->Register["ru-RU"]["menu.ginfo.thorns"]            = "Шипы";
    this->Register["ru-RU"]["menu.ginfo.thorns.info"]       = "{white}Когда сущность, обладающая данным статусом, подвергается{nl}   атаке, {reset}{white}{underline}50% урона{reset}{white} возвращается {underline}атакующей сущности{reset}{white}.{reset}";
    this->Register["ru-RU"]["menu.ginfo.weak"]              = "Слабость";
    this->Register["ru-RU"]["menu.ginfo.weak.info"]         = "{white}Для ослабленных противников действует {underline}{purple}ограничение{reset}{nl}   {underline}{purple}в 60 очков здоровья (HP) и брони (AR){reset}, {white}за раунд у них{nl}   восполняется {underline}{purple}на 75% меньше энергии{reset}{white}, {reset}{white}а также они{nl}   {underline}{purple}реже атакуют{reset}{white}. Этот статус длится {weakness_time} раунда.{reset}";

    // Settings texts
    this->Register["ru-RU"]["menu.options.title"]           = "Настройки";
    this->Register["ru-RU"]["menu.options.cat1"]            = " 1 НАСТРОЙКИ DISCORD ";
    this->Register["ru-RU"]["menu.options.cat2"]            = " 2 НАСТРОЙКИ ЯЗЫКА ";
    this->Register["ru-RU"]["menu.options.cat3"]            = " 3 НАСТРОЙКИ ПОЛЬЗОВАТЕЛЯ ";
    this->Register["ru-RU"]["menu.options.c1o1"]            = "Discord RPC:";
    this->Register["ru-RU"]["menu.options.login"]           = "Вы вошли под именем";
    this->Register["ru-RU"]["menu.options.currlang"]        = "Текущий язык:";
    this->Register["ru-RU"]["menu.options.changelang"]      = "Изменить язык...";
    this->Register["ru-RU"]["menu.options.langutils"]       = "Языковые параметры...";
    this->Register["ru-RU"]["menu.options.export1"]         = "Экспортировать язык в датапак (xml)...";
    this->Register["ru-RU"]["menu.options.export2"]         = "Экспортировать язык в текстовый формат (txt)...";
    this->Register["ru-RU"]["menu.options.export3"]         = "Конвертировать текстовый файл в датапак (xml)...";
    this->Register["ru-RU"]["menu.options.newuser"]         = "Создать нового пользователя...";
    this->Register["ru-RU"]["menu.options.changename"]      = "Изменить имя пользователя...";
    this->Register["ru-RU"]["menu.options.help1"]           = "{white}Нажмите {green}1{white}, чтобы войти в {green}режим редактирования{white}. Нажмите {red}9{white}, чтобы {red}вернуться в главное меню{white}.{reset}";
    this->Register["ru-RU"]["menu.options.help2"]           = "{white}Нажмите {red}стрелку влево{white}, чтобы выйти из {red}режима редактирования{white}.{reset}";
    this->Register["ru-RU"]["menu.options.help3"]           = "{white}Используйте {purple}стрелки вверх и вниз{white} для {purple}перемещения{white}.{reset}";
    this->Register["ru-RU"]["menu.options.help4"]           = "{white}Нажмите {yellow}стрелку вправо{white}, чтобы {yellow}изменить настройку{white}.{reset}";
    this->Register["ru-RU"]["menu.options.enteruser"]       = "Введите имя пользователя:";
    this->Register["ru-RU"]["menu.options.usererror"]       = "В имени пользователя не должно быть пробелов!";
    this->Register["ru-RU"]["menu.options.lang.select"]     = "Выбор языка";
    this->Register["ru-RU"]["menu.options.lang.loading"]    = "Загрузка...";
    this->Register["ru-RU"]["menu.options.lang.line1"]      = "Текущий язык: {lang}";
    this->Register["ru-RU"]["menu.options.lang.line2"]      = "Загружено {lang_count} языков.";
    this->Register["ru-RU"]["menu.options.lang.line3"]      = "Стрелки вверх/вниз для перемещения, вправо - для выбора языка, влево - для выхода.";

    // Language utilities texts
    this->Register["ru-RU"]["menu.langutils.success"]       = "Язык {lang_id} экспортирован успешно!";
    this->Register["ru-RU"]["menu.langutils.fail"]          = "При экспорте произошла ошибка...";
    this->Register["ru-RU"]["menu.langutils.getpath"]       = "Введите путь к текстовому файлу:";
    this->Register["ru-RU"]["menu.langutils.pathfail"]      = "Такого пути не существует!";
    this->Register["ru-RU"]["menu.langutils.notfile"]       = "Путь не указывает на файл!";

    // Greet texts
    this->Register["ru-RU"]["greet.morning.1"]              = "{white}Доброе утро, {username}. Готовы убивать?{reset}";
    this->Register["ru-RU"]["greet.morning.2"]              = "{white}Доброе утро, {username}. Возьмите чашечку кофе и разгромите парочку сущностей.{reset}";
    this->Register["ru-RU"]["greet.morning.3"]              = "{white}Доброе утро, {username}. Проснись и пой!{reset}";
    this->Register["ru-RU"]["greet.afternoon.1"]            = "{white}Добрый день, {username}. Хотите ещё больше крови?{reset}";
    this->Register["ru-RU"]["greet.afternoon.2"]            = "{white}Добрый день, {username}. А сегодня у нас на обед: Entities{reset}";
    this->Register["ru-RU"]["greet.afternoon.3"]            = "{white}Добрый день, {username}. Я бы сейчас не отказался вздремнуть...{reset}";
    this->Register["ru-RU"]["greet.evening.1"]              = "{white}Добрый вечер, {username}. Осталось 5 минут до отхода ко сну.{reset}";
    this->Register["ru-RU"]["greet.evening.2"]              = "{white}Добрый вечер, {username}. Сущности уже хотят спать, внезапное нападение!{reset}";
    this->Register["ru-RU"]["greet.evening.3"]              = "{white}Добрый вечер, {username}. *{italic}зевает{reset}{white}*{reset}";
    this->Register["ru-RU"]["greet.earlynight.1"]           = "{white}Доброй ночи, {username}. Не можешь уснуть?{reset}";
    this->Register["ru-RU"]["greet.earlynight.2"]           = "{white}Доброй ночи, {username}. Ужин сегодня был вкусным?{reset}";
    this->Register["ru-RU"]["greet.threeam.1"]              = "{white}Доброй ночи, {username}. Настало время для ужасов!{reset}";
    this->Register["ru-RU"]["greet.threeam.2"]              = "{white}Сладких снов, {username}. Грань между смертным и потусторонним стирается...{reset}";
    this->Register["ru-RU"]["greet.threeam.3"]              = "{white}Доброй ночи, {username}. Что-то не так..{reset}";

    // Gameplay strings
    this->Register["ru-RU"]["game.battle.announce"]         = "{red}{italic}Битва начинается. Удачи, {username}!{reset}";
    this->Register["ru-RU"]["game.battle.what_happened"]    = "{white}В предыдущем раунде:{reset}{nl}{what_happened}{reset}";
    this->Register["ru-RU"]["game.battle.ply_header"]       = "{dark_gray}---<<< Ход {blue}{bold}игрока {username}{reset}{dark_gray}! >>>---{reset}";
    this->Register["ru-RU"]["game.battle.ene_header"]       = "{dark_gray}---<<< Ход {red}{bold}противника{reset}{dark_gray}! >>>---{reset}";
    this->Register["ru-RU"]["game.battle.enemy"]            = "ПРОТИВНИК";
    this->Register["ru-RU"]["game.battle.regen_moves"]      = "Сменить ходы...";
    this->Register["ru-RU"]["game.battle.move_choose"]      = "{white}Выберите свой ход. {dark_gray}{bold}[1,2,3,4,5] (0 выйти){reset}";
    this->Register["ru-RU"]["game.battle.exit"]             = "Вы действительно хотите прекратить битву?";
    this->Register["ru-RU"]["game.battle.skip"]             = "пропустил свой ход.";
    this->Register["ru-RU"]["game.battle.enemy_skip"]       = "{red}{bold}Противник{reset} {white}пропустил ход.{reset}";
    this->Register["ru-RU"]["game.battle.no_energy"]        = "Недостаточно энергии!";
    this->Register["ru-RU"]["game.battle.rerolled"]         = "{blue}{bold}{username}{reset}{white} сменил ходы...{reset}";
    this->Register["ru-RU"]["game.battle.ai_think"]         = "ИИ думает...";
    this->Register["ru-RU"]["game.moves.attack"]            = "{red}Атака! {white}Нанести противнику {purple}{value}{white} единиц урона.{reset}";
    this->Register["ru-RU"]["game.moves.heal"]              = "{green}Исцеление! {white}Вы получите {purple}+{value}{white} HP{reset}";
    this->Register["ru-RU"]["game.moves.regen"]             = "{blue}Восстановить защиту{white}! Вы получите {purple}+{value}{white} AR{reset}";
    this->Register["ru-RU"]["game.moves.autoheal"]          = "{white}Применить статус {green}Регенерация{white}! Восстанавливает {purple}{value} {white}HP когда наступает ваш ход{reset}";
    this->Register["ru-RU"]["game.moves.icrit"]             = "{white}Применить статус {red}Повышение крит. шанса{white}! Увеличивает {red}шанс крит. попадания при атаке{reset}";
    this->Register["ru-RU"]["game.moves.invis"]             = "{white}Применить статус {hot_pink}Невидимка{white}! Противник может {hot_pink}промахнуться{reset}";
    this->Register["ru-RU"]["game.moves.poison"]            = "{white}Наложить на противника статус {dark_green}Яд{white}! Наносит {purple}{value}{white} единиц урона ядом{reset}";
    this->Register["ru-RU"]["game.moves.thorns"]            = "{white}Применить статус {teal}Шипы{white}! Противник при атаке {bold}также будет получать урон{reset}";
    this->Register["ru-RU"]["game.moves.weakness"]          = "{white}Наложить на противника статус {brown}Слабость{white}! Противник будет ослаблен...{reset}";
    this->Register["ru-RU"]["game.moves.gameover"]          = "{white}---<<< {blue}{bold}{username}{reset} {white}мёртв. {red}{bold}Противник{reset}{white} побеждает!!! >>>---{reset}";
    this->Register["ru-RU"]["game.moves.victory"]           = "{white}---<<< {red}{bold}Противник{reset} {white}мёртв. {blue}{bold}{username}{reset}{white} побеждает!!! >>>---{reset}";
    this->Register["ru-RU"]["game.moves.rematch"]           = "Ещё раз";
    this->Register["ru-RU"]["game.applied.autoheal"]        = "{white}применил статус {green}Регенерация{white}.";
    this->Register["ru-RU"]["game.applied.incr_crit"]       = "{white}применил статус {red}Повышение крит. шанса{white}.";
    this->Register["ru-RU"]["game.applied.invis"]           = "{white}применил статус {hot_pink}Невидимка{white}.";
    this->Register["ru-RU"]["game.applied.poison"]          = "{who} {white}наложил статус {dark_green}Яд{white} на {who2}{white}.{reset}";
    this->Register["ru-RU"]["game.applied.thorns"]          = "{white}применил статус {teal}Шипы{white}.";
    this->Register["ru-RU"]["game.applied.weakness"]        = "{who} {white}наложил статус {brown}Слабость{white} на {who2}{white}.{reset}";

    // Entity attack texts
    this->Register["ru-RU"]["entity.attack.ply_missed"]     = "{blue}{bold}{username}{reset} {white}попытался атаковать, но {italic}промахнулся{reset}{white}!{reset}";
    this->Register["ru-RU"]["entity.attack.ene_missed"]     = "{red}{bold}Противник{reset} {white}попытался атаковать, но {italic}промахнулся{reset}{white}!{reset}";
    this->Register["ru-RU"]["entity.attack.ply_normal"]     = "{blue}{bold}{username}{reset} {white}атаковал {red}{bold}противника{reset}{white}! {red}{bold}Противник{reset} {purple}-{dmg}HP{reset}";
    this->Register["ru-RU"]["entity.attack.ply_crit"]       = "{blue}{bold}{username}{reset} {white}атаковал {red}{bold}противника{reset}{white}! {gold}{italic}КРИТ. УДАР{reset}{white}! {red}{bold}Противник{reset} {purple}-{dmg}HP{reset}";
    this->Register["ru-RU"]["entity.attack.ene_normal"]     = "{red}{bold}Противник{reset} {white}атаковал {blue}{bold}{username}{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";
    this->Register["ru-RU"]["entity.attack.ene_crit"]       = "{red}{bold}Противник{reset} {white}атаковал {blue}{bold}{username}{reset}{white}! {gold}{italic}КРИТ. УДАР{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";

    // Exit messages :3
    this->Register["ru-RU"]["exit.message.1"]               = "{white}Нееееет не уходи :<{reset}";
    this->Register["ru-RU"]["exit.message.win2"]            = "{white}Вы уверены? {italic}Windows гораздо хуже...{reset}";
    this->Register["ru-RU"]["exit.message.win3"]            = "{white}Ну конечно, как будто Windows интереснее!{reset}";
    this->Register["ru-RU"]["exit.message.win4"]            = "{white}Ты же знаешь, что Биллу Гейтсу нравится эта игра, так ведь?{reset}";
    this->Register["ru-RU"]["exit.message.win5"]            = "{white}Ладно, не забудьте закрыть окна, когда будете уходить.{reset}";
    this->Register["ru-RU"]["exit.message.mac2"]            = "{white}Вы уверены? {italic}macOS гораздо хуже...{reset}";
    this->Register["ru-RU"]["exit.message.mac3"]            = "{white}Ну конечно, как будто macOS интереснее!{reset}";
    this->Register["ru-RU"]["exit.message.mac4"]            = "{white}Ты же знаешь, что Стиву Джобсу нравится эта игра, так ведь?{reset}";
    this->Register["ru-RU"]["exit.message.mac5"]            = "{white}У вас мак, да? А вы богатый человек :D{reset}";
    this->Register["ru-RU"]["exit.message.lix2"]            = "{white}Вы уверены? {italic}Linux гораздо хуже...{reset}";
    this->Register["ru-RU"]["exit.message.lix3"]            = "{white}Ну конечно, как будто Linux интереснее!{reset}";
    this->Register["ru-RU"]["exit.message.lix4"]            = "{white}Ты же знаешь, что Линусу Торвальдсу нравится эта игра, так ведь?{reset}";
    this->Register["ru-RU"]["exit.message.lix5"]            = "{white}Linuwux{reset}";
    this->Register["ru-RU"]["exit.message.6"]               = "{white}У противника ещё осталось 6 хп!{reset}";
    this->Register["ru-RU"]["exit.message.8"]               = "{white}А? Почему?{reset}";
    this->Register["ru-RU"]["exit.message.9"]               = "{white}Если вы уйдете сейчас, число убийств сбросится!{reset}";
    this->Register["ru-RU"]["exit.message.10"]              = "{white}Вы хотя бы попытались, с этим не поспоришь.{reset}";
    this->Register["ru-RU"]["exit.message.11"]              = "{white}Не уходи, пожалуйста!{reset}";
    this->Register["ru-RU"]["exit.message.12"]              = "{white}Постой, я дам тебе три бесплатных усиления, если останешься... ;){reset}";
    this->Register["ru-RU"]["exit.message.13"]              = "{white}Вы уверены? Там снаружи опасно...{reset}";
    this->Register["ru-RU"]["exit.message.14"]              = "{white}Просто уходите. Вы - недостойный противник.{reset}";
    this->Register["ru-RU"]["exit.message.15"]              = "{white}Ладно{reset}";
    this->Register["ru-RU"]["exit.message.16"]              = "{white}Ты изменяешь мне с Java-играми?{reset}";
    this->Register["ru-RU"]["exit.message.19"]              = "{white}Пророчество гласит, что вы продолжите игру.{nl}Вы смеете помешать исполнению этого пророчества?{reset}";
    this->Register["ru-RU"]["exit.message.21"]              = "{white}Благодарим вас за скачивание нашего вируса :3{reset}";
    this->Register["ru-RU"]["exit.message.22"]              = "{white}Нажмите 'y', и вы будете лежать в гробу!{reset}";
    this->Register["ru-RU"]["exit.message.23"]              = "{white}Не будь глупышкой! Побудь ещё немного здесь!{reset}";
    this->Register["ru-RU"]["exit.message.24"]              = "{white}Сущности живут у тебя в стенах{reset}";
    this->Register["ru-RU"]["exit.message.25"]              = "{white}Я, norbcodes, живу у тебя в потолке... и даже не плачу за аренду!{reset}";
    this->Register["ru-RU"]["exit.message.26"]              = "{white}Серьёзно?{reset}";
    this->Register["ru-RU"]["exit.message.27"]              = "{white}Ты шутишь?{reset}";
    this->Register["ru-RU"]["exit.message.28"]              = "{white}Неееет! Не бросай меня!{reset}";
    this->Register["ru-RU"]["exit.message.29"]              = "{white}Как поживает твой холодильник...?{reset}";
    this->Register["ru-RU"]["exit.message.30"]              = "{white}А вы выключили плиту...?{reset}";
    this->Register["ru-RU"]["exit.message.31"]              = "{white}Что? Динамическое выделение памяти пугает вас?{reset}";
    this->Register["ru-RU"]["exit.message.32"]              = "{white}Есть шанс, что через ваш череп{nl}прямо сейчас проходит частица нейтрино.{reset}";
    this->Register["ru-RU"]["exit.message.33"]              = "{white}У вас есть время подумать.{reset}";
    this->Register["ru-RU"]["exit.message.34"]              = "{white}О нет! У тебя на клавиатуре сломалась буква 'y'!{reset}";
    this->Register["ru-RU"]["exit.message.35"]              = "{white}АХАХАХАХА{reset}";
    this->Register["ru-RU"]["exit.message.36"]              = "{white}Внешнего мира не существует. Проснись. Проснись!{reset}";
    this->Register["ru-RU"]["exit.message.37"]              = "{white}Первая часть entities веселее?{reset}";
    this->Register["ru-RU"]["exit.message.39"]              = "{white}Я, norbcodes, этого не одобряю!!! >:({reset}";
    this->Register["ru-RU"]["exit.message.40"]              = "{white}Может тогда, сломать тебе клавиатуру?{reset}";
    this->Register["ru-RU"]["exit.message.41"]              = "{white}Возвращайтесь поскорее. У нас будет вечеринка с пиццей.{reset}";
    this->Register["ru-RU"]["exit.message.42"]              = "{white}Пока :3{reset}";
    this->Register["ru-RU"]["exit.message.45"]              = "{white}*{italic}введите сюда сообщение о выходе{reset}{white}*{reset}";
    this->Register["ru-RU"]["exit.message.47"]              = "{white}Чувак, просто поставь сложность пониже. Не нужно кардинальных мер.{reset}";
    this->Register["ru-RU"]["exit.message.48"]              = "{white}*{italic}введите сюда устрашающее сообщение о выходе{reset}{white}*{reset}";
    this->Register["ru-RU"]["exit.message.49"]              = "{white}Ладно, убирайся с глаз моих долой.{reset}";
    this->Register["ru-RU"]["exit.message.50"]              = "{white}Ни ухади позязя :({reset}";
    this->Register["ru-RU"]["exit.message.51"]              = "{white}><>     <---- рыбка{reset}";
    this->Register["ru-RU"]["exit.message.52"]              = "{red}exit{reset}{white}(){reset}";
    this->Register["ru-RU"]["exit.message.53"]              = "{white}Никакой для тебя подсветки синтаксиса!!!{reset}";
    this->Register["ru-RU"]["exit.message.54"]              = "{{red}}{{bold}}Чёрт, весь текст поехал{{reset}}";
    this->Register["ru-RU"]["exit.message.56"]              = "{white}Не{nl}  выходи{nl}        ПОЖАЛУЙСТА{reset}";
    this->Register["ru-RU"]["exit.message.57"]              = "{white}Ненавижу тебя >:({reset}";
    this->Register["ru-RU"]["exit.message.58"]              = "{white}Ты ведь ЗНАЕШЬ, что это лучшая игра в мире, правда?{reset}";
    this->Register["ru-RU"]["exit.message.59"]              = "{white}Классика, просто сдаётесь при первой же неудаче.{reset}";
    this->Register["ru-RU"]["exit.message.61"]              = "{white}Если выйдешь из игры, тебя забанят >:({reset}";
    this->Register["ru-RU"]["exit.message.62"]              = "{white}Мяу муррр :3{reset}";
    this->Register["ru-RU"]["exit.message.64"]              = "{white}А награду «Лучший игрок» получает...{reset}";
    this->Register["ru-RU"]["exit.message.65"]              = "{white}У тебя кишка тонка :>{reset}";
    this->Register["ru-RU"]["exit.message.67"]              = "{white}Давай, иди в свой валорант или во что вы там сейчас играете, детишки{reset}";
    this->Register["ru-RU"]["exit.message.70"]              = "{white}Когда у тебя день рождения?{reset}";
    this->Register["ru-RU"]["exit.message.special"]         = "{white}А вы знали? Вероятность появления каждого из этих сообщений составляет {purple}{perc:.2f}%{white}.{reset}";

    // Credits :3
    this->Register["ru-RU"]["credits.title1"]               = "ВОТ ОНИ - ТИТРЫ!";
    this->Register["ru-RU"]["credits.gameby"]               = "{gold}{bold}Игра{reset} {white}от{reset} {blue}{bold}Norb{reset}";
    this->Register["ru-RU"]["credits.writtenin"]            = "{hot_pink}{bold}Игра написана{reset} {white}на{reset} {green}{bold}C++{reset}";
    this->Register["ru-RU"]["credits.moreinfo1"]            = "Версия 1.0 создана примерно за 2 дня.";
    this->Register["ru-RU"]["credits.moreinfo2"]            = "(Пока я пишу эти титры, Discord говорит, что я сижу в VS Code уже 6 часов)";
    this->Register["ru-RU"]["credits.moreinfo3"]            = "Эти прекрасные цвета подобраны с помощью";
    this->Register["ru-RU"]["credits.moreinfo4"]            = "Зацените entity1 и главную страницу";
    this->Register["ru-RU"]["credits.title2"]               = "ИСПОЛЬЗУЕМЫЕ БИБЛИОТЕКИ:";
    this->Register["ru-RU"]["credits.discordlib"]           = "{blue}{bold}discord-rpc{reset} {dark_gray}:: {lavender}{italic}Спасибо, {name} :){reset}";
    this->Register["ru-RU"]["credits.fmtlib"]               = "{bold}{red}{{{orange}f{yellow}m{green}t{blue}}}{reset} {dark_gray}::{reset} {hot_pink}{italic}Спасибо всей команде разработчиков библиотеки {name}!! :P{reset}";
    this->Register["ru-RU"]["credits.pugilib"]              = "{white}{bold}pugi{reset}{brown}{bold}xml{reset} {dark_gray}::{reset} {pink}{italic}Спасибо {name} ({name2} на GitHub)!! :3{reset}";
    this->Register["ru-RU"]["credits.arglib"]               = "{orange}{bold}arg{gold}parse{reset} {dark_gray}::{reset} {green}{italic}Спасибо {name} {dark_green}за такую классную библиотеку :>{reset}";
    this->Register["ru-RU"]["credits.jsonlib"]              = "{blue}{bold}{italic}json{reset} {dark_gray}::{reset} {teal}{italic}Спасибо {name} за эту шикарную библиотеку!!{reset}";
    this->Register["ru-RU"]["credits.compiled"]             = "{dark_gray}entities2.cpp версия {entities2_ver} скомпилирована {compile_date} {compile_time} ;){reset}";
    this->Register["ru-RU"]["credits.title3"]               = "ОТДЕЛЬНОЕ СПАСИБО ПЕРЕВОДЧИКАМ:";
    this->Register["ru-RU"]["credits.slovak"]               = "{blue}{bold}{name}{reset} {dark_gray}::{reset} {white}{bold}английский{reset}{white} (основной язык игры) и {bold}словацкий{reset} {white}языки{reset}";
    this->Register["ru-RU"]["credits.russian"]              = "{purple}{bold}{name}{reset} {dark_gray}::{reset} {white}{bold}русский{reset} {white}язык{reset}";
    this->Register["ru-RU"]["credits.portuguese"]           = "{yellow}{bold}{name}{reset} {dark_gray}::{reset} {white}{bold}португальский{reset} {white}язык{reset}";
    this->Register["ru-RU"]["credits.tagalog"]              = "{light_blue}{bold}{name}{reset} {dark_gray}::{reset} {white}{bold}тагальский{reset} {white}язык{reset}";
    
    #endif // __ENTITIES2_BAKED_IN_RUSSIAN__
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Load all of Tagalog translation.
 * \note Needs to be enabled when cmake is invoked...
 */
void TranslationEngine::LoadTagalog()
{
    #ifdef __ENTITIES2_BAKED_IN_TAGALOG__

    // Language specific strings
    this->Register["tl-PH"]["lang.name"]                    = "Tagalog (Pilipinas)";
    this->Register["tl-PH"]["lang.id"]                      = "tl-PH";

    // General texts
    this->Register["tl-PH"]["general.quit"]                 = "Umalis";
    this->Register["tl-PH"]["general.exit"]                 = "Lumabas";
    this->Register["tl-PH"]["general.on"]                   = "ON";
    this->Register["tl-PH"]["general.off"]                  = "OFF";
    this->Register["tl-PH"]["general.by"]                   = "ni";
    this->Register["tl-PH"]["general.enter_to_exit"]        = "Pindutin ang 'enter' para magpatuloy.";
    this->Register["tl-PH"]["general.healed"]               = "ay naghilom";
    this->Register["tl-PH"]["general.regenerated"]          = "ay nag-regenerate";
    this->Register["tl-PH"]["general.enemy"]                = "Kalaban";

    // Main menu texts
    this->Register["tl-PH"]["menu.main.subtitle"]           = "Isang larong gawa ni norbcodes.";
    this->Register["tl-PH"]["menu.main.optionpick"]         = "Mga Pagpipilian:";
    this->Register["tl-PH"]["menu.main.play"]               = "Maglaro";
    this->Register["tl-PH"]["menu.main.ginfo"]              = "Impormasyon ng Laro";
    this->Register["tl-PH"]["menu.main.datapacks"]          = "Mga Datapack";
    this->Register["tl-PH"]["menu.main.settings"]           = "Setting";
    this->Register["tl-PH"]["menu.exit.confirm"]            = "Kumpirmahin ang paglabas?";
    this->Register["tl-PH"]["menu.unstable"]                = "{red}Gumagamit ka ng bersyon na {bold}hindi pa pinal!{reset}{nl}{white}Mag-ingat sa pagpapatuloy. {red}Nais mo pa bang maglaro? [y,n]{reset}";

    // Difficulty picker texts
    this->Register["tl-PH"]["menu.diffpicker.title"]        = "Antas ng Kahirapan";
    this->Register["tl-PH"]["menu.diffpicker.easy"]         = "Ubusin ang mga Nilalang!";
    this->Register["tl-PH"]["menu.diffpicker.medium"]       = "Wala 'to sa 'kin";
    this->Register["tl-PH"]["menu.diffpicker.hard"]         = "Ibagsak ang mga Nilalang!";
    this->Register["tl-PH"]["menu.diffpicker.random"]       = "Halu-halo! ";
    this->Register["tl-PH"]["menu.diffpicker.record"]       = "I-record ang demo";

    // Datapack viewer stuff
    this->Register["tl-PH"]["menu.datapacks.title"]         = "Datapacks";
    this->Register["tl-PH"]["menu.datapacks.loaded"]        = "{white}Kasalukuyang kinakarga ang {purple}{datapack_count}{reset}{white} na datapack.{reset}";
    this->Register["tl-PH"]["menu.datapacks.help1"]         = "Gamitin ang up at down arrow para gumalaw.";
    this->Register["tl-PH"]["menu.datapacks.empty"]         = "Wala ang mga datapack!";
    this->Register["tl-PH"]["menu.datapacks.info"]          = "Pindutin ang left arrow para bumalik.{nl}Pindutin ang right arrow para tingnan ang impormasyon ng datapacks.";
    this->Register["tl-PH"]["menu.datapacks.title2"]        = "Datapack Info";
    this->Register["tl-PH"]["menu.datapacks.subtitle"]      = "Metadata:";
    this->Register["tl-PH"]["menu.datapacks.name"]          = "Pangalan:";
    this->Register["tl-PH"]["menu.datapacks.author"]        = "May-akda:";
    this->Register["tl-PH"]["menu.datapacks.id"]            = "Datapack id:";
    this->Register["tl-PH"]["menu.datapacks.desc"]          = "Deskripsyon:";
    this->Register["tl-PH"]["menu.datapacks.size"]          = "Bigat ng Disk";
    this->Register["tl-PH"]["menu.datapacks.veryhuge"]      = "Mas malaki pa sa Jupiter";
    this->Register["tl-PH"]["menu.datapacks.error1"]        = "Nawawala ang main \"Datapack\" block!";
    this->Register["tl-PH"]["menu.datapacks.error2"]        = "Nawawala ang main \"Meta\" block!";
    this->Register["tl-PH"]["menu.datapacks.error3"]        = "Nawawala ang main \"Data\" block!";
    this->Register["tl-PH"]["menu.datapacks.error4"]        = "Nawawala ang pangalan ng datapack!";
    this->Register["tl-PH"]["menu.datapacks.error5"]        = "Nawawala ang may-akda ng datapack!";
    this->Register["tl-PH"]["menu.datapacks.error6"]        = "Nawawala ang datapack identificator!";
    this->Register["tl-PH"]["menu.datapacks.error7"]        = "Sira ang translations!";
    this->Register["tl-PH"]["menu.datapacks.error8"]        = "Ang pagbati ay walang sinabing oras!";
    this->Register["tl-PH"]["menu.datapacks.error9"]        = "Walang pagbati!";
    this->Register["tl-PH"]["menu.datapacks.error10"]       = "Walang exit message!";

    // Gameplay info
    this->Register["tl-PH"]["menu.ginfo.title"]             = "Imporasyon ng Laro!";
    this->Register["tl-PH"]["menu.ginfo.tips"]              = "Mga payo at diskarte";
    this->Register["tl-PH"]["menu.ginfo.status"]            = "Ang mga status at ang kanilang mga gamit";
    this->Register["tl-PH"]["menu.ginfo.tiptitle"]          = "MGA PAYO & DISKARTE!";
    this->Register["tl-PH"]["menu.ginfo.tip1"]              = "Maaari mong ipagpaliban ang tira na hindi pinipili ang 0, 1, 2, 3, o 4.";
    this->Register["tl-PH"]["menu.ginfo.tip2"]              = "Kung kinakailangan, maaari mong ipagpaliban ang round para ibalik ang iyong enerhiya.";
    this->Register["tl-PH"]["menu.ginfo.tip3"]              = "Susubukan kang atakihin ng AI kapag nasa higit na 60 ang kanyang HP.";
    this->Register["tl-PH"]["menu.ginfo.statustitle1"]      = "ANG MGA STATUS";
    this->Register["tl-PH"]["menu.ginfo.statustitle2"]      = "at ang kanilang mga gamit...";
    this->Register["tl-PH"]["menu.ginfo.autoheal"]          = "AutoHeal";
    this->Register["tl-PH"]["menu.ginfo.autoheal.info"]     = "{white}Sa simula ng {underline}bagong round{reset}{white}, ang may-ari{reset}{nl}   {white}ng {underline}turn ay makakatanggap ng {purple}{bold}+{autoheal_amount}HP.{reset}";
    this->Register["tl-PH"]["menu.ginfo.icrit"]             = "IncreasedCrit";
    this->Register["tl-PH"]["menu.ginfo.icrit.info"]        = "{white}Kung sinuman ang may status na ito ay magkakaroon ng {underline}{purple}~30%{reset}{nl}   {white}ng pagtira ng {underline}kritikal na pag-atake{reset}{white}, na nagbibigay ng{reset}{nl}   {white}mas {underline}maraming damage.{reset}";
    this->Register["tl-PH"]["menu.ginfo.invis"]             = "Invisibility";
    this->Register["tl-PH"]["menu.ginfo.invis.info"]        = "{white}Kung sinuman ang may status na ito ay may{reset}{nl}   {white}a {underline}{purple}~20%{reset} {white}tsansang {underline}sumablay ang tira{reset}{nl}   {white}{underline}ng mga umaatake.{reset}";
    this->Register["tl-PH"]["menu.ginfo.poison"]            = "Poison";
    this->Register["tl-PH"]["menu.ginfo.poison.info"]       = "{white}Sa simula ng {underline}bagong round{reset}, ang may-ari{reset}{nl}   {white}ng {underline}turn ay makakatanggap ng {purple}{bold}-{poison_amount}HP ng damage.{reset}";
    this->Register["tl-PH"]["menu.ginfo.thorns"]            = "Thorns";
    this->Register["tl-PH"]["menu.ginfo.thorns.info"]       = "{white}Kapag ang gumamit nito ay{reset}{nl}   {white}inatake, {underline}50% ng damage{reset}{white} ay ibabalik sa {underline}umatake.{reset}";
    this->Register["tl-PH"]["menu.ginfo.weak"]              = "Weakness";
    this->Register["tl-PH"]["menu.ginfo.weak.info"]         = "{white}Ang HP at AR ng mahinang kalaban ay {underline}{purple}aabot hanggang 60 lamang.{reset}{nl}   {white}Ang kanilang enerhiya ay babalik ng {underline}{purple}kulang sa 75% bawat round{reset}{white}.{reset}{nl}   {white}Ang kanyang pag-atake ay{underline}{purple}'di gaanong kalakas{reset}{white}.{nl}   Ang status na ito ay aabot lamang sa {weakness_time} round.{reset}";

    // Settings texts
    this->Register["tl-PH"]["menu.options.title"]           = "Mga Pagpipilian";
    this->Register["tl-PH"]["menu.options.cat1"]            = " 1 SETTING NG DISCORD ";
    this->Register["tl-PH"]["menu.options.cat2"]            = " 2 SETTING NG WIKA ";
    this->Register["tl-PH"]["menu.options.cat3"]            = " 3 SETTING NG GUMAGAMIT ";
    this->Register["tl-PH"]["menu.options.c1o1"]            = "Discord RPC:";
    this->Register["tl-PH"]["menu.options.login"]           = "Naka-login bilang";
    this->Register["tl-PH"]["menu.options.currlang"]        = "Kasalukyang wika:";
    this->Register["tl-PH"]["menu.options.changelang"]      = "Palitan ang wika...";
    this->Register["tl-PH"]["menu.options.langutils"]       = "Utility Pang-Wika...";
    this->Register["tl-PH"]["menu.options.export1"]         = "I-export ang wika sa Datapack (xml)...";
    this->Register["tl-PH"]["menu.options.export2"]         = "I-export ang wika bilang Text (txt)...";
    this->Register["tl-PH"]["menu.options.export3"]         = "Palitan ang TXT sa Datapack (xml)...";
    this->Register["tl-PH"]["menu.options.newuser"]         = "Gumawa ng bagong user...";
    this->Register["tl-PH"]["menu.options.changename"]      = "Palitan ang username...";
    this->Register["tl-PH"]["menu.options.help1"]           = "{white}Pindutin ang {green}1{white} para pumasok sa {green}Edit{white} mode.{nl}Pindutin ang {red}9{white} para {red}bumalik sa main menu{white}.{reset}";
    this->Register["tl-PH"]["menu.options.help2"]           = "{white}Pindutin ang {red}left arrow{white} para lumabas sa {red}Edit{white} mode.{reset}";
    this->Register["tl-PH"]["menu.options.help3"]           = "{white}Gamitin ang {purple}up at down arrow{white} para {purple}gumalaw{white}.{reset}";
    this->Register["tl-PH"]["menu.options.help4"]           = "{white}Pindutin ang {yellow}right arrow{white} para {yellow}palitan ang setting{white}.{reset}";
    this->Register["tl-PH"]["menu.options.enteruser"]       = "Isulat ang iyong username:";
    this->Register["tl-PH"]["menu.options.usererror"]       = "Walang espasyo sa username!";
    this->Register["tl-PH"]["menu.options.lang.select"]     = "Pagpipilian ng mga Wika";
    this->Register["tl-PH"]["menu.options.lang.loading"]    = "Kumakarga...";
    this->Register["tl-PH"]["menu.options.lang.line1"]      = "Kasalukyang wika: {lang}";
    this->Register["tl-PH"]["menu.options.lang.line2"]      = "{lang_count} mga wika ang naka-load.";
    this->Register["tl-PH"]["menu.options.lang.line3"]      = "Up/down arrow para gumalaw, right arrow para pumili ng wika at left arrow para umalis.";

    // Language utilities texts
    this->Register["tl-PH"]["menu.langutils.success"]       = "Tagumpay na na-export ang wikang {lang_id}!";
    this->Register["tl-PH"]["menu.langutils.fail"]          = "May masamang nangyari habang nag-eexport";
    this->Register["tl-PH"]["menu.langutils.getpath"]       = "Paki-input ng path sa TXT:";
    this->Register["tl-PH"]["menu.langutils.pathfail"]      = "Hindi mahanap ang path!";
    this->Register["tl-PH"]["menu.langutils.notfile"]       = "Ang path ay hindi tugma sa file!";

    // Greet texts
    this->Register["tl-PH"]["greet.morning.1"]              = "{white}Magandang umaga, {username}. Handa ka na bang pumatay?{reset}";
    this->Register["tl-PH"]["greet.morning.2"]              = "{white}Magandang umaga, {username}. Kumuha na ng kape at durugin ang mga kalaban.{reset}";
    this->Register["tl-PH"]["greet.morning.3"]              = "{white}Magandang umaga, {username}. Bangon na!{reset}";
    this->Register["tl-PH"]["greet.afternoon.1"]            = "{white}Magandang hapon, {username}. Naparito ka ba para sa mambasag ng bungo?{reset}";
    this->Register["tl-PH"]["greet.afternoon.2"]            = "{white}Magandang hapon, {username}. Ang Tanghalian: Mga Nilalang {reset}";
    this->Register["tl-PH"]["greet.afternoon.3"]            = "{white}Magandang hapon, {username}. Gusto kong umidlip ngayon din...{reset}";
    this->Register["tl-PH"]["greet.evening.1"]              = "{white}Magandang gabi, {username}. 5 minuto pa bago matulog.{reset}";
    this->Register["tl-PH"]["greet.evening.2"]              = "{white}Magandang gabi, {username}. Tulog na ang mga halimaw, supresahin natin sila! {reset}";
    this->Register["tl-PH"]["greet.evening.3"]              = "{white}Magandang gabi, {username}. *{italic}Hikab{reset}{white}*{reset}";
    this->Register["tl-PH"]["greet.earlynight.1"]           = "{white}Magandang gabi, {username}. Hindi ka pa tulog?{reset}";
    this->Register["tl-PH"]["greet.earlynight.2"]           = "{white}Magandang gabi, {username}. Masarap ba ang hapunan mo?{reset}";
    this->Register["tl-PH"]["greet.threeam.1"]              = "{white}Magandang gabi, {username}. Oras na ng kababalaghan!{reset}";
    this->Register["tl-PH"]["greet.threeam.2"]              = "{white}Magandang gabi, {username}. Halos 'di na matukoy ang guhit sa pagitan ng mortal at ang kabilang dako...{reset}";
    this->Register["tl-PH"]["greet.threeam.3"]              = "{white}Magandang gabi, {username}. May kakaibang nangyayari...{reset}";

    // Gameplay strings
    this->Register["tl-PH"]["game.battle.announce"]         = "{red}{italic}Nagsimula na ang laban. Galingan mo, {username}!{reset}";
    this->Register["tl-PH"]["game.battle.what_happened"]    = "{white}Ang nakaraang round:{reset}{nl}{what_happened}{reset}";
    this->Register["tl-PH"]["game.battle.ply_header"]       = "{dark_gray}---<<< {dark_gray}Tira ni{reset} {blue}{bold}{username}! >>>---{reset}";
    this->Register["tl-PH"]["game.battle.ene_header"]       = "{dark_gray}---<<< {dark_gray}Tira ng{reset} {red}{bold}kalaban! >>>---{reset}";
    this->Register["tl-PH"]["game.battle.enemy"]            = "KALABAN";
    this->Register["tl-PH"]["game.battle.regen_moves"]      = "Binabago ang mga aksyon...";
    this->Register["tl-PH"]["game.battle.move_choose"]      = "{white}Piliin ang iyong aksyon. {dark_gray}{bold}[1,2,3,4,5] (0 para lumabas){reset}";
    this->Register["tl-PH"]["game.battle.exit"]             = "Nais mo bang tapusin ang laban?";
    this->Register["tl-PH"]["game.battle.skip"]             = "Pinagpaliban ang tira.";
    this->Register["tl-PH"]["game.battle.enemy_skip"]       = "{white}Ipinagpaliban ng{reset} {red}{bold}kalaban{reset} {white}ang kanyang tira.{reset}";
    this->Register["tl-PH"]["game.battle.no_energy"]        = "Kulang sa enerhiya!";
    this->Register["tl-PH"]["game.battle.rerolled"]         = "{blue}Na-reroll ni {bold}{username}{reset}{white} ang kanyang mga aksyon...{reset}";
    this->Register["tl-PH"]["game.battle.ai_think"]         = "Nag-iisip ang AI...";
    this->Register["tl-PH"]["game.moves.attack"]            = "{red}Umatake! {white}Bigyan ng {purple}{value}{white} damage ang kalaban mo.{reset}";
    this->Register["tl-PH"]["game.moves.heal"]              = "{green}Maghilom! {white}Bibigyan ka ng {purple}+{value}{white} HP{reset}";
    this->Register["tl-PH"]["game.moves.regen"]             = "{blue}Regen armor{white}! Bibigyan ka ng {purple}+{value}{white} AR{reset}";
    this->Register["tl-PH"]["game.moves.autoheal"]          = "{white}Paganahin ang {green}AutoHeal {white}status! Bibigyan ka ng {purple}{value} {white}HP kapag tira mo na.{reset}";
    this->Register["tl-PH"]["game.moves.icrit"]             = "{white}Paganahin ang {red}IncreasedCrit {white}status! Mas mataas na tsansa ng {red}kritikal na pag-atake{reset}";
    this->Register["tl-PH"]["game.moves.invis"]             = "{white}Paganahin ang {hot_pink}Invis {white}status! Ang kalaban ay may tsansang {hot_pink}sumablay sa pagtira{reset}";
    this->Register["tl-PH"]["game.moves.poison"]            = "{white}Bigyan ang kalaban ng {dark_green}Poison {white}status!  {purple}{value}{white} poison damage {reset}";
    this->Register["tl-PH"]["game.moves.thorns"]            = "{white}Paganahin ang {teal}Thorns {white}status! Ang kalaban ay {bold}makakatanggap din ng damage kapag ika'y inatake{reset}";
    this->Register["tl-PH"]["game.moves.weakness"]          = "{white}Bigyan ang kalaban ng {brown}Weakness {white}status! Maghihina ang kalaban...{reset}";
    this->Register["tl-PH"]["game.moves.gameover"]          = "{white}---<<< {white}Namatay si{reset} {blue}{bold}{username}.{reset} {white}Panalo ang{reset} {red}{bold}kalaban!>>>---{reset}";
    this->Register["tl-PH"]["game.moves.victory"]           = "{white}---<<< {white}Namatay ang{reset} {red}{bold}kalaban.{reset} {white}Panalo si{reset} {blue}{bold}{username}!>>>---{reset}";
    this->Register["tl-PH"]["game.moves.rematch"]           = "Ulitin ang laban!";
    this->Register["tl-PH"]["game.applied.autoheal"]        = "{white}ay gumamit ng {green}Autoheal{white}.";
    this->Register["tl-PH"]["game.applied.incr_crit"]       = "{white}ay gumamit ng {red}IncreasedCrit{white}.";
    this->Register["tl-PH"]["game.applied.invis"]           = "{white}ay gumamit ng {hot_pink}Invis{white}.";
    this->Register["tl-PH"]["game.applied.poison"]          = "{who} {white}ay nagbigay ng {dark_green}Poison{white} kay {who2}{white}.{reset}";
    this->Register["tl-PH"]["game.applied.thorns"]          = "{white}ay gumamit ng {teal}Thorns{white}.";
    this->Register["tl-PH"]["game.applied.weakness"]        = "{who} {white}ay nagbigay ng {brown}Weakness{white} kay {who2}{white}.{reset}";

    // Entity attack texts
    this->Register["tl-PH"]["entity.attack.ply_missed"]     = "{white}Sinubukan ni{reset} {blue}{bold}{username}{reset} {white}na umatake, pero ito'y {italic}sumablay{reset}{white}!{reset}";
    this->Register["tl-PH"]["entity.attack.ene_missed"]     = "{white}Sinubukan ng{reset} {red}{bold}Kalaban{reset} {white}na umatake, pero ito'y {italic}sumablay{reset}{white}!{reset}";
    this->Register["tl-PH"]["entity.attack.ply_normal"]     = "{white}Inatake ni{reset} {blue}{bold}{username}{reset} {white}ang {red}{bold}Kalaban{reset}{white}! {red}{bold}Kalaban{reset} {purple}-{dmg}HP{reset}";
    this->Register["tl-PH"]["entity.attack.ply_crit"]       = "{white}Inatake ni{reset} {blue}{bold}{username}{reset} {white}ang {red}{bold}Kalaban{reset}{white}! {gold}{italic}CRITICAL HIT{reset}{white}! {red}{bold}Kalaban{reset} {purple}-{dmg}HP{reset}";
    this->Register["tl-PH"]["entity.attack.ene_normal"]     = "{white}Inatake ng{reset} {red}{bold}Kalaban{reset} {white}si {blue}{bold}{username}{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";
    this->Register["tl-PH"]["entity.attack.ene_crit"]       = "{white}Inatake ng{reset} {red}{bold}Kalaban{reset} {white}si {blue}{bold}{username}{reset}{white}! {gold}{italic}CRITICAL HIT{reset}{white}! {blue}{bold}{username}{reset} {purple}-{dmg}HP{reset}";

    // Exit messages :3
    this->Register["tl-PH"]["exit.message.1"]               = "{white}Uuuyyyyyy! 'Wag mo 'kong iwan :<{reset}";
    this->Register["tl-PH"]["exit.message.win2"]            = "{white}Sigurado ka? {italic}Mas malala ang Windows...{reset}";
    this->Register["tl-PH"]["exit.message.win3"]            = "{white}Syempre, kung kwela lang sana ang Windows!{reset}{reset}";
    this->Register["tl-PH"]["exit.message.win4"]            = "{white}Alam mo namang gusto ni Bill Gates ang larong ito, 'di ba?{reset}";
    this->Register["tl-PH"]["exit.message.win5"]            = "{white}'Wag mong kalimutang patayin 'yung WINDOWS paglabas mo.{reset}";
    this->Register["tl-PH"]["exit.message.mac2"]            = "{white}Sigurado ka? {italic}Mas malala ang Mac...{reset}";
    this->Register["tl-PH"]["exit.message.mac3"]            = "{white}Syempre, kung kwela lang sana ang Mac!{reset}";
    this->Register["tl-PH"]["exit.message.mac4"]            = "{white}Alam mo namang gusto ni Steve Jobs ang larong ito, 'di ba?{reset}";
    this->Register["tl-PH"]["exit.message.mac5"]            = "{white}Aanhin mo ang IPhone, kung wala ka namang datung?{reset}";
    this->Register["tl-PH"]["exit.message.lix2"]            = "{white}Sigurado ka? {italic}Mas malala ang Linux...{reset}";
    this->Register["tl-PH"]["exit.message.lix3"]            = "{white}Syempre, kung kwela lang sana ang Linux!{reset}";
    this->Register["tl-PH"]["exit.message.lix4"]            = "{white}Alam mo namang gusto ni Linus Torvalds ang larong ito, 'di ba?{reset}";
    this->Register["tl-PH"]["exit.message.lix5"]            = "{white}Linuwux{reset}";
    this->Register["tl-PH"]["exit.message.6"]               = "{white}May 6 na HP pa 'yung kalaban mo!{reset}";
    this->Register["tl-PH"]["exit.message.8"]               = "{white}Huh? Bakit?{reset}";
    this->Register["tl-PH"]["exit.message.9"]               = "{white}Kapag umalis ka, burado agad ang kill count mo!{reset}";
    this->Register["tl-PH"]["exit.message.10"]              = "{white}Kahit paano sinubukan mo. Wala akong reklamo diyan.{reset}";
    this->Register["tl-PH"]["exit.message.11"]              = "{white}'Wag ka munang umalis!{reset}";
    this->Register["tl-PH"]["exit.message.12"]              = "{white}Pssst, kapag nanatili ka, bibigyan kita ng 3 libreng powerups... ;){reset}";
    this->Register["tl-PH"]["exit.message.13"]              = "{white}Sigurado ka? Mapanganib ang labas...{reset}";
    this->Register["tl-PH"]["exit.message.14"]              = "{white}Tsk, lumayas ka. Mahinang nilalang.{reset}";
    this->Register["tl-PH"]["exit.message.15"]              = "{white}Okey{reset}";
    this->Register["tl-PH"]["exit.message.16"]              = "{white}Pangga, pinagpalit mo na ba 'ko sa mga larong Java?{reset}";
    this->Register["tl-PH"]["exit.message.19"]              = "{white}Nakasaad sa propesiya na dapat mong ituloy ang laro. Sinusuway mo na ba ang iyong kapalaran?{reset}";
    this->Register["tl-PH"]["exit.message.21"]              = "{white}Salamat sa pag-download ng malware namin :3{reset}";
    this->Register["tl-PH"]["exit.message.22"]              = "{white}Pindutin ang 'y' at ika'y hihiga sa iyong kabaong!{reset}";
    this->Register["tl-PH"]["exit.message.23"]              = "{white}'Wag kang baliw! Manatili ka pa nang matagal!{reset}";
    this->Register["tl-PH"]["exit.message.24"]              = "{white}Nasa loob ng iyong dingding ang mga Nilalang{reset}";
    this->Register["tl-PH"]["exit.message.25"]              = "{white}Ako, si norbcodes, ay nakatambay sa kisame mo{reset}";
    this->Register["tl-PH"]["exit.message.26"]              = "{white}Seryoso ka?{reset}";
    this->Register["tl-PH"]["exit.message.27"]              = "{white}Weeh. 'Di nga.{reset}";
    this->Register["tl-PH"]["exit.message.28"]              = "{white}Nakupo, babeeee!{reset}";
    this->Register["tl-PH"]["exit.message.29"]              = "{white}Tumatakbo ba 'yung ref mo...?{reset}";
    this->Register["tl-PH"]["exit.message.30"]              = "{white}Nakapatay ba 'yung kalan mo...?{reset}";
    this->Register["tl-PH"]["exit.message.31"]              = "{white}Ano? Natakot ka sa heap memory allocs?{reset}";
    this->Register["tl-PH"]["exit.message.32"]              = "{white}May tsansang matatamaan ang ulo mo ng{nl}neutrino particle{reset}";
    this->Register["tl-PH"]["exit.message.33"]              = "{white}Isip-isip din 'pag may time.{reset}";
    this->Register["tl-PH"]["exit.message.34"]              = "{white}Nakupo! Nasira 'yung 'y' button mo!{reset}";
    this->Register["tl-PH"]["exit.message.35"]              = "{white}HAHAHAHA{reset}";
    this->Register["tl-PH"]["exit.message.36"]              = "{white}Gawa-gawa lang ang labas. Gising. Gumising ka.{reset}";
    this->Register["tl-PH"]["exit.message.37"]              = "{white}Mas kwela ba ang mga orihinal na Nilalang?{reset}";
    this->Register["tl-PH"]["exit.message.39"]              = "{white}Ako, si norbcodes, ay tutol sa pasya mo >:({reset}";
    this->Register["tl-PH"]["exit.message.40"]              = "{white}Sisirain ko 'yang keyboard mo{reset}";
    this->Register["tl-PH"]["exit.message.41"]              = "{white}Bumalik ka. Magkakaroon tayo ng pizza party.{reset}";
    this->Register["tl-PH"]["exit.message.42"]              = "{white}Paalam :3{reset}";
    this->Register["tl-PH"]["exit.message.45"]              = "{white}*{italic}isulat ang exit message dito{reset}{white}*{reset}";
    this->Register["tl-PH"]["exit.message.47"]              = "{white}'Tol, piliin mo 'yung mas madali. 'Wag mong pahirapan 'yang sarili mo.{reset}";
    this->Register["tl-PH"]["exit.message.48"]              = "{white}*{italic}isulat ang pagbabanta rito {reset}{white}*{reset}";
    this->Register["tl-PH"]["exit.message.49"]              = "{white}Sige na nga. Umalis ka sa harapan ko.{reset}";
    this->Register["tl-PH"]["exit.message.50"]              = "{white}Manatili ka pa pwease :({reset}";
    this->Register["tl-PH"]["exit.message.51"]              = "{white}><>     <---- isda{reset}";
    this->Register["tl-PH"]["exit.message.52"]              = "{red}exit{reset}{white}(){reset}";
    this->Register["tl-PH"]["exit.message.53"]              = "{white}Walang syntax highlighting para sa 'yo!!!{reset}";
    this->Register["tl-PH"]["exit.message.54"]              = "{{red}}{{bold}}Putsa, sira 'yung formatting ko{{reset}}";
    this->Register["tl-PH"]["exit.message.56"]              = "{white}Huwag{nl}     kang{nl}         umalis,{nl}                PAKIUSAP{reset}";
    this->Register["tl-PH"]["exit.message.57"]              = "{white}Ayoko sa 'yo >:( {reset}";
    this->Register["tl-PH"]["exit.message.58"]              = "{white}ALAM mo namang ito ang pinaka-dabest na laro, 'di ba?{reset}";
    this->Register["tl-PH"]["exit.message.59"]              = "{white}Magaling. Natalo lang ng isang beses, suko agad.{reset}";
    this->Register["tl-PH"]["exit.message.61"]              = "{white}I-rereport kita sa GitHub 'pag umalis ka >:({reset}";
    this->Register["tl-PH"]["exit.message.62"]              = "{white}Miyaw meerpppp :3{reset}";
    this->Register["tl-PH"]["exit.message.64"]              = "{white}At ang \"Pinakamahusay na Manlalaro\" ay iginawad kay...{reset}";
    this->Register["tl-PH"]["exit.message.65"]              = "{white}walang bayag :>{reset}";
    this->Register["tl-PH"]["exit.message.67"]              = "{white}Laruin mo na 'yang Valorant o kung ano man 'yung nilalaro ng mga bata ngayon{reset}";
    this->Register["tl-PH"]["exit.message.70"]              = "{white}Kailan 'yung kaarawan mo?{reset}";
    this->Register["tl-PH"]["exit.message.special"]         = "{white}Alam mo ba? May {purple}{perc:.2f}%{white} tsansang magpakita rito ang bawat mensahe.{reset}";

    // Credits :3
    this->Register["tl-PH"]["credits.title1"]               = "KREDITS, MGA TSONG!!!";
    this->Register["tl-PH"]["credits.gameby"]               = "{gold}{bold}Laro{reset} {white}ni{reset} {blue}{bold}Norb{reset}";
    this->Register["tl-PH"]["credits.writtenin"]            = "{hot_pink}{bold}Isinulat{reset} {white}gamit ang{reset} {green}{bold}C++{reset}";
    this->Register["tl-PH"]["credits.moreinfo1"]            = "Na-icode ang v1.0 sa loob ng 2 araw.";
    this->Register["tl-PH"]["credits.moreinfo2"]            = "(Habang sinusulat ko ang credits, naka-6 na oras daw ako sa VScode sabi ng Discord)";
    this->Register["tl-PH"]["credits.moreinfo3"]            = "Itong mga pinong kulay ay pinili gamit ang";
    this->Register["tl-PH"]["credits.moreinfo4"]            = "Bisitahin ang entity1 at ang homepage sa";
    this->Register["tl-PH"]["credits.title2"]               = "ANG MGA GINAMIT NA EXTERNAL LIBRARY:";
    this->Register["tl-PH"]["credits.discordlib"]           = "{blue}{bold}discord-rpc{reset} {dark_gray}:: {lavender}{italic}Salamat kay {name} :){reset}";
    this->Register["tl-PH"]["credits.fmtlib"]               = "{bold}{red}{{{orange}f{yellow}m{green}t{blue}}}{reset} {dark_gray}::{reset} {hot_pink}{italic}Salamat sa buong {name} lib team!! :P{reset}";
    this->Register["tl-PH"]["credits.pugilib"]              = "{white}{bold}pugi{reset}{brown}{bold}xml{reset} {dark_gray}::{reset} {pink}{italic}Salamat kay {name} (alyas {name2} sa github)!! :3{reset}";
    this->Register["tl-PH"]["credits.arglib"]               = "{orange}{bold}arg{gold}parse{reset} {dark_gray}::{reset} {green}{italic}Salamat kay {name} {dark_green}para sa astig lib na 'to :>{reset}";
    this->Register["tl-PH"]["credits.jsonlib"]              = "{blue}{bold}{italic}json{reset} {dark_gray}::{reset} {teal}{italic}Salamat kay {name} para sa halimaw na lib na 'to!!{reset}";
    this->Register["tl-PH"]["credits.compiled"]             = "{dark_gray}Na-compile ang entities2.cpp version {entities2_ver} sa {compile_date} {compile_time} ;){reset}";
    this->Register["tl-PH"]["credits.title3"]               = "MARAMING SALAMAT SA MGA TAGASALIN:";
    this->Register["tl-PH"]["credits.slovak"]               = "{blue}{bold}{name}{reset} {dark_gray}::{reset} {white}{bold}wikang Ingles{reset}{white} (base game lang) at {bold}Eslobako{reset}";
    this->Register["tl-PH"]["credits.russian"]              = "{purple}{bold}{name}{reset} {dark_gray}::{reset} {white}Sinalin sa {bold}wikang Ruso{reset}";
    this->Register["tl-PH"]["credits.portuguese"]           = "{yellow}{bold}{name}{reset} {dark_gray}::{reset} {white}Sinalin sa {bold}wikang Portuges{reset}";
    this->Register["tl-PH"]["credits.tagalog"]              = "{light_blue}{bold}{name}{reset} {dark_gray}::{reset} {white}Sinalin sa {bold}wikang Tagalog{reset}";

    #endif // __ENTITIES2_BAKED_IN_TAGALOG__
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Load all of Portuguese translation.
 * \note Needs to be enabled when cmake is invoked...
 */
void TranslationEngine::LoadPortuguese()
{
    #ifdef __ENTITIES2_BAKED_IN_PORTUGUESE__

    // Language specific strings
    //this->Register["pt-PT"]["lang.name"]                    = ;
    this->Register["pt-PT"]["lang.id"]                      = "pt-PT";

    // General texts
    //this->Register["pt-PT"]["general.quit"]                 = ;
    //this->Register["pt-PT"]["general.exit"]                 = ;
    //this->Register["pt-PT"]["general.on"]                   = ;
    //this->Register["pt-PT"]["general.off"]                  = ;
    //this->Register["pt-PT"]["general.by"]                   = ;
    //this->Register["pt-PT"]["general.enter_to_exit"]        = ;
    //this->Register["pt-PT"]["general.healed"]               = ;
    //this->Register["pt-PT"]["general.regenerated"]          = ;
    //this->Register["pt-PT"]["general.enemy"]                = ;

    // Main menu texts
    //this->Register["pt-PT"]["menu.main.subtitle"]           = ;
    //this->Register["pt-PT"]["menu.main.optionpick"]         = ;
    //this->Register["pt-PT"]["menu.main.play"]               = ;
    //this->Register["pt-PT"]["menu.main.ginfo"]              = ;
    //this->Register["pt-PT"]["menu.main.datapacks"]          = ;
    //this->Register["pt-PT"]["menu.main.settings"]           = ;
    //this->Register["pt-PT"]["menu.exit.confirm"]            = ;
    //this->Register["pt-PT"]["menu.unstable"]                = ;

    // Difficulty picker texts
    //this->Register["pt-PT"]["menu.diffpicker.title"]        = ;
    //this->Register["pt-PT"]["menu.diffpicker.easy"]         = ;
    //this->Register["pt-PT"]["menu.diffpicker.medium"]       = ;
    //this->Register["pt-PT"]["menu.diffpicker.hard"]         = ;
    //this->Register["pt-PT"]["menu.diffpicker.random"]       = ;
    //this->Register["pt-PT"]["menu.diffpicker.record"]       = ;

    // Datapack viewer stuff
    //this->Register["pt-PT"]["menu.datapacks.title"]         = ;
    //this->Register["pt-PT"]["menu.datapacks.loaded"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.help1"]         = ;
    //this->Register["pt-PT"]["menu.datapacks.empty"]         = ;
    //this->Register["pt-PT"]["menu.datapacks.info"]          = ;
    //this->Register["pt-PT"]["menu.datapacks.title2"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.subtitle"]      = ;
    //this->Register["pt-PT"]["menu.datapacks.name"]          = ;
    //this->Register["pt-PT"]["menu.datapacks.author"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.id"]            = ;
    //this->Register["pt-PT"]["menu.datapacks.desc"]          = ;
    //this->Register["pt-PT"]["menu.datapacks.size"]          = ;
    //this->Register["pt-PT"]["menu.datapacks.veryhuge"]      = ;
    //this->Register["pt-PT"]["menu.datapacks.error1"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error2"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error3"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error4"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error5"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error6"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error7"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error8"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error9"]        = ;
    //this->Register["pt-PT"]["menu.datapacks.error10"]       = ;

    // Gameplay info
    //this->Register["pt-PT"]["menu.ginfo.title"]             = ;
    //this->Register["pt-PT"]["menu.ginfo.tips"]              = ;
    //this->Register["pt-PT"]["menu.ginfo.status"]            = ;
    //this->Register["pt-PT"]["menu.ginfo.tiptitle"]          = ;
    //this->Register["pt-PT"]["menu.ginfo.tip1"]              = ;
    //this->Register["pt-PT"]["menu.ginfo.tip2"]              = ;
    //this->Register["pt-PT"]["menu.ginfo.tip3"]              = ;
    //this->Register["pt-PT"]["menu.ginfo.statustitle1"]      = ;
    //this->Register["pt-PT"]["menu.ginfo.statustitle2"]      = ;
    //this->Register["pt-PT"]["menu.ginfo.autoheal"]          = ;
    //this->Register["pt-PT"]["menu.ginfo.autoheal.info"]     = ;
    //this->Register["pt-PT"]["menu.ginfo.icrit"]             = ;
    //this->Register["pt-PT"]["menu.ginfo.icrit.info"]        = ;
    //this->Register["pt-PT"]["menu.ginfo.invis"]             = ;
    //this->Register["pt-PT"]["menu.ginfo.invis.info"]        = ;
    //this->Register["pt-PT"]["menu.ginfo.poison"]            = ;
    //this->Register["pt-PT"]["menu.ginfo.poison.info"]       = ;
    //this->Register["pt-PT"]["menu.ginfo.thorns"]            = ;
    //this->Register["pt-PT"]["menu.ginfo.thorns.info"]       = ;
    //this->Register["pt-PT"]["menu.ginfo.weak"]              = ;
    //this->Register["pt-PT"]["menu.ginfo.weak.info"]         = ;

    // Settings texts
    //this->Register["pt-PT"]["menu.options.title"]           = ;
    //this->Register["pt-PT"]["menu.options.cat1"]            = ;
    //this->Register["pt-PT"]["menu.options.cat2"]            = ;
    //this->Register["pt-PT"]["menu.options.cat3"]            = ;
    //this->Register["pt-PT"]["menu.options.c1o1"]            = ;
    //this->Register["pt-PT"]["menu.options.login"]           = ;
    //this->Register["pt-PT"]["menu.options.currlang"]        = ;
    //this->Register["pt-PT"]["menu.options.changelang"]      = ;
    //this->Register["pt-PT"]["menu.options.langutils"]       = ;
    //this->Register["pt-PT"]["menu.options.export1"]         = ;
    //this->Register["pt-PT"]["menu.options.export2"]         = ;
    //this->Register["pt-PT"]["menu.options.export3"]         = ;
    //this->Register["pt-PT"]["menu.options.newuser"]         = ;
    //this->Register["pt-PT"]["menu.options.changename"]      = ;
    //this->Register["pt-PT"]["menu.options.help1"]           = ;
    //this->Register["pt-PT"]["menu.options.help2"]           = ;
    //this->Register["pt-PT"]["menu.options.help3"]           = ;
    //this->Register["pt-PT"]["menu.options.help4"]           = ;
    //this->Register["pt-PT"]["menu.options.enteruser"]       = ;
    //this->Register["pt-PT"]["menu.options.usererror"]       = ;
    //this->Register["pt-PT"]["menu.options.lang.select"]     = ;
    //this->Register["pt-PT"]["menu.options.lang.loading"]    = ;
    //this->Register["pt-PT"]["menu.options.lang.line1"]      = ;
    //this->Register["pt-PT"]["menu.options.lang.line2"]      = ;
    //this->Register["pt-PT"]["menu.options.lang.line3"]      = ;

    // Language utilities texts
    //this->Register["pt-PT"]["menu.langutils.success"]       = ;
    //this->Register["pt-PT"]["menu.langutils.fail"]          = ;
    //this->Register["pt-PT"]["menu.langutils.getpath"]       = ;
    //this->Register["pt-PT"]["menu.langutils.pathfail"]      = ;
    //this->Register["pt-PT"]["menu.langutils.notfile"]       = ;

    // Greet texts
    //this->Register["pt-PT"]["greet.morning.1"]              = ;
    //this->Register["pt-PT"]["greet.morning.2"]              = ;
    //this->Register["pt-PT"]["greet.morning.3"]              = ;
    //this->Register["pt-PT"]["greet.afternoon.1"]            = ;
    //this->Register["pt-PT"]["greet.afternoon.2"]            = ;
    //this->Register["pt-PT"]["greet.afternoon.3"]            = ;
    //this->Register["pt-PT"]["greet.evening.1"]              = ;
    //this->Register["pt-PT"]["greet.evening.2"]              = ;
    //this->Register["pt-PT"]["greet.evening.3"]              = ;
    //this->Register["pt-PT"]["greet.earlynight.1"]           = ;
    //this->Register["pt-PT"]["greet.earlynight.2"]           = ;
    //this->Register["pt-PT"]["greet.threeam.1"]              = ;
    //this->Register["pt-PT"]["greet.threeam.2"]              = ;
    //this->Register["pt-PT"]["greet.threeam.3"]              = ;

    // Gameplay strings
    //this->Register["pt-PT"]["game.battle.announce"]         = ;
    //this->Register["pt-PT"]["game.battle.what_happened"]    = ;
    //this->Register["pt-PT"]["game.battle.ply_header"]       = ;
    //this->Register["pt-PT"]["game.battle.ene_header"]       = ;
    //this->Register["pt-PT"]["game.battle.enemy"]            = ;
    //this->Register["pt-PT"]["game.battle.regen_moves"]      = ;
    //this->Register["pt-PT"]["game.battle.move_choose"]      = ;
    //this->Register["pt-PT"]["game.battle.exit"]             = ;
    //this->Register["pt-PT"]["game.battle.skip"]             = ;
    //this->Register["pt-PT"]["game.battle.enemy_skip"]       = ;
    //this->Register["pt-PT"]["game.battle.no_energy"]        = ;
    //this->Register["pt-PT"]["game.battle.rerolled"]         = ;
    //this->Register["pt-PT"]["game.battle.ai_think"]         = ;
    //this->Register["pt-PT"]["game.moves.attack"]            = ;
    //this->Register["pt-PT"]["game.moves.heal"]              = ;
    //this->Register["pt-PT"]["game.moves.regen"]             = ;
    //this->Register["pt-PT"]["game.moves.autoheal"]          = ;
    //this->Register["pt-PT"]["game.moves.icrit"]             = ;
    //this->Register["pt-PT"]["game.moves.invis"]             = ;
    //this->Register["pt-PT"]["game.moves.poison"]            = ;
    //this->Register["pt-PT"]["game.moves.thorns"]            = ;
    //this->Register["pt-PT"]["game.moves.weakness"]          = ;
    //this->Register["pt-PT"]["game.moves.gameover"]          = ;
    //this->Register["pt-PT"]["game.moves.victory"]           = ;
    //this->Register["pt-PT"]["game.moves.rematch"]           = ;
    //this->Register["pt-PT"]["game.applied.autoheal"]        = ;
    //this->Register["pt-PT"]["game.applied.incr_crit"]       = ;
    //this->Register["pt-PT"]["game.applied.invis"]           = ;
    //this->Register["pt-PT"]["game.applied.poison"]          = ;
    //this->Register["pt-PT"]["game.applied.thorns"]          = ;
    //this->Register["pt-PT"]["game.applied.weakness"]        = ;

    // Entity attack texts
    //this->Register["pt-PT"]["entity.attack.ply_missed"]     = ;
    //this->Register["pt-PT"]["entity.attack.ene_missed"]     = ;
    //this->Register["pt-PT"]["entity.attack.ply_normal"]     = ;
    //this->Register["pt-PT"]["entity.attack.ply_crit"]       = ;
    //this->Register["pt-PT"]["entity.attack.ene_normal"]     = ;
    //this->Register["pt-PT"]["entity.attack.ene_crit"]       = ;

    // Exit messages :3
    //this->Register["pt-PT"]["exit.message.1"]               = ;
    //this->Register["pt-PT"]["exit.message.win2"]            = ;
    //this->Register["pt-PT"]["exit.message.win3"]            = ;
    //this->Register["pt-PT"]["exit.message.win4"]            = ;
    //this->Register["pt-PT"]["exit.message.win5"]            = ;
    //this->Register["pt-PT"]["exit.message.mac2"]            = ;
    //this->Register["pt-PT"]["exit.message.mac3"]            = ;
    //this->Register["pt-PT"]["exit.message.mac4"]            = ;
    //this->Register["pt-PT"]["exit.message.mac5"]            = ;
    //this->Register["pt-PT"]["exit.message.lix2"]            = ;
    //this->Register["pt-PT"]["exit.message.lix3"]            = ;
    //this->Register["pt-PT"]["exit.message.lix4"]            = ;
    //this->Register["pt-PT"]["exit.message.lix5"]            = ;
    //this->Register["pt-PT"]["exit.message.6"]               = ;
    //this->Register["pt-PT"]["exit.message.8"]               = ;
    //this->Register["pt-PT"]["exit.message.9"]               = ;
    //this->Register["pt-PT"]["exit.message.10"]              = ;
    //this->Register["pt-PT"]["exit.message.11"]              = ;
    //this->Register["pt-PT"]["exit.message.12"]              = ;
    //this->Register["pt-PT"]["exit.message.13"]              = ;
    //this->Register["pt-PT"]["exit.message.14"]              = ;
    //this->Register["pt-PT"]["exit.message.15"]              = ;
    //this->Register["pt-PT"]["exit.message.16"]              = ;
    //this->Register["pt-PT"]["exit.message.19"]              = ;
    //this->Register["pt-PT"]["exit.message.21"]              = ;
    //this->Register["pt-PT"]["exit.message.22"]              = ;
    //this->Register["pt-PT"]["exit.message.23"]              = ;
    //this->Register["pt-PT"]["exit.message.24"]              = ;
    //this->Register["pt-PT"]["exit.message.25"]              = ;
    //this->Register["pt-PT"]["exit.message.26"]              = ;
    //this->Register["pt-PT"]["exit.message.27"]              = ;
    //this->Register["pt-PT"]["exit.message.28"]              = ;
    //this->Register["pt-PT"]["exit.message.29"]              = ;
    //this->Register["pt-PT"]["exit.message.30"]              = ;
    //this->Register["pt-PT"]["exit.message.31"]              = ;
    //this->Register["pt-PT"]["exit.message.32"]              = ;
    //this->Register["pt-PT"]["exit.message.33"]              = ;
    //this->Register["pt-PT"]["exit.message.34"]              = ;
    //this->Register["pt-PT"]["exit.message.35"]              = ;
    //this->Register["pt-PT"]["exit.message.36"]              = ;
    //this->Register["pt-PT"]["exit.message.37"]              = ;
    //this->Register["pt-PT"]["exit.message.39"]              = ;
    //this->Register["pt-PT"]["exit.message.40"]              = ;
    //this->Register["pt-PT"]["exit.message.41"]              = ;
    //this->Register["pt-PT"]["exit.message.42"]              = ;
    //this->Register["pt-PT"]["exit.message.45"]              = ;
    //this->Register["pt-PT"]["exit.message.47"]              = ;
    //this->Register["pt-PT"]["exit.message.48"]              = ;
    //this->Register["pt-PT"]["exit.message.49"]              = ;
    //this->Register["pt-PT"]["exit.message.50"]              = ;
    //this->Register["pt-PT"]["exit.message.51"]              = ;
    //this->Register["pt-PT"]["exit.message.52"]              = ;
    //this->Register["pt-PT"]["exit.message.53"]              = ;
    //this->Register["pt-PT"]["exit.message.54"]              = ;
    //this->Register["pt-PT"]["exit.message.56"]              = ;
    //this->Register["pt-PT"]["exit.message.57"]              = ;
    //this->Register["pt-PT"]["exit.message.58"]              = ;
    //this->Register["pt-PT"]["exit.message.59"]              = ;
    //this->Register["pt-PT"]["exit.message.61"]              = ;
    //this->Register["pt-PT"]["exit.message.62"]              = ;
    //this->Register["pt-PT"]["exit.message.64"]              = ;
    //this->Register["pt-PT"]["exit.message.65"]              = ;
    //this->Register["pt-PT"]["exit.message.67"]              = ;
    //this->Register["pt-PT"]["exit.message.70"]              = ;
    //this->Register["pt-PT"]["exit.message.special"]         = ;

    // Credits :3
    //this->Register["pt-PT"]["credits.title1"]               = ;
    //this->Register["pt-PT"]["credits.gameby"]               = ;
    //this->Register["pt-PT"]["credits.writtenin"]            = ;
    //this->Register["pt-PT"]["credits.moreinfo1"]            = ;
    //this->Register["pt-PT"]["credits.moreinfo2"]            = ;
    //this->Register["pt-PT"]["credits.moreinfo3"]            = ;
    //this->Register["pt-PT"]["credits.moreinfo4"]            = ;
    //this->Register["pt-PT"]["credits.title2"]               = ;
    //this->Register["pt-PT"]["credits.discordlib"]           = ;
    //this->Register["pt-PT"]["credits.fmtlib"]               = ;
    //this->Register["pt-PT"]["credits.pugilib"]              = ;
    //this->Register["pt-PT"]["credits.arglib"]               = ;
    //this->Register["pt-PT"]["credits.jsonlib"]              = ;
    //this->Register["pt-PT"]["credits.compiled"]             = ;
    //this->Register["pt-PT"]["credits.title3"]               = ;
    //this->Register["pt-PT"]["credits.slovak"]               = ;
    //this->Register["pt-PT"]["credits.russian"]              = ;
    //this->Register["pt-PT"]["credits.portuguese"]           = ;
    //this->Register["pt-PT"]["credits.tagalog"]              = ;

    #endif // __ENTITIES2_BAKED_IN_PORTUGUESE__
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.