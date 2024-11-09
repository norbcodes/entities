// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file datapacks.cpp
 * \author norbcodes
 * \brief Datapacks!! :3
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \details Datapack reading and loading code.
 */

#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <pugixml.hpp>
#include <vector>
#include <fmt/format.h>

#include "exit_msg.hpp"
#include "datapacks.hpp"
#include "cmd_args.hpp"
#include "game_string_formatter.hpp"
#include "greetings.hpp"
#include "user_settings.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

// Datapack methods

/**
 * \brief The ACTUAL constructor for Datapack class.
 * \param[in] path Path to the .xml file, in <b>const char*</b> form.
 */
void Datapack::_constructor(const char* path)
{
    // IN CONSTRUCTOR, ONLY READ "META" SECTION.
    this->Xml.load_file(path);
    
    // Read
    // Check if Datapack and Meta and Data
    if (!this->Xml.child("Datapack") || !this->Xml.child("Datapack").child("Meta") || !this->Xml.child("Datapack").child("Data"))
    {
        this->Failbit = true;
        return;
    }

    // Check if Name
    if (this->Xml.child("Datapack").child("Meta").child("Name"))
    {
        this->Name = this->Xml.child("Datapack").child("Meta").child("Name").text().as_string();
    }
    else
    {
        this->Failbit = true;
        return;
    }
    
    // Check if Author
    if (this->Xml.child("Datapack").child("Meta").child("Author"))
    {
        this->Author = this->Xml.child("Datapack").child("Meta").child("Author").text().as_string();
    }
    else
    {
        this->Failbit = true;
        return;
    }
    
    this->Description = this->Xml.child("Datapack").child("Meta").child("Description").text().as_string("No description specified.");
}

/**
 * \brief Constructor for Datapack class.
 * \param[in] path Path to the .xml file, in <b>const char*</b> form.
 */
Datapack::Datapack(const char* path) : Path(path), Failbit(false)
{
    this->_constructor(path);
}

/**
 * \brief Constructor for Datapack class.
 * \param[in] path Path to the .xml file, in <b>const std::string&</b> form.
 */
Datapack::Datapack(const std::string& path) : Path(path), Failbit(false)
{
    this->_constructor(path.c_str());
}

/**
 * \brief Get Datapack Name.
 * \return The name.
 */
const std::string& Datapack::GetName() const
{
    return (this->Name);
}

/**
 * \brief Get Datapack Author.
 * \return The author.
 */
const std::string& Datapack::GetAuthor() const
{
    return (this->Author);
}

/**
 * \brief Get Datapack Description.
 * \return The description.
 */
const std::string& Datapack::GetDesc() const
{
    return (this->Description);
}

/**
 * \brief Get Datapack XML object.
 * \return The pugi::xml_document object.
 */
const pugi::xml_document& Datapack::GetXml() const
{
    return this->Xml;
}

/**
 * \brief Get path of the loaded .xml file.
 * \return The path.
 */
const std::string& Datapack::GetPath() const
{
    return (this->Path);
}

/**
 * \brief Check if the datapack has loaded properly.
 * \return Boolean.
 */
bool Datapack::LoadSuccessful() const
{
    return !(this->Failbit);
}

/**
 * \brief Get Datapack contents and load self.
 * \param[in] user_settings User settings.
 */
void Datapack::Load(const UserSettingsClass& user_settings)
{
    // YAAAY now we load :3

    for (pugi::xml_node Data : this->Xml.child("Datapack").child("Data").children())
    {
        // ExitMsg
        if (std::string(Data.name()) == std::string("ExitMsg"))
        {
            // Oki
            // Try to get the "formatted" attribute:
            if (Data.attribute("formatted").as_bool())
            {
                // Formatting ON, format string and put into ExitMsg array
                AddExitMsg(MsgFormatter(Data.text().as_string(), user_settings));
            }
            else
            {
                // Same thing, but with no formatting
                AddExitMsg(Data.text().as_string());
            }
        }
        // Greet
        else if (std::string(Data.name()) == std::string("Greet"))
        {
            // Okay
            // Get the time for the greeting
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Morning
            ///////////////////////////////////////////////////////////////////////////////////////////
            if (Data.attribute("time").as_string() == std::string("Morning"))
            {
                // Morning time, check formatting
                if (Data.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Data.text().as_string(), user_settings), G_MORNING);
                }
                else
                {
                    AddGreetMsg(Data.text().as_string(), G_MORNING);
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Afternoon
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Data.attribute("time").as_string() == std::string("Afternoon"))
            {
                // Afternoon time, check formatting
                if (Data.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Data.text().as_string(), user_settings), G_AFTERNOON);
                }
                else
                {
                    AddGreetMsg(Data.text().as_string(), G_AFTERNOON);
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Evening
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Data.attribute("time").as_string() == std::string("Evening"))
            {
                // Evening time, check formatting
                if (Data.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Data.text().as_string(), user_settings), G_EVENING);
                }
                else
                {
                    AddGreetMsg(Data.text().as_string(), G_EVENING);
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Early Night
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Data.attribute("time").as_string() == std::string("EarlyNight"))
            {
                // Early Night time, check formatting
                if (Data.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Data.text().as_string(), user_settings), G_ENIGHT);
                }
                else
                {
                    AddGreetMsg(Data.text().as_string(), G_ENIGHT);
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // 3 AM time
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Data.attribute("time").as_string() == std::string("3AM"))
            {
                // 3 AM time, check formatting
                if (Data.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Data.text().as_string(), user_settings), G_3AM);
                }
                else
                {
                    AddGreetMsg(Data.text().as_string(), G_3AM);
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

// DatapackEngine methods

/**
 * \brief DatapackEngine constructor.
 * \details Creates a folder for Datapacks ("./datapacks/", or if specified with -df option),<br>
 *          also creates a readme.txt If folder exists, then it reads all datapacks, and<br>
 *          prepares them for loading stage.
 * \param[in] game_args Game CMD arguments.
 */
DatapackEngine::DatapackEngine(const GameArgs& game_args)
{
    // Can load
    if (game_args.NoDatapacks())
    {
        return;
    }
    // Check if "datapacks" folder exists
    struct stat sb;
    if (!stat(game_args.DatapackFolder().c_str(), &sb) == 0)
    {
        std::filesystem::create_directory(game_args.DatapackFolder());
        // Write a lil readme.txt :)
        std::ofstream readme(fmt::format("{0}readme.txt", game_args.DatapackFolder()));
        readme << "Hello!!!\nHere, you can put your .xml datapacks for entities2!\nYou may also create subfolders to organize your files.";
        readme.close();
        return;
        // Since we just created the folder, there's obviously not gonna be any XML files yet.
    }
    else
    {
        // Folder DOES exist
        // Now we can actually scan the folder and find datapacks

        // First, reserve our little vector :3
        this->datapacks.reserve(32);

        for (const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator(game_args.DatapackFolder()))
        {
            // We don't need symlinks support lol
            // This iterates through all stuff in the folder.
            // Check if file:
            if (file.is_regular_file())
            {
                // Check extention
                if (file.path().extension() == ".xml")
                {
                    // :3
                    this->datapacks.emplace_back(file.path().string());
                }
            }
        }
    }
}

/**
 * \brief Load all Datapacks :)
 * \param[in] game_args Game CMD arguments.
 * \param[in] user_settings User game settings.
 */
void DatapackEngine::LoadAll(const GameArgs& game_args, const UserSettingsClass& user_settings)
{
    // Check if we can load Datapacks
    if (game_args.NoDatapacks())
    {
        return;
    }
    // Load
    for (uint8_t i = 0; i != this->datapacks.size(); i++)
    {
        this->datapacks[i].Load(user_settings);
    }
}

/**
 * \brief Get the amount of Datapacks.
 * \return The amount of Datapacks.
 */
uint32_t DatapackEngine::DatapackCount() const
{
    return this->datapacks.size();
}

/**
 * \brief Return a constant reference to a Datapack instance.
 * \param[in] i Index in the Datapack array.
 * \return Constant reference to a Datapack instance.
 */
const Datapack& DatapackEngine::GetConstDatapackRef(uint32_t i) const
{
    return this->datapacks[i];
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0