/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: October 20, 2026
*/
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"

namespace seneca {
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseAttack{};
        int m_baseDefense{};
        FirstAbility_t m_firstAbility{};
        SecondAbility_t m_secondAbility{};
        Dagger m_weapon{};

    public:
        Rogue(const char* name, int health, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, health),
            m_baseAttack(baseAttack),
            m_baseDefense(baseDefense) {
        }

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
            if (!enemy) return;

            std::cout << this->getName() << " attacks "
                << enemy->getName() << ".\n";

            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);

            int damage = getAttackAmnt();
            m_firstAbility.transformDamageDealt(damage);
            m_secondAbility.transformDamageDealt(damage);

            std::cout << "    Damage dealt: " << damage << '\n';
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);

            int actual = dmg - getDefenseAmnt();
            if (actual < 0) actual = 0;

            CharacterTpl<T>::takeDamage(actual);
        }
    };
}
#endif