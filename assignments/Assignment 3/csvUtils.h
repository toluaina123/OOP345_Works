
#ifndef SENECA_CSVUTILS_H
#define SENECA_CSVUTILS_H

#include <string>
#include <vector>

namespace seneca {

    inline std::string trimToken(std::string s) {
        auto first = s.find_first_not_of(" \t\r\n");

        if (first == std::string::npos) {
            return {};
        }

        auto last = s.find_last_not_of(" \t\r\n");

        return s.substr(first, last - first + 1);
    }

    inline std::vector<std::string> splitCSV(const std::string& line) {
        std::vector<std::string> fields;
        std::string token;
        bool quoted = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];

            if (c == '"') {
                token += c;

                if (quoted && i + 1 < line.size() &&
                    line[i + 1] == '"') {
                    token += line[++i];
                }
                else {
                    quoted = !quoted;
                }
            }
            else if (c == ',' && !quoted) {
                fields.push_back(trimToken(token));
                token.clear();
            }
            else {
                token += c;
            }
        }

        fields.push_back(trimToken(token));

        for (auto& field : fields) {
            size_t pos = 0;

            while ((pos = field.find("__COMMA__", pos))
                != std::string::npos) {
                field.replace(pos, 9, ",");
                ++pos;
            }
        }

        return fields;
    }

    inline std::string unquote(std::string s) {
        if (s.size() >= 2 &&
            s.front() == '"' &&
            s.back() == '"') {
            return s.substr(1, s.size() - 2);
        }

        return s;
    }

}

#endif
