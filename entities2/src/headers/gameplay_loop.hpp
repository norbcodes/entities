// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

#include "cmd_args.hpp"
#include "global_settings.hpp"
#include "user_settings.hpp"
#include "translation_engine.hpp"

void Game(uint32_t mode, bool& picker_flag, const GlobalSettingsClass& global_settings, UserSettingsClass& user_settings, const TranslationEngine& GameTranslation);

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0