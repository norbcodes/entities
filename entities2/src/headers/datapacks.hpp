// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file datapacks.hpp
 * \author norbcodes
 * \brief Datapack and DatapackEngine classes.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <pugixml.hpp>

#include "cmd_args.hpp"
#include "user_settings.hpp"
#include "translation_engine.hpp"

/**
 * \class Datapack
 * \brief Datapack class.
 * \details Contains datapack metadata, the datapack contents itself, and some helpful methods.
 */
class Datapack
{
    public:
        // Constructors
        Datapack(const char* path);
        Datapack(const std::string& path);
        // Getters
        const std::string& GetName() const;
        const std::string& GetAuthor() const;
        const std::string& GetDatapackId() const;
        const std::string& GetDesc() const;
        const pugi::xml_document& GetXml() const;
        const std::string& GetPath() const;
        bool LoadSuccessful() const;
        const std::string& GetFailReason() const;
        // :3
        void Load(const UserSettingsClass& user_settings, TranslationEngine& GameTranslation);
    private:
        void _constructor(const char* path);  // the actual

        /**
         * \var std::string Name
         * \brief Name of the datapack.
         */
        std::string Name;

        /**
         * \var std::string Author
         * \brief Author of the datapack.
         */
        std::string Author;

        /**
         * \var std::string DatapackId
         * \brief Datapack Identifier.
         */
        std::string DatapackId;

        /**
         * \var std::string Description
         * \brief Description of the datapack.
         */
        std::string Description;

        /**
         * \var pugi::xml_document Xml
         * \brief The XML object of the datapack.
         */
        pugi::xml_document Xml;

        /**
         * \var std::string Path
         * \brief Path to the XML file.
         */
        std::string Path;

        /**
         * \var bool Failbit
         * \brief 'true' if failed to load said datapack.
         */
        bool Failbit;

        /**
         * \var std::string FailReason
         * \brief If Failbit is true, this holds the reason why the Datapack errored.
         */
        std::string FailReason;
};

/**
 * \class DatapackEngine
 * \brief DatapackEngine class.
 * \details Stores all Datapack objects, and acts like a manager for them.
 */
class DatapackEngine
{
    public:
        // Constructor
        DatapackEngine(const GameArgs& game_args);
        // Load ALL datapacks
        void LoadAll(const GameArgs& game_args, const UserSettingsClass& user_settings, TranslationEngine& GameTranslation);
        // Getters
        uint32_t DatapackCount() const;
        const Datapack& GetConstDatapackRef(uint32_t i) const;

    private:
        /**
         * \var std::vector<Datapack> datapacks
         * \brief A dynamic array of Datapack objects.
         */
        std::vector<Datapack> datapacks;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0