#include "dictionary.h"
#include "settings.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace seneca {

    static PartOfSpeech getPartOfSpeech(const std::string& pos) {

        if (pos == "n." || pos == "n. pl.")
            return PartOfSpeech::Noun;

        if (pos == "adv.")
            return PartOfSpeech::Adverb;

        if (pos == "a.")
            return PartOfSpeech::Adjective;

        if (pos == "v." ||
            pos == "v. i." ||
            pos == "v. t." ||
            pos == "v. t. & i.")
            return PartOfSpeech::Verb;

        if (pos == "prep.")
            return PartOfSpeech::Preposition;

        if (pos == "pron.")
            return PartOfSpeech::Pronoun;

        if (pos == "conj.")
            return PartOfSpeech::Conjunction;

        if (pos == "interj.")
            return PartOfSpeech::Interjection;

        return PartOfSpeech::Unknown;
    }

    static const char* partOfSpeechName(PartOfSpeech pos) {

        switch (pos) {
        case PartOfSpeech::Noun:
            return "noun";

        case PartOfSpeech::Pronoun:
            return "pronoun";

        case PartOfSpeech::Adjective:
            return "adjective";

        case PartOfSpeech::Adverb:
            return "adverb";

        case PartOfSpeech::Verb:
            return "verb";

        case PartOfSpeech::Preposition:
            return "preposition";

        case PartOfSpeech::Conjunction:
            return "conjunction";

        case PartOfSpeech::Interjection:
            return "interjection";

        default:
            return "";
        }
    }

    Dictionary::Dictionary(const char* filename) {

        std::ifstream file(filename);

        if (!file) {
            m_words = nullptr;
            m_size = 0;
            return;
        }

        size_t count = 0;
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty())
                ++count;
        }

        file.clear();
        file.seekg(0);

        m_size = count;

        if (m_size > 0) {
            m_words = new Word[m_size];
        }

        size_t index = 0;

        while (std::getline(file, line)) {

            if (line.empty())
                continue;

            std::stringstream ss(line);

            std::string word;
            std::string pos;
            std::string definition;

            std::getline(ss, word, ',');
            std::getline(ss, pos, ',');
            std::getline(ss, definition);

            m_words[index].m_word = word;
            m_words[index].m_definition = definition;
            m_words[index].m_pos = getPartOfSpeech(pos);

            ++index;
        }
    }

    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    Dictionary::Dictionary(const Dictionary& other)
        : m_size(other.m_size) {

        if (m_size > 0) {
            m_words = new Word[m_size];

            for (size_t i = 0; i < m_size; ++i) {
                m_words[i] = other.m_words[i];
            }
        }
    }

    Dictionary& Dictionary::operator=(const Dictionary& other) {

        if (this != &other) {

            delete[] m_words;

            m_words = nullptr;
            m_size = other.m_size;

            if (m_size > 0) {
                m_words = new Word[m_size];

                for (size_t i = 0; i < m_size; ++i) {
                    m_words[i] = other.m_words[i];
                }
            }
        }

        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept
        : m_words(other.m_words),
        m_size(other.m_size) {

        other.m_words = nullptr;
        other.m_size = 0;
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {

        if (this != &other) {

            delete[] m_words;

            m_words = other.m_words;
            m_size = other.m_size;

            other.m_words = nullptr;
            other.m_size = 0;
        }

        return *this;
    }

    void Dictionary::searchWord(const char* word) {

        bool found = false;

        for (size_t i = 0; i < m_size; ++i) {

            if (m_words[i].m_word == word) {

                if (!found) {

                    std::cout << m_words[i].m_word << " - ";

                    if (g_settings.m_verbose &&
                        m_words[i].m_pos != PartOfSpeech::Unknown) {

                        std::cout << "("
                            << partOfSpeechName(m_words[i].m_pos)
                            << ") ";
                    }

                    std::cout << m_words[i].m_definition
                        << std::endl;

                    found = true;
                }
                else {

                    std::cout << std::string(
                        m_words[i].m_word.length(), ' '
                    ) << " - ";

                    if (g_settings.m_verbose &&
                        m_words[i].m_pos != PartOfSpeech::Unknown) {

                        std::cout << "("
                            << partOfSpeechName(m_words[i].m_pos)
                            << ") ";
                    }

                    std::cout << m_words[i].m_definition
                        << std::endl;
                }

                if (!g_settings.m_show_all) {
                    break;
                }
            }
        }

        if (!found) {
            std::cout << "Word '"
                << word
                << "' was not found in the dictionary."
                << std::endl;
        }
    }

}