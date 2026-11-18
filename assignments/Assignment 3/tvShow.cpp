
/*
Name: Toluwani Aina
Course: OOP345

Ownership and Borrowing:
TvShow owns its ID string and stores episodes by value.
Each TvEpisode::m_show pointer borrows its parent TvShow.
Collection pointers are borrowed during episode lookup.
No ownership of the parent show transfers to an episode.
*/
#include "tvShow.h"
#include "settings.h"
#include "csvUtils.h"
#include "collection.h"

#include <iomanip>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

namespace seneca {

    TvShow::TvShow(
        const std::string& id,
        const std::string& title,
        unsigned short year,
        const std::string& summary
    )
        : MediaItem(title, summary, year),
        m_id(id) {}

    TvShow* TvShow::createItem(const std::string& strShow) {

        std::string trimmed = trimToken(strShow);

        if (trimmed.empty() || trimmed[0] == '#') {
            throw "Not a valid show.";
        }

        std::vector<std::string> fields = splitCSV(strShow);

        if (fields.size() != 4) {
            throw "Not a valid show.";
        }

        try {
            return new TvShow(
                fields[0],
                fields[1],
                static_cast<unsigned short>(std::stoi(fields[2])),
                fields[3]
            );
        }
        catch (...) {
            throw "Not a valid show.";
        }
    }

    template<typename Collection_t>
    void TvShow::addEpisode(
        Collection_t& col,
        const std::string& strEpisode
    ) {

        std::string trimmed = trimToken(strEpisode);

        if (trimmed.empty() || trimmed[0] == '#') {
            return;
        }

        std::vector<std::string> fields = splitCSV(strEpisode);

        if (fields.size() != 8) {
            throw "Not a valid episode.";
        }

        try {
            TvEpisode episode{};

            episode.m_numberOverall =
                static_cast<unsigned short>(std::stoi(fields[1]));

            episode.m_season = fields[2].empty()
                ? 1
                : static_cast<unsigned short>(std::stoi(fields[2]));

            episode.m_numberInSeason = fields[3].empty()
                ? 0
                : static_cast<unsigned short>(std::stoi(fields[3]));

            episode.m_airDate = fields[4];

            unsigned int hours = 0;
            unsigned int minutes = 0;
            unsigned int seconds = 0;

            const std::string& length = fields[5];

            if (length.size() >= 8) {
                hours = static_cast<unsigned int>(
                    std::stoul(length.substr(0, 2))
                    );

                minutes = static_cast<unsigned int>(
                    std::stoul(length.substr(3, 2))
                    );

                seconds = static_cast<unsigned int>(
                    std::stoul(length.substr(6, 2))
                    );
            }

            episode.m_length =
                hours * 3600 + minutes * 60 + seconds;

            episode.m_title = fields[6];
            episode.m_summary = fields[7];

            bool found = false;

            for (unsigned int i = 0; i < col.size(); ++i) {

                auto* show = dynamic_cast<TvShow*>(col[i]);

                if (show && show->m_id == fields[0]) {
                    episode.m_show = show;
                    show->m_episodes.push_back(episode);
                    found = true;
                    break;
                }
            }

            if (!found) {
                throw std::string(
                    "Episode belongs to a show not in the collection: "
                ) + fields[0] + ".";
            }
        }
        catch (const std::string&) {
            throw;
        }
        catch (...) {
            throw "Not a valid episode.";
        }
    }

    template void TvShow::addEpisode<Collection>(
        Collection&,
        const std::string&
    );

    void TvShow::display(std::ostream& out) const {

        if (g_settings.m_tableView) {

            out << "S | "
                << std::left << std::setfill('.')
                << std::setw(50) << getTitle()
                << " | "
                << std::right << std::setfill(' ')
                << std::setw(2) << m_episodes.size()
                << " | "
                << std::setw(4) << getYear()
                << " | "
                << std::left;

            std::string summary = getSummary();

            if (g_settings.m_maxSummaryWidth >= 3 &&
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

            if (g_settings.m_maxSummaryWidth > 0) {
                for (size_t i = 0; i < summary.size();
                    i += g_settings.m_maxSummaryWidth) {

                    out << "    "
                        << summary.substr(
                            i, g_settings.m_maxSummaryWidth
                        )
                        << '\n';
                }
            }

            for (const auto& episode : m_episodes) {

                out << std::setfill('0') << std::right
                    << "    S"
                    << std::setw(2) << episode.m_season
                    << 'E'
                    << std::setw(2) << episode.m_numberInSeason
                    << ' ';

                if (episode.m_title.empty()) {
                    out << "Episode "
                        << episode.m_numberOverall;
                }
                else {
                    out << episode.m_title;
                }

                out << '\n';

                if (g_settings.m_maxSummaryWidth > 8) {
                    for (size_t i = 0;
                        i < episode.m_summary.size();
                        i += g_settings.m_maxSummaryWidth - 8) {

                        out << "            "
                            << episode.m_summary.substr(
                                i, g_settings.m_maxSummaryWidth - 8
                            )
                            << '\n';
                    }
                }
            }

            out << std::setw(title.size() + 7)
                << std::setfill('-') << ""
                << std::setfill(' ')
                << '\n';
        }
    }

    double TvShow::getEpisodeAverageLength() const {

        if (m_episodes.empty()) {
            return 0.0;
        }

        auto total = std::accumulate(
            m_episodes.begin(),
            m_episodes.end(),
            0ULL,
            [](unsigned long long sum, const TvEpisode& episode) {
                return sum + episode.m_length;
            }
        );

        return static_cast<double>(total) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const {

        std::list<TvEpisode> longEpisodes;

        std::copy_if(
            m_episodes.begin(),
            m_episodes.end(),
            std::back_inserter(longEpisodes),
            [](const TvEpisode& episode) {
                return episode.m_length >= 3600;
            }
        );

        std::list<std::string> titles;

        std::transform(
            longEpisodes.begin(),
            longEpisodes.end(),
            std::back_inserter(titles),
            [](const TvEpisode& episode) {
                return episode.m_title.empty()
                    ? "Episode " + std::to_string(
                        episode.m_numberOverall
                    )
                    : episode.m_title;
            }
        );

        return titles;
    }

}
