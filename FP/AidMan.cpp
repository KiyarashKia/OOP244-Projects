/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
MS5 - AidMan.cpp
Date : 13/03/2023
 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

#include "AidMan.h"
#include "Utils.h"
#include "Item.h"
#include "Perishable.h"


using namespace std;
namespace sdds {
	
    unsigned int AidMan::menu() {
        Date date{};
        date.formatted(true);

        cout << "Aid Management System" << endl << "Date: ";
        cout << date << endl;
        cout << "Data file: " << ((name) ? name : "No file") << endl;
        cout << "---------------------------------" << endl;

        return mainMenu.run();
    }



	AidMan::AidMan(const char* filename) {
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
		deallocate();
		delete[] name;
		name = nullptr;
	}

    void AidMan::run() {
        unsigned int input{};
        do {
            input = menu();

            if (input == 0) {
                cout << "Exiting Program!" << endl;
            }
            else {
                if (name) {
                    mainMenu.printItem(input);
                    cin.ignore();

                    switch (input) {
                    case 1:
                        listItems();
                        break;
                    case 2:
                        addItem();
                        break;
                    case 3:
                        removeItem();
                        break;
                    case 4:
                        updateQuantity();
                        break;
                    case 5:
                        sort();
                        break;
                    case 6:
                        shipItems();
                        break;
                    case 7:
                        loadDatabase();
                        break;
                    default:
                        break;
                    }
                }
                else {
                    mainMenu.printItem(7);
                    loadDatabase();
                }
                cout << endl;
            }
        } while (input != 0);
    }

    void AidMan::save() {
        if (name)
        {
            ofstream fileOpen(name);
            for (int i = 0; i < noItems; i++)
            {
                m_items[i]->save(fileOpen) << endl;
            }
            fileOpen.close();
        }
    }


    void AidMan::deallocate() {
        for (int i = 0; i < noItems; i++) {
            delete m_items[i];
            m_items[i] = nullptr;
        }
        noItems = 0;
    }

    bool AidMan::load() {
        save();
        deallocate();
        cin.ignore();

        if (name) {
            ifstream file(name);
            if (file.is_open()) {
                cout << "Failed to open " << name << " for reading!" << endl;
                cout << "Would you like to create a new data file?" << endl;
                Menu menu("1- Yes!");
                if (menu.run()) {
                    char temp[1000]{ '\0' };
                    cin.getline(temp, 1000, '\n');
                    delete[] name;
                    name = nullptr;
                    ut.alocpy(name, temp);
                    ofstream outputFile(name);
                    outputFile << "";
                    outputFile.close();
                }
                else cout << "Exiting Program!" << endl;
            }
            file.close();
        }
        else {
            cout << "Enter file name: ";
            char temp[1000]{ '\0' };
            cin.getline(temp, 1000, '\n');
            ut.alocpy(name, temp);
        }

        ifstream file(name);
        int i;
        for (i = 0; i < sdds_max_num_items; i++) {
            int peek = file.peek();

            if (peek >= 49 && peek <= 51) {
                m_items[i] = new Perishable();
                if (m_items[i]->load(file)) noItems++;
                else {
                    delete m_items[i];
                    m_items[i] = nullptr;
                }
            }
            else if (peek >= 52 && peek <= 57) {
                m_items[i] = new Item();
                if (m_items[i]->load(file)) noItems++;
                else {
                    delete m_items[i];
                    m_items[i] = nullptr;
                }
            }
            else file.setstate(std::ios::failbit);
        }
        cout << noItems << " records loaded!" << endl;
        file.close();
        return noItems;
    }

    int AidMan::list(const char* sub_desc) {
        int counter{ 0 };
        cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        for (int i = 0; i < noItems; i++)
        {
            if (!sub_desc) {
                m_items[i]->linear(true);
                cout << std::setw(4) << std::setfill(' ') << std::right << (i + 1) << " | ";
                m_items[i]->display(cout) << endl;
                counter++;
            }
            else {
                if (m_items[i]->subString(sub_desc)) {
                    m_items[i]->linear(true);
                    cout << std::setw(4) << std::setfill(' ') << std::right << (i + 1) << " | ";
                    m_items[i]->display(cout) << endl;
                    counter++;
                }
            }
        }
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        return counter;
    }

    void AidMan::listItems() {
        if (list())
        {
            cout << "Enter row number to display details or <ENTER> to continue:" << endl << "> ";
            if (cin.peek() != '\n') {
                int row = ut.getint();
                m_items[row - 1]->linear(false);
                m_items[row - 1]->display(cout) << endl;
            }
            else {

                cin.ignore();
            }
        }

    }

}