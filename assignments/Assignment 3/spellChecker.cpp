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
#include "spellChecker.h"
#include <fstream>
#include <iomanip>
namespace seneca {
	SpellChecker::SpellChecker(const char* filename) { std::ifstream f(filename); if (!f) throw "Bad file name!"; for (int i = 0; i<6 && f >> m_badWords[i] >> m_goodWords[i]; ++i) {} }
	void SpellChecker::operator()(std::string& text) { for (int i = 0; i < 6; ++i) { size_t p = 0; while ((p = text.find(m_badWords[i], p)) != std::string::npos) { text.replace(p, m_badWords[i].size(), m_goodWords[i]); p += m_goodWords[i].size(); ++m_counts[i]; } } }
	void SpellChecker::showStatistics(std::ostream& out) const { for (int i = 0; i < 6; ++i) out << std::right << std::setw(15) << m_badWords[i] << ": " << m_counts[i] << " replacements\n"; }
}
