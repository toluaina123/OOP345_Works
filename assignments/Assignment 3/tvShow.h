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
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <list>
#include <string>
#include <vector>
#include "mediaItem.h"
#include "util.h"

namespace seneca {

    class TvShow;

    struct TvEpisode
    {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem {
        std::string m_id{};
        std::list<TvEpisode> m_episodes{};

        TvShow(const std::string& id, const std::string& title,
            unsigned short year, const std::string& summary);


        static unsigned int toSeconds(const std::string& text);

    public:
        void display(std::ostream& out) const override;

        static TvShow* createItem(const std::string& strShow);

        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode)
        {
            std::string trimmed = trimToken(strEpisode);
            if (trimmed.empty() || trimmed[0] == '#') {
                throw "Not a valid episode.";
            }


            std::vector<std::string> f;
            size_t start = 0;
            while (f.size() < 7) {
                size_t c = trimmed.find(',', start);
                if (c == std::string::npos) break;
                f.push_back(trimToken(trimmed.substr(start, c - start)));
                start = c + 1;
            }
            f.push_back(trimToken(trimmed.substr(start)));

            if (f.size() != 8) {
                throw "Not a valid episode.";
            }

            TvEpisode ep{};
            try {
                ep.m_numberOverall = static_cast<unsigned short>(std::stoi(f[1]));
                ep.m_season = f[2].empty() ? 1
                    : static_cast<unsigned short>(std::stoi(f[2]));
                ep.m_numberInSeason = f[3].empty() ? 0
                    : static_cast<unsigned short>(std::stoi(f[3]));
                ep.m_airDate = f[4];
                ep.m_length = toSeconds(f[5]);
                ep.m_title = f[6];
                ep.m_summary = f[7];
            }
            catch (...) {
                throw "Not a valid episode.";
            }

            for (size_t i = 0; i < col.size(); ++i) {
                TvShow* show = dynamic_cast<TvShow*>(col[i]);
                if (show && show->m_id == f[0]) {
                    ep.m_show = show;
                    show->m_episodes.push_back(ep);
                    return;
                }
            }

            throw std::string("Episode belongs to a show not in the collection: ")
                + f[0] + ".";
        }

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };

}

#endif