// Name: YIWEN HAO
// Seneca Student ID: 123562191
// Seneca email: YHAO18@MYSENECA.CA
// Date of completion: Apr 2, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_
#include <iostream>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name;
		std::string m_product;
		size_t m_cntItem{};
		//dynamically allocated array of pointers. 
		Item** m_lstItem{};
		static size_t m_widthField;

	public:
		CustomerOrder() {};
		CustomerOrder(const std::string& object);
		~CustomerOrder();

		CustomerOrder(CustomerOrder& c);
		CustomerOrder& operator = (CustomerOrder& c) = delete;

		CustomerOrder(CustomerOrder&& C) noexcept;
		CustomerOrder& operator = (CustomerOrder&& C)noexcept;

		bool isFilled() const;
		bool isItemFilled(const std::string& itemName);
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;

	};
}
#endif