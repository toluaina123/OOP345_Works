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
#include "movie.h"
#include "settings.h"
#include "util.h"

namespace seneca {

    Movie::Movie(const std::string& title, unsigned short year,
        const std::string& summary)
        : MediaItem(title, summary, year) {}

    Movie* Movie::createItem(const std::string& strMovie) {
        std::string trimmed = trimToken(strMovie);
        if (trimmed.empty() || trimmed[0] == '#') {
            throw "Not a valid movie.";
        }

        std::vector<std::string> fields = splitCSV(trimmed);
        if (fields.size() < 3) {
            throw "Not a valid movie.";
        }

        try {
            std::string summary = fields[2];
            for (size_t i = 3; i < fields.size(); ++i) {
                summary += ", " + fields[i];
            }
            return new Movie(fields[0],
                static_cast<unsigned short>(std::stoi(fields[1])),
                summary);
        }
        catch (...) {
            throw "Not a valid movie.";
        }
    }

    void Movie::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
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