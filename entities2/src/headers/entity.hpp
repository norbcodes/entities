// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "status.hpp"

class Entity
{
    private:
        int32_t health;
        int32_t armor;
        double energy;
        std::vector<Status> status_list;
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
};

void PrintEntityStats(const Entity& ent);
void EntityAttack(Entity& attacker, Entity& victim, uint32_t dmg, std::string& msg, bool enemy_turn);