/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 52 - Menu.h
Date : 12/06/2023
 */

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds {

	const int size = 33;
	const int maxNumOptions = 15;

	class Menu {

		char* options;
		unsigned int numOptions; // To ensure the value is not negativee
		bool isValid;

	public:

		Menu(const char* content);

		// RO3
		~Menu();
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;

		unsigned int run(bool flag = true) const;
		void printItem(unsigned int option);
	};

}

#endif // !SDDS_MENU_H
