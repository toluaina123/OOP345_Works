/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026
*/
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include <cstddef>
#include "character.h"

namespace seneca {

    class Guild {
        std::string m_name;
        Character** m_members{};
        std::size_t m_size{};

        void clear();
        void copyFrom(const Guild& src);

    public:
        Guild(const char* name = "");

        ~Guild();

        Guild(const Guild& src);
        Guild& operator=(const Guild& src);

        Guild(Guild&& src) noexcept;
        Guild& operator=(Guild&& src) noexcept;

        void swap(Guild& other) noexcept;

        void addMember(Character* character);
        void removeMember(const std::string& name);

        Character* operator[](std::size_t index) const;

        void showMembers() const;
    };

}

#endif