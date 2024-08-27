// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>
#define _WIN32_WINNT 0x0500
#include <windows.h>

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