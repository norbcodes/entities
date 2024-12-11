// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file demo_system.cpp
 * \author norbcodes
 * \brief Demo system!
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <ctime>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <fmt/core.h>

#include "colors.hpp"
#include "cmd_args.hpp"
#include "demo_system.hpp"
#include "version.hpp"
#include "utils.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Default constructor.
 * \param[in] move Move.
 * \param[in] from_enemy Simple.
 */
CapturedMove::CapturedMove(uint32_t move, bool from_enemy) : Move(move), FromEnemy(from_enemy) {}

/**
 * \brief Getter for Move variable.
 * \return The move value.
 */
uint32_t CapturedMove::GetMove() const
{
    return (this->Move);
}

/**
 * \brief Getter for FromEnemy variable.
 * \return Boolean.
 */
bool CapturedMove::IsEnemyMove() const
{
    return (this->FromEnemy);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Constructor. Used when demo is being recorded.
 * \param[in] seed RNG seed used for the battle.
 * \param[in] name The recorders' username.
 * \param[in] Diff The game difficulty.
 */
Demo::Demo(uint64_t seed, const std::string& name, uint8_t Diff) : Version(ENTITIES2_DEMO_VER), RngSeed(seed), GameDifficulty(Diff), PlayerName(name) 
{
    this->CapturedMoves.reserve(32); // hmmmm
}

/**
 * \brief The REAL constructor for loading demos.
 * \param[in] path Path to demo file.
 * \param[out] failbit Is set to true when something goes wrong.
 */
void Demo::_constructor(const char* path, bool& failbit)
{
    std::ifstream demo(path, std::ios::binary);
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // Chek magic
    uint32_t magic_num;
    demo.read(reinterpret_cast<char*>(&magic_num), sizeof(magic_num));
    // Uh oh
    if (magic_num != EDEMO_MAGIC_NUM)
    {
        ClearScreen();
        Div();
        fmt::print("{1}Failed to load demo!\nNot a demo...{0}\n", RESET, RED);
        Div();
        failbit = true;
        return;
    }
    // Chek if game versions match
    uint32_t game_ver;
    demo.read(reinterpret_cast<char*>(&game_ver), sizeof(game_ver));
    if (game_ver != ENTITIES2_VER_INT)
    {
        ClearScreen();
        Div();
        fmt::print("{1}Failed to load demo!\nGame versions don't match!{0}\n", RESET, RED);
        Div();
        failbit = true;
        return;
    }
    // Chek if edemo formats match
    uint32_t edemo_ver;
    demo.read(reinterpret_cast<char*>(&edemo_ver), sizeof(edemo_ver));
    if (edemo_ver != ENTITIES2_DEMO_VER)
    {
        ClearScreen();
        Div();
        fmt::print("{1}Failed to load demo!\nDemo formats don't match! Use tool to convert.{0}\n", RESET, RED);
        Div();
        failbit = true;
        return;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // We load
    demo.read(reinterpret_cast<char*>(&(this->RngSeed)), sizeof(this->RngSeed));
    demo.read(reinterpret_cast<char*>(&(this->DemoStart)), sizeof(this->DemoStart));
    demo.read(reinterpret_cast<char*>(&(this->DemoEnd)), sizeof(this->DemoEnd));
    uint32_t moves_to_read;
    demo.read(reinterpret_cast<char*>(&moves_to_read), sizeof(moves_to_read));
    demo.read(reinterpret_cast<char*>(&(this->GameDifficulty)), sizeof(this->GameDifficulty));
    // Ooof, now we read the username
    char current_char = ' ';
    while (current_char != '\x00')
    {
        demo.read(&current_char, 1);
        this->PlayerName += current_char;
    }
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // The best part!!!!!!
    this->CapturedMoves.reserve(moves_to_read);
    for (uint32_t i = 0; i != moves_to_read; i++)
    {
        int8_t coded_move;
        demo.read(reinterpret_cast<char*>(&coded_move), sizeof(coded_move));
        // We know that if coded_move >= 0 then it's a player move
        if (coded_move >= 0)
        {
            this->CapturedMoves.emplace_back(static_cast<uint32_t>(coded_move), false);
        }
        else
        {
            coded_move = abs(coded_move);
            this->CapturedMoves.emplace_back(static_cast<uint32_t>(coded_move), true);
        }
    }
}

/**
 * \brief Constructor for loading demos. (const char* version)
 * \note Calls _constructor function under the hood.
 * \param[in] path Path to demo file.
 * \param[out] failbit Is set to true when something goes wrong.
 */
Demo::Demo(const char* path, bool& failbit)
{
    this->_constructor(path, failbit);
}

/**
 * \brief Constructor for loading demos. (const std::string& version)
 * \note Calls _constructor function under the hood.
 * \param[in] path Path to demo file.
 * \param[out] failbit Is set to true when something goes wrong.
 */
Demo::Demo(const std::string& path, bool& failbit)
{
    this->_constructor(path.c_str(), failbit);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Saves the recording start time.
 */
void Demo::TimeBegin()
{
    std::time_t now = std::time(0);
    this->DemoStart = static_cast<int64_t>(now);
}

/**
 * \brief Saves the recording end time.
 */
void Demo::TimeEnd()
{
    std::time_t now = std::time(0);
    this->DemoEnd = static_cast<int64_t>(now);
}

/**
 * \brief Captures a move.
 * \param[in] move The move value.
 * \param[in] from_enemy Is from enemy?
 */
void Demo::Capture(uint32_t move, bool from_enemy)
{
    this->CapturedMoves.emplace_back(move, from_enemy);
}

/**
 * \brief Save to file!
 * \param[in] path Path to output file.
 * \param[in] game_args CMD arguments.
 */
void Demo::Save(const char* path, const GameArgs& game_args) const
{
    // Yeppp yeep yeeeepp
    // First, create folder if it doesn't already
    struct stat sb;
    if (!stat(game_args.DemoFolder().c_str(), &sb) == 0)
    {
        std::filesystem::create_directory(game_args.DemoFolder());
    }
    // Now the actual thing
    std::ofstream demo(path, std::ios::binary);
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // HEADER
    // temp variables so the magic can happen
    uint32_t edemo_magic_num = EDEMO_MAGIC_NUM;
    uint32_t entities2_ver_int = ENTITIES2_VER_INT;
    uint32_t demo_size = static_cast<uint32_t>(this->CapturedMoves.size());
    // magic num
    demo.write(reinterpret_cast<const char*>(&edemo_magic_num), sizeof(edemo_magic_num));
    // Entities2 version
    demo.write(reinterpret_cast<const char*>(&entities2_ver_int), sizeof(entities2_ver_int));
        // Format version...
    demo.write(reinterpret_cast<const char*>(&(this->Version)), sizeof(this->Version));
    // Rng seed
    demo.write(reinterpret_cast<const char*>(&(this->RngSeed)), sizeof(this->RngSeed));
    // Timestamps
    demo.write(reinterpret_cast<const char*>(&(this->DemoStart)), sizeof(this->DemoStart));
    demo.write(reinterpret_cast<const char*>(&(this->DemoEnd)), sizeof(this->DemoEnd));
    // Demo length
    demo.write(reinterpret_cast<const char*>(&demo_size), sizeof(demo_size));
    // Game difficulty
    demo.write(reinterpret_cast<const char*>(&(this->GameDifficulty)), sizeof(this->GameDifficulty));
    // Username
    demo.write(this->PlayerName.c_str(), this->PlayerName.size() + 1);
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // Now, the actual body of the demo.
    for (uint32_t indx = 0; indx != (this->CapturedMoves.size()); indx++)
    {
        // Okay honestly?
        // Moves can range from 0 to 15 (15 when confirming exit from battle, 14 when changed mind)
        // So we can fit into one nibble of a byte,
        int8_t coded = static_cast<int8_t>(this->CapturedMoves[indx].GetMove());
        
        if (this->CapturedMoves[indx].IsEnemyMove())
        {
            coded = -(coded);
        }

        demo.write(reinterpret_cast<const char*>(&coded), sizeof(coded));
    }
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // Close. Done.
    demo.close();
}

/**
 * \brief Save to file! (calls the previous Save method under the hood.)
 * \param[in] path Path to output file in std::string form.
 * \param[in] game_args CMD arguments.
 */
void Demo::Save(const std::string& path, const GameArgs& game_args) const
{
    // :3
    this->Save(path.c_str(), game_args);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get RNG seed.
 * \return The seed.
 */
uint64_t Demo::GetSeed() const
{
    return (this->RngSeed);
}

/**
 * \brief Get recorders' username.
 * \return The username.
 */
const std::string& Demo::GetUsername() const
{
    return (this->PlayerName);
}

/**
 * \brief Get game difficulty.
 * \return The difficulty.
 */
uint8_t Demo::GetDifficulty() const
{
    return (this->GameDifficulty);
}

/**
 * \brief Get next captured move.
 * \return The move.
 */
uint32_t Demo::GetMove() const
{
    static int32_t _i = -1;
    _i++;
    return (this->CapturedMoves[_i].GetMove());
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Returns back a filename in the format demo_<day>_<month>_<year>.edemo
 * \param[in] game_args CMD arguments.
 * \return Demo name.
 */
std::string MakeDemoName(const GameArgs& game_args)
{
    std::time_t now = std::time(0);
    std::tm* local_time = std::localtime(&now);
    uint32_t num = 0;
    struct stat sb;
    // Loooooop
    while (true)
    {
        std::string file_name = fmt::format("{0}/demo_{1}_{2}_{3}_{4}.edemo", game_args.DemoFolder(), local_time->tm_wday, local_time->tm_mon, local_time->tm_year + 1900, num);
        if (!stat(file_name.c_str(), &sb) == 0)
        {
            return file_name;
        }
        num++;
    }
}

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0