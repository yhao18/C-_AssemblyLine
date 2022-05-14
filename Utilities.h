// Name: YIWEN HAO
// Seneca Student ID: 123562191
// Seneca email: YHAO18@MYSENECA.CA
// Date of completion: MAR 25, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_
#include <iostream>
#include <string>

namespace sdds {
	
	class Utilities {
		size_t m_widthField = 1;
		static char m_delimiter;

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
	
}
#endif