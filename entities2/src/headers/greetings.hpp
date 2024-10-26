// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>
#include <string>

#include "user_settings.hpp"

#define G_MORNING           0
#define G_AFTERNOON         1
#define G_EVENING           2
#define G_ENIGHT            3
#define G_3AM               4

void InitializeGreets(const UserSettingsClass& user_settings);
const std::string GetGreeting();
void AddGreetMsg(const std::string& str, uint32_t where);

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0