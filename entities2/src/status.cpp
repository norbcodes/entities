// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>

#include "status.hpp"

Status::Status(uint8_t type, uint8_t time_left) : type(0), time_left(0) 
{
    this->type = type;
    this->time_left = time_left;
}

uint8_t Status::GetType() const
{
    return this->type;
}

uint8_t Status::GetTimeLeft() const
{
    return this->time_left;
}

void Status::Age()
{
    this->time_left--;
}