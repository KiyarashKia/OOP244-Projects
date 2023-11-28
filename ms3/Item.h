#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Status.h"

namespace sdds {

	class Item : public iProduct {

		double price;
		int quantity;
		int nQuantity;
		char* descItem;
		bool flagLinear;

	protected:

		Status state;
		int m_sku;

		// Method
		bool linear() const;

	public:

		Item();

		~Item();
		Item(const Item& other);
		Item& operator=(const Item& other);

		int qtyNeeded() const override;
		int qty() const override;
		operator double() const override;
		operator bool() const override;

		int operator-=(int qty) override;
		int operator+=(int qty) override;
		bool linear(bool isLinear) override;

		void clear();

		bool operator==(int sku) const override;
		bool operator==(const char* description) const override;

		virtual std::ofstream& save(std::ofstream& ofstr) const override;
		virtual std::ifstream& load(std::ifstream& ifstr) override;
		virtual std::ostream& display(std::ostream& ostr) const override;
		virtual std::istream& read(std::istream& istr) override;
		virtual int readSku(std::istream& istr) override;
	};


}




#endif // !SDDS_ITEM_H
