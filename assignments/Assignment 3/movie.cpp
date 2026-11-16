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
#include "movie.h"
#include "settings.h"
#include "csvUtils.h"

#include <iomanip>
#include <string>
#include <vector>

namespace seneca {

    Movie::Movie(
        const std::string& title,
        unsigned short year,
        const std::string& summary)
        : MediaItem(title, summary, year) {}

    Movie* Movie::createItem(const std::string& line) {

        std::string trimmed = trimToken(line);

        if (trimmed.empty() || trimmed[0] == '#') {
            throw "Not a valid movie.";
        }

        std::vector<std::string> fields = splitCSV(line);

        if (fields.size() < 3) {
            throw "Not a valid movie.";
        }

        try {
            std::string summary = fields[2];

            for (size_t i = 3; i < fields.size(); ++i) {
                summary += ", " + fields[i];
            }

            return new Movie(
                fields[0],
                static_cast<unsigned short>(std::stoi(fields[1])),
                summary
            );
        }
        catch (...) {
            throw "Not a valid movie.";
        }
    }

    void Movie::display(std::ostream& out) const {

        if (g_settings.m_tableView) {

            out << "M | "
                << std::left << std::setfill('.')
                << std::setw(50) << getTitle()
                << " | "
                << std::right << std::setfill(' ')
                << std::setw(9) << getYear()
                << " | "
                << std::left;

            std::string summary = getSummary();

            if (g_settings.m_maxSummaryWidth > -1 &&
                summary.size() >
                static_cast<size_t>(g_settings.m_maxSummaryWidth)) {

                summary = summary.substr(
                    0,
                    g_settings.m_maxSummaryWidth - 3
                ) + "...";
            }

            out << summary << std::endl;
        }
        else {

            std::string title = getTitle();
            std::string summary = getSummary();

            out << title << " [" << getYear() << "]\n";

            out << std::setw(title.size() + 7)
                << std::setfill('-') << ""
                << '\n'
                << std::setfill(' ');

            for (size_t i = 0;
                i < summary.size();
                i += g_settings.m_maxSummaryWidth) {

                out << "    "
                    << summary.substr(
                        i,
                        g_settings.m_maxSummaryWidth
                    )
                    << '\n';
            }

            out << std::setw(title.size() + 7)
                << std::setfill('-') << ""
                << std::setfill(' ')
                << '\n';
        }
    }

}
