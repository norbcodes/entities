// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file keyboard.cpp (Windows)
 * \author norbcodes
 * \brief Keyboard functions.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <windows.h>
#include <conio.h>

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
        char key = getch();
        if (key >= 48 && key <= 57)
        {
            return (uint32_t)(key - 48);
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
        char key = getch();

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
        if (getch() == 13)
        {
            break;
        }
    }
}

/**
 * \details Get arrow key.
 */
uint32_t GetArrowKey()
{
    while (true)
    {
        char first = getch();
        if (!(first == 0 || first == 224))
        {
            continue;
        }
        switch (getch())
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
}