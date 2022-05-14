#include "Utilities.h"


namespace sdds{

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	std::string token;
	size_t new_pos = str.find(m_delimiter, next_pos);
	if (new_pos == next_pos) {
		more = false;
		throw "Error: No content between two delimiters.";
		
	}
	else if (new_pos == std::string::npos) {
		more = false;
		token = str.substr(next_pos);
	}
	else {
		more = true;
		token = str.substr(next_pos, new_pos - next_pos);
		next_pos = new_pos + 1u;
	}

	if (token.length() > m_widthField) m_widthField = token.length();

	return token;
}

void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter()
{
	return m_delimiter;
}

}

