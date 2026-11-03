/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026
*/
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <string>
#include <cstddef>
#include "character.h"

namespace seneca {

    class Team {
        std::string m_name;
        Character** m_members{};
        std::size_t m_size{};

        void clear();
        void copyFrom(const Team& src);

    public:
        Team(const char* name = "");
        ~Team();

        Team(const Team& src);
        Team& operator=(const Team& src);

        Team(Team&& src) noexcept;
        Team& operator=(Team&& src) noexcept;

        void swap(Team& other) noexcept;

        void addMember(const Character* character);
        void removeMember(const std::string& name);

        Character* operator[](std::size_t index) const;

        void showMembers() const;
    };

}

#endif