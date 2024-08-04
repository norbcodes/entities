// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/*
MADE BY NORB

The long awaited... entities2!!!!
*/

#include <iostream>
#include <cstdint>
#include <random>
#include <string>
#include <math.h>
#include <chrono>   // chrono::seconds()
#include <vector>

#ifdef __linux__
#include <unistd.h>
#else
#include <windows.h>
#endif

// Game version
#define ENTITIES2_VER       "v1.0.1"

// Cap
#define MAX_STAT_CAP        200
// Stuff
#define PLAYER_START_HP     100
#define PLAYER_START_AR     100
#define ENEMY_START_HP      100
#define ENEMY_START_AR      100
#define HEALTH_F            5
#define ARMOR_F             2
// OPTION TYPES
#define ATTACK              0
#define HEAL                1
#define ARMOR               2
#define STATUS              3
// FACTORS
#define ATTACK_F            5
#define HEAL_F              5
#define ARM_F               5
// STATUSES
#define STATUS_C            3
#define AUTO_HEAL           0
#define INCR_CRIT           1
#define INVIS               2
#define STATUS_TIME_LEFT    4
#define AUTO_HEAL_AMOUNT    10
// COLOR MACROS
#define ITALIC(x)           std::string("\x1b[3m") + std::string(x) + std::string("\x1b[0m")
#define BOLD(x)             std::string("\x1b[1m") + std::string(x) + std::string("\x1b[0m")
#define RED(x)              std::string("\x1b[38;2;255;25;25m") + std::string(x) + std::string("\x1b[0m")
#define BLUE(x)             std::string("\x1b[38;2;36;80;255m") + std::string(x) + std::string("\x1b[0m")
#define ORANGE(x)           std::string("\x1b[38;2;230;153;0m") + std::string(x) + std::string("\x1b[0m")
#define WHITE(x)            std::string("\x1b[38;2;230;230;230m") + std::string(x) + std::string("\x1b[0m")
#define HOT_PINK(x)         std::string("\x1b[38;2;153;0;77m") + std::string(x) + std::string("\x1b[0m")
#define GRAY(x)             std::string("\x1b[38;2;99;99;99m") + std::string(x) + std::string("\x1b[0m")
#define DARK_GRAY(x)        std::string("\x1b[38;2;68;68;68m") + std::string(x) + std::string("\x1b[0m")
#define PINK(x)             std::string("\x1b[38;2;234;128;255m") + std::string(x) + std::string("\x1b[0m")
#define GOLD(x)             std::string("\x1b[38;2;255;195;77m") + std::string(x) + std::string("\x1b[0m")
#define GREEN(x)            std::string("\x1b[38;2;0;255;42m") + std::string(x) + std::string("\x1b[0m")
#define PURPLE(x)           std::string("\x1b[38;2;76;0;230m") + std::string(x) + std::string("\x1b[0m")
// INLINES
#define ITALIC_IN(x)        std::string("\x1b[3m") + std::string(x)
#define BOLD_IN(x)          std::string("\x1b[1m") + std::string(x)
#define RED_IN(x)           std::string("\x1b[38;2;255;25;25m") + std::string(x)
#define BLUE_IN(x)          std::string("\x1b[38;2;36;80;255m") + std::string(x)
#define ORANGE_IN(x)        std::string("\x1b[38;2;230;153;0m") + std::string(x)
#define WHITE_IN(x)         std::string("\x1b[38;2;230;230;230m") + std::string(x)
#define HOT_PINK_IN(x)      std::string("\x1b[38;2;153;0;77m") + std::string(x)
#define GRAY_IN(x)          std::string("\x1b[38;2;99;99;99m") + std::string(x)
#define DARK_GRAY_IN(x)     std::string("\x1b[38;2;68;68;68m") + std::string(x)
#define PINK_IN(x)          std::string("\x1b[38;2;234;128;255m") + std::string(x)
#define GOLD_IN(x)          std::string("\x1b[38;2;255;195;77m") + std::string(x)
#define GREEN_IN(x)         std::string("\x1b[38;2;0;255;42m") + std::string(x)
#define PURPLE_IN(x)        std::string("\x1b[38;2;76;0;230m") + std::string(x)

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void ClearScreen()
{
    #ifdef __linux__
    system("clear");
    #else
    system("cls");
    #endif
}

void SleepSeconds(uint32_t seconds)
{
    #ifdef __linux__
    sleep(seconds);
    #else
    Sleep(1000 * seconds);
    #endif
}

uint32_t rng(uint32_t limit)
{
    // SHAMELESSLY COPIED FROM ENTITIES.CPP
    std::random_device rd;
    std::mt19937 gen(rd());
    // Check if limit is zero to avoud doing % 0
    if (limit == 0)
    {
        return 0;
    }
    // I spent like an hour and half hunting this bug down
    return gen() % limit;
}

void Div()
{
    std::cout << DARK_GRAY(BOLD_IN("------------------------------------------------------------------------")) << std::endl;
}

void Credits()
{
    Div();
    std::cout << GOLD(ITALIC_IN("DEM CREDITS!!!!")) << std::endl << std::endl;
    std::cout << GOLD(BOLD_IN("Game")) + WHITE(" by ") + BLUE(BOLD_IN("Norb")) << std::endl;
    std::cout << HOT_PINK(BOLD_IN("Coded")) + WHITE(" in ") + GREEN(BOLD_IN("C++")) << std::endl;
    std::cout << WHITE("Coded in about 2 days.\n") + DARK_GRAY("(As of writting the credits, Discord says I spent 6 hours on VScode)") << std::endl;
    std::cout << BLUE("These fine colors picked out using ") + BLUE(BOLD_IN("rgbcolorcode.com")) + BLUE("! B)") << std::endl;
    std::cout << PURPLE("Check out entity1 and the homepage at ") + PURPLE(BOLD_IN("github.com/norbcodes/entities")) << std::endl;
    std::cout << std::endl << DARK_GRAY("entities2.cpp version ") + DARK_GRAY(ENTITIES2_VER) + DARK_GRAY(" compiled at ") + DARK_GRAY(__DATE__) + " " + DARK_GRAY(__TIME__) + " ;)" << std::endl;
    Div();
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class Status
{
    private:
        uint8_t type;
        uint8_t time_left;
    public:
        Status(uint8_t type, uint8_t time_left);
        uint8_t GetType() const;
        uint8_t GetTimeLeft() const;
        void Age();
};

Status::Status(uint8_t type, uint8_t time_left) : type(0), time_left(0) 
{
    this->type = type;
    this->time_left = time_left;
}

uint8_t Status::GetType() const
{
    return this->type;
}

uint8_t Status::GetTimeLeft() const
{
    return this->time_left;
}

void Status::Age()
{
    this->time_left--;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
    private:
        int32_t health;
        int32_t armor;
        std::vector<Status> status_list;
    public:
        Entity(int32_t start_health, int32_t start_armor);
        int32_t GetHealth() const;
        int32_t GetArmor() const;
        void Hurt(uint32_t dmg);
        void HurtArmor(uint32_t dmg);
        void Heal(uint32_t val);
        void RegenArmor(uint32_t val);
        bool StatusActive(uint8_t type) const;
        void GiveStatus(uint8_t type);
        uint8_t StatusCount() const;
        Status GetStatusAt(uint8_t i) const;
        void UpdateStatuses(std::string& msg, bool turn);
};

Entity::Entity(int32_t start_health, int32_t start_armor) : health(start_health), armor(start_armor) 
{
    this->status_list.reserve(64);
}

int32_t Entity::GetHealth() const
{
    return this->health;
}

int32_t Entity::GetArmor() const
{
    return this->armor;
}

void Entity::Hurt(uint32_t dmg)
{
    if ((this->health - dmg) <= 0)
    {
        this->health = 0;
        return;
    }
    this->health -= dmg;
}

void Entity::HurtArmor(uint32_t dmg)
{
    if ((this->armor - dmg) <= 0)
    {
        this->armor = 0;
        return;
    }
    this->armor -= dmg;
}

void Entity::Heal(uint32_t val)
{
    if ((this->health + val) >= MAX_STAT_CAP)
    {
        this->health = MAX_STAT_CAP;
        return;
    }
    this->health += val;
}

void Entity::RegenArmor(uint32_t val)
{
    if ((this->armor + val) >= MAX_STAT_CAP)
    {
        this->armor = MAX_STAT_CAP;
        return;
    }
    this->armor += val;
}

bool Entity::StatusActive(uint8_t type) const
{
    for (int i = 0; i != this->status_list.size(); i++)
    {
        if (this->status_list[i].GetType() == type)
        {
            return true;
        }
    }
    return false;
}

void Entity::GiveStatus(uint8_t type)
{
    this->status_list.emplace_back(type, STATUS_TIME_LEFT);
}

uint8_t Entity::StatusCount() const
{
    return this->status_list.size();
}

Status Entity::GetStatusAt(uint8_t i) const
{
    return this->status_list[i];
}

void Entity::UpdateStatuses(std::string& msg, bool turn)
{
    // Guard
    if (this->status_list.size() == 0)
    {
        return;
    }
    // yay
    for (int i = 0; i < this->status_list.size(); i++)
    {
        this->status_list[i].Age();
        // Only apply AutoHeal, Invis and IncreasedCrit are handled in the Hurt method
        if (this->status_list[i].GetType() == AUTO_HEAL)
        {
            this->Heal(AUTO_HEAL_AMOUNT);
            switch (turn)
            {
                case true:
                    msg += RED(BOLD_IN("Enemy ")) + WHITE("has autohealed! ") + WHITE(BOLD_IN("+" + std::to_string(AUTO_HEAL_AMOUNT) + "HP\n"));
                    break;
                case false:
                    msg += BLUE(BOLD_IN("Player ")) + WHITE("has autohealed! ") + WHITE(BOLD_IN("+" + std::to_string(AUTO_HEAL_AMOUNT) + "HP\n"));
                    break;
            }
        }
        if (this->status_list[i].GetTimeLeft() == 0)
        {
            this->status_list.erase(this->status_list.begin() + i);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void PrintEntityStats(const Entity& ent)
{
    std::cout << GREEN(BOLD_IN("HP: ")) << WHITE(std::to_string(ent.GetHealth())) << PINK(BOLD_IN(" AR: ")) << WHITE(std::to_string(ent.GetArmor()));
    std::cout << GOLD(BOLD_IN("\tS: "));
    for (int i = 0; i != ent.StatusCount(); i++)
    {
        Status _s = ent.GetStatusAt(i);
        if (_s.GetType() == AUTO_HEAL)
        {
            std::cout << GREEN("+") << DARK_GRAY(std::to_string((int)_s.GetTimeLeft())) << " ";
        }
        else if (_s.GetType() == INCR_CRIT)
        {
            std::cout << RED("X") << DARK_GRAY(std::to_string((int)_s.GetTimeLeft())) << " ";
        }
        else if (_s.GetType() == INVIS)
        {
            std::cout << WHITE("O") << DARK_GRAY(std::to_string((int)_s.GetTimeLeft())) << " ";
        }
    }
    std::cout << std::endl;
}

void EntityAttack(const Entity& attacker, Entity& victim, uint32_t dmg, std::string& msg, bool enemy_turn)
{
    // if victim has invis
    if (victim.StatusActive(INVIS) && rng(100) > 80)
    {
        if (enemy_turn)
        {
            msg += RED(BOLD_IN("Enemy ")) + WHITE("tried to attack, but ") + WHITE(ITALIC_IN("missed")) + WHITE("!");
        }
        else
        {
            msg += BLUE(BOLD_IN("Player ")) + WHITE("tried to attack, but ") + WHITE(ITALIC_IN("missed")) + WHITE("!");
        }
        return;
    }

    uint32_t health_dmg = dmg;
    uint32_t armor_dmg = 0;
    bool crit_flag = false;
    // Crit
    if (attacker.StatusActive(INCR_CRIT) && rng(100) > 70)
    {
        health_dmg *= 2;
        crit_flag = true;
    }
    // If victim has armor, we split health_dmg
    if (victim.GetArmor() != 0)
    {
        uint8_t _temp = health_dmg;
        health_dmg = (uint32_t)(ceilf(health_dmg / 2));
        armor_dmg = (uint32_t)(floorf(_temp / 2));
    }
    // IF armor_dmg takes more armor than the victim has (armor < 0) then do this
    if (armor_dmg > victim.GetArmor())
    {
        health_dmg += armor_dmg - victim.GetArmor();
        armor_dmg = victim.GetArmor();
    }

    victim.Hurt(health_dmg);
    victim.HurtArmor(armor_dmg);

    if (!enemy_turn)
    {
        if (!crit_flag)
        {
            msg += BLUE(BOLD_IN("Player ")) + WHITE("has attacked ") + RED(BOLD_IN("Enemy")) + WHITE("! ") + RED(BOLD_IN("Enemy ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
            return;
        }
        msg += BLUE(BOLD_IN("Player ")) + WHITE("has attacked ") + RED(BOLD_IN("Enemy")) + WHITE("! ") + GOLD(ITALIC_IN("CRITICAL HIT")) + WHITE("! ") + RED(BOLD_IN("Enemy ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
        return;
    }
    else
    {
        if (!crit_flag)
        {
            msg += RED(BOLD_IN("Enemy ")) + WHITE("has attacked ") + BLUE(BOLD_IN("Player")) + WHITE("! ") + BLUE(BOLD_IN("Player ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
            return;
        }
        msg += RED(BOLD_IN("Enemy ")) + WHITE("has attacked ") + BLUE(BOLD_IN("Player")) + WHITE("! ") + GOLD(ITALIC_IN("CRITICAL HIT")) + WHITE("! ") + BLUE(BOLD_IN("Player ")) + PURPLE("-" + std::to_string(health_dmg)) + WHITE(" HP ") + ((armor_dmg != 0) ? (PURPLE("-" + std::to_string(armor_dmg)) + WHITE(" AR")) : WHITE(""));
        return;
    }
}

uint32_t AiChoose(uint8_t* picks_list, uint8_t* types_list, const Entity& player, const Entity& enemy)
{
    // Basically, heal if health < 40 if posslbe
    // Attack if health > 80 if possible
    // (middle zone 40 < health < 80, choose a random status if possible)
    // If armor < 50, take RegenArmor if possible

    // The ai
    // I copy+pasted a lot of this shit

    // Can we armor?
    
    if (enemy.GetArmor() <= 50)
    {
        uint32_t max_armor_amount = 0;
        for (int i = 0; i != 4; i++)
        {
            // Is of type heal
            if (types_list[i] == ARMOR)
            {
                // Get the highest heal amount
                if (picks_list[i] > max_armor_amount)
                {
                    max_armor_amount = picks_list[i];
                }
            }
        }
        // If max_armor_amount is not 0
        if (max_armor_amount != 0)
        {
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == max_armor_amount)
                {
                    return i;
                }
            }
        } // else just continue.
    }

    // Can we heal?
    if (enemy.GetHealth() <= 40)
    {
        uint32_t max_heal_amount = 0;
        for (int i = 0; i != 4; i++)
        {
            // Is of type heal
            if (types_list[i] == HEAL)
            {
                // Get the highest heal amount
                if (picks_list[i] > max_heal_amount)
                {
                    max_heal_amount = picks_list[i];
                }
            }
        }
        // If max_heal_amount is not 0
        if (max_heal_amount != 0)
        {
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == max_heal_amount)
                {
                    return i;
                }
            }
        } // else just continue.
    }

    // Attack
    if (enemy.GetHealth() >= 80)
    {
        uint32_t max_dmg_amount = 0;
        for (int i = 0; i != 4; i++)
        {
            // Is of type heal
            if (types_list[i] == ATTACK)
            {
                // Get the highest heal amount
                if (picks_list[i] > max_dmg_amount)
                {
                    max_dmg_amount = picks_list[i];
                }
            }
        }
        // If max_dmg_amount is not 0
        if (max_dmg_amount != 0)
        {
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == max_dmg_amount)
                {
                    return i;
                }
            }
        } // else just continue.
    }

    // Choose a status
    if (40 < enemy.GetHealth() && enemy.GetHealth() < 80)
    {
        uint8_t count = 0;
        for (int i = 0; i != 4; i++)
        {
            if (types_list[i] == STATUS)
            {
                count++;
            }
        }
        uint8_t pick = rng(count);
        uint8_t index = 0;
        // The loop of doom
        while (pick != 0)
        {
            if (picks_list[index] == STATUS)
            {
                pick--;
            }
            if (pick == 0)
            {
                return index;
            }
            if (index == 3)
            {
                return index;
            }
            index++;
        }
    }

    // If literally nothing get picked
    return rng(3);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void Game(const std::string& mode)
{
    uint8_t difficulty_scale;
    // Is easy?
    if (mode == "easy")
    {
        difficulty_scale = 0;
    }
    // Is medium?
    else if (mode == "medium")
    {
        difficulty_scale = 1;
    }
    // Is hard?
    else if (mode == "hard")
    {
        difficulty_scale = 2;
    }
    // or no
    else 
    {
        std::cerr << RED(BOLD_IN("WRONG DIFFICULTY!!!! Or maybe bad spelling or something")) << std::endl;
        return;
    }

    // Create player and enemy
    // Heap alloc for funnidifficulty_scale
    Entity* Player = new Entity(PLAYER_START_HP - difficulty_scale * HEALTH_F, PLAYER_START_AR - difficulty_scale * ARMOR_F);
    Entity* Enemy = new Entity(ENEMY_START_HP + difficulty_scale * HEALTH_F, ENEMY_START_AR + difficulty_scale * ARMOR_F);
    // Yes, it literally rigs the game against you

    // Gameplay loop
    bool is_running = true;
    bool turn = false;  // true = Enemy, false = Player
    std::string what_happened = RED(ITALIC_IN("The fight begins."));

    while (is_running)
    {
        ClearScreen();
        Div();
        // Generate 4 options to choose from.
        // There are 4 types: Attack, Heal, Regen armor, Status
        uint8_t* moves = new uint8_t[4];
        uint8_t* move_types = new uint8_t[4];

        if (Player->GetHealth() <= 0)
        {
            std::cout << WHITE("---<<< ") + BLUE(BOLD_IN("Player ")) + WHITE("dead. ") + RED(BOLD_IN("Enemy ")) + WHITE("wins!!! >>>---") << std::endl << std::endl;
            std::cout << GRAY("Press enter to exit") << std::endl << std::endl;
            Div();
            std::cout << "\x1b[2A";
            std::string garbage;
            std::cin >> garbage;
            is_running = false;
            goto END_GAME;
        }

        if (Enemy->GetHealth() <= 0)
        {
            std::cout << WHITE("---<<< ") + RED(BOLD_IN("Enemy ")) + WHITE("dead. ") + BLUE(BOLD_IN("Player ")) + WHITE("wins!!! >>>---") << std::endl << std::endl;
            std::cout << GRAY("Press enter to exit") << std::endl << std::endl;
            Div();
            std::cout << "\x1b[2A";
            std::string garbage;
            std::cin >> garbage;
            is_running = false;
        }

        // Print header
        std::cout << DARK_GRAY("---<<< ") << (turn ? RED(BOLD_IN("Enemy's")) : BLUE(BOLD_IN("Player's"))) << DARK_GRAY(" turn! >>>---") << std::endl;

        std::cout << WHITE("What happened:\n") << what_happened << std::endl << std::endl;
        what_happened = "";

        switch (turn)
        {
            case true:
                Enemy->UpdateStatuses(what_happened, true);
                break;
            case false:
                Player->UpdateStatuses(what_happened, false);
                break;
        }
        // random switch go brrrr

        // Print stats
        std::cout << BLUE(BOLD_IN("[Player]\t"));
        PrintEntityStats(*Player);
        std::cout << RED (BOLD_IN("[Enemy] \t"));
        PrintEntityStats(*Enemy);
        std::cout << std::endl;

        for (int i = 0; i != 4; i++)
        {
            uint32_t type = rng(4);  // 4 option types
            switch (type)
            {
                case ATTACK:
                    move_types[i] = ATTACK;
                    moves[i] = ATTACK_F * (rng(8) + 1);
                    std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + RED("Attack!") + WHITE(" Deal ") + PURPLE(std::to_string((int)moves[i]) ) + WHITE(" damage to opponent.") << std::endl;
                    break;
                case HEAL:
                    move_types[i] = HEAL;
                    moves[i] = HEAL_F * (rng(5) + 1);
                    std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + GREEN("Heal! ") + WHITE("Gives you ") + PURPLE("+" + std::to_string((int)moves[i])) + WHITE(" HP") << std::endl;
                    break;
                case ARMOR:
                    move_types[i] = ARMOR;
                    moves[i] = ARM_F * (rng(9) + 1);
                    std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + BLUE("Regen armor") + WHITE("! Give you ") + PURPLE("+" + std::to_string((int)moves[i])) + WHITE(" AR") << std::endl;
                    break;
                case STATUS:
                    move_types[i] = STATUS;
                    moves[i] = rng(STATUS_C);
                    
                    switch (moves[i])
                    {
                        case AUTO_HEAL:
                            std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + GREEN("AutoHeal ") + WHITE("status! Gives you ") + PURPLE("+5") + WHITE(" HP when it's your turn") << std::endl;
                            break;
                        case INCR_CRIT:
                            std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + RED("IncreasedCrit") + WHITE(" status! Increased chance to deal a ") + RED("critical attack") << std::endl;
                            break;
                        case INVIS:
                            std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + HOT_PINK("Invis ") + WHITE("status! Opponent has a chance to ") + HOT_PINK("miss") << std::endl;
                            break;
                    }

                    break;
                default:
                    std::cerr << RED(BOLD_IN("wtf")) << std::endl;
                    is_running = !is_running;
                    break;
            }
        }

        std::cout << std::endl;

        // Yay!
        // Ask for input...
        if (!turn)
        {
            POINT:
            std::cout << WHITE("Choose your move.") + BOLD(GRAY(" [1,2,3,4,9] (9 to exit)                                           ")) << std::endl << std::endl;
            Div();
            std::cout << "\x1b[2A";
            // Player
            uint32_t picked_move;
            std::cin >> picked_move;

            if (picked_move == 9)
            {
                std::cout << RED("Do you really wanna end the battle?") + BOLD(GRAY(" [y,n]                                                             ")) << std::endl << std::endl;
                Div();
                std::cout << "\x1b[2A";
                std::string option;
                std::cin >> option;
                if (option == "y")
                {
                    is_running = false;
                    goto END_GAME;
                }
                else
                {
                    goto POINT;
                }
            }

            // if pick is not 0, 1, 2, 3 or 9 = skip round
            if (picked_move != 1 && picked_move != 2 && picked_move != 3 && picked_move != 4 && picked_move != 9)
            {
                what_happened += BLUE(BOLD_IN("Player ")) + WHITE("skipped the round.");
                goto SKIP_ROUND;
            }

            picked_move--;

            if (move_types[picked_move] == ATTACK)
            {
                EntityAttack(*Player, *Enemy, moves[picked_move], what_happened, turn);
            }
            else if (move_types[picked_move] == HEAL)
            {
                Player->Heal(moves[picked_move]);
                what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has healed ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" health.");
            }
            else if (move_types[picked_move] == ARMOR)
            {
                Player->RegenArmor(moves[picked_move]);
                what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has regen'd ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" armor.");
            }
            else if (move_types[picked_move] == STATUS)
            {
                Player->GiveStatus(moves[picked_move]);
                switch (moves[picked_move])
                {
                    case AUTO_HEAL:
                        what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + GREEN("AutoHeal") + WHITE(".");
                        break;
                    case INCR_CRIT:
                        what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + RED("IncreasedCrit") + WHITE(".");
                        break;
                    case INVIS:
                        what_happened += BLUE(BOLD_IN("Player ")) + WHITE("has applied ") + HOT_PINK("Invis") + WHITE(".");
                        break;
                }
            }
        }
        else
        {
            std::cout << GOLD(ITALIC_IN("The AI is thinking...")) << std::endl << std::endl;
            Div();
            std::cout << "\x1b[2A";
            // bot
            uint32_t picked_move = AiChoose(moves, move_types, *Player, *Enemy);
            // Print random num
            for (int i = 0; i != 19000; i++)
            {
                std::cout << rng(3) + 1;
                std::cout << "\x1B[1D";
            }
            std::cout << picked_move + 1;
            SleepSeconds(2);
            // Botttttt
            if (move_types[picked_move] == ATTACK)
            {
                EntityAttack(*Enemy, *Player, moves[picked_move], what_happened, turn);
            }
            else if (move_types[picked_move] == HEAL)
            {
                Enemy->Heal(moves[picked_move]);
                what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has healed ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" health.");
            }
            else if (move_types[picked_move] == ARMOR)
            {
                Enemy->RegenArmor(moves[picked_move]);
                what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has regen'd ") + PURPLE(std::to_string(moves[picked_move])) + WHITE(" armor.");
            }
            else if (move_types[picked_move] == STATUS)
            {
                Enemy->GiveStatus(moves[picked_move]);
                switch (moves[picked_move])
                {
                    case AUTO_HEAL:
                        what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + GREEN("AutoHeal") + WHITE(".");
                        break;
                    case INCR_CRIT:
                        what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + RED("IncreasedCrit") + WHITE(".");
                        break;
                    case INVIS:
                        what_happened += RED(BOLD_IN("Enemy ")) + WHITE("has applied ") + HOT_PINK("Invis") + WHITE(".");
                        break;
                }
            }
        }

        SKIP_ROUND:
        END_GAME:
        turn = !turn;
        delete[] moves;
        delete[] move_types;
    }

    // Make sure to annihilate
    delete Player;
    delete Enemy;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // force 256 
    std::cout << "\x1b[=19h" << std::endl;
    while (true)
    {
        ClearScreen();
        Div();
        std::cout << WHITE("Welcome to ") + GOLD(ITALIC_IN("entities2.cpp")) + WHITE("!!!!\nPlease, pick a difficulty:\n") << std::endl;
        std::cout << BLUE("easy") << std::endl;
        std::cout << ORANGE("medium") << std::endl;
        std::cout << RED("hard") << std::endl;
        std::cout << DARK_GRAY("Or type 'quit' to quit") << std::endl << std::endl;
        Div();
        std::cout << "\x1b[2A";
        std::string option;
        std::cin >> option;

        if (option == "quit")
        {
            ClearScreen();
            Credits();
            SleepSeconds(1);
            break;
        }

        // do
        Game(option);
    }

    return 0;
}