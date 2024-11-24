// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

#include "cmd_args.hpp"
#include "global_settings.hpp"
#include "user_settings.hpp"
#include "translation_engine.hpp"

void Game(uint32_t mode, bool& picker_flag, const GameArgs& game_args, const GlobalSettingsClass& global_settings, UserSettingsClass& user_settings, uint8_t demo_mode, const TranslationEngine& GameTranslation);
void DemoPlaybackGame(const std::string& demo_path, const TranslationEngine& GameTranslation);

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0