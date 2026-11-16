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
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca {

    struct Settings {
        short m_maxSummaryWidth{ 80 };
        bool m_tableView{ false };
    };

    extern Settings g_settings;

}

#endif