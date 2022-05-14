#include<iomanip>
#include "CustomerOrder.h"

namespace sdds {
	size_t CustomerOrder::m_widthField=0;

	CustomerOrder::CustomerOrder(const std::string& object)
	{
		Utilities utility;
		size_t next_pos = 0u, count= 0u, temp_pos;
		std::string items;
		bool more = true;

		if (object.empty()) {
			m_name = "";
			m_product = "";
		}
		else {
			m_name = utility.extractToken(object, next_pos, more);
			if (more) {
				m_product = utility.extractToken(object, next_pos, more);
			}
			temp_pos = next_pos;
			while (more) {
				items = utility.extractToken(object, temp_pos, more);
				count++;
			}
			m_cntItem = count++;
			more = true;

			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0u; i < m_cntItem && more; i++) {
				m_lstItem[i] = new Item(utility.extractToken(object, next_pos, more));
			}

			if (utility.getFieldWidth() > m_widthField) m_widthField = utility.getFieldWidth();


		}
	}

	CustomerOrder::~CustomerOrder()
	{
		for (auto i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	CustomerOrder::CustomerOrder(CustomerOrder& c)
	{
		throw "Error: Copy is not allowed!";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& C) noexcept
	{
		*this = std::move(C);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& C) noexcept
	{
		if (this != &C) {
			for (auto i = 0u; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;

			m_name = C.m_name;
			m_product = C.m_product;
			m_cntItem = C.m_cntItem;
			m_lstItem = C.m_lstItem;

			C.m_lstItem = nullptr;
			C.m_cntItem = 0;
		}
		return *this;
	}

	bool CustomerOrder::isFilled() const
	{
		bool status = true;

		for (size_t i = 0u; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				status = false;
			}
		}
		return status;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName)
	{
		bool itemStatus = true;
		for (size_t i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName)
				itemStatus = m_lstItem[i]->m_isFilled;
		}
		return itemStatus;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;

				}else {
				os << "    Unable to fill" << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				
			}	
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0u; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";

			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}

			os << std::endl;
		}
	}

}

