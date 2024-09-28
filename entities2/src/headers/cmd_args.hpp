// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file cmd_args.hpp
 * \author norbcodes
 * \brief GameArgs class.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

/**
 * \class GameArgs
 * \brief GameArgs class.
 * \details Contains variables that store values of each command line argument, and getters to access them.
 */
class GameArgs
{
    public:
        // Constructor
        GameArgs(int argc, char* argv[]);
        // Getters
        bool NoDatapacks() const;
    
    private:
        /**
         * \var bool v_NoDatapacks
         * \brief Boolean value, as set by the "-nd" (or "--NoDatapacks") cmd argument.
         */
        bool v_NoDatapacks;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0