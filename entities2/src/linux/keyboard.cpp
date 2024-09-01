// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

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

void Keyguard() {}