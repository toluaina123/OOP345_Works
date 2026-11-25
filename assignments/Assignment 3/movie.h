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


#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include <iostream>
#include <string>
#include "mediaItem.h"
namespace seneca {
    class Movie : public MediaItem {
        Movie(const std::string& title, unsigned short year, const std::string& summary);
    public:
        void display(std::ostream& out) const override;
        static Movie* createItem(const std::string& strMovie);
    };
}
#endif