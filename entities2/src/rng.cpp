// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>
#include <random>

uint32_t rng(uint32_t limit)
{
    // SHAMELESSLY COPIED FROM ENTITIES.CPP
    std::random_device rd;
    std::mt19937 gen(rd());
    // Check if limit is zero to avoud doing % 0
    if (limit == 0)
    {
        return 0;
    }
    // I spent like an hour and half hunting this bug down
    return gen() % limit;
}