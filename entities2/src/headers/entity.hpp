// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file entity.hpp
 * \author norbcodes
 * \brief Entity class declaration.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "status.hpp"

/**
 * \class Entity
 * \brief The entity class itself.
 * \details The base entity class. Stores entity data, and other stuff.
 */
class Entity
{
    public:
        Entity(int32_t start_health, int32_t start_armor);
        int32_t GetHealth() const;
        int32_t GetArmor() const;
        void Hurt(uint32_t dmg);
        void HurtArmor(uint32_t dmg);
        void Heal(uint32_t val);
        void RegenArmor(uint32_t val);
        bool StatusActive(uint8_t type) const;
        void GiveStatus(uint8_t type);
        uint8_t StatusCount() const;
        Status GetStatusAt(uint8_t i) const;
        void UpdateStatuses(std::string& msg, bool turn);
        double GetEnergy() const;
        void GiveEnergy(double val);
        void TakeEnergy(double val);
    private:
        /**
         * \var int32_t health
         * \brief The Entity's health variable.
         */
        int32_t health;

        /**
         * \var int32_t armor
         * \brief The Entity's armor variable.
         */
        int32_t armor;

        /**
         * \var double energy
         * \brief The Entity's energy variable.
         */
        double energy;

        /**
         * \var std::vector<Status> status_list
         * \brief The Entity's list of statuses.
         */
        std::vector<Status> status_list;
};

void PrintEntityStats(const Entity& ent);
void EntityAttack(Entity& attacker, Entity& victim, uint32_t dmg, std::string& msg, bool enemy_turn);