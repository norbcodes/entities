// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

// COLOR MACROS
#define ITALIC(x)           std::string("\x1b[3m") + std::string(x) + std::string("\x1b[0m")
#define BOLD(x)             std::string("\x1b[1m") + std::string(x) + std::string("\x1b[0m")
#define RED(x)              std::string("\x1b[38;2;255;25;25m") + std::string(x) + std::string("\x1b[0m")
#define BLUE(x)             std::string("\x1b[38;2;36;80;255m") + std::string(x) + std::string("\x1b[0m")
#define ORANGE(x)           std::string("\x1b[38;2;230;153;0m") + std::string(x) + std::string("\x1b[0m")
#define WHITE(x)            std::string("\x1b[38;2;230;230;230m") + std::string(x) + std::string("\x1b[0m")
#define HOT_PINK(x)         std::string("\x1b[38;2;153;0;77m") + std::string(x) + std::string("\x1b[0m")
#define GRAY(x)             std::string("\x1b[38;2;99;99;99m") + std::string(x) + std::string("\x1b[0m")
#define DARK_GRAY(x)        std::string("\x1b[38;2;68;68;68m") + std::string(x) + std::string("\x1b[0m")
#define PINK(x)             std::string("\x1b[38;2;234;128;255m") + std::string(x) + std::string("\x1b[0m")
#define GOLD(x)             std::string("\x1b[38;2;255;195;77m") + std::string(x) + std::string("\x1b[0m")
#define GREEN(x)            std::string("\x1b[38;2;0;255;42m") + std::string(x) + std::string("\x1b[0m")
#define PURPLE(x)           std::string("\x1b[38;2;76;0;230m") + std::string(x) + std::string("\x1b[0m")
// INLINES
#define ITALIC_IN(x)        std::string("\x1b[3m") + std::string(x)
#define BOLD_IN(x)          std::string("\x1b[1m") + std::string(x)
#define RED_IN(x)           std::string("\x1b[38;2;255;25;25m") + std::string(x)
#define BLUE_IN(x)          std::string("\x1b[38;2;36;80;255m") + std::string(x)
#define ORANGE_IN(x)        std::string("\x1b[38;2;230;153;0m") + std::string(x)
#define WHITE_IN(x)         std::string("\x1b[38;2;230;230;230m") + std::string(x)
#define HOT_PINK_IN(x)      std::string("\x1b[38;2;153;0;77m") + std::string(x)
#define GRAY_IN(x)          std::string("\x1b[38;2;99;99;99m") + std::string(x)
#define DARK_GRAY_IN(x)     std::string("\x1b[38;2;68;68;68m") + std::string(x)
#define PINK_IN(x)          std::string("\x1b[38;2;234;128;255m") + std::string(x)
#define GOLD_IN(x)          std::string("\x1b[38;2;255;195;77m") + std::string(x)
#define GREEN_IN(x)         std::string("\x1b[38;2;0;255;42m") + std::string(x)
#define PURPLE_IN(x)        std::string("\x1b[38;2;76;0;230m") + std::string(x)