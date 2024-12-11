// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file demo_system.hpp
 * \author norbcodes
 * \brief Demo and CapturedMove class documentation.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "cmd_args.hpp"

/**
 * \def ENTITIES2_DEMO_VER_MAJOR
 * \brief Demo format major version. (The 'x' in 'x.y.z')
 */
#define ENTITIES2_DEMO_VER_MAJOR 1

/**
 * \def ENTITIES2_DEMO_VER_MINOR
 * \brief Demo format minor version. (The 'y' in 'x.y.z')
 */
#define ENTITIES2_DEMO_VER_MINOR 0

/**
 * \def ENTITIES2_DEMO_VER_PATCH
 * \brief Demo format patch version. (The 'z' in 'x.y.z')
 */
#define ENTITIES2_DEMO_VER_PATCH 0

/**
 * \def ENTITIES2_DEMO_VER
 * \brief Demo format version.
 */
#define ENTITIES2_DEMO_VER       ((ENTITIES2_DEMO_VER_MAJOR * 1000000) + (ENTITIES2_DEMO_VER_MINOR * 1000) + (ENTITIES2_DEMO_VER_PATCH))

// Format specific macros
/**
 * \def EDEMO_MAGIC_NUM
 * \brief Magic number, the first 4 bytes of any .edemo file used for identification.
 */
#define EDEMO_MAGIC_NUM         1296385093

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \class CapturedMove
 * \brief A little class for tracking captured moves.
 */
class CapturedMove
{
    public:
        CapturedMove(uint32_t move, bool from_enemy);
        // Getters
        uint32_t GetMove() const;
        bool IsEnemyMove() const;

    private:
        /**
         * \var uint32_t Move
         * \brief The move.
         */
        uint32_t Move;

        /**
         * \var bool FromEnemy
         * \brief Is from enemy or player?
         */
        bool FromEnemy;
};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \class Demo
 * \brief Demo class!
 * \details Contains Demo stuff. Reading/Writing and all that good stuff.
 */
class Demo
{
    public:
        Demo(uint64_t rng_seed, const std::string& username, uint8_t Diff);       // Default constructor, use when recording
        void _constructor(const char* path, bool& failbit);                       // REAL CONSTRUCTOR
        Demo(const char* path, bool& failbit);                                    // with filepath 1, use for loading
        Demo(const std::string& path, bool& failbit);                             // with filepath 2, use for loading
        // During recording
        void TimeBegin();
        void TimeEnd();
        void Capture(uint32_t move, bool from_enemy);
        void Save(const char* path, const GameArgs& game_args) const;
        void Save(const std::string& path, const GameArgs& game_args) const;
        // During playback
        uint64_t GetSeed() const;
        const std::string& GetUsername() const;
        uint8_t GetDifficulty() const;
        uint32_t GetMove() const;
        //...
    private:
        /**
         * \var uint32_t Version
         * \brief Demo format version.
         */
        uint32_t Version;

        /**
         * \var uint64_t RngSeed
         * \brief RNG seed.
         */
        uint64_t RngSeed;

        /**
         * \var int64_t DemoStart
         * \brief Unix timestamp of when the demo recording started.
         */
        int64_t DemoStart;

        /**
         * \var int64_t DemoEnd
         * \brief Unix timestamp of when the demo recording ended.
         */
        int64_t DemoEnd;

        /**
         * \var uint8_t GameDifficulty
         * \brief Game difficulty.
         */
        uint8_t GameDifficulty;

        /**
         * \var std::string PlayerName
         * \brief Demo recorders' username.
         */
        std::string PlayerName;

        /**
         * \var std::vector<CapturedMove> CapturedMoves
         * \brief Dynamic array of CapturedMove objects.
         */
        std::vector<CapturedMove> CapturedMoves;
};

std::string MakeDemoName(const GameArgs& game_args);

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0