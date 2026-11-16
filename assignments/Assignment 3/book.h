#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include "mediaItem.h"
#include <string>
namespace seneca {
	class Book : public MediaItem {
		std::string m_author, m_country; double m_price{};
		Book(const std::string&, const std::string&, const std::string&, double, unsigned short, const std::string&);
	public:
		void display(std::ostream& out) const override;
		static Book* createItem(const std::string& strBook);
	};
}
#endif
