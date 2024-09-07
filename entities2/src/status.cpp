// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>
#include <string>
#include <fmt/core.h>

#include "status_constants.hpp"
#include "colors.hpp"
#include "status.hpp"
#include "entity.hpp"

/**
 * \brief Constructor function for Status.
 * \param[in] type The type of Status.
 * \param[in] time_left Time left until expiration.
 */
Status::Status(uint8_t type, uint8_t time_left) : type(0), time_left(0) 
{
    this->type = type;
    this->time_left = time_left;
}

/**
 * \brief Get type of this Status.
 * \return The type.
 */
uint8_t Status::GetType() const
{
    return this->type;
}

/**
 * \brief Get Status time left.
 * \return The time left until expiration.
 */
uint8_t Status::GetTimeLeft() const
{
    return this->time_left;
}

/**
 * \brief Decrease status lifetime.
 */
void Status::Age()
{
    this->time_left--;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Does this Entity have the specified Status?
 * \param[in] type Type of Status to check for.
 * \return True if Status is active, otherwise False.
 */
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

/**
 * \brief Give Status to Entity.
 * \param[in] type Type of Status to give.
 */
void Entity::GiveStatus(uint8_t type)
{
    this->status_list.emplace_back(type, STATUS_TIME_LEFT);
}

/**
 * \brief Number of statuses this Entity has.
 * \return Number of statuses.
 */
uint8_t Entity::StatusCount() const
{
    return this->status_list.size();
}

/**
 * \brief Return the Status at index <i>i</i>.
 * \param[in] i The index.
 * \return Status object.
 */
Status Entity::GetStatusAt(uint8_t i) const
{
    return this->status_list[i];
}

/**
 * \brief Process all statuses of the Entity.
 * \param[out] msg The "What happened:" text, which is why it's string&,<br>
 *                 because we write into it.
 * \param[in] enemy_turn For prompt generation.
 */
void Entity::UpdateStatuses(std::string& msg, bool enemy_turn)
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
        // Only apply AutoHeal and Poison, Invis and IncreasedCrit and Thorns are handled in the Hurt method
        if (this->status_list[i].GetType() == AUTO_HEAL)
        {
            this->Heal(AUTO_HEAL_AMOUNT);
            if (enemy_turn)
            {
                msg += fmt::format("{2}{3}Enemy{0} {4}has autohealed! {3}+{1}HP{0}\n", RESET, AUTO_HEAL_AMOUNT, RED, BOLD, WHITE);
            }
            else
            {
                msg += fmt::format("{2}{3}Player{0} {4}has autohealed! {3}+{1}HP{0}\n", RESET, AUTO_HEAL_AMOUNT, BLUE, BOLD, WHITE);
            }
        }
        else if (this->status_list[i].GetType() == POISON)
        {
            this->Hurt(POISON_AMOUNT);
            if (enemy_turn)
            {
                msg += fmt::format("{2}{3}Enemy{0} {4}has felt the poison! {3}-{1}HP{0}\n", RESET, POISON_AMOUNT, RED, BOLD, WHITE);
            }
            else
            {
                msg += fmt::format("{2}{3}Player{0} {4}has felt the poison! {3}-{1}HP{0}\n", RESET, POISON_AMOUNT, BLUE, BOLD, WHITE);
            }
        }

        if (this->status_list[i].GetTimeLeft() == 0)
        {
            this->status_list.erase(this->status_list.begin() + i);
            i = -1;  // This will be 0 on next iteration
        }
    }
}