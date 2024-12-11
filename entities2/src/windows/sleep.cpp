// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file sleep.cpp (Windows)
 * \author norbcodes
 * \brief Sleep function.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>

#include <windows.h>

/**
 * \brief Does exactly what the title says.
 * \param[in] seconds The amount of seconds to sleep for.
 */
void SleepSeconds(uint32_t seconds)
{
    Sleep(1000 * seconds);
}

/**
 * \brief Does exactly what the title says :)
 * \param[in] miliseconds The amount of miliseconds to sleep for.
 */
void SleepMiliseconds(uint32_t miliseconds)
{
    Sleep(miliseconds);
}