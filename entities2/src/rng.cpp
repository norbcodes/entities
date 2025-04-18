// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file rng.cpp
 * \author norbcodes
 * \brief RNG Code.
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 * \details Code that controls the random chaos within entities2.
 */

#include <cstdint>
#include <random>

/**
 * \namespace E2_RNG
 * \brief E2_RNG game namespace.
 * \details Internal game namespace, stores two variables for RNG specific stuff.<br>
 *          Variables inside of this namespace should not be used outside of this file (rng.cpp)<br>
 *          They are static anyway.
 */
namespace E2_RNG
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
}

/**
 * \brief RNG function.
 * \details Returns a random number within <b>a</b> and <b>b</b>.<br>
 *          The underlying generator is Mersenne Twister 19937 (mt19937).
 * \param[in] a The lower bound of the randomly generated number.
 * \param[in] b The upper bound of the randomly generater number.
 * \return A randomly generated number.
 */
uint32_t rng(uint32_t a, uint32_t b)
{
    std::uniform_int_distribution<uint32_t> distribution(a,b);
    return distribution(E2_RNG::generator);
}

/**
 * \brief Seeds the RNG, using a random seed.
 */
void SeedRNG()
{
    E2_RNG::generator.seed(E2_RNG::rd());
}

/**
 * \brief Seeds the RNG, using a custom seed (usually stored inside a demo.)
 * \param[in] seed The seed.
 */
void SeedRNG(uint64_t seed)
{
    E2_RNG::generator.seed(seed);
}

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0