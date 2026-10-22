/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: October 20, 2026
*/
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <string>
#include <utility>
#include "character.h"

namespace seneca {
    class Team {
        std::string m_name;
        Character** m_members{};
        int m_size{};

        void clear() {
            for (int i = 0; i < m_size; ++i) {
                delete m_members[i];
            }

            delete[] m_members;
            m_members = nullptr;
            m_size = 0;
        }

        void copyFrom(const Team& src) {
            if (src.m_size == 0) return;

            m_members = new Character * [src.m_size] {};

            for (int i = 0; i < src.m_size; ++i) {
                m_members[i] = src.m_members[i]->clone();
                ++m_size;
            }
        }

    public:
        Team(const char* name = "")
            : m_name(name ? name : "") {
        }

        ~Team() {
            clear();
        }

        Team(const Team& src)
            : m_name(src.m_name) {
            copyFrom(src);
        }

        Team& operator=(const Team& src) {
            if (this != &src) {
                Team temp(src);
                swap(temp);
            }
            return *this;
        }

        Team(Team&& src) noexcept
            : m_name(std::move(src.m_name)),
            m_members(src.m_members),
            m_size(src.m_size) {
            src.m_members = nullptr;
            src.m_size = 0;
        }

        Team& operator=(Team&& src) noexcept {
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

        void swap(Team& other) noexcept {
            using std::swap;
            swap(m_name, other.m_name);
            swap(m_members, other.m_members);
            swap(m_size, other.m_size);
        }

        void addMember(const Character* character) {
            if (!character) return;

            for (int i = 0; i < m_size; ++i) {
                if (m_members[i]->getName() == character->getName()) {
                    return;
                }
            }

            Character** next = new Character * [m_size + 1];

            for (int i = 0; i < m_size; ++i) {
                next[i] = m_members[i];
            }

            next[m_size] = character->clone();

            delete[] m_members;
            m_members = next;
            ++m_size;
        }

        void removeMember(const std::string& name) {
            int i = 0;

            while (i < m_size &&
                m_members[i]->getName() != name) {
                ++i;
            }

            if (i == m_size) return;

            delete m_members[i];

            for (; i < m_size - 1; ++i) {
                m_members[i] = m_members[i + 1];
            }

            --m_size;

            if (m_size == 0) {
                delete[] m_members;
                m_members = nullptr;
            }
        }

        Character* operator[](int index) const {
            if (index < 0 || index >= m_size) {
                return nullptr;
            }

            return m_members[index];
        }

        void showMembers() const {
            std::cout << "Team: " << m_name << '\n';

            for (int i = 0; i < m_size; ++i) {
                std::cout << "    " << *m_members[i] << '\n';
            }
        }
    };
}
#endif