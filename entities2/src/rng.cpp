// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>
#include <random>

namespace EntitiesRNG
{
    std::random_device rd;
    std::mt19937 generator(rd());
}

uint32_t rng(uint32_t a, uint32_t b)
{
    std::uniform_int_distribution<uint32_t> distribution(a,b);
    return distribution(EntitiesRNG::generator);
}