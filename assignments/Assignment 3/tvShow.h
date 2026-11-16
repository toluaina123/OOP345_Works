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

#include "mediaItem.h"
#include <list>
#include <string>

namespace seneca {

    class TvShow;

    struct TvEpisode {
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

        std::string m_id;
        std::list<TvEpisode> m_episodes;

        TvShow(
            const std::string& id,
            const std::string& title,
            unsigned short year,
            const std::string& summary
        );

    public:
        void display(std::ostream& out) const override;

        static TvShow* createItem(const std::string& strShow);

        template<typename Collection_t>
        static void addEpisode(
            Collection_t& col,
            const std::string& strEpisode
        );

        double getEpisodeAverageLength() const;

        std::list<std::string> getLongEpisodes() const;
    };

}

#endif
