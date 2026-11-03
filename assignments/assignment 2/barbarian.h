
/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

AI assistance from ChatGPT was used to revise the Barbarian class.
*/
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include <iostream>

namespace seneca {

    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense;
        int m_baseAttack;
        Ability_t m_ability;
        Weapon_t m_weapon[2];

    public:
        Barbarian(const char* name, int healthMax,
            int baseAttack, int baseDefense,
            Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax),
            m_baseDefense(baseDefense),
            m_baseAttack(baseAttack),
            m_ability{},
            m_weapon{ primaryWeapon, secondaryWeapon } {
        }

        int getAttackAmnt() const override {
            return m_baseAttack +
                static_cast<int>(
                    (static_cast<double>(m_weapon[0]) +
                        static_cast<double>(m_weapon[1])) / 2
                    );
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Barbarian(*this);
        }

        void attack(Character* enemy) override {
            if (enemy == nullptr) {
                return;
            }

            std::cout << this->getName()
                << " is attacking "
                << enemy->getName() << ".\n";

            m_ability.useAbility(this);

            int damage = getAttackAmnt();
            m_ability.transformDamageDealt(damage);

            std::cout << "    Barbarian deals "
                << damage << " melee damage!\n";

            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName()
                << " is attacked for "
                << dmg << " damage.\n";

            std::cout << "    Barbarian has a defense of "
                << m_baseDefense
                << ". Reducing damage received.\n";

            // Apply defense before the special ability.
            dmg -= m_baseDefense;

            if (dmg < 0) {
                dmg = 0;
            }

            m_ability.transformDamageReceived(dmg);

            if (dmg < 0) {
                dmg = 0;
            }

            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}

#endif
