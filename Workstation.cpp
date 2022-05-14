#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;
	Workstation::Workstation(const std::string& str) : Station(str){}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			while (!m_orders.front().isItemFilled(getItemName()))
				m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder()
	{

		if (m_orders.empty())
			 return false;

		if (m_orders.front().isItemFilled(this -> getItemName()) || this->getQuantity() == 0) {
			if (m_pNextStation) {
				*m_pNextStation += std::move(m_orders.front());
			}
			else if(m_orders.front().isFilled()){
				completed.push_back(std::move(m_orders.front()));
			}
			else {
				incomplete.push_back(std::move(m_orders.front()));
			}
			m_orders.pop_front();
			return true;  //if an order has been moved, return true
		}
		else{ 
			return false;
		}
	}
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		if (m_pNextStation) {
			os << m_pNextStation->getItemName();
		}
		else {
			os << "End of Line";
		}
		os << std::endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}

