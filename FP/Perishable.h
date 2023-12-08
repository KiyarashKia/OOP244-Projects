/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 54 - Perishable.h
Date : 12/08/2023
 */

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>
#include "Item.h"
#include "Date.h"

namespace sdds {

	class Perishable : public Item {

		Date exDate{};
		Date m_exDate{};
		char* m_handling{};

	public:
		Perishable() = default;
		
		virtual ~Perishable();
		Perishable(const Perishable& other);
		Perishable& operator=(const Perishable& other);

		const Date& expiry() const;

		// Virtuals
		virtual int readSku(std::istream& istr) override;
		virtual std::ofstream& save(std::ofstream& ofstr) const override;
		virtual std::ifstream& load(std::ifstream& ifstr) override;
		virtual std::ostream& display(std::ostream& ostr) const override;
		virtual std::istream& read(std::istream& istr) override;
	};



}



#endif // !SDDS_PERISHABLE_H
