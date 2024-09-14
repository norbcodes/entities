// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/*
Exit messages lmfao
*/

#pragma once

#include <cstdint>
#include <string>

const std::string& GetExitMsg();
void AddExitMsg(const std::string& str);
uint32_t GetExitMsgCount();
std::string ExitMsgFormatter(const std::string& str);

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0