
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

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <iostream>
#include <string>
#include "mediaItem.h"
namespace seneca {
    class Book : public MediaItem {
        std::string m_author{};
        std::string m_country{};
        double m_price{};
        Book(const std::string& author, const std::string& title, const std::string& country,
            double price, unsigned short year, const std::string& summary);
    public:
        void display(std::ostream& out) const override;
        static Book* createItem(const std::string& strBook);
    };
}
#endif