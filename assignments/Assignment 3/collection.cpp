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
#include "collection.h"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <ostream>

namespace seneca {

    Collection::Collection(const std::string& name)
        : m_name(name) {}

    Collection::~Collection() {
        std::for_each(m_items.begin(), m_items.end(),
            [](MediaItem* p) {
                delete p;
            });
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

        auto it = std::find_if(
            m_items.begin(), m_items.end(),
            [item](MediaItem* p) {
                return p != nullptr &&
                    p->getTitle() == item->getTitle();
            });

        if (it != m_items.end()) {
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

    MediaItem* Collection::operator[](
        const std::string& title) const {

        auto it = std::find_if(
            m_items.begin(), m_items.end(),
            [title](MediaItem* p) {
                return p != nullptr &&
                    p->getTitle() == title;
            });

        return it == m_items.end() ? nullptr : *it;
    }

    void Collection::removeQuotes() {
        std::for_each(
            m_items.begin(), m_items.end(),
            [](MediaItem* p) {
                if (p != nullptr) {
                    std::string title = p->getTitle();
                    std::string summary = p->getSummary();

                    if (title.size() >= 2 &&
                        title.front() == '"' &&
                        title.back() == '"') {
                        p->setTitle(
                            title.substr(1, title.size() - 2));
                    }

                    if (summary.size() >= 2 &&
                        summary.front() == '"' &&
                        summary.back() == '"') {
                        p->setSummary(
                            summary.substr(1, summary.size() - 2));
                    }
                }
            });
    }

    void Collection::sort(const std::string& field) {
        if (field == "title") {
            std::sort(
                m_items.begin(), m_items.end(),
                [](MediaItem* a, MediaItem* b) {
                    if (!a) return false;
                    if (!b) return true;
                    return a->getTitle() < b->getTitle();
                });
        }
        else if (field == "year") {
            std::sort(
                m_items.begin(), m_items.end(),
                [](MediaItem* a, MediaItem* b) {
                    if (!a) return false;
                    if (!b) return true;
                    return a->getYear() < b->getYear();
                });
        }
    }

    std::ostream& operator<<(
        std::ostream& out, const Collection& col) {

        std::for_each(
            col.m_items.begin(), col.m_items.end(),
            [&out](MediaItem* p) {
                if (p != nullptr) {
                    p->display(out);
                }
            });

        return out;
    }

}