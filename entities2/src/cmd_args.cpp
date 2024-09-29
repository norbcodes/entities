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
    
    // Parse :)
    entities2.parse_args(argc, argv);
}

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

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0