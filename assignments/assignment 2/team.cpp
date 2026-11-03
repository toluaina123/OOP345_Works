/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

Implementation developed with AI assistance.
*/

#include "team.h"
#include <utility>

namespace seneca {

    Team::Team(const char* name)
        : m_name(name ? name : "") {}

    Team::~Team() {
        clear();
    }

    void Team::clear() {
        for (std::size_t i = 0; i < m_size; ++i) {
            delete m_members[i];
        }

        delete[] m_members;
        m_members = nullptr;
        m_size = 0;
    }

    void Team::copyFrom(const Team& src) {
        if (src.m_size == 0) {
            return;
        }

        m_members = new Character * [src.m_size] {};

        try {
            for (std::size_t i = 0; i < src.m_size; ++i) {
                m_members[i] = src.m_members[i]->clone();
                ++m_size;
            }
        }
        catch (...) {
            clear();
            throw;
        }
    }

    Team::Team(const Team& src)
        : m_name(src.m_name) {
        copyFrom(src);
    }

    Team& Team::operator=(const Team& src) {
        if (this != &src) {
            Team temp(src);
            swap(temp);
        }

        return *this;
    }

    Team::Team(Team&& src) noexcept
        : m_name(std::move(src.m_name)),
        m_members(src.m_members),
        m_size(src.m_size) {

        src.m_members = nullptr;
        src.m_size = 0;
    }

    Team& Team::operator=(Team&& src) noexcept {
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

    void Team::swap(Team& other) noexcept {
        using std::swap;

        swap(m_name, other.m_name);
        swap(m_members, other.m_members);
        swap(m_size, other.m_size);
    }

    void Team::addMember(const Character* character) {
        if (!character) {
            return;
        }

        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == character->getName()) {
                return;
            }
        }

        Character* newMember = character->clone();

        Character** temp = new Character * [m_size + 1];

        for (std::size_t i = 0; i < m_size; ++i) {
            temp[i] = m_members[i];
        }

        temp[m_size] = newMember;

        delete[] m_members;

        m_members = temp;
        ++m_size;
    }

    void Team::removeMember(const std::string& name) {
        std::size_t index = 0;

        while (index < m_size &&
            m_members[index]->getName() != name) {
            ++index;
        }

        if (index == m_size) {
            return;
        }

        delete m_members[index];

        for (std::size_t i = index; i < m_size - 1; ++i) {
            m_members[i] = m_members[i + 1];
        }

        --m_size;

        if (m_size == 0) {
            delete[] m_members;
            m_members = nullptr;
        }
    }

    Character* Team::operator[](std::size_t index) const {
        if (index >= m_size) {
            return nullptr;
        }

        return m_members[index];
    }

    void Team::showMembers() const {
        std::cout << "[Team] " << m_name << '\n';

        if (m_size == 0) {
            std::cout << "No team." << '\n';
            return;
        }

        for (std::size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": "
                << *m_members[i] << '\n';
        }
    }

}