/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 53 - AidMan.h
Date : 12/08/2023
 */


#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

const int sdds_max_num_items = 100;


namespace sdds {

	class AidMan {

		iProduct* m_items[sdds_max_num_items]{ nullptr };
		int noItems = 0;
		char* name{ nullptr };
		Menu mainMenu{ "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database" };

		unsigned int menu() const;

		// Menu Item 7
		void save();
		void deallocate();
		bool load();

		// Menu Item 1
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void remove(int index);
		bool smallerDiffQty(const iProduct* p1, const iProduct* p2) const;
		void swap(iProduct*& a, iProduct*& b);
		void descendingSort(iProduct* arr[], int size);

	public:

		AidMan() = default;
		AidMan(const char* filename);
		~AidMan();
		void run();
		void listItems();
		void addItem();
		void removeItem();
		void updateQuantity();
		void sort();
		void shipItems();
		void loadDatabase();



	};

}



#endif // !SDDS_AIDMAN_H
