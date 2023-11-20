/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 2 - AidMan.h
Date : 11/20/2023
 */

#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
namespace sdds {

	class AidMan {

		char* name;
		Menu mainMenu;

		unsigned int menu();

	public:
		AidMan(const char* filename);

		~AidMan();
		AidMan(const AidMan&) = delete;
		AidMan& operator=(const AidMan&) = delete;

		void run();
	};

}



#endif // !SDDS_AIDMAN_H
