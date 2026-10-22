/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: October 20, 2026
*/
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
#include "weapons.h"

namespace seneca {
    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth> {
        int m_baseAttack{};
        int m_baseDefense{};
        Weapon_t m_weapon{};

    public:
        Archer(const char* name, int health, int baseAttack,
            int baseDefense, Weapon_t weapon)
            : CharacterTpl<SuperHealth>(name, health),
            m_baseAttack(baseAttack),
            m_baseDefense(baseDefense),
            m_weapon(weapon) {
        }

        int getAttackAmnt() const override {
            return static_cast<int>(m_baseAttack * 1.3);
        }

        int getDefenseAmnt() const override {
            return static_cast<int>(m_baseDefense * 1.2);
        }

        Character* clone() const override {
            return new Archer(*this);
        }

        void attack(Character* enemy) override {
            if (!enemy) return;

            std::cout << this->getName() << " attacks "
                << enemy->getName() << ".\n";

            int damage = getAttackAmnt();

            std::cout << "    Damage dealt: " << damage << '\n';
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            int actual = dmg - getDefenseAmnt();
            if (actual < 0) actual = 0;

            CharacterTpl<SuperHealth>::takeDamage(actual);
        }
    };
}
#endif