#include<iomanip>

#include "Station.h"
#include "Utilities.h"

namespace sdds {

size_t Station:: m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station(const std::string& str)
{
	m_id = ++id_generator;
	Utilities utility;
	bool more = true;
	size_t next_pos = 0u;

	try {
		m_name = utility.extractToken(str, next_pos, more);
		if (more) {
			m_serialNum = std::stoi(utility.extractToken(str, next_pos, more));
		}
		if (more) {
			m_count = std::stoi(utility.extractToken(str, next_pos, more));
		}
		if (m_widthField < utility.getFieldWidth()) {
			m_widthField = utility.getFieldWidth();
		}
		if (more) {
			m_des = utility.extractToken(str, next_pos, more);
		}
	}
	catch (const char* err)
	{
		std::cout << "ERROR : " << err << std::endl;
	}
	
}
const std::string& Station::getItemName() const
{
	return m_name;
}
size_t Station::getNextSerialNumber()
{
	return m_serialNum++;
}
size_t Station::getQuantity() const
{
	return m_count;
}
void Station::updateQuantity()
{
	if (m_count > 0) {
		m_count--;
	}
}
void Station::display(std::ostream& os, bool full) const
{
	os << "[" << std::setw(3) << std::setfill('0') << std::right << m_id << "] ";
	os << "Item: " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " [";
	os << std::setw(6) << std::setfill('0') << std::right << m_serialNum << "]";
	if (full) {
		os << " Quantity: " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_count << " Description: " << m_des << std::endl;
	}
	else {
		os << std::endl;
	}

}
}

