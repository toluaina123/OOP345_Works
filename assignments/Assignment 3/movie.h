#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"
namespace seneca {
	class Movie : public MediaItem {
		Movie(const std::string&, unsigned short, const std::string&);
	public:
		void display(std::ostream& out) const override;
		static Movie* createItem(const std::string& strMovie);
	};
}
#endif
