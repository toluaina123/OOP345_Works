
/*
Name: Toluwani Aina
Course: OOP345

Ownership and Borrowing:
TvShow owns its ID string and stores episodes by value.
Each TvEpisode::m_show pointer borrows its parent TvShow.
Collection pointers are borrowed during episode lookup.
No ownership of the parent show transfers to an episode.
*/
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#include "tvShow.h"
#include "settings.h"
#include "util.h"

namespace seneca {

    TvShow::TvShow(const std::string& id, const std::string& title,
        unsigned short year, const std::string& summary)
        : MediaItem(title, summary, year), m_id(id) {}

    unsigned int TvShow::toSeconds(const std::string& text)
    {

        if (text.size() != 8 || text[2] != ':' ||
            (text[5] != ':' && text[5] != '.')) {
            throw "Not a valid episode.";
        }
        unsigned int h = static_cast<unsigned int>(std::stoul(text.substr(0, 2)));
        unsigned int m = static_cast<unsigned int>(std::stoul(text.substr(3, 2)));
        unsigned int s = static_cast<unsigned int>(std::stoul(text.substr(6, 2)));
        return h * 3600 + m * 60 + s;
    }

    TvShow* TvShow::createItem(const std::string& strShow)
    {
        std::string trimmed = trimToken(strShow);
        if (trimmed.empty() || trimmed[0] == '#') {
            throw "Not a valid show.";
        }

        std::vector<std::string> fields = splitCSV(trimmed);
        if (fields.size() != 4) {
            throw "Not a valid show.";
        }

        try {
            return new TvShow(fields[0], fields[1],
                static_cast<unsigned short>(std::stoi(fields[2])),
                fields[3]);
        }
        catch (...) {
            throw "Not a valid show.";
        }
    }

    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    double TvShow::getEpisodeAverageLength() const
    {
        if (m_episodes.empty()) {
            return 0.0;
        }
        unsigned long long total = std::accumulate(
            m_episodes.begin(), m_episodes.end(), 0ULL,
            [](unsigned long long sum, const TvEpisode& e) {
                return sum + e.m_length;
            });
        return static_cast<double>(total) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const
    {
        std::list<TvEpisode> longEpisodes;
        std::copy_if(m_episodes.begin(), m_episodes.end(),
            std::back_inserter(longEpisodes),
            [](const TvEpisode& e) { return e.m_length >= 3600; });

        std::list<std::string> titles;
        std::transform(longEpisodes.begin(), longEpisodes.end(),
            std::back_inserter(titles),
            [](const TvEpisode& e) {
                return e.m_title.empty()
                    ? "Episode " + std::to_string(e.m_numberOverall)
                    : e.m_title;
            });
        return titles;
    }

}
