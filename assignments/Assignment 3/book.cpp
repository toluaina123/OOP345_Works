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

#include <iomanip>
#include <string>
#include <vector>
#include "book.h"
#include "settings.h"
#include "util.h"

namespace seneca {

    Book::Book(const std::string& author, const std::string& title,
        const std::string& country, double price,
        unsigned short year, const std::string& summary)
        : MediaItem(title, summary, year),
        m_author(author), m_country(country), m_price(price) {}

    Book* Book::createItem(const std::string& strBook) {
        std::string trimmed = trimToken(strBook);
        if (trimmed.empty() || trimmed[0] == '#') {
            throw "Not a valid book.";
        }

        std::vector<std::string> fields = splitCSV(trimmed);
        if (fields.size() < 6) {
            throw "Not a valid book.";
        }

        try {
            std::string summary = fields[5];
            for (size_t i = 6; i < fields.size(); ++i) {
                summary += ", " + fields[i];
            }
            return new Book(fields[0], fields[1], fields[2],
                std::stod(fields[3]),
                static_cast<unsigned short>(std::stoi(fields[4])),
                summary);
        }
        catch (...) {
            throw "Not a valid book.";
        }
    }

    void Book::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

}