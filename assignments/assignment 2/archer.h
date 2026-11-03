/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

*/
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
#include <iostream>

namespace seneca {

    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth> {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon{};

    public:
        Archer(const char* name, int healthMax,
            int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<SuperHealth>(name, healthMax),
            m_baseDefense(baseDefense),
            m_baseAttack(baseAttack),
            m_weapon(weapon) {}

        int getAttackAmnt() const override {
            return static_cast<int>(1.3 * m_baseAttack);
        }

        int getDefenseAmnt() const override {
            return static_cast<int>(1.2 * m_baseDefense);
        }

        Character* clone() const override {
            return new Archer(*this);
        }

        void attack(Character* enemy) override {
            if (enemy == nullptr) {
                return;
            }

            std::cout << this->getName() << " is attacking "
                << enemy->getName() << ".\n";

            int damage = getAttackAmnt();

            std::cout << "    Archer deals " << damage
                << " ranged damage!\n";

            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName()
                << " is attacked for " << dmg << " damage.\n";

            std::cout << "    Archer has a defense of "
                << getDefenseAmnt()
                << ". Reducing damage received.\n";

            int actualDamage = dmg - getDefenseAmnt();
            if (actualDamage < 0) {
                actualDamage = 0;
            }

            CharacterTpl<SuperHealth>::takeDamage(actualDamage);
        }
    };

}

#endif