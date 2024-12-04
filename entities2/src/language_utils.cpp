// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file language_utils.cpp
 * \author norbcodes
 * \brief Utilities for all things about localization.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <string>
#include <pugixml.hpp>
#include <fmt/core.h>
#include <map>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <regex>

#include "cmd_args.hpp"
#include "colors.hpp"
#include "user_settings.hpp"
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"
#include "language_picker.hpp"
#include "keyboard.hpp"
#include "utils.hpp"

static void ExportLanguageAsDatapack(const std::string& id, const TranslationEngine& GameTranslation, const GameArgs& GameArguments, const UserSettingsClass& UserSettings)
{
    // Create document
    pugi::xml_document ExportedDatapack;
    pugi::xml_node Declaration = ExportedDatapack.prepend_child(pugi::node_declaration);
    Declaration.append_attribute("version").set_value("1.0");
    Declaration.append_attribute("encoding").set_value("UTF-8");
    // Assign the default values
    pugi::xml_node DatapackNode = ExportedDatapack.append_child("Datapack");
    // Meta node
    pugi::xml_node MetaNode = DatapackNode.append_child("Meta");
    pugi::xml_node NameNode = MetaNode.append_child("Name");
    pugi::xml_node AuthorNode = MetaNode.append_child("Author");
    pugi::xml_node DescNode = MetaNode.append_child("Description");
    pugi::xml_node IdNode = MetaNode.append_child("DatapackId");
    NameNode.text().set(id.c_str());
    AuthorNode.text().set(UserSettings.GetUsername().c_str());
    DescNode.text().set("");
    IdNode.text().set( fmt::format("{0}.{1}", UserSettings.GetUsername(), id).c_str() );
    // Data node
    pugi::xml_node DataNode = DatapackNode.append_child("Data");

    // Now we do the cool thing
    for (std::unordered_map<std::string, std::string>::const_iterator i = GameTranslation.TranslationIteratorBegin(id); i != GameTranslation.TranslationIteratorEnd(id); i++)
    {
        // Kill me
        pugi::xml_node TransNode = DataNode.append_child("Translation");
        TransNode.append_attribute("lang").set_value(id.c_str());
        TransNode.append_attribute("id").set_value((i->first).c_str());
        TransNode.append_attribute("overwrite").set_value(true);
        TransNode.text().set((i->second).c_str());
    }

    // Save file
    std::string filename = fmt::format("{0}Exported-{1}.xml", GameArguments.DatapackFolder(), id);
    if (ExportedDatapack.save_file(filename.c_str()))
    {
        ClearScreen();
        Div();
        fmt::print("{1}{2}{0}\n", RESET, WHITE, CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.langutils.success"), fmt::arg("lang_id", id)));
        fmt::print("{1}{2}{0}\n", RESET, WHITE, filename);
        EndDiv();
        BlockUntilEnter();
    }
    else
    {
        ClearScreen();
        Div();
        fmt::print("{1}{2}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.langutils.fail"));
        EndDiv();
        BlockUntilEnter();
    }
}

static void ExportLanguageToTXT(const std::string& id, const TranslationEngine& GameTranslation, const GameArgs& GameArguments)
{
    std::string filename = fmt::format("{0}Exported-{1}.txt", GameArguments.DatapackFolder(), id);
    std::ofstream ExportedTxt(filename);
    // Now do the same iteration
    // For safety and visual beautifulness (is that even a word)
    uint32_t longest_translation_key = 0;
    std::vector<std::string> trans_keys;
    trans_keys.reserve(128);
    // First iteration
    for (std::unordered_map<std::string, std::string>::const_iterator i = GameTranslation.TranslationIteratorBegin(id); i != GameTranslation.TranslationIteratorEnd(id); i++)
    {
        trans_keys.emplace_back(i->first);
        uint32_t length = (i->first).length();
        if (length > longest_translation_key)
        {
            longest_translation_key = length;
        }
    }
    std::sort(trans_keys.begin(), trans_keys.end());
    // Yes it's really that necessary
    // Second iteration
    for (std::vector<std::string>::const_iterator i = trans_keys.cbegin(); i != trans_keys.cend(); i++)
    {
        // End me
        ExportedTxt << fmt::format("{0: <{2}} = {1}\n", i->c_str(), GameTranslation.GetTranslated(i->c_str(), id), longest_translation_key + 8);
    }
    ExportedTxt.close();
    if (!ExportedTxt.fail())
    {
        ClearScreen();
        Div();
        fmt::print("{1}{2}{0}\n", RESET, WHITE, CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.langutils.success"), fmt::arg("lang_id", id)));
        fmt::print("{1}{2}{0}\n", RESET, WHITE, filename);
        EndDiv();
        BlockUntilEnter();
    }
    else
    {
        ClearScreen();
        Div();
        fmt::print("{1}{2}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.langutils.fail"));
        EndDiv();
        BlockUntilEnter();
    }
}

static void ConvertTxtToXml(const TranslationEngine& GameTranslation, const GameArgs& GameArguments, const UserSettingsClass& UserSettings)
{
    ClearScreen();
    Div();
    // Get
    std::filesystem::path path_to_txt = "";
    fmt::print("{1}{2}{0}\n\n", RESET, WHITE, GameTranslation.GetTranslated("menu.langutils.getpath"));
    EndDivNoNewl();
    std::cin >> path_to_txt;
    // Check if correct
    if (std::filesystem::exists(path_to_txt))
    {
        if (std::filesystem::is_regular_file(path_to_txt))
        {
            // Open the file
            std::ifstream txt(path_to_txt);
            // Yay we can load now
            std::string line;
            std::regex search_re("([\\w\\.]+)[\\s]*=[\\s]*(.+)", std::regex_constants::optimize);
            std::vector<std::string> trans_keys;
            std::vector<std::string> trans_strings;
            trans_keys.reserve(128);
            trans_strings.reserve(128);
            // Read line and loop
            while (std::getline(txt, line, '\n'))
            {
                // Fuck it i'm using regex
                std::smatch match;
                // Find
                if (std::regex_search(line, match, search_re))
                {
                    trans_keys.emplace_back(match.str(1));
                    trans_strings.emplace_back(match.str(2));
                }
            }
            // Get lang id
            std::string lang_id = "unknown";
            for (uint32_t i = 0; i != trans_keys.size(); i++)
            {
                if (trans_keys[i] == "lang.id")
                {
                    lang_id = trans_strings[i];
                }
            }
            // Copied from the other function
            // Create document
            pugi::xml_document ExportedDatapack;
            pugi::xml_node Declaration = ExportedDatapack.prepend_child(pugi::node_declaration);
            Declaration.append_attribute("version").set_value("1.0");
            Declaration.append_attribute("encoding").set_value("UTF-8");
            // Assign the default values
            pugi::xml_node DatapackNode = ExportedDatapack.append_child("Datapack");
            // Meta node
            pugi::xml_node MetaNode = DatapackNode.append_child("Meta");
            pugi::xml_node NameNode = MetaNode.append_child("Name");
            pugi::xml_node AuthorNode = MetaNode.append_child("Author");
            pugi::xml_node DescNode = MetaNode.append_child("Description");
            pugi::xml_node IdNode = MetaNode.append_child("DatapackId");
            NameNode.text().set(lang_id.c_str());
            AuthorNode.text().set(UserSettings.GetUsername().c_str());
            DescNode.text().set("");
            IdNode.text().set( fmt::format("{0}.{1}", UserSettings.GetUsername(), lang_id).c_str() );
            // Data node
            pugi::xml_node DataNode = DatapackNode.append_child("Data");
            // Yeah
            // Now we do the cool thing
            for (uint32_t i = 0; i != trans_keys.size(); i++)
            {
                // Kill me
                pugi::xml_node TransNode = DataNode.append_child("Translation");
                TransNode.append_attribute("lang").set_value(lang_id.c_str());
                TransNode.append_attribute("id").set_value((trans_keys[i]).c_str());
                TransNode.append_attribute("overwrite").set_value(true);
                TransNode.text().set((trans_strings[i]).c_str());
            }
            // Save file
            std::string filename = fmt::format("{0}Exported-{1}.xml", GameArguments.DatapackFolder(), lang_id);
            if (ExportedDatapack.save_file(filename.c_str()))
            {
                ClearScreen();
                Div();
                fmt::print("{1}{2}{0}\n", RESET, WHITE, CustomMsgFormatterNoUser(GameTranslation.GetTranslated("menu.langutils.success"), fmt::arg("lang_id", lang_id)));
                fmt::print("{1}{2}{0}\n", RESET, WHITE, filename);
                EndDiv();
                BlockUntilEnter();
                return;
            }
            else
            {
                ClearScreen();
                Div();
                fmt::print("{1}{2}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.langutils.fail"));
                EndDiv();
                BlockUntilEnter();
                return;
            }
        }
        else
        {
            ClearScreen();
            Div();
            fmt::print("{1}{2}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.langutils.notfile"));
            EndDiv();
            BlockUntilEnter();
            return;
        }
    }
    else
    {
        ClearScreen();
        Div();
        fmt::print("{1}{2}{0}\n", RESET, RED, GameTranslation.GetTranslated("menu.langutils.pathfail"));
        EndDiv();
        BlockUntilEnter();
        return;
    }
}

/**
 * \brief Menu displaying language tools.
 * \param[in] GameTranslation We are working with languages, so this is needed.
 * \param[in] GameArguments For knowing where to put files and such.
 * \param[in] UserSettings for User settings :>
 */
void LanguageUtilitiesMenu(const TranslationEngine& GameTranslation, const GameArgs& GameArguments, const UserSettingsClass& UserSettings)
{
    bool in_menu = true;
    while (in_menu)
    {
        ClearScreen();
        Div();
        fmt::print("{1}{2}{0}\n\n", RESET, PINK, GameTranslation.GetTranslated("menu.options.langutils"));
        fmt::print("{1}[{2}{3}1{0}{1}]{0} {4}{5}{0}\n", RESET, DARK_GRAY, GOLD, BOLD, BLUE, GameTranslation.GetTranslated("menu.options.export1"));
        fmt::print("{1}[{2}{3}2{0}{1}]{0} {4}{5}{0}\n", RESET, DARK_GRAY, GOLD, BOLD, GREEN, GameTranslation.GetTranslated("menu.options.export2"));
        fmt::print("{1}[{2}{3}3{0}{1}]{0} {4}{5}{0}\n\n", RESET, DARK_GRAY, GOLD, BOLD, BROWN, GameTranslation.GetTranslated("menu.options.export3"));
        fmt::print("{1}[{2}{3}4{0}{1}]{0} {4}{5}{0}\n", RESET, DARK_GRAY, GOLD, BOLD, RED, GameTranslation.GetTranslated("general.exit"));
        EndDiv();

        switch (WaitForNumkey())
        {
            case 1:
                ExportLanguageAsDatapack(PickLanguage(GameTranslation), GameTranslation, GameArguments, UserSettings);
                break;
            case 2:
                ExportLanguageToTXT(PickLanguage(GameTranslation), GameTranslation, GameArguments);
                break;
            case 3:
                ConvertTxtToXml(GameTranslation, GameArguments, UserSettings);
                break;
            case 4:
                in_menu = false;
                break;
            default:
                break;
        }
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0