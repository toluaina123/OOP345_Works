#include "book.h"
#include "settings.h"
#include "csvUtils.h"

#include <iostream>
#include <iomanip>
#include <string>

namespace seneca {

    Book::Book(
        const std::string& author,
        const std::string& title,
        const std::string& country,
        double price,
        unsigned short year,
        const std::string& summary)
        : MediaItem(title, summary, year),
        m_author(author),
        m_country(country),
        m_price(price) {}

    Book* Book::createItem(const std::string& strBook) {

        if (trimToken(strBook).empty() || trimToken(strBook)[0] == '#') {
            throw "Not a valid book.";
        }

        std::vector<std::string> fields = splitCSV(strBook);

        if (fields.size() != 6) {
            throw "Not a valid book.";
        }

        try {
            return new Book(
                fields[0],
                fields[1],
                fields[2],
                std::stod(fields[3]),
                static_cast<unsigned short>(std::stoi(fields[4])),
                fields[5]
            );
        }
        catch (...) {
            throw "Not a valid book.";
        }
    }

    void Book::display(std::ostream& out) const {

        if (g_settings.m_tableView) {

            out << "B | "
                << std::left << std::setfill('.')
                << std::setw(50) << getTitle()
                << " | "
                << std::right << std::setfill(' ')
                << std::setw(2) << m_country
                << " | "
                << std::setw(4) << getYear()
                << " | "
                << std::left;

            std::string summary = getSummary();

            if (g_settings.m_maxSummaryWidth > -1 &&
                summary.size() > static_cast<size_t>(g_settings.m_maxSummaryWidth)) {

                summary = summary.substr(
                    0, g_settings.m_maxSummaryWidth - 3
                ) + "...";
            }

            out << summary << std::endl;
        }
        else {

            std::string title = getTitle();
            std::string summary = getSummary();

            out << title << " [" << getYear() << "] "
                << "[" << m_author << "] "
                << "[" << m_country << "] "
                << "[" << m_price << "]\n";

            out << std::setw(title.size() + 7)
                << std::setfill('-') << ""
                << '\n' << std::setfill(' ');

            for (size_t i = 0; i < summary.size();
                i += g_settings.m_maxSummaryWidth) {

                out << "    "
                    << summary.substr(i, g_settings.m_maxSummaryWidth)
                    << '\n';
            }

            out << std::setw(title.size() + 7)
                << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

}