// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file cmd_args.cpp
 * \author norbcodes
 * \brief Parsing command line arguments >:)
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <string>
#include <argparse/argparse.hpp>

#include "cmd_args.hpp"

/**
 * \brief Constructor.
 * \param[in] argc Number of CMD arguments.
 * \param[in] argv The arguments.
 */
GameArgs::GameArgs(int argc, char* argv[]) : v_NoDatapacks(false)
{
    // Create argparser
    argparse::ArgumentParser entities2("entities2");
    entities2.add_description("entities2 is a small silly turn based combat CLI game.");

    // Create arguments
    entities2.add_argument("-nd", "--NoDatapacks")
        .help("Disable loading of Datapacks.")
        .flag()
        .store_into(this->v_NoDatapacks);
    
    entities2.add_argument("-df", "--DatapackFolder")
        .help("Where the game searches for .xml datapack files.\n(Relative paths start from the folder where the .exe is.)")
        #ifdef _WIN32
        .default_value(".\\datapacks\\")
        #else
        .default_value("./datapacks/")
        #endif
        .store_into(this->v_DatapackFolder);
    
    entities2.add_argument("-gs", "--GlobalSettings")
        .help("Path to the global settings json file for the game to use.")
        #ifdef _WIN32
        .default_value(".\\global.json")
        #else
        .default_value("./global.json")
        #endif
        .store_into(this->v_GlobalSettings);
    
    entities2.add_argument("-uf", "--UserFolder")
        .help("Path to the folder where User saves are saved.")
        #ifdef _WIN32
        .default_value(".\\users\\")
        #else
        .default_value("./users/")
        #endif
        .store_into(this->v_UserFolder);
    
    entities2.add_argument("-df", "--DemoFolder")
        .help("Path to the folder where demos are saved.")
        #ifdef _WIN32
        .default_value(".\\demos\\")
        #else
        .default_value("./demos/")
        #endif
        .store_into(this->v_DemoFolder);

    entities2.add_argument("-pd", "--PlayDemo")
        .help("Play demo!")
        .default_value("")
        .store_into(this->v_DemoToPlay);
    
    entities2.add_argument("-lo", "--LanguageOverride")
        .help("Ignore saved language in global.json, and load this language instead.\n(Note: use language id, like \"EN-US\")")
        .default_value("")
        .store_into(this->v_LanguageOverride);
    
    // Parse :)
    entities2.parse_args(argc, argv);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * \brief Getter for v_NoDatapacks variable.
 * \return Boolean.
 */
bool GameArgs::NoDatapacks() const
{
    return (this->v_NoDatapacks);
}

/**
 * \brief Getter for v_DatapackFolder variable.
 * \return String, the path to the Datapack folder.
 */
const std::string& GameArgs::DatapackFolder() const
{
    return (this->v_DatapackFolder);
}

/**
 * \brief Getter for v_GlobalSettings variable.
 * \return String, the path to the global settings json file.
 */
const std::string& GameArgs::GlobalSettings() const
{
    return (this->v_GlobalSettings);
}

/**
 * \brief Getter for v_UserFolder variable.
 * \return String, path to the folder where User saves are saved.
 */
const std::string& GameArgs::UserFolder() const
{
    return (this->v_UserFolder);
}

/**
 * \brief Getter for v_DemoFolder variable.
 * \return String, path to the folder where demos are saved.
 */
const std::string& GameArgs::DemoFolder() const
{
    return (this->v_DemoFolder);
}

/**
 * \brief Getter for v_DemoToPlay variable.
 * \return String, path to a demo to play!
 */
const std::string& GameArgs::DemoToPlay() const
{
    return (this->v_DemoToPlay);
}

/**
 * \brief Getter for v_LanguageOverride variable.
 * \return Language override.
 */
const std::string& GameArgs::LanguageOverride() const
{
    return (this->v_LanguageOverride);
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0