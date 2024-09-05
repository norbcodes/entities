// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file sleep.cpp (Linux)
 * \author norbcodes
 * \brief Sleep function.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>

#include <unistd.h>

/**
 * \brief Does exactly what the title says.
 * \param[in] seconds The amount of seconds to sleep for.
 */
void SleepSeconds(uint32_t seconds)
{
    sleep(seconds);
}