// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/*
Exit messages lmfao
*/

#pragma once

#include <cstdint>
#include <string>

#include "translation_engine.hpp"

const std::string GetExitMsg(const TranslationEngine& GameTranslation, bool& Was_Translated);
void AddExitMsg(const std::string& str);
uint32_t GetExitMsgCount();

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0