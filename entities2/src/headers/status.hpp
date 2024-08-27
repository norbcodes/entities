// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

#include <cstdint>

class Status
{
    public:
        Status(uint8_t type, uint8_t time_left);
        uint8_t GetType() const;
        uint8_t GetTimeLeft() const;
        void Age();
    private:
        uint8_t type;
        uint8_t time_left;
};