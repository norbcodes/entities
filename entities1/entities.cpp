#include <iostream>
#include <random>

int rng(int limit)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    return abs(gen()) % limit;
}

struct Entity
{
    int health;
    int dmg;

    Entity(int h, int d)
    {
        this->health = h;
        this->dmg = d;
    }
};

void LogStats(const Entity& entity)
{
    std::cout << "-----------------\n";
    std::cout << "Health: " << entity.health << "| DMG: " << entity.dmg << std::endl;
}

void E_Attack(const Entity& attacker, Entity& target)
{
    target.health -= attacker.dmg + rng(3);
}

void E_SuperAttack(const Entity& attacker, Entity& target)
{
    target.health -= (attacker.dmg * 2) + rng(3);
}

int main()
{
    Entity E1 = Entity(100, 5);
    Entity E2 = Entity(100, 6);
    LogStats(E1);
    LogStats(E2);

    E_Attack(E2, E1);

    LogStats(E1);
    LogStats(E2);

    E_SuperAttack(E1, E2);

    LogStats(E1);
    LogStats(E2);
    return 0;
}