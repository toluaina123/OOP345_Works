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
#ifndef SENECA_MEDIAITEM_H
#define SENECA_MEDIAITEM_H

#include <string>
#include <iostream>

namespace seneca
{
	class MediaItem
	{
		std::string m_title{};
		std::string m_summary{};
		unsigned short m_year{};
	protected:
		static void trim(std::string& str)
		{
			size_t i = 0u;
			for (i = 0u; i < str.length() && str[i] == ' '; ++i);
			str = str.substr(i);

			for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
			str = str.substr(0, i);
		}
	public:
		MediaItem(const std::string& title, const std::string& summary, unsigned short year) :
			m_title{ title }, m_summary{ summary }, m_year{ year } {}
		virtual ~MediaItem() = default;

		std::string getTitle() const { return m_title; }
		void setTitle(const std::string& title) { m_title = title; }
		std::string getSummary() const { return m_summary; }
		void setSummary(const std::string& summary) { m_summary = summary; }
		unsigned short getYear() const { return m_year; }
		//void setYear(unsigned short year) { m_year = year; }

		virtual void display(std::ostream& out = std::cout) const = 0;

		template<typename Functor_t>
		void fixSpelling(Functor_t& spellChecker)
		{
			spellChecker(m_title);
			spellChecker(m_summary);
		}
	};
	inline std::ostream& operator<<(std::ostream& out, const MediaItem& item)
	{
		item.display(out);
		return out;
	}
}

#endif