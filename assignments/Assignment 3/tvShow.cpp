#include "tvShow.h"
#include "settings.h"
#include "csvUtils.h"
#include "collection.h"
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <stdexcept>
namespace seneca {
	TvShow::TvShow(const std::string& id, const std::string& t, unsigned short y, const std::string& s) :MediaItem(t, s, y), m_id(id) {}
	TvShow* TvShow::createItem(const std::string& line) {
		if (trimToken(line).empty() || trimToken(line)[0] == '#') throw "Not a valid show.";
		auto f = splitCSV(line); if (f.size() != 4) throw "Not a valid show.";
		try { return new TvShow(f[0], f[1], static_cast<unsigned short>(std::stoi(f[2])), f[3]); }
		catch (...) { throw "Not a valid show."; }
	}
	template<typename Collection_t> void TvShow::addEpisode(Collection_t& col, const std::string& line) {
		if (trimToken(line).empty() || trimToken(line)[0] == '#') throw "Not a valid episode.";
		auto f = splitCSV(line); if (f.size() != 8) throw "Not a valid episode.";
		try {
			TvEpisode ep{}; ep.m_numberOverall = static_cast<unsigned short>(std::stoi(f[1])); ep.m_season = f[2].empty() ? 1 : static_cast<unsigned short>(std::stoi(f[2])); ep.m_numberInSeason = f[3].empty() ? 0 : static_cast<unsigned short>(std::stoi(f[3])); ep.m_airDate = f[4];
			auto time = f[5]; unsigned h = 0, m = 0, s = 0; if (time.size() >= 8) { h = std::stoul(time.substr(0, 2)); m = std::stoul(time.substr(3, 2)); s = std::stoul(time.substr(6, 2)); } ep.m_length = h * 3600 + m * 60 + s;
			ep.m_title = f[6]; ep.m_summary = f[7];
			bool found = false; for (unsigned i = 0; i < col.size(); ++i) { auto* show = dynamic_cast<TvShow*>(col[i]); if (show && show->m_id == f[0]) { ep.m_show = show; show->m_episodes.push_back(ep); found = true; break; } }
			if (!found) throw std::string("Episode belongs to a show not in the collection: ") + f[0] + ".";
		}
		catch (const std::string&) { throw; }
		catch (...) { throw "Not a valid episode."; }
	}
	// Explicit instantiation for the assignment's Collection container.
	class Collection;
	template void TvShow::addEpisode<Collection>(Collection&, const std::string&);
	void TvShow::display(std::ostream& out) const {
		if (g_settings.m_tableView) { out << "S | " << std::left << std::setfill('.') << std::setw(50) << getTitle() << " | " << std::right << std::setfill(' ') << std::setw(2) << m_episodes.size() << " | " << std::setw(4) << getYear() << " | " << std::left; auto s = getSummary(); if (g_settings.m_maxSummaryWidth > -1 && s.size() > static_cast<size_t>(g_settings.m_maxSummaryWidth)) s = s.substr(0, g_settings.m_maxSummaryWidth - 3) + "..."; out << s << std::endl; }
		else {
			auto t = getTitle(), s = getSummary(); out << t << " [" << getYear() << "]\n" << std::setw(t.size() + 7) << std::setfill('-') << "" << '\n' << std::setfill(' '); for (size_t p = 0; p < s.size(); p += g_settings.m_maxSummaryWidth) out << "    " << s.substr(p, g_settings.m_maxSummaryWidth) << '\n';
			for (const auto& e : m_episodes) { out << std::setfill('0') << std::right << "    S" << std::setw(2) << e.m_season << 'E' << std::setw(2) << e.m_numberInSeason << ' '; out << (e.m_title.empty() ? "Episode " + std::to_string(e.m_numberOverall) : e.m_title) << '\n'; for (size_t p = 0; p < e.m_summary.size(); p += g_settings.m_maxSummaryWidth - 8) out << "            " << e.m_summary.substr(p, g_settings.m_maxSummaryWidth - 8) << '\n'; }
			out << std::setw(t.size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
		}
	}
	double TvShow::getEpisodeAverageLength() const { if (m_episodes.empty()) return 0.0; auto total = std::accumulate(m_episodes.begin(), m_episodes.end(), 0ULL, [](unsigned long long n, const TvEpisode& e) {return n + e.m_length; }); return static_cast<double>(total) / m_episodes.size(); }
	std::list<std::string> TvShow::getLongEpisodes() const { std::list<TvEpisode> longOnes; std::copy_if(m_episodes.begin(), m_episodes.end(), std::back_inserter(longOnes), [](const TvEpisode& e) {return e.m_length >= 3600; }); std::list<std::string> titles; std::transform(longOnes.begin(), longOnes.end(), std::back_inserter(titles), [](const TvEpisode& e) {return e.m_title.empty() ? "Episode " + std::to_string(e.m_numberOverall) : e.m_title; }); return titles; }
}
