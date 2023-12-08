/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 54 - AidMan.cpp
Date : 12/08/2023
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
	
    unsigned int AidMan::menu() const {
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


    int AidMan::search(int sku) const {
        for (int i = 0; i < noItems; i++) {
            if (*m_items[i] == sku) return i;
        }
        return -1;
    }


    void AidMan::remove(int index) {
        delete m_items[index];
        m_items[index] = nullptr;
        for (int i = index; i < noItems - 1; i++) {
            m_items[i] = m_items[i + 1];
        }
        m_items[noItems - 1] = nullptr;
        noItems--;
    }

    bool AidMan::smallerDiffQty(const iProduct* p1, const iProduct* p2) const {
        return (p1->qtyNeeded() - p1->qty()) < (p2->qtyNeeded() - p2->qty());
    }
    void AidMan::swap(iProduct*& a, iProduct*& b) {
        iProduct* temp = a;
        a = b;
        b = temp;
    }

    void AidMan::descendingSort(iProduct* arr[], int size) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (smallerDiffQty(arr[j], arr[j + 1])) {
                    swap(arr[j], arr[j + 1]);
                }
            }
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
        if (name) {
            ofstream file(name);
            for (int i = 0; i < noItems; i++) {
                m_items[i]->save(file) << endl;
            }
            file.close();
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

    void AidMan::addItem() {
        if (noItems >= sdds_max_num_items) {
            cout << "Database full!" << endl;
        }
        else {
            Menu itemMenu("Perishable\tNon-Perishable");
            int input = itemMenu.run(false);
            if (input) {
                m_items[noItems] = (input == 1) ? new Perishable : new Item;
                int sku = m_items[noItems]->readSku(cin);
                if (search(sku) < 0) {
                    m_items[noItems]->read(cin);
                    if (*m_items[noItems]) {
                        ofstream file(name, ios::app);
                        m_items[noItems]->save(file) << '\n';
                        file.close();
                        noItems++;
                    }
                    else {
                        delete m_items[noItems];
                        m_items[noItems] = nullptr;
                    }
                }
                else {
                    cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl;
                    delete m_items[noItems];
                    m_items[noItems] = nullptr;
                }
            }
            else {
                cout << "Aborted" << endl;
            }
        }
    }

    void AidMan::removeItem() {
        cout << "Item description: ";
        char temp[1000]{};
        cin.getline(temp, 1000);
        if (list(temp)) {
            int sku = ut.getint("Enter SKU: ");
            int index = search(sku);
            if (index >= 0) {
                cout << "Following item will be removed: " << endl;
                m_items[index]->linear(false);
                m_items[index]->display(cout) << endl;
                cout << "Are you sure?" << endl;
                Menu confirmMenu("Yes!");
                if (confirmMenu.run(false)) {
                    remove(index);
                    save();
                    cout << "Item removed!" << endl;
                }
                else {
                    cout << "Aborted!" << endl;
                }
            }
            else {
                cout << "SKU not found!" << endl;
            }
        }
        else {
            cout << "No matches found!" << endl;
        }
    }

    void AidMan::updateQuantity() {
        cout << "Item description: ";
        char temp[1000]{};
        cin.getline(temp, 1000);
        if (list(temp)) {
            int sku = ut.getint("Enter SKU: ");
            int index = search(sku);
            if (index >= 0) {
                Menu qtyMenu("Add\tReduce");
                switch (qtyMenu.run(false)) {
                case 1:
                    if (m_items[index]->qty() == m_items[index]->qtyNeeded()) {
                        cout << "Quantity Needed already fulfilled!" << endl;
                    }
                    else {
                        int addQty = ut.getint(1, m_items[index]->qtyNeeded(), "Quantity to add: ");
                        *m_items[index] += addQty;
                        cout << addQty << " items added!" << endl;
                        save();
                    }
                    break;
                case 2:
                    if (m_items[index]->qty() == 0) {
                        cout << "There are no Items to reduce!" << endl;
                    }
                    else {
                        int reduceQty = ut.getint(1, m_items[index]->qty(), "Quantity to reduce: ");
                        *m_items[index] -= reduceQty;
                        cout << reduceQty << " items removed!" << endl;
                        save();
                    }
                    break;
                default:
                    cout << "Aborted!" << endl;
                    break;
                }
            }
            else {
                cout << "SKU not found!" << endl;
            }
        }
        else {
            cout << "No matches found!" << endl;
        }
    }

    void AidMan::sort() {
        descendingSort(m_items, noItems);
        save();
        cout << "Sort completed!" << endl;
    }

    void AidMan::shipItems() {
        ofstream shipFile("shippingOrder.txt");
        Date currentDate{};
        currentDate.formatted(true);
        shipFile << "Shipping Order, Date: " << currentDate << endl;
        shipFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        shipFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        int shippedItems = 0;
        for (int i = 0; i < noItems; i++) {
            if (m_items[i]->qty() == m_items[i]->qtyNeeded()) {
                m_items[i]->linear(true);
                shipFile << setw(4) << setfill(' ') << right << (++shippedItems) << " | ";
                m_items[i]->display(shipFile) << endl;
                remove(i);
                i--;
            }
        }
        shipFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        save();
        cout << "Shipping Order for " << shippedItems << " items saved!" << endl;
    }

    void AidMan::loadDatabase() {
        load();
    }



}