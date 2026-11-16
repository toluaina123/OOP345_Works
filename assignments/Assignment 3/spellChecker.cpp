#include "spellChecker.h"
#include <fstream>
#include <iomanip>
namespace seneca {
	SpellChecker::SpellChecker(const char* filename) { std::ifstream f(filename); if (!f) throw "Bad file name!"; for (int i = 0; i<6 && f >> m_badWords[i] >> m_goodWords[i]; ++i) {} }
	void SpellChecker::operator()(std::string& text) { for (int i = 0; i < 6; ++i) { size_t p = 0; while ((p = text.find(m_badWords[i], p)) != std::string::npos) { text.replace(p, m_badWords[i].size(), m_goodWords[i]); p += m_goodWords[i].size(); ++m_counts[i]; } } }
	void SpellChecker::showStatistics(std::ostream& out) const { for (int i = 0; i < 6; ++i) out << std::right << std::setw(15) << m_badWords[i] << ": " << m_counts[i] << " replacements\n"; }
}
