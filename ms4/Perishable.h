#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>
#include "Item.h"
#include "Date.h"

namespace sdds {

	class Perishable : public Item {

		Date exDate{};
		char* m_handling{};

	public:
		Perishable() = default;
		
		~Perishable();
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
