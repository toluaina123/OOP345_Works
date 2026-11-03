/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

*/

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>
#include <cstddef>

namespace seneca {

    class Team {
        std::string m_name;
        Character** m_members;
        size_t m_size;

        void clear();
        void copyFrom(const Team& other);
        void swap(Team& other) noexcept;

    public:
        Team();
        Team(const char* name);

        ~Team();

        Team(const Team& other);
        Team& operator=(const Team& other);

        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;

        void addMember(const Character* character);
        void removeMember(const std::string& name);

        Character* operator[](size_t index) const;

        void showMembers() const;
    };

}

#endif