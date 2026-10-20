/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: October 20, 2026
*/
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"

namespace seneca {
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        Ability_t m_ability{};
        int m_baseAttack{};
        int m_baseDefense{};
        Weapon_t m_weapon1{};
        Weapon_t m_weapon2{};

    public:
        Barbarian(const char* name, int health, int baseAttack,
            int baseDefense, Weapon_t weapon1, Weapon_t weapon2)
            : CharacterTpl<T>(name, health),
            m_baseAttack(baseAttack),
            m_baseDefense(baseDefense),
            m_weapon1(weapon1),
            m_weapon2(weapon2) {
        }

        int getAttackAmnt() const override {
            return m_baseAttack
                + static_cast<int>(static_cast<double>(m_weapon1) / 2)
                + static_cast<int>(static_cast<double>(m_weapon2) / 2);
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Barbarian(*this);
        }

        void attack(Character* enemy) override {
            if (!enemy) return;

            std::cout << this->getName() << " attacks "
                << enemy->getName() << ".\n";

            m_ability.useAbility(this);

            int damage = getAttackAmnt();
            m_ability.transformDamageDealt(damage);

            std::cout << "    Damage dealt: " << damage << '\n';
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            m_ability.transformDamageReceived(dmg);

            int actual = dmg - getDefenseAmnt();
            if (actual < 0) actual = 0;

            CharacterTpl<T>::takeDamage(actual);
        }
    };
}
#endif