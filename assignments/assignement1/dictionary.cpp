#include "dictionary.h"
#include "settings.h"

#include <fstream>
#include <iostream>
#include <string>

namespace seneca {

    static PartOfSpeech getPartOfSpeech(const std::string& pos)
    {
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

    static const char* getPartOfSpeechName(PartOfSpeech pos)
    {
        switch (pos)
        {
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

    Dictionary::Dictionary(const char* filename)
        : m_words(nullptr),
        m_size(0)
    {
        if (filename == nullptr)
            return;

        std::ifstream file(filename);

        // Visual Studio may use a different working directory.
        // Try the Debug folder where the CSV files are located.
        if (!file)
        {
            std::string debugPath = "x64\\Debug\\";
            debugPath += filename;

            file.open(debugPath);
        }

        if (!file)
            return;

        std::size_t count = 0;
        std::string line;

        // First pass: count the records.
        while (std::getline(file, line))
        {
            if (!line.empty())
                ++count;
        }

        if (count == 0)
            return;

        // Go back to the beginning.
        file.clear();
        file.seekg(0, std::ios::beg);

        // Allocate exactly enough memory.
        m_words = new Word[count];

        // Second pass: load the records.
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::size_t firstComma = line.find(',');

            if (firstComma == std::string::npos)
                continue;

            std::size_t secondComma =
                line.find(',', firstComma + 1);

            if (secondComma == std::string::npos)
                continue;

            m_words[m_size].m_word =
                line.substr(0, firstComma);

            std::string pos =
                line.substr(
                    firstComma + 1,
                    secondComma - firstComma - 1);

            m_words[m_size].m_definition =
                line.substr(secondComma + 1);

            m_words[m_size].m_pos =
                getPartOfSpeech(pos);

            ++m_size;
        }
    }

    Dictionary::~Dictionary()
    {
        delete[] m_words;
    }

    Dictionary::Dictionary(const Dictionary& other)
        : m_words(nullptr),
        m_size(other.m_size)
    {
        if (m_size > 0)
        {
            m_words = new Word[m_size];

            for (std::size_t i = 0; i < m_size; ++i)
            {
                m_words[i] = other.m_words[i];
            }
        }
    }

    Dictionary& Dictionary::operator=(const Dictionary& other)
    {
        if (this != &other)
        {
            Word* newWords = nullptr;

            if (other.m_size > 0)
            {
                newWords = new Word[other.m_size];

                for (std::size_t i = 0;
                    i < other.m_size;
                    ++i)
                {
                    newWords[i] = other.m_words[i];
                }
            }

            delete[] m_words;

            m_words = newWords;
            m_size = other.m_size;
        }

        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept
        : m_words(other.m_words),
        m_size(other.m_size)
    {
        other.m_words = nullptr;
        other.m_size = 0;
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_words;

            m_words = other.m_words;
            m_size = other.m_size;

            other.m_words = nullptr;
            other.m_size = 0;
        }

        return *this;
    }

    void Dictionary::searchWord(const char* word)
    {
        bool found = false;

        for (std::size_t i = 0; i < m_size; ++i)
        {
            if (m_words[i].m_word == word)
            {
                if (!found)
                {
                    std::cout
                        << m_words[i].m_word
                        << " - ";

                    if (g_settings.m_verbose &&
                        m_words[i].m_pos !=
                        PartOfSpeech::Unknown)
                    {
                        std::cout
                            << "("
                            << getPartOfSpeechName(
                                m_words[i].m_pos)
                            << ") ";
                    }

                    std::cout
                        << m_words[i].m_definition
                        << std::endl;

                    found = true;
                }
                else
                {
                    std::cout
                        << std::string(
                            m_words[i].m_word.length(),
                            ' ')
                        << " - ";

                    if (g_settings.m_verbose &&
                        m_words[i].m_pos !=
                        PartOfSpeech::Unknown)
                    {
                        std::cout
                            << "("
                            << getPartOfSpeechName(
                                m_words[i].m_pos)
                            << ") ";
                    }

                    std::cout
                        << m_words[i].m_definition
                        << std::endl;
                }

                if (!g_settings.m_show_all)
                    break;
            }
        }

        if (!found)
        {
            std::cout
                << "Word '"
                << word
                << "' was not found in the dictionary."
                << std::endl;
        }
    }

}