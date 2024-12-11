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
        const std::string& UserFolder() const;
        const std::string& DemoFolder() const;
        const std::string& DemoToPlay() const;
        const std::string& LanguageOverride() const;
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

        /**
         * \var std::string v_UserFolder
         * \brief Path to the folder where User saves are saved.
         */
        std::string v_UserFolder;

        /**
         * \var std::string v_DemoFolder
         * \brief Path to the folder where demos are saved.
         */
        std::string v_DemoFolder;

        /**
         * \var std::string v_DemoToPlay
         * \brief Path to a demo to play!
         */
        std::string v_DemoToPlay;

        /**
         * \var std::string v_LanguageOverride
         * \brief Language override for the game.
         */
        std::string v_LanguageOverride;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0