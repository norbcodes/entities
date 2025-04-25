// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file sleep.cpp (Linux)
 * \author norbcodes
 * \brief Sleep function.
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>

#include <unistd.h>
#include <ctime>

/**
 * \brief Does exactly what the title says.
 * \param[in] seconds The amount of seconds to sleep for.
 */
void SleepSeconds(uint32_t seconds)
{
    sleep(seconds);
}

/**
 * \brief Does exactly what the title says :3
 * \param[in] miliseconds The amount of miliseconds to sleep for.
 */
void SleepMiliseconds(uint32_t miliseconds)
{
    // Make this
    struct timespec Request;
    struct timespec Remain;
    // Prepare
    Request.tv_sec = 0;
    Request.tv_nsec = miliseconds * 1000;
    // Sleep
    nanosleep(&Request, &Remain);
}