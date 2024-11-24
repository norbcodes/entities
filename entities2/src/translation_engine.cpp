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
 */
void TranslationEngine::SetLang(const std::string& id)
{
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
        return str;
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
        return str;
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
std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator TranslationEngine::Begin() const
{
    return (this->Register.begin());
}

/**
 * \brief An iterator of the internal std::map.
 * \return std::map<...>::const_iterator
 */
std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator TranslationEngine::End() const
{
    return (this->Register.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Load all of English translation.
 */
void TranslationEngine::LoadEnglish()
{
    // IS ALWAYS CALLED.
    // THE BASE LANGUAGE.
    // Strings are in raw form
    // They are formatted where they are needed

    // Language specific strings
    this->Register["EN-US"]["lang.name"]                    = "English (USA)";
    this->Register["EN-US"]["lang.id"]                      = "EN-US";

    // General texts
    this->Register["EN-US"]["general.quit"]                 = "Quit";
    this->Register["EN-US"]["general.exit"]                 = "Exit";
    this->Register["EN-US"]["general.on"]                   = "ON";
    this->Register["EN-US"]["general.off"]                  = "OFF";
    this->Register["EN-US"]["general.by"]                   = "by";
    this->Register["EN-US"]["general.enter_to_exit"]        = "Press enter to continue.";

    // Main menu texts
    this->Register["EN-US"]["menu.main.subtitle"]           = "A game by norbcodes.";
    this->Register["EN-US"]["menu.main.optionpick"]         = "Pick an option:";
    this->Register["EN-US"]["menu.main.play"]               = "Play";
    this->Register["EN-US"]["menu.main.ginfo"]              = "Gameplay Info";
    this->Register["EN-US"]["menu.main.datapacks"]          = "Datapacks";
    this->Register["EN-US"]["menu.main.settings"]           = "Settings";
    this->Register["EN-US"]["menu.exit.confirm"]            = "Confirm exit?";
    this->Register["EN-US"]["menu.unstable"]                = "{red}You are using a game build that is {bold}still under Development!{reset}\n{white}Proceed with caution. {red}Do you still wanna play? [y,n]{reset}";

    // Difficulty picker texts
    this->Register["EN-US"]["menu.diffpicker.title"]        = "Difficulty Selection";
    this->Register["EN-US"]["menu.diffpicker.easy"]         = "I kick Entities ass";
    this->Register["EN-US"]["menu.diffpicker.medium"]       = "I've seen worse";
    this->Register["EN-US"]["menu.diffpicker.hard"]         = "Down with the Entities";
    this->Register["EN-US"]["menu.diffpicker.random"]       = "Random!";
    this->Register["EN-US"]["menu.diffpicker.record"]       = "Record demo";

    // Datapack viewer stuff
    this->Register["EN-US"]["menu.datapacks.title"]         = "Datapacks";
    this->Register["EN-US"]["menu.datapacks.loaded"]        = "{white}Currently loaded {purple}{datapack_count}{reset}{white} datapacks.{reset}";
    this->Register["EN-US"]["menu.datapacks.help1"]         = "Use up, down arrows to scroll.";
    this->Register["EN-US"]["menu.datapacks.empty"]         = "No datapacks!";
    this->Register["EN-US"]["menu.datapacks.info"]          = "Press left arrow to go back. Press right arrow to view a datapacks' info.";
    this->Register["EN-US"]["menu.datapacks.title2"]        = "Datapack Info";
    this->Register["EN-US"]["menu.datapacks.subtitle"]      = "Metadata:";
    this->Register["EN-US"]["menu.datapacks.name"]          = "Name:";
    this->Register["EN-US"]["menu.datapacks.author"]        = "Author:";
    this->Register["EN-US"]["menu.datapacks.id"]            = "Datapack id:";
    this->Register["EN-US"]["menu.datapacks.desc"]          = "Description:";
    this->Register["EN-US"]["menu.datapacks.error1"]        = "Main \"Datapack\" block missing!";
    this->Register["EN-US"]["menu.datapacks.error2"]        = "Main \"Meta\" block missing!";
    this->Register["EN-US"]["menu.datapacks.error3"]        = "Main \"Data\" block missing!";
    this->Register["EN-US"]["menu.datapacks.error4"]        = "Datapack name missing!";
    this->Register["EN-US"]["menu.datapacks.error5"]        = "Datapack author missing!";
    this->Register["EN-US"]["menu.datapacks.error6"]        = "Datapack identificator missing!";
    this->Register["EN-US"]["menu.datapacks.error7"]        = "Broken translations!";
    this->Register["EN-US"]["menu.datapacks.error8"]        = "Greeting has no time specified!";
    this->Register["EN-US"]["menu.datapacks.error9"]        = "Empty greeting!";
    this->Register["EN-US"]["menu.datapacks.error10"]       = "Empty exit message!";

    // Gameplay info
    this->Register["EN-US"]["menu.ginfo.title"]             = "Gameplay Info!";
    this->Register["EN-US"]["menu.ginfo.tips"]              = "Tips and Tricks";
    this->Register["EN-US"]["menu.ginfo.status"]            = "Statuses and what they do";
    this->Register["EN-US"]["menu.ginfo.tiptitle"]          = "TIPS 'N' TRICKS";
    this->Register["EN-US"]["menu.ginfo.tip1"]              = "You can use skip a round by choosing neither 0, 1, 2, 3 or 4.";
    this->Register["EN-US"]["menu.ginfo.tip2"]              = "If need be, you can skip a round to recharge your energy.";
    this->Register["EN-US"]["menu.ginfo.tip3"]              = "The AI will try to attack if it has more than 60 HP.";
    this->Register["EN-US"]["menu.ginfo.statustitle1"]      = "STATUSES";
    this->Register["EN-US"]["menu.ginfo.statustitle2"]      = "and what they do...";
    this->Register["EN-US"]["menu.ginfo.autoheal"]          = "AutoHeal";
    this->Register["EN-US"]["menu.ginfo.autoheal.info"]     = "{white}At the start of a {underline}new round{reset}{white}, the entity that{reset}\n   {white}has {underline}their turn will recieve {purple}{bold}+{autoheal_amount}HP of health.{reset}";
    this->Register["EN-US"]["menu.ginfo.icrit"]             = "IncreasedCrit";
    this->Register["EN-US"]["menu.ginfo.icrit.info"]        = "{white}When an entity has this status, it has {underline}about {purple}~30%{reset}\n   {white}of dealing a {underline}critical attack{reset}{white}, which deals{reset}\n   {white}significantly {underline}more damage.{reset}";
    this->Register["EN-US"]["menu.ginfo.invis"]             = "Invisibility";
    this->Register["EN-US"]["menu.ginfo.invis.info"]        = "{white}When an entity has this status, there's{reset}\n   {white}a {underline}{purple}~20%{reset} {white}chance of an attacker {underline}missing{reset}\n   {white}{underline}the attack when attacking this entity.{reset}";
    this->Register["EN-US"]["menu.ginfo.poison"]            = "Poison";
    this->Register["EN-US"]["menu.ginfo.poison.info"]       = "{white}At the start of a {underline}new round{reset}, the entity that{reset}\n   {white}has {underline}their turn will recieve {purple}{bold}-{poison_amount}HP of damage.{reset}";
    this->Register["EN-US"]["menu.ginfo.thorns"]            = "Thorns";
    this->Register["EN-US"]["menu.ginfo.thorns.info"]       = "{white}When an entity with this status is{reset}\n   {white}attacked, {underline}50% of the damage{reset}{white} goes back to the {underline}attacker.{reset}";
    this->Register["EN-US"]["menu.ginfo.weak"]              = "Weakness";
    this->Register["EN-US"]["menu.ginfo.weak.info"]         = "{white}A weakened enemy has their HP and AR {underline}{purple}capped at 60 only.{reset}\n   {white}Their energy replenishes {underline}{purple}75% less per round{reset}{white}, too.{reset}\n   {white}They also {underline}{purple}attack less{reset}{white}. This status only lasts {weakness_time} rounds.{reset}";

    // Settings texts
    this->Register["EN-US"]["menu.options.title"]           = "Settings";
    this->Register["EN-US"]["menu.options.cat1"]            = " 1 DISCORD SETTINGS ";
    this->Register["EN-US"]["menu.options.cat2"]            = " 2 LANGUAGE SETTINGS ";
    this->Register["EN-US"]["menu.options.cat3"]            = " 3 USER SETTINGS ";
    this->Register["EN-US"]["menu.options.c1o1"]            = "Discord RPC:";
    this->Register["EN-US"]["menu.options.login"]           = "Logged in as";
    this->Register["EN-US"]["menu.options.currlang"]        = "Current language:";
    this->Register["EN-US"]["menu.options.changelang"]      = "Change language...";
    this->Register["EN-US"]["menu.options.newuser"]         = "Create new user...";
    this->Register["EN-US"]["menu.options.changename"]      = "Change username...";
    this->Register["EN-US"]["menu.options.help1"]           = "{white}Press {green}1{white} to enter {green}Edit{white} mode. Press {red}9{white} to {red}go back to main menu{white}.{reset}";
    this->Register["EN-US"]["menu.options.help2"]           = "{white}Press {red}left arrow{white} to exit {red}Edit{white} mode.{reset}";
    this->Register["EN-US"]["menu.options.help3"]           = "{white}Use {purple}up and down arrows{white} to {purple}move{white}.{reset}";
    this->Register["EN-US"]["menu.options.help4"]           = "{white}Press {yellow}right arrow{white} to {yellow}change a setting{white}.{reset}";
    this->Register["EN-US"]["menu.options.enteruser"]       = "Enter your username:";
    this->Register["EN-US"]["menu.options.usererror"]       = "Username cannot have spaces!";
    this->Register["EN-US"]["menu.options.lang.select"]     = "Language Selection";
    this->Register["EN-US"]["menu.options.lang.laoding"]    = "Loading...";
    this->Register["EN-US"]["menu.options.lang.line1"]      = "Current language: {lang}";
    this->Register["EN-US"]["menu.options.lang.line2"]      = "There are {lang_count} languages loaded.";
    this->Register["EN-US"]["menu.options.lang.line3"]      = "Up/down arrows to move, right to select language and left to leave.";

    // Greet texts
    this->Register["EN-US"]["greet.morning.1"]              = "{white}Good morning, {username}. Ready to kill?{reset}";
    this->Register["EN-US"]["greet.morning.2"]              = "{white}Good morning, {username}. Grab a coffee and crush some entities.{reset}";
    this->Register["EN-US"]["greet.morning.3"]              = "{white}Good morning, {username}. Rise and shine!{reset}";
    this->Register["EN-US"]["greet.afternoon.1"]            = "{white}Good afternoon, {username}. Back for more blood?{reset}";
    this->Register["EN-US"]["greet.afternoon.2"]            = "{white}Good afternoon, {username}. Today's lunch: Entities{reset}";
    this->Register["EN-US"]["greet.afternoon.3"]            = "{white}Good afternoon, {username}. I would really go for a nap now...{reset}";
    this->Register["EN-US"]["greet.evening.1"]              = "{white}Good evening, {username}. 5 minutes until bedtime.{reset}";
    this->Register["EN-US"]["greet.evening.2"]              = "{white}Good evening, {username}. Entities are sleepy now, surprise attack!{reset}";
    this->Register["EN-US"]["greet.evening.3"]              = "{white}Good evening, {username}. *{italic}Yawn{reset}{white}*{reset}";
    this->Register["EN-US"]["greet.earlynight.1"]           = "{white}Good night, {username}. Can't sleep yet?{reset}";
    this->Register["EN-US"]["greet.earlynight.2"]           = "{white}Good night, {username}. Was dinner yummy?{reset}";
    this->Register["EN-US"]["greet.threeam.1"]              = "{white}Good night, {username}. Spooky time!{reset}";
    this->Register["EN-US"]["greet.threeam.2"]              = "{white}Good night, {username}. The line between mortal and the other side blurs...{reset}";
    this->Register["EN-US"]["greet.threeam.3"]              = "{white}Good night, {username}. Something feels off..{reset}";

    // Gameplay strings
    this->Register["EN-US"]["game.battle.announce"]         = "{red}{italic}The fights begins. Good luck {username}!{reset}";
    this->Register["EN-US"]["game.battle.what_happened"]    = "{white}What happened last round:{reset}\n{what_happened}{reset}";
    this->Register["EN-US"]["game.battle.ply_header"]       = "{dark_gray}---<<< {blue}{bold}{username}'s{reset} {dark_gray}turn! >>>---{reset}";
    this->Register["EN-US"]["game.battle.ene_header"]       = "{dark_gray}---<<< {red}{bold}Enemy's{reset} {dark_gray}turn! >>>---{reset}";
    this->Register["EN-US"]["game.battle.enemy"]            = "ENEMY";
    this->Register["EN-US"]["game.battle.regen_moves"]      = "Regenerate moves...";
    this->Register["EN-US"]["game.battle.move_choose"]      = "{white}Choose your move. {dark_gray}{bold}[1,2,3,4,5] (0 to exit){reset}";
    this->Register["EN-US"]["game.battle.exit"]             = "Do you really wanna end the battle?";
    this->Register["EN-US"]["game.battle.skip"]             = "skipped the round.";
    this->Register["EN-US"]["game.battle.enemy_skip"]       = "{red}{bold}Enemy{reset} {white}skipped the round.{reset}";
    this->Register["EN-US"]["game.battle.no_energy"]        = "Not enough energy!";
    this->Register["EN-US"]["game.battle.rerolled"]         = "{blue}{bold}{username}{reset}{white} rerolled their moves...{reset}";
    this->Register["EN-US"]["game.battle.ai_think"]         = "The AI is thinking...";
    this->Register["EN-US"]["game.moves.attack"]            = "{red}Attack! {white}Deal {purple}{value}{white} damage to opponent.{reset}";
    this->Register["EN-US"]["game.moves.heal"]              = "{green}Heal! {white}Gives you {purple}+{value}{white} HP{reset}";
    this->Register["EN-US"]["game.moves.regen"]             = "{blue}Regen armor{white}! Gives you {purple}+{value}{white} AR{reset}";
    this->Register["EN-US"]["game.moves.autoheal"]          = "{white}Apply {green}AutoHeal {white}status! Gives you {purple}{value} {white}HP when it's your turn{reset}";
    this->Register["EN-US"]["game.moves.icrit"]             = "{white}Apply {red}IncreasedCrit {white}status! Increased {red}critical attack chance{reset}";
    this->Register["EN-US"]["game.moves.invis"]             = "{white}Apply {hot_pink}Invis {white}status! Opponent has a chance to {hot_pink}miss{reset}";
    this->Register["EN-US"]["game.moves.poison"]            = "{white}Give opponent {dark_green}Poison {white}status! Deals {purple}{value}{white} poison damage{reset}";
    this->Register["EN-US"]["game.moves.thorns"]            = "{white}Apply {teal}Thorns {white}status! Opponent will {bold}take damage too on attack{reset}";
    this->Register["EN-US"]["game.moves.weakness"]          = "{white}Give opponent {brown}Weakness {white}status! Opponent will be weakened...{reset}";
    this->Register["EN-US"]["game.moves.gameover"]          = "{white}---<<< {blue}{bold}{username}{reset} {white}dead. {red}{bold}Enemy{reset}{white} wins!!! >>>---{reset}";
    this->Register["EN-US"]["game.moves.victory"]           = "{white}---<<< {red}{bold}Enemy{reset} {white}dead. {blue}{bold}{username}{reset}{white} wins!!! >>>---{reset}";
    this->Register["EN-US"]["game.moves.rematch"]           = "Rematch!";

    // Exit messages :3
    this->Register["EN-US"]["exit.message.1"]               = "{white}Noooooo don't leave yet :<{reset}";
    this->Register["EN-US"]["exit.message.win2"]            = "{white}Are you sure? {italic}Windows is much worse...{reset}";
    this->Register["EN-US"]["exit.message.win3"]            = "{white}Of course, as if Windows is more fun!{reset}";
    this->Register["EN-US"]["exit.message.win4"]            = "{white}You know that Bill Gates approves of this game, right?{reset}";
    this->Register["EN-US"]["exit.message.win5"]            = "{white}Right right, don't forget to close the windows on the way out.{reset}";
    this->Register["EN-US"]["exit.message.mac2"]            = "{white}Are you sure? {italic}Mac is much worse...{reset}";
    this->Register["EN-US"]["exit.message.mac3"]            = "{white}Of course, as if Mac is more fun!{reset}";
    this->Register["EN-US"]["exit.message.mac4"]            = "{white}You know that Steve Jobs approved of this game, right?{reset}";
    this->Register["EN-US"]["exit.message.mac5"]            = "{white}An Apple a day keeps the wallet away.{reset}";
    this->Register["EN-US"]["exit.message.lix2"]            = "{white}Are you sure? {italic}Linux is much worse...{reset}";
    this->Register["EN-US"]["exit.message.lix3"]            = "{white}Of course, as if Linux is more fun!{reset}";
    this->Register["EN-US"]["exit.message.lix4"]            = "{white}You know that Linus Torvalds approves of this game, right?{reset}";
    this->Register["EN-US"]["exit.message.lix5"]            = "{white}Linuwux{reset}";
    this->Register["EN-US"]["exit.message.6"]               = "{white}The enemy still has 6 hp left!{reset}";
    this->Register["EN-US"]["exit.message.8"]               = "{white}Huh? Why?{reset}";
    this->Register["EN-US"]["exit.message.9"]               = "{white}You leave now, you forfeit your kill count!{reset}";
    this->Register["EN-US"]["exit.message.10"]              = "{white}Atleast you tried, can't argue with that.{reset}";
    this->Register["EN-US"]["exit.message.11"]              = "{white}Don't go yet!{reset}";
    this->Register["EN-US"]["exit.message.12"]              = "{white}Pssst, i'll give you 3 free powerups if you stay... ;){reset}";
    this->Register["EN-US"]["exit.message.13"]              = "{white}Are you sure? It's dangerous outside...{reset}";
    this->Register["EN-US"]["exit.message.14"]              = "{white}Tch, just go. Unworthy.{reset}";
    this->Register["EN-US"]["exit.message.15"]              = "{white}Ok{reset}";
    this->Register["EN-US"]["exit.message.16"]              = "{white}Honey are you cheating on me with Java games?{reset}";
    this->Register["EN-US"]["exit.message.19"]              = "{white}The prophecy says you'll continue playing. You dare break the prophecy?{reset}";
    this->Register["EN-US"]["exit.message.21"]              = "{white}Thank you for downloading our malware :3{reset}";
    this->Register["EN-US"]["exit.message.22"]              = "{white}Press 'y', and in your coffin you will lay!{reset}";
    this->Register["EN-US"]["exit.message.23"]              = "{white}Don't be silly! Stay a while longer!{reset}";
    this->Register["EN-US"]["exit.message.24"]              = "{white}The entities live in your walls{reset}";
    this->Register["EN-US"]["exit.message.25"]              = "{white}I, norbcodes, live rent free in your ceiling{reset}";
    this->Register["EN-US"]["exit.message.26"]              = "{white}Really?{reset}";
    this->Register["EN-US"]["exit.message.27"]              = "{white}For reals?{reset}";
    this->Register["EN-US"]["exit.message.28"]              = "{white}Babeeee! No!{reset}";
    this->Register["EN-US"]["exit.message.29"]              = "{white}Is your fridge running...?{reset}";
    this->Register["EN-US"]["exit.message.30"]              = "{white}Is your stove turned off...?{reset}";
    this->Register["EN-US"]["exit.message.31"]              = "{white}What? Heap memory allocs scared you away?{reset}";
    this->Register["EN-US"]["exit.message.32"]              = "{white}There's a chance a neutrino particle is\npassing through your skull right now.{reset}";
    this->Register["EN-US"]["exit.message.33"]              = "{white}Let that sink in.{reset}";
    this->Register["EN-US"]["exit.message.34"]              = "{white}Oh no! Your 'y' button just broke!{reset}";
    this->Register["EN-US"]["exit.message.35"]              = "{white}LMFAOOOOO{reset}";
    this->Register["EN-US"]["exit.message.36"]              = "{white}The outside is not real. Wake up. Wake up.{reset}";
    this->Register["EN-US"]["exit.message.37"]              = "{white}Original entities more fun?{reset}";
    this->Register["EN-US"]["exit.message.39"]              = "{white}I, norbcodes, do not approve!!! >:({reset}";
    this->Register["EN-US"]["exit.message.40"]              = "{white}Maybe i'll break your keyboard then{reset}";
    this->Register["EN-US"]["exit.message.41"]              = "{white}Come back soon. We're gonna be having a pizza party.{reset}";
    this->Register["EN-US"]["exit.message.42"]              = "{white}Goodbye :3{reset}";
    this->Register["EN-US"]["exit.message.45"]              = "{white}*{italic}insert exit message here{reset}{white}*{reset}";
    this->Register["EN-US"]["exit.message.47"]              = "{white}Dude, just choose a lower difficulty. No need for drastic measures.{reset}";
    this->Register["EN-US"]["exit.message.48"]              = "{white}*{italic}insert threatening exit message here{reset}{white}*{reset}";
    this->Register["EN-US"]["exit.message.49"]              = "{white}Fine, get out of my face.{reset}";
    this->Register["EN-US"]["exit.message.50"]              = "{white}Nuuuuu pwease staay :({reset}";
    this->Register["EN-US"]["exit.message.51"]              = "{white}><>     <---- fish{reset}";
    this->Register["EN-US"]["exit.message.52"]              = "{red}exit{reset}{white}(){reset}";
    this->Register["EN-US"]["exit.message.53"]              = "{white}No syntax highlighting for you!!!{reset}";
    this->Register["EN-US"]["exit.message.54"]              = "{{red}}{{bold}}Damn, my formatting broke{{reset}}";
    this->Register["EN-US"]["exit.message.56"]              = "{white}Do\n  not\n     exit,\n          PLEASE{reset}";
    this->Register["EN-US"]["exit.message.57"]              = "{white}I hate you >:({reset}";
    this->Register["EN-US"]["exit.message.58"]              = "{white}You KNOW that this is the best game ever made, right?{reset}";
    this->Register["EN-US"]["exit.message.59"]              = "{white}Classic, just give up when you fail once.{reset}";
    this->Register["EN-US"]["exit.message.61"]              = "{white}I will report your Github account if you leave >:({reset}";
    this->Register["EN-US"]["exit.message.62"]              = "{white}Meow meerpppp :3{reset}";
    this->Register["EN-US"]["exit.message.64"]              = "{white}And the \"Best Player\" award goes to...{reset}";
    this->Register["EN-US"]["exit.message.65"]              = "{white}no balls :>{reset}";
    this->Register["EN-US"]["exit.message.67"]              = "{white}Yeah go play your Valorant or whatever you kids play nowadays{reset}";
    this->Register["EN-US"]["exit.message.70"]              = "{white}When's your birthday?{reset}";
    this->Register["EN-US"]["exit.message.special"]         = "{white}Did you know? Each of these message has a {purple}{perc:.2f}%{white} chance to appear.{reset}";
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0