/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

*/
#include "guild.h"
#include <utility>

namespace seneca {

    Guild::Guild(const char* name)
        : m_name(name ? name : "") {}

    Guild::~Guild() {
        clear();
    }

    void Guild::clear() {
        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_bonusApplied[i]) {
                m_members[i]->setHealthMax(
                    m_members[i]->getHealthMax() - 300
                );
            }
        }

        delete[] m_members;
        delete[] m_bonusApplied;

        m_members = nullptr;
        m_bonusApplied = nullptr;
        m_size = 0;
    }

    void Guild::copyFrom(const Guild& src) {
        if (src.m_size == 0) {
            return;
        }

        Character** newMembers = new Character * [src.m_size];
        bool* newBonusApplied = nullptr;

        try {
            newBonusApplied = new bool[src.m_size];
        }
        catch (...) {
            delete[] newMembers;
            throw;
        }

        for (std::size_t i = 0; i < src.m_size; ++i) {
            newMembers[i] = src.m_members[i];
            newBonusApplied[i] = false;
        }

        m_members = newMembers;
        m_bonusApplied = newBonusApplied;
        m_size = src.m_size;
    }

    Guild::Guild(const Guild& src)
        : m_name(src.m_name) {
        copyFrom(src);
    }

    Guild& Guild::operator=(const Guild& src) {
        if (this != &src) {
            Guild temp(src);
            swap(temp);
        }

        return *this;
    }

    Guild::Guild(Guild&& src) noexcept
        : m_name(std::move(src.m_name)),
        m_members(src.m_members),
        m_bonusApplied(src.m_bonusApplied),
        m_size(src.m_size) {

        src.m_members = nullptr;
        src.m_bonusApplied = nullptr;
        src.m_size = 0;
    }

    Guild& Guild::operator=(Guild&& src) noexcept {
        if (this != &src) {
            clear();

            m_name = std::move(src.m_name);
            m_members = src.m_members;
            m_bonusApplied = src.m_bonusApplied;
            m_size = src.m_size;

            src.m_members = nullptr;
            src.m_bonusApplied = nullptr;
            src.m_size = 0;
        }

        return *this;
    }

    void Guild::swap(Guild& other) noexcept {
        using std::swap;

        swap(m_name, other.m_name);
        swap(m_members, other.m_members);
        swap(m_bonusApplied, other.m_bonusApplied);
        swap(m_size, other.m_size);
    }

    void Guild::addMember(Character* character) {
        if (character == nullptr) {
            return;
        }

        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == character->getName()) {
                return;
            }
        }

        Character** newMembers = new Character * [m_size + 1];
        bool* newBonusApplied = nullptr;

        try {
            newBonusApplied = new bool[m_size + 1];
        }
        catch (...) {
            delete[] newMembers;
            throw;
        }

        for (std::size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i];
            newBonusApplied[i] = m_bonusApplied[i];
        }

        newMembers[m_size] = character;
        newBonusApplied[m_size] = true;

        delete[] m_members;
        delete[] m_bonusApplied;

        m_members = newMembers;
        m_bonusApplied = newBonusApplied;

        ++m_size;

        character->setHealthMax(
            character->getHealthMax() + 300
        );
    }

    void Guild::removeMember(const std::string& name) {
        std::size_t index = 0;

        while (index < m_size &&
            m_members[index]->getName() != name) {
            ++index;
        }

        if (index == m_size) {
            return;
        }

        if (m_bonusApplied[index]) {
            m_members[index]->setHealthMax(
                m_members[index]->getHealthMax() - 300
            );
        }

        for (std::size_t i = index; i + 1 < m_size; ++i) {
            m_members[i] = m_members[i + 1];
            m_bonusApplied[i] = m_bonusApplied[i + 1];
        }

        --m_size;

        if (m_size == 0) {
            delete[] m_members;
            delete[] m_bonusApplied;

            m_members = nullptr;
            m_bonusApplied = nullptr;
        }
    }

    Character* Guild::operator[](std::size_t index) const {
        if (index >= m_size) {
            return nullptr;
        }

        return m_members[index];
    }

    void Guild::showMembers() const {
        if (m_name.empty()) {
            std::cout << "No guild.\n";
            return;
        }

        std::cout << "[Guild] " << m_name << '\n';

        for (std::size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": "
                << *m_members[i] << '\n';
        }
    }

}