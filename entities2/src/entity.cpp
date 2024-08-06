// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <math.h>

#include "constants.hpp"
#include "colors.hpp"
#include "entity.hpp"
#include "utils.hpp"
#include "rng.hpp"

Entity::Entity(int32_t start_health, int32_t start_armor) : health(start_health), armor(start_armor) 
{
    this->status_list.reserve(64);
}

int32_t Entity::GetHealth() const
{
    return this->health;
}

int32_t Entity::GetArmor() const
{
    return this->armor;
}

void Entity::Hurt(uint32_t dmg)
{
    if ((this->health - dmg) <= 0)
    {
        this->health = 0;
        return;
    }
    this->health -= dmg;
}

void Entity::HurtArmor(uint32_t dmg)
{
    if ((this->armor - dmg) <= 0)
    {
        this->armor = 0;
        return;
    }
    this->armor -= dmg;
}

void Entity::Heal(uint32_t val)
{
    if ((this->health + val) >= MAX_STAT_CAP)
    {
        this->health = MAX_STAT_CAP;
        return;
    }
    this->health += val;
}

void Entity::RegenArmor(uint32_t val)
{
    if ((this->armor + val) >= MAX_STAT_CAP)
    {
        this->armor = MAX_STAT_CAP;
        return;
    }
    this->armor += val;
}

bool Entity::StatusActive(uint8_t type) const
{
    for (int i = 0; i != this->status_list.size(); i++)
    {
        if (this->status_list[i].GetType() == type)
        {
            return true;
        }
    }
    return false;
}

void Entity::GiveStatus(uint8_t type)
{
    this->status_list.emplace_back(type, STATUS_TIME_LEFT);
}

uint8_t Entity::StatusCount() const
{
    return this->status_list.size();
}

Status Entity::GetStatusAt(uint8_t i) const
{
    return this->status_list[i];
}

void Entity::UpdateStatuses(std::string& msg, bool turn)
{
    // Guard
    if (this->status_list.size() == 0)
    {
        return;
    }
    // yay
    for (int i = 0; i < this->status_list.size(); i++)
    {
        this->status_list[i].Age();
        // Only apply AutoHeal, Invis and IncreasedCrit are handled in the Hurt method
        if (this->status_list[i].GetType() == AUTO_HEAL)
        {
            this->Heal(AUTO_HEAL_AMOUNT);
            switch (turn)
            {
                case true:
                    msg += RED(BOLD_IN("Enemy ")) + WHITE("has autohealed! ") + WHITE(BOLD_IN("+" + std::to_string(AUTO_HEAL_AMOUNT) + "HP\n"));
                    break;
                case false:
                    msg += BLUE(BOLD_IN("Player ")) + WHITE("has autohealed! ") + WHITE(BOLD_IN("+" + std::to_string(AUTO_HEAL_AMOUNT) + "HP\n"));
                    break;
            }
        }
        if (this->status_list[i].GetTimeLeft() == 0)
        {
            this->status_list.erase(this->status_list.begin() + i);
        }
    }
}

void PrintEntityStats(const Entity& ent)
{
    std::cout << GREEN(BOLD_IN("HP: ")) << WHITE(std::to_string(ent.GetHealth())) << PINK(BOLD_IN(" AR: ")) << WHITE(std::to_string(ent.GetArmor()));
    std::cout << GOLD(BOLD_IN("\tS: "));
    for (int i = 0; i != ent.StatusCount(); i++)
    {
        Status _s = ent.GetStatusAt(i);
        if (_s.GetType() == AUTO_HEAL)
        {
            std::cout << GREEN("+") << DARK_GRAY(std::to_string((int)_s.GetTimeLeft())) << " ";
        }
        else if (_s.GetType() == INCR_CRIT)
        {
            std::cout << RED("X") << DARK_GRAY(std::to_string((int)_s.GetTimeLeft())) << " ";
        }
        else if (_s.GetType() == INVIS)
        {
            std::cout << WHITE("O") << DARK_GRAY(std::to_string((int)_s.GetTimeLeft())) << " ";
        }
    }
    std::cout << std::endl;
}

void EntityAttack(const Entity& attacker, Entity& victim, uint32_t dmg, std::string& msg, bool enemy_turn)
{
    // if victim has invis
    if (victim.StatusActive(INVIS) && rng(100) > 80)
    {
        if (enemy_turn)
        {
            msg += RED(BOLD_IN("Enemy ")) + WHITE("tried to attack, but ") + WHITE(ITALIC_IN("missed")) + WHITE("!");
        }
        else
        {
            msg += BLUE(BOLD_IN("Player ")) + WHITE("tried to attack, but ") + WHITE(ITALIC_IN("missed")) + WHITE("!");
        }
        return;
    }

    uint32_t health_dmg = dmg;
    uint32_t armor_dmg = 0;
    bool crit_flag = false;
    // Crit
    if (attacker.StatusActive(INCR_CRIT) && rng(100) > 70)
    {
        health_dmg *= 2;
        crit_flag = true;
    }
    // If victim has armor, we split health_dmg
    if (victim.GetArmor() != 0)
    {
        uint8_t _temp = health_dmg;
        health_dmg = (uint32_t)(ceilf(health_dmg / 2));
        armor_dmg = (uint32_t)(floorf(_temp / 2));
    }
    // IF armor_dmg takes more armor than the victim has (armor < 0) then do this
    if (armor_dmg > victim.GetArmor())
    {
        health_dmg += armor_dmg - victim.GetArmor();
        armor_dmg = victim.GetArmor();
    }

    victim.Hurt(health_dmg);
    victim.HurtArmor(armor_dmg);

    if (!enemy_turn)
    {
        if (!crit_flag)
        {
            msg += BLUE(BOLD_IN("Player ")) + WHITE("has attacked ") + RED(BOLD_IN("Enemy")) + WHITE("! ") + RED(BOLD_IN("Enemy ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
            return;
        }
        msg += BLUE(BOLD_IN("Player ")) + WHITE("has attacked ") + RED(BOLD_IN("Enemy")) + WHITE("! ") + GOLD(ITALIC_IN("CRITICAL HIT")) + WHITE("! ") + RED(BOLD_IN("Enemy ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
        return;
    }
    else
    {
        if (!crit_flag)
        {
            msg += RED(BOLD_IN("Enemy ")) + WHITE("has attacked ") + BLUE(BOLD_IN("Player")) + WHITE("! ") + BLUE(BOLD_IN("Player ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
            return;
        }
        msg += RED(BOLD_IN("Enemy ")) + WHITE("has attacked ") + BLUE(BOLD_IN("Player")) + WHITE("! ") + GOLD(ITALIC_IN("CRITICAL HIT")) + WHITE("! ") + BLUE(BOLD_IN("Player ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
        return;
    }
}