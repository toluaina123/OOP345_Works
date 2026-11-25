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
#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <string>
#include "collection.h"

namespace seneca {

    Collection::Collection(const std::string& name) : m_name(name) {}

    Collection::~Collection() {
        for (MediaItem* item : m_items) {
            delete item;
        }
    }

    const std::string& Collection::name() const {
        return m_name;
    }

    size_t Collection::size() const {
        return m_items.size();
    }

    void Collection::setObserver(
        void (*observer)(const Collection&, const MediaItem&)) {
        m_observer = observer;
    }

    Collection& Collection::operator+=(MediaItem* item) {
        if (item == nullptr) {
            return *this;
        }

        bool duplicate = false;
        for (size_t i = 0; i < m_items.size() && !duplicate; ++i) {
            duplicate = (m_items[i]->getTitle() == item->getTitle());
        }

        if (duplicate) {
            delete item;
        }
        else {
            m_items.push_back(item);
            if (m_observer) {
                m_observer(*this, *item);
            }
        }
        return *this;
    }

    MediaItem* Collection::operator[](size_t idx) const {
        if (idx >= m_items.size()) {
            throw std::out_of_range(
                "Bad index [" + std::to_string(idx) +
                "]. Collection has [" +
                std::to_string(m_items.size()) + "] items.");
        }
        return m_items[idx];
    }

    MediaItem* Collection::operator[](const std::string& title) const {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [title](const MediaItem* p) {
                return p->getTitle() == title;
            });
        return it == m_items.end() ? nullptr : *it;
    }

    void Collection::removeQuotes() {
        std::for_each(m_items.begin(), m_items.end(),
            [](MediaItem* p) {
                std::string title = p->getTitle();
                std::string summary = p->getSummary();

                if (!title.empty() && title.front() == '"') title.erase(0, 1);
                if (!title.empty() && title.back() == '"') title.pop_back();
                if (!summary.empty() && summary.front() == '"') summary.erase(0, 1);
                if (!summary.empty() && summary.back() == '"') summary.pop_back();

                p->setTitle(title);
                p->setSummary(summary);
            });
    }

    void Collection::sort(const std::string& field) {
        if (field == "title") {
            std::sort(m_items.begin(), m_items.end(),
                [](const MediaItem* a, const MediaItem* b) {
                    return a->getTitle() < b->getTitle();
                });
        }
        else if (field == "year") {
            std::sort(m_items.begin(), m_items.end(),
                [](const MediaItem* a, const MediaItem* b) {
                    return a->getYear() < b->getYear();
                });
        }
    }

    std::ostream& operator<<(std::ostream& out, const Collection& col) {
        for (size_t i = 0; i < col.size(); ++i) {
            col[i]->display(out);
        }
        return out;
    }

}