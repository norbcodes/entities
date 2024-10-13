// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file entity.cpp
 * \author norbcodes
 * \brief Entity specific code!
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <string>
#include <vector>
#include <math.h>
#include <fmt/core.h>

#include "energy_constants.hpp"
#include "entity_constants.hpp"
#include "status_constants.hpp"
#include "colors.hpp"
#include "entity.hpp"
#include "utils.hpp"
#include "rng.hpp"
#include "user_settings.hpp"

/**
 * \brief Entity constructor function.
 * \details Initializes the Entity class, and allocates the status_list vector with size 32.
 * \param[in] start_health Starting health.
 * \param[in] start_armor Starting armor.
 */
Entity::Entity(int32_t start_health, int32_t start_armor) : health(start_health), armor(start_armor), energy(STARTING_ENERGY)
{
    this->status_list.reserve(32);
}

/**
 * \brief Return the Entity's health.
 * \return The health, in int32_t form.
 */
int32_t Entity::GetHealth() const
{
    return this->health;
}

/**
 * \brief Return the Entity's armor.
 * \return The armor, in int32_t form.
 */
int32_t Entity::GetArmor() const
{
    return this->armor;
}

/**
 * \brief Deal damage to this Entity.
 * \param[in] dmg The damage value.
 */
void Entity::Hurt(uint32_t dmg)
{
    if ((this->health - dmg) <= 0)
    {
        this->health = 0;
        return;
    }
    this->health -= dmg;
}

/**
 * \brief Deal damage to this Entity's armor.
 * \param[in] dmg The damage value.
 */
void Entity::HurtArmor(uint32_t dmg)
{
    if ((this->armor - dmg) <= 0)
    {
        this->armor = 0;
        return;
    }
    this->armor -= dmg;
}

/**
 * \brief Heal this Entity.
 * \param[in] val The health value.
 */
void Entity::Heal(uint32_t val)
{
    if (this->StatusActive(WEAKNESS))
    {
        if ((this->health + val) >= 60)
        {
            this->health = 60;
            return;
        }
        this->health += val;
        return;
    }

    if ((this->health + val) >= MAX_STAT_CAP)
    {
        this->health = MAX_STAT_CAP;
        return;
    }
    this->health += val;
}

/**
 * \brief Heal this Entity's armor.
 * \param[in] val The healing value.
 */
void Entity::RegenArmor(uint32_t val)
{
    if (this->StatusActive(WEAKNESS))
    {
        if ((this->armor + val) >= 60)
        {
            this->armor = 60;
            return;
        }
        this->armor += val;
        return;
    }

    if ((this->armor + val) >= MAX_STAT_CAP)
    {
        this->armor = MAX_STAT_CAP;
        return;
    }
    this->armor += val;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print Entity stats.
 * \param[in] ent A constant reference to an instance of class Entity.<br>
 *                This is where we pull data from to display.
 */
void PrintEntityStats(const Entity& ent)
{
    // I love fmt so much
    // Print HP and AR and S
    fmt::print("{3}{4}HP: {0}{5}{1:>3} {6}{4}AR: {0}{5}{2:>3}{0} {7}{4}S: {0}", RESET, ent.GetHealth(), ent.GetArmor(), GREEN, BOLD, WHITE, PINK, GOLD);
    // Iterate through the statuses and print them
    for (int i = 0; i != ent.StatusCount(); i++)
    {
        Status _s = ent.GetStatusAt(i);
        if (_s.GetType() == AUTO_HEAL)
        {
            fmt::print("{2}+{3}{1}{0} ", RESET, _s.GetTimeLeft(), GREEN, DARK_GRAY);
        }
        else if (_s.GetType() == INCR_CRIT)
        {
            fmt::print("{2}X{3}{1}{0} ", RESET, _s.GetTimeLeft(), RED, DARK_GRAY);
        }
        else if (_s.GetType() == INVIS)
        {
            fmt::print("{2}O{3}{1}{0} ", RESET, _s.GetTimeLeft(), WHITE, DARK_GRAY);
        }
        else if (_s.GetType() == POISON)
        {
            fmt::print("{2}P{3}{1}{0} ", RESET, _s.GetTimeLeft(), DARK_GREEN, DARK_GRAY);
        }
        else if (_s.GetType() == THORNS)
        {
            fmt::print("{2}*{3}{1}{0} ", RESET, _s.GetTimeLeft(), TEAL, DARK_GRAY);
        }
        else if (_s.GetType() == WEAKNESS)
        {
            fmt::print("{2}W{3}{1}{0} ", RESET, _s.GetTimeLeft(), BROWN, DARK_GRAY);
        }
    }
    fmt::print("\n");
}

/**
 * \brief Attack between to entities!
 * \note Notice how both <b>attacker</b> and <b>victim</b> are not CONSTANT,<br>
 *       this is because of the <i>Thorns</i> status.
 * \param[in] attacker A reference to an instance of Entity class.<br>
 *                     This is the ATTACKING entity.
 * \param[in] victim A reference to an instance of Entity class.<br>
 *                   This is the entity that is getting ATTACKED.
 * \param[in] dmg The amount of damage the ATTACKING entity is giving.
 * \param[out] msg This is the "What happened:" text, and is of type sting& for the exact reason,<br>
 *                 because we are writing to it.
 * \param[in] enemy_turn Name is self explanatory. Just changes which prompts are written to msg.
 * \param[in] user_settings User game settings.
 */
void EntityAttack(Entity& attacker, Entity& victim, uint32_t dmg, std::string& msg, bool enemy_turn, UserSettingsClass& user_settings)
{
    // if victim has invis
    if (victim.StatusActive(INVIS) && rng(0, 100) > 80)
    {
        if (enemy_turn)
        {
            msg += fmt::format("{4}{1}Enemy{0} {3}tried to attack, but {2}missed{0}{3}!{0}", RESET, BOLD, ITALIC, WHITE, RED);
            return;
        }
        msg += fmt::format("{4}{1}{5}{0} {3}tried to attack, but {2}missed{0}{3}!{0}", RESET, BOLD, ITALIC, WHITE, BLUE, user_settings.GetUsername());
        return;
    }

    uint32_t health_dmg = dmg;
    uint32_t armor_dmg = 0;
    uint32_t thorns_hp_dmg = 0;
    uint32_t thorns_ar_dmg = 0;
    bool crit_flag = false;

    // Check if weakened?
    if (attacker.StatusActive(WEAKNESS))
    {
        health_dmg -= 3;
    }

    // Crit
    if (attacker.StatusActive(INCR_CRIT) && rng(0, 100) > 70)
    {
        health_dmg *= 2;
        crit_flag = true;
    }

    // If victim has thorns...
    if (victim.StatusActive(THORNS))
    {
        thorns_hp_dmg = health_dmg >> 1;
    }

    // If victim has armor, we split health_dmg
    if (victim.GetArmor() > 0)
    {
        uint32_t _temp = health_dmg;
        health_dmg >>= 1;
        armor_dmg = _temp >> 1;
    }

    // If victim has thorns, we split thorns_hp_dmg too
    if (victim.StatusActive(THORNS) && attacker.GetArmor() > 0)
    {
        uint32_t _temp = thorns_hp_dmg;
        thorns_hp_dmg >>= 1;
        thorns_ar_dmg = _temp >> 1;
    }

    // IF armor_dmg takes more armor than the victim has (armor < 0) then do this
    if (((int32_t)armor_dmg) > victim.GetArmor())
    {
        health_dmg += armor_dmg - victim.GetArmor();
        armor_dmg = victim.GetArmor();
    }

    victim.Hurt(health_dmg);
    victim.HurtArmor(armor_dmg);
    if (victim.StatusActive(THORNS))
    {
        attacker.Hurt(thorns_hp_dmg);
        attacker.Hurt(thorns_ar_dmg);
    }

    if (!enemy_turn)
    {
        if (!crit_flag)
        {
            msg += fmt::format("{5}{3}{7}{0} {2}has attacked {4}{3}Enemy{0}{2}! {4}{3}Enemy{0} {6}-{1}HP{0}", RESET, health_dmg, WHITE, BOLD, RED, BLUE, PURPLE, user_settings.GetUsername());
            if (armor_dmg > 0)
            {
                msg += fmt::format(" {2}-{1}AR{0}", RESET, armor_dmg, PURPLE);
            }
            return;
        }
        msg += fmt::format("{5}{3}{9}{0} {2}has attacked {4}{3}Enemy{0}{2}! {8}{7}CRITICAL HIT{0}{2}! {4}{3}Enemy{0} {6}-{1}HP{0}", RESET, health_dmg, WHITE, BOLD, RED, BLUE, PURPLE, ITALIC, GOLD, user_settings.GetUsername());
        if (armor_dmg > 0)
        {
            msg += fmt::format(" {2}-{1}AR{0}", RESET, armor_dmg, PURPLE);
        }
        return;
    }
    else
    {
        if (!crit_flag)
        {
            msg += fmt::format("{4}{3}Enemy{0} {2}has attacked {5}{3}{7}{0}{2}! {5}{3}Player{0} {6}-{1}HP{0}", RESET, health_dmg, WHITE, BOLD, RED, BLUE, PURPLE, user_settings.GetUsername());
            if (armor_dmg > 0)
            {
                msg += fmt::format(" {2}-{1}AR{0}", RESET, armor_dmg, PURPLE);
            }
            return;
            return;
        }
        msg += fmt::format("{4}{3}Enemy{0} {2}has attacked {5}{3}{9}{0}{2}! {8}{7}CRITICAL HIT{0}{2}! {5}{3}Player{0} {6}-{1}HP{0}", RESET, health_dmg, WHITE, BOLD, RED, BLUE, PURPLE, ITALIC, GOLD, user_settings.GetUsername());
        if (armor_dmg > 0)
        {
            msg += fmt::format(" {2}-{1}AR{0}", RESET, armor_dmg, PURPLE);
        }
        return;
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0