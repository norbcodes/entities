// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file translation_engine.hpp
 * \author norbcodes
 * \brief TranslationEngine class.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include "global_settings.hpp"

/**
 * \class TranslationEngine
 * \brief TranslationEngine class.
 * \details Contains the language registry and functions for localization within Entities2.
 */
class TranslationEngine
{
    public:
        // Constructor and stuff
        TranslationEngine();
        void LoadEnglish(); // IS ALWAYS CALLED!
        // Setters + Adders
        void SetLang(const std::string& id, GlobalSettingsClass& global_settings);
        void AddTranslation(const std::string& lang_id, const std::string& trans_id, const std::string& str);
        // Getters
        const std::string& GetCurrentLangId() const;
        const std::string& GetTranslated(const std::string& str) const;
        const std::string& GetTranslated(const std::string& str, const std::string& lang_id) const;
        bool TranslationStringExists(const std::string& what) const;
        bool LangIdExists(const std::string& what) const;
        std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator LangIteratorBegin() const;
        std::map<std::string, std::unordered_map<std::string, std::string>>::const_iterator LangIteratorEnd() const;
        std::unordered_map<std::string, std::string>::const_iterator TranslationIteratorBegin(const std::string& id) const;
        std::unordered_map<std::string, std::string>::const_iterator TranslationIteratorEnd(const std::string& id) const;
    private:
        /**
         * \var std::string CurrentLangId
         * \brief Currently selected language.
         */
        std::string CurrentLangId;

        /**
         * \var GameTranslationRegister Register
         * \brief Holds all the translations in a format of: *language_id* -> *translation_id* -> *string*
         */
        std::map<std::string, std::unordered_map<std::string, std::string>> Register;
};

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0