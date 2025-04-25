// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file keyboard.cpp (Windows)
 * \author norbcodes
 * \brief Keyboard functions.
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <windows.h>
#include <conio.h>
#include <iostream>

#include "keyboard.hpp"

/**
 * \brief Waits for a numeric key.
 * \return The numeric key.
 */
uint32_t WaitForNumkey()
{
    // Run in a while loop, and return the key
    while (true)
    {
        char key = _getch();
        if (key >= 48 && key <= 57)
        {
            return static_cast<uint32_t>(key - 48);
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
        char key = _getch();

        if (key == 'y' || key == 'Y')
        {
            return true;
        }

        else if (key == 'n' || key == 'N')
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
        if (_getch() == 13)
        {
            break;
        }
    }
}

/**
 * \details Get arrow key.
 * \return Arrow key codes, see the macros.
 */
uint32_t GetArrowKey()
{
    while (true)
    {
        char first = _getch();
        if (first == 0 || first == -32)
        {
            switch (_getch())
            {
                case 72:
                    return UP_KEY;
                case 80:
                    return DOWN_KEY;
                case 75:
                    return LEFT_KEY;
                case 77:
                    return RIGHT_KEY;
                default:
                    break;
            }
        }
        else
        {
            continue;
        }
    }
}