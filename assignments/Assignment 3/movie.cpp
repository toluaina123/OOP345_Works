#include "movie.h"
#include "settings.h"
#include "csvUtils.h"
#include <iomanip>
namespace seneca {
	Movie::Movie(const std::string& t, unsigned short y, const std::string& s) :MediaItem(t, s, y) {}
	Movie* Movie::createItem(const std::string& line) {
		if (trimToken(line).empty() || trimToken(line)[0] == '#') throw "Not a valid movie.";
		auto f = splitCSV(line); if (f.size() != 3) throw "Not a valid movie.";
		try { return new Movie(f[0], static_cast<unsigned short>(std::stoi(f[1])), f[2]); }
		catch (...) { throw "Not a valid movie."; }
	}
	void Movie::display(std::ostream& out) const {
		if (g_settings.m_tableView) { out << "M | " << std::left << std::setfill('.') << std::setw(50) << getTitle() << " | " << std::right << std::setfill(' ') << std::setw(9) << getYear() << " | " << std::left; auto s = getSummary(); if (g_settings.m_maxSummaryWidth > -1 && s.size() > static_cast<size_t>(g_settings.m_maxSummaryWidth)) s = s.substr(0, g_settings.m_maxSummaryWidth - 3) + "..."; out << s << std::endl; }
		else { auto t = getTitle(), s = getSummary(); out << t << " [" << getYear() << "]\n" << std::setw(t.size() + 7) << std::setfill('-') << "" << '\n' << std::setfill(' '); for (size_t p = 0; p < s.size(); p += g_settings.m_maxSummaryWidth) out << "    " << s.substr(p, g_settings.m_maxSummaryWidth) << '\n'; out << std::setw(t.size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n'; }
	}
}
