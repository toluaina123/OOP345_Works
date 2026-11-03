/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

Implementation developed with AI assistance.
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
            m_members[i]->setHealthMax(
                m_members[i]->getHealthMax() - 300
            );
        }

        delete[] m_members;
        m_members = nullptr;
        m_size = 0;
    }

    void Guild::copyFrom(const Guild& src) {
        if (src.m_size == 0) {
            return;
        }

        m_members = new Character * [src.m_size];

        for (std::size_t i = 0; i < src.m_size; ++i) {
            m_members[i] = src.m_members[i];

            m_members[i]->setHealthMax(
                m_members[i]->getHealthMax() + 300
            );

            ++m_size;
        }
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
        m_size(src.m_size) {

        src.m_members = nullptr;
        src.m_size = 0;
    }

    Guild& Guild::operator=(Guild&& src) noexcept {
        if (this != &src) {
            clear();

            m_name = std::move(src.m_name);
            m_members = src.m_members;
            m_size = src.m_size;

            src.m_members = nullptr;
            src.m_size = 0;
        }

        return *this;
    }

    void Guild::swap(Guild& other) noexcept {
        using std::swap;

        swap(m_name, other.m_name);
        swap(m_members, other.m_members);
        swap(m_size, other.m_size);
    }

    void Guild::addMember(Character* character) {
        if (!character) {
            return;
        }

        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == character->getName()) {
                return;
            }
        }

        Character** temp = new Character * [m_size + 1];

        for (std::size_t i = 0; i < m_size; ++i) {
            temp[i] = m_members[i];
        }

        temp[m_size] = character;

        delete[] m_members;

        m_members = temp;
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

        m_members[index]->setHealthMax(
            m_members[index]->getHealthMax() - 300
        );

        for (std::size_t i = index; i < m_size - 1; ++i) {
            m_members[i] = m_members[i + 1];
        }

        --m_size;

        if (m_size == 0) {
            delete[] m_members;
            m_members = nullptr;
        }
    }

    Character* Guild::operator[](std::size_t index) const {
        if (index >= m_size) {
            return nullptr;
        }

        return m_members[index];
    }

    void Guild::showMembers() const {
        std::cout << "[Guild] " << m_name << '\n';

        if (m_size == 0) {
            std::cout << "No guild." << '\n';
            return;
        }

        for (std::size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": "
                << *m_members[i] << '\n';
        }
    }

}