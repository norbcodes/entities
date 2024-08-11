// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

#include "entity.hpp"

double CalcEnergyCost(uint32_t move, uint32_t type);
void PrintEnergyBar(const Entity& entity);