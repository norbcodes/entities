// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file datapacks.cpp
 * \author norbcodes
 * \brief Datapacks!! :3
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 * \details Datapack reading and loading code.
 */

#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <pugixml.hpp>
#include <vector>
#include <fmt/format.h>
#include <map>
#include <unordered_map>
#include <cmath>

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
    if (!this->Xml.child("Datapack"))
    {
        this->Failbit = true;
        this->FailReason = "menu.datapacks.error1";
        return;
    }

    if (!this->Xml.child("Datapack").child("Meta"))
    {
        this->Failbit = true;
        this->FailReason = "menu.datapacks.error2";
        return;
    }

    if (!this->Xml.child("Datapack").child("Data"))
    {
        this->Failbit = true;
        this->FailReason = "menu.datapacks.error3";
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
        this->FailReason = "menu.datapacks.error4";
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
        this->FailReason = "menu.datapacks.error5";
        return;
    }

    // Check if datapack id
    if (this->Xml.child("Datapack").child("Meta").child("DatapackId"))
    {
        this->DatapackId = this->Xml.child("Datapack").child("Meta").child("DatapackId").text().as_string();
    }
    else
    {
        this->Failbit = true;
        this->FailReason = "menu.datapacks.error6";
        return;
    }
    
    this->Description = this->Xml.child("Datapack").child("Meta").child("Description").text().as_string("No description specified.");

    // Also grab file size
    this->Bytes_Filesize = static_cast<uint32_t>(std::filesystem::file_size(path));
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

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

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
 * \brief Get Datapack Identifier.
 * \return The ID.
 */
const std::string& Datapack::GetDatapackId() const
{
    return (this->DatapackId);
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
 * \brief Get why the Datapack failed.
 * \return String.
 */
const std::string& Datapack::GetFailReason() const
{
    return (this->FailReason);
}

/**
 * \brief Return Datapack file size in bytes.
 * \return The Datapack file size in bytes.
 */
uint32_t Datapack::GetFilesizeInBytes() const
{
    return (this->Bytes_Filesize);
}

/**
 * \brief Return Datapack file size, formatted.
 * \param[in] GameTranslation
 * \return The Datapack file size, formatted.
 */
const std::string Datapack::GetFilesizeFormatted(const TranslationEngine& GameTranslation) const
{
    double size = this->Bytes_Filesize;
    uint16_t divs = 0;
    // In this loop, we will try to convert to a higher unit
    // If the conversion results in a number that is < 1.0
    // Then that's our sign to stop
    while (true)
    {
        if (size / 1000.0 < 1.0)
        {
            break;
        }
        size /= 1000.0;
        divs++;
    }
    // Now, we print.
    switch (divs)
    {
        case 0:
            // We are in bytes.
            return fmt::format("{0} B", size);
        case 1:
            // We are in kilobytes.
            return fmt::format("{0:.2f} KB", size);
        case 2:
            // We are in megabytes.
            return fmt::format("{0:.2f} MB", size);
        default:
            // HOW
            return GameTranslation.GetTranslated("menu.datapacks.veryhuge");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get Datapack contents and load self.
 * \param[in] user_settings User settings.
 * \param[in] GameTranslation Game Translation System.
 */
void Datapack::Load(const UserSettingsClass& user_settings, TranslationEngine& GameTranslation)
{
    // YAAAY now we load :3

    for (pugi::xml_node Node : this->Xml.child("Datapack").child("Data").children())
    {
        // ExitMsg
        if (std::string(Node.name()) == std::string("ExitMsg"))
        {
            // Oki
            // Check if not empty
            if (Node.text().as_string() == std::string(""))
            {
                this->Failbit = true;
                this->FailReason = "menu.datapacks.error10";
                return;
            }
            // Try to get the "formatted" attribute:
            if (Node.attribute("formatted").as_bool())
            {
                // Formatting ON, format string and put into ExitMsg array
                AddExitMsg(MsgFormatter(Node.text().as_string(), user_settings));
            }
            else
            {
                // Same thing, but with no formatting
                if (Node.attribute("local_translation").as_bool())
                {
                    AddExitMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()));
                }
                else
                {
                    AddExitMsg(Node.text().as_string());
                }
            }
        }
        // Greet
        else if (std::string(Node.name()) == std::string("Greet"))
        {
            // Okay
            // Get the time for the greeting
            // Check if not empty
            if (Node.text().as_string() == std::string(""))
            {
                this->Failbit = true;
                this->FailReason = "menu.datapacks.error9";
                return;
            }

            ///////////////////////////////////////////////////////////////////////////////////////////
            // Morning
            ///////////////////////////////////////////////////////////////////////////////////////////
            if (Node.attribute("time").as_string() == std::string("Morning"))
            {
                // Morning time, check formatting
                if (Node.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_MORNING);
                }
                else
                {
                    if (Node.attribute("local_translation").as_bool())
                    {
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_MORNING);
                    }
                    else
                    {
                        AddGreetMsg(Node.text().as_string(), G_MORNING);
                    }
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Afternoon
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Node.attribute("time").as_string() == std::string("Afternoon"))
            {
                // Afternoon time, check formatting
                if (Node.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_AFTERNOON);
                }
                else
                {
                    if (Node.attribute("local_translation").as_bool())
                    {
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_AFTERNOON);
                    }
                    else
                    {
                        AddGreetMsg(Node.text().as_string(), G_AFTERNOON);
                    }
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Evening
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Node.attribute("time").as_string() == std::string("Evening"))
            {
                // Evening time, check formatting
                if (Node.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_EVENING);
                }
                else
                {
                    if (Node.attribute("local_translation").as_bool())
                    {
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_EVENING);
                    }
                    else
                    {
                        AddGreetMsg(Node.text().as_string(), G_EVENING);
                    }
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Early Night
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Node.attribute("time").as_string() == std::string("EarlyNight"))
            {
                // Early Night time, check formatting
                if (Node.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_ENIGHT);
                }
                else
                {
                    if (Node.attribute("local_translation").as_bool())
                    {
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_ENIGHT);
                    }
                    else
                    {
                        AddGreetMsg(Node.text().as_string(), G_ENIGHT);
                    }
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // 3 AM time
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Node.attribute("time").as_string() == std::string("3AM"))
            {
                // 3 AM time, check formatting
                if (Node.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_3AM);
                }
                else
                {
                    if (Node.attribute("local_translation").as_bool())
                    {
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_3AM);
                    }
                    else
                    {
                        AddGreetMsg(Node.text().as_string(), G_3AM);
                    }
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            //All times
            ///////////////////////////////////////////////////////////////////////////////////////////
            else if (Node.attribute("time").as_string() == std::string("All"))
            {
                // 3 AM time, check formatting
                if (Node.attribute("formatted").as_bool())
                {
                    // Formatting ON, format string and put into array
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_MORNING);
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_AFTERNOON);
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_EVENING);
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_ENIGHT);
                    AddGreetMsg(MsgFormatter(Node.text().as_string(), user_settings), G_3AM);
                }
                else
                {
                    if (Node.attribute("local_translation").as_bool())
                    {
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_MORNING);
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_AFTERNOON);
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_EVENING);
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_ENIGHT);
                        AddGreetMsg(fmt::format("{0}.{1}", this->DatapackId, Node.text().as_string()), G_3AM);
                    }
                    else
                    {
                        AddGreetMsg(Node.text().as_string(), G_MORNING);
                        AddGreetMsg(Node.text().as_string(), G_AFTERNOON);
                        AddGreetMsg(Node.text().as_string(), G_EVENING);
                        AddGreetMsg(Node.text().as_string(), G_ENIGHT);
                        AddGreetMsg(Node.text().as_string(), G_3AM);
                    }
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////
            // Else? Error
            ///////////////////////////////////////////////////////////////////////////////////////////
            else
            {
                this->Failbit = true;
                this->FailReason = "menu.datapacks.error8";
                return;
            }
        }
        // Translation
        else if (std::string(Node.name()) == std::string("Translation"))
        {
            // Check if lang attribute exists
            if (Node.attribute("lang").as_string() == std::string(""))
            {
                this->Failbit = true;
                this->FailReason = "menu.datapacks.error7";
                return;
            }

            // Check if id attribute exists
            if (Node.attribute("id").as_string() == std::string(""))
            {
                this->Failbit = true;
                this->FailReason = "menu.datapacks.error7";
                return;
            }

            // Check if node is not empty
            if (Node.text().as_string() == std::string(""))
            {
                this->Failbit = true;
                this->FailReason = "menu.datapacks.error7";
                return;
            }

            // Check if lang attribute is "All"
            if (Node.attribute("lang").as_string() == std::string("All"))
            {
                // This is special because this means this translation string will be
                // the same on all languages
                for (std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator i = GameTranslation.LangIteratorBegin(); i != GameTranslation.LangIteratorEnd(); i++)
                {
                    if (Node.attribute("overwrite").as_bool())
                    {
                        GameTranslation.AddTranslation(
                            i->first,
                            Node.attribute("id").as_string(),
                            Node.text().as_string()
                        );
                    }
                    else
                    {
                        GameTranslation.AddTranslation(
                            i->first,
                            fmt::format("{0}.{1}", this->DatapackId, Node.attribute("id").as_string()),
                            Node.text().as_string()
                        );
                    }
                }
            }
            else
            {
                if (Node.attribute("overwrite").as_bool())
                {
                    // Now add
                    GameTranslation.AddTranslation(
                        Node.attribute("lang").as_string(),
                        Node.attribute("id").as_string(),
                        Node.text().as_string()
                    );
                }
                else
                {
                    // Now add
                    GameTranslation.AddTranslation(
                        Node.attribute("lang").as_string(),
                        fmt::format("{0}.{1}", this->DatapackId, Node.attribute("id").as_string()),
                        Node.text().as_string()
                    );
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
 * \param[in] GameTranslation Game Translation System.
 */
void DatapackEngine::LoadAll(const GameArgs& game_args, const UserSettingsClass& user_settings, TranslationEngine& GameTranslation)
{
    // Check if we can load Datapacks
    if (game_args.NoDatapacks())
    {
        return;
    }
    // Load
    for (uint8_t i = 0; i != this->datapacks.size(); i++)
    {
        this->datapacks[i].Load(user_settings, GameTranslation);
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

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0