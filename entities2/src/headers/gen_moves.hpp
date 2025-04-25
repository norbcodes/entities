// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

#include "translation_engine.hpp"

bool MoveExists(uint32_t* moves, uint32_t* move_types, uint32_t val, uint32_t type);
void GenerateMoves(uint32_t* moves, uint32_t* move_types, double* energies, const TranslationEngine& GameTranslation);

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0