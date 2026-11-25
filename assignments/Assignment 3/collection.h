/*
Name: Toluwani Aina
Course: OOP345

I confirm that I completed this assignment independently.
I wrote and implemented the submitted code myself.

Ownership and Borrowing:
All dynamically allocated resources are managed according to
their ownership responsibilities. Non-owning pointers and
references are borrowed and are not deleted by the borrowing
object.

Any external resources or references used are acknowledged
where applicable.
*/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>
#include <string>
#include <vector>
#include "mediaItem.h"
namespace seneca {
    class Collection {
        std::string m_name{};
        std::vector<MediaItem*> m_items{};
        void (*m_observer)(const Collection&, const MediaItem&) {};
    public:
        Collection(const std::string& name);
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;
        ~Collection();

        const std::string& name() const;
        size_t size() const;
        void setObserver(void (*observer)(const Collection&, const MediaItem&));
        Collection& operator+=(MediaItem* item);
        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;
        void removeQuotes();
        void sort(const std::string& field);
    };
    std::ostream& operator<<(std::ostream& out, const Collection& col);
}
#endif