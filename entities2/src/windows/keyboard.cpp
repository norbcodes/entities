// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file keyboard.cpp (Windows)
 * \author norbcodes
 * \brief Keyboard functions.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>

/**
 * \def _WIN32_WINNT
 * \brief Required for windows.h
 */
#define _WIN32_WINNT 0x0500

#include <windows.h>

/**
 * \brief Waits for a numeric key.
 * \return The numeric key.
 */
uint32_t WaitForNumkey()
{
    // Run in a while loop, and return the key
    while (true)
    {
        for (int i = 0x30; i != 0x3A; i++)
        {
            if (GetKeyState(i) & 0x8000)
            {
                return i - 0x30;
            }
        }
        for (int i = 0x60; i != 0x6A; i++)
        {
            if (GetKeyState(i) & 0x8000)
            {
                return i - 0x60;
            }
        }
    }
}

/**
 * \brief A binary (y/n) choice.
 * \return True if 'y', else False if 'n'
 */
bool BinaryChoice()
{
    // either y or n.
    while (true)
    {
        if (GetKeyState(0x59) & 0x8000)
        {
            return true;
        }
        else if (GetKeyState(0x4E) & 0x8000)
        {
            return false;
        }
    }
}

/**
 * \details Stop execution until enter is pressed.
 */
void BlockUntilEnter()
{
    while (true)
    {
        if (GetKeyState(VK_RETURN) & 0x8000)
        {
            break;
        }
    }
}

/**
 * \details Stop execution if any key on the keyboard is held down.
 */
void Keyguard()
{
    // Loop forever until no keys are pressed
    bool _wait = true;
    while (_wait)
    {
        _wait = false;
        for (int i = 0; i != 256; i++)
        {
            if (GetAsyncKeyState(i) & 0x8000)
            {
                _wait = true;
            }
        }
    }
}