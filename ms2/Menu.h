#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds {

	const int maxNumOptions = 15;

	class Menu {

		char* options;
		unsigned int numOptions; // To ensure the value is nt negative
		bool isValid;

	public:

		Menu(const char* content);

		// RO3
		~Menu();
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;

		unsigned int run() const;

	};





}



#endif // !SDDS_MENU_H
