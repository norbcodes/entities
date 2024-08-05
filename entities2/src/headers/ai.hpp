// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

#include "entity.hpp"

uint32_t AiChoose(uint8_t* picks_list, uint8_t* types_list, const Entity& player, const Entity& enemy);