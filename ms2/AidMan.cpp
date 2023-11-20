/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 2 - AidMan.cpp
Date : 11/20/2023
 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

#include "AidMan.h"
#include "Utils.h"
#include "Menu.h"

using namespace std;
namespace sdds {
	
	unsigned int AidMan::menu() {
		int year, month, day;

		cout << "Aid Management System\n";
		ut.getSystemDate(&year, &month, &day);
		cout << "Date: " << year << "/" << (month < 10 ? "0" : "") 
			<< month << "/" << (day < 10 ? "0" : "") << day << "\n";
		cout << "Data file: " << (name ? name : "No file") << endl << endl;

		return mainMenu.run();
	}


	AidMan::AidMan(const char* filename) : mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		if (filename)
		{
			name = new char[strlen(filename) + 1];
			strcpy(name, filename);
		}
		else
		{
			name = nullptr;
		}

	}

	AidMan::~AidMan() {
		delete[] name;
	}

	void AidMan::run() {
		unsigned int input{};

		do
		{
			input = menu();

			switch (input)
			{
			case 1:
				std::cout << "\n****List Items****\n\n";
				break;
			case 2:
				std::cout << "\n****Add Item****\n\n";
				break;
			case 3:
				std::cout << "\n****Remove Item****\n\n";
				break;
			case 4:
				std::cout << "\n****Update Quantity****\n\n";
				break;
			case 5:
				std::cout << "\n****Sort****\n\n";
				break;
			case 6:
				std::cout << "\n****Ship Items****\n\n";
				break;
			case 7:
				std::cout << "\n****New/Open Aid Database****\n\n";
				break;
			default:
				break;
			}
		} while (input != 0);

		std::cout << "Exiting Program!\n";
	}



}