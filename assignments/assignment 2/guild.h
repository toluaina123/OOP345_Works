/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: October 20, 2026
*/
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include <utility>
#include "character.h"

namespace seneca {
    class Guild {
        std::string m_name;
        Character** m_members{};
        int m_size{};

        void clear() {
            for (int i = 0; i < m_size; ++i) {
                m_members[i]->setHealthMax(
                    m_members[i]->getHealthMax() - 300
                );
            }

            delete[] m_members;
            m_members = nullptr;
            m_size = 0;
        }

        void copyFrom(const Guild& src) {
            if (src.m_size == 0) return;

            m_members = new Character * [src.m_size];

            for (int i = 0; i < src.m_size; ++i) {
                m_members[i] = src.m_members[i];
                ++m_size;
            }
        }

    public:
        Guild(const char* name = "")
            : m_name(name ? name : "") {
        }

        ~Guild() {
            clear();
        }

        Guild(const Guild& src)
            : m_name(src.m_name) {
            copyFrom(src);
        }

        Guild& operator=(const Guild& src) {
            if (this != &src) {
                Guild temp(src);
                swap(temp);
            }
            return *this;
        }

        Guild(Guild&& src) noexcept
            : m_name(std::move(src.m_name)),
            m_members(src.m_members),
            m_size(src.m_size) {
            src.m_members = nullptr;
            src.m_size = 0;
        }

        Guild& operator=(Guild&& src) noexcept {
            if (this != &src) {
                delete[] m_members;

                m_name = std::move(src.m_name);
                m_members = src.m_members;
                m_size = src.m_size;

                src.m_members = nullptr;
                src.m_size = 0;
            }
            return *this;
        }

        void swap(Guild& other) noexcept {
            using std::swap;
            swap(m_name, other.m_name);
            swap(m_members, other.m_members);
            swap(m_size, other.m_size);
        }

        void addMember(Character* character) {
            if (!character) return;

            for (int i = 0; i < m_size; ++i) {
                if (m_members[i]->getName() ==
                    character->getName()) {
                    return;
                }
            }

            Character** next = new Character * [m_size + 1];

            for (int i = 0; i < m_size; ++i) {
                next[i] = m_members[i];
            }

            next[m_size] = character;

            delete[] m_members;
            m_members = next;
            ++m_size;

            character->setHealthMax(
                character->getHealthMax() + 300
            );
        }

        void removeMember(const std::string& name) {
            int i = 0;

            while (i < m_size &&
                m_members[i]->getName() != name) {
                ++i;
            }

            if (i == m_size) return;

            m_members[i]->setHealthMax(
                m_members[i]->getHealthMax() - 300
            );

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
            std::cout << "Guild: " << m_name << '\n';

            for (int i = 0; i < m_size; ++i) {
                std::cout << "    " << *m_members[i] << '\n';
            }
        }
    };
}
#endif