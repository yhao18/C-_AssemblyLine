// Name: YIWEN HAO
// Seneca Student ID: 123562191
// Seneca email: YHAO18@MYSENECA.CA
// Date of completion: MAR 25, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include <iostream>
#include <string>


namespace sdds {

	class Station {
		int m_id;
		std::string m_name;
		std::string m_des;
		size_t m_serialNum;
		size_t m_count;

		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};


}
#endif