// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>
#include <string>

#include "translation_engine.hpp"

#define G_MORNING           0
#define G_AFTERNOON         1
#define G_EVENING           2
#define G_ENIGHT            3
#define G_3AM               4

const std::string GetGreeting(const TranslationEngine& GameTranslation, bool& Was_Translated);
void AddGreetMsg(const std::string& str, uint32_t where);

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0