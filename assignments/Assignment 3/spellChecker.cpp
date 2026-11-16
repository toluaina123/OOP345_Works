
/*
Name: Toluwani Aina
Course: OOP345

I completed this assignment independently.

Ownership and Borrowing:
SpellChecker owns its arrays of strings and replacement
counters through value semantics. The filename passed to
the constructor is borrowed. The file stream is locally
owned and closes automatically when the constructor ends.
*/
#include "spellChecker.h"

#include <fstream>
#include <iomanip>
#include <cctype>

namespace seneca {

    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);

        if (!file) {
            throw "Bad file name!";
        }

        for (int i = 0; i < 6 && file >> m_badWords[i] >> m_goodWords[i]; ++i) {
        }
    }

    void SpellChecker::operator()(std::string& text) {
        for (int i = 0; i < 6; ++i) {
            size_t pos = 0;

            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {

                size_t end = pos + m_badWords[i].size();

                bool leftBoundary =
                    pos == 0 ||
                    !std::isalnum(static_cast<unsigned char>(text[pos - 1]));

                bool rightBoundary =
                    end == text.size() ||
                    !std::isalnum(static_cast<unsigned char>(text[end]));

                if (leftBoundary && rightBoundary) {
                    text.replace(pos, m_badWords[i].size(), m_goodWords[i]);

                    pos += m_goodWords[i].size();
                    ++m_counts[i];
                }
                else {
                    pos += m_badWords[i].size();
                }
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const {
        for (int i = 0; i < 6; ++i) {
            out << std::left
                << std::setw(15) << m_badWords[i]
                << ": " << m_counts[i]
                << " replacements\n";
        }
    }

}
