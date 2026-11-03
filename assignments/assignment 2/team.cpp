/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

*/

#include "team.h"
#include <iostream>
#include <memory>
#include <utility>

namespace seneca {

    Team::Team()
        : m_name(""), m_members(nullptr), m_size(0) {}

    Team::Team(const char* name)
        : m_name(name ? name : ""), m_members(nullptr), m_size(0) {}

    Team::~Team() {
        clear();
    }

    void Team::clear() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i];
        }

        delete[] m_members;
        m_members = nullptr;
        m_size = 0;
    }

    void Team::copyFrom(const Team& other) {
        if (other.m_size == 0) {
            return;
        }

        m_members = new Character * [other.m_size] {};

        try {
            for (size_t i = 0; i < other.m_size; ++i) {
                m_members[i] = other.m_members[i]->clone();
                ++m_size;
            }
        }
        catch (...) {
            clear();
            throw;
        }
    }

    Team::Team(const Team& other)
        : m_name(other.m_name), m_members(nullptr), m_size(0) {
        copyFrom(other);
    }

    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            Team temp(other);
            swap(temp);
        }

        return *this;
    }

    Team::Team(Team&& other) noexcept
        : m_name(std::move(other.m_name)),
        m_members(other.m_members),
        m_size(other.m_size) {

        other.m_members = nullptr;
        other.m_size = 0;
    }

    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            clear();

            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_size = other.m_size;

            other.m_members = nullptr;
            other.m_size = 0;
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
        if (character == nullptr) {
            return;
        }

        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == character->getName()) {
                return;
            }
        }

        std::unique_ptr<Character> newMember(character->clone());

        Character** newMembers = new Character * [m_size + 1];

        for (size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i];
        }

        newMembers[m_size] = newMember.get();

        delete[] m_members;
        m_members = newMembers;
        ++m_size;

        newMember.release();
    }

    void Team::removeMember(const std::string& name) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == name) {
                delete m_members[i];

                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }

                --m_size;

                if (m_size == 0) {
                    delete[] m_members;
                    m_members = nullptr;
                }

                return;
            }
        }
    }

    Character* Team::operator[](size_t index) const {
        if (index >= m_size) {
            return nullptr;
        }

        return m_members[index];
    }

    void Team::showMembers() const {
        if (m_size == 0) {
            std::cout << "No team." << std::endl;
            return;
        }

        std::cout << "[Team] " << m_name << std::endl;

        for (size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": "
                << *m_members[i] << std::endl;
        }
    }

}