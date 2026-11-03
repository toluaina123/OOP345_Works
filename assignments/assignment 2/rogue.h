/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

*/
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"
#include <iostream>

namespace seneca {

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseAttack{};
        int m_baseDefense{};
        FirstAbility_t m_firstAbility{};
        SecondAbility_t m_secondAbility{};
        Dagger m_weapon{};

    public:
        Rogue(const char* name, int healthMax,
            int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax),
            m_baseAttack(baseAttack),
            m_baseDefense(baseDefense) {}

        int getAttackAmnt() const override {
            return m_baseAttack +
                static_cast<int>(2 * static_cast<double>(m_weapon));
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Rogue(*this);
        }

        void attack(Character* enemy) override {
            if (enemy == nullptr) {
                return;
            }

            std::cout << this->getName() << " is attacking "
                << enemy->getName() << ".\n";

            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);

            int damage = getAttackAmnt();
            m_firstAbility.transformDamageDealt(damage);
            m_secondAbility.transformDamageDealt(damage);

            std::cout << "    Rogue deals " << damage
                << " melee damage!\n";

            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName()
                << " is attacked for " << dmg << " damage.\n";

            std::cout << "    Rogue has a defense of "
                << m_baseDefense
                << ". Reducing damage received.\n";

            dmg -= m_baseDefense;
            if (dmg < 0) {
                dmg = 0;
            }

            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);

            if (dmg < 0) {
                dmg = 0;
            }

            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}

#endif