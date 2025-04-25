// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file keyboard.cpp (Linux)
 * \author norbcodes
 * \brief Keyboard functions.
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "keyboard.hpp"

/**
 * \brief Waits for a numeric key.
 * \return The numeric key.
 */
uint32_t WaitForNumkey()
{
    // SHAMELESSLY COPIED
    struct termios oldt;
    struct termios newt;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (true)
    {
        char option = getchar();

        if (option >= 48 && option <= 57)
        {
            // Restore the old terminal settings
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return (uint32_t)(option - 48);
        }
    }
}

/**
 * \brief A binary (y/n) choice.
 * \return True if 'y', else False if 'n'
 */
bool BinaryChoice()
{
    // SHAMELESSLY COPIED
    struct termios oldt;
    struct termios newt;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (true)
    {
        char option = getchar();

        if (option == 'y' || option == 'Y')
        {
            // Restore the old terminal settings
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return true;
        }
        else if (option == 'n' || option == 'N')
        {
            // Restore the old terminal settings
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return false;
        }
    }
}

/**
 * \details Stop execution until enter is pressed.
 */
void BlockUntilEnter()
{
    // SHAMELESSLY COPIED
    struct termios oldt;
    struct termios newt;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (true)
    {
        char option = getchar();

        if (option == '\n')
        {
            break;
        }
    }

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

/**
 * \details Get arrow key.
 * \return Arrow key codes, see the macros.
 */
uint32_t GetArrowKey()
{
        // SHAMELESSLY COPIED
    struct termios oldt;
    struct termios newt;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (true)
    {
        if (getchar() == 27)
        {
            getchar();
            switch(getchar())
            {
                case 'A':
                    return UP_KEY;
                case 'B':
                    return DOWN_KEY;
                case 'C':
                    return RIGHT_KEY;
                case 'D':
                    return LEFT_KEY;
            }
        }
    }

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}