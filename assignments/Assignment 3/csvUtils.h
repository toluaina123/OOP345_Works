#ifndef SENECA_CSVUTILS_H
#define SENECA_CSVUTILS_H
#include <string>
#include <vector>
namespace seneca {
	inline std::string trimToken(std::string s) {
		auto first = s.find_first_not_of(" \t\r\n"); if (first == std::string::npos) return {};
		auto last = s.find_last_not_of(" \t\r\n"); return s.substr(first, last - first + 1);
	}
	inline std::vector<std::string> splitCSV(const std::string& line) {
		std::vector<std::string> out; std::string token; bool quoted = false;
		for (size_t i = 0; i < line.size(); ++i) {
			char c = line[i];
			if (c == '"') { if (quoted && i + 1 < line.size() && line[i + 1] == '"') { token += '"'; ++i; } else quoted = !quoted; }
			else if (c == ',' && !quoted) { out.push_back(trimToken(token)); token.clear(); }
			else token += c;
		}
		out.push_back(trimToken(token));
		for (auto& v : out) { size_t p = 0; while ((p = v.find("__COMMA__", p)) != std::string::npos) { v.replace(p, 9, ","); ++p; } }
		return out;
	}
	inline std::string unquote(std::string s) { if (s.size() >= 2 && s.front() == '"' && s.back() == '"') return s.substr(1, s.size() - 2); return s; }
}
#endif
