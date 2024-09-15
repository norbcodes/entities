// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

#define UP_KEY      100
#define DOWN_KEY    101
#define LEFT_KEY    102
#define RIGHT_KEY   103

uint32_t WaitForNumkey();
bool BinaryChoice();
void BlockUntilEnter();
uint32_t GetArrowKey();