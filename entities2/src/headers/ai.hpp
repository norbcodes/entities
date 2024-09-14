// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

#include "entity.hpp"

uint32_t AiChoose(uint32_t* picks_list, uint32_t* types_list, double* energies, const Entity& player, const Entity& enemy, uint32_t difficulty_scale);

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0