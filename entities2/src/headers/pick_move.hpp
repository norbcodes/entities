// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>
#include <string>

#include "entity.hpp"

void PickMove(Entity* ent1, Entity* ent2, uint32_t picked_move, uint32_t* moves, uint32_t* move_types, double* energy_costs, bool enemy_turn, std::string& what_happened);