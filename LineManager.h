
// Name: YIWEN HAO
// Seneca Student ID: 123562191
// Seneca email: YHAO18@MYSENECA.CA
// Date of completion: Apr 6, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_LINEMANAGER_H_
#define SDDS_LINEMANAGER_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Station.h"
#include "Workstation.h"

namespace sdds {
	class Workstation;
	class LineManager {
		std::vector<Workstation*> activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};
}
#endif