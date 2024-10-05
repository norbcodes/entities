// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file cmd_args.hpp
 * \author norbcodes
 * \brief GameArgs class.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <string>

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
        const std::string& DatapackFolder() const;
        const std::string& GlobalSettings() const;
    
    private:
        /**
         * \var bool v_NoDatapacks
         * \brief Boolean value, as set by the "-nd" (or "--NoDatapacks") cmd argument.
         */
        bool v_NoDatapacks;

        /**
         * \var std::string v_DatapackFolder
         * \brief Where the game searches for .xml datapack files.
         */
        std::string v_DatapackFolder;

        /**
         * \var std::string v_GlobalSettings
         * \brief The path to the global settings json to use.
         */
        std::string v_GlobalSettings;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0