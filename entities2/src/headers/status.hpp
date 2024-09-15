// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file status.hpp
 * \author norbcodes
 * \brief Status class declaration.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <cstdint>

/**
 * \class Status
 * \brief Status class.
 * \details This class describes a status, and controls it's lifetime.
 */
class Status
{
    public:
        Status(uint8_t type, uint8_t time_left);
        uint8_t GetType() const;
        uint8_t GetTimeLeft() const;
        void Age();
    private:
        /**
         * \var uint8_t type
         * \brief Type of the Status.
         */
        uint8_t type;

        /**
         * \var uint8_t time_left
         * \brief The amount of rounds before this Status expires.
         */
        uint8_t time_left;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0