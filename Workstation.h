// Name: YIWEN HAO
// Seneca Student ID: 123562191
// Seneca email: YHAO18@MYSENECA.CA
// Date of completion: Apr 6, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_
#include <iostream>
#include <deque>
#include <string>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

namespace sdds {
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation: public Station
	{
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{nullptr};

	public: 
		Workstation(const std::string& str);
		Workstation(Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&) = delete;
		Workstation& operator = (Workstation&&) = delete;

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}
#endif