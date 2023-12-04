/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
MS4 - Item.cpp
Date : 12/01/2023
 */

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Item.h"
#include "Utils.h"


namespace sdds {

    Item::Item() : price(0.0), quantity(0), nQuantity(0), descItem(nullptr), flagLinear(false), m_sku(0) {}

    Item::~Item() {
        delete[] descItem;
        state.clear();
    }
    


    Item::Item(const Item& other)
        : iProduct(other),
        price(other.price),
        quantity(other.quantity),  // as I had warning for not initializing
        nQuantity(other.nQuantity),  // as I had warning for not initializing
        descItem(nullptr), // as I had warning for not initializing
        flagLinear(other.flagLinear),  // as I had warning for not initializing
        state(other.state),
        m_sku(other.m_sku) 
    {
        ut.alocpy(descItem, other.descItem);
    }

    Item& Item::operator=(const Item& other) {
        if (this != &other) {
            price = other.price;
            quantity = other.quantity;
            nQuantity = other.nQuantity;
            flagLinear = other.flagLinear;
            m_sku = other.m_sku;
            state = other.state;
            ut.alocpy(descItem, other.descItem);
        }
        return *this;
    }

    int Item::qtyNeeded() const {
        return nQuantity;
    }

    int Item::qty() const {
        return quantity;
    }

    Item::operator double() const {
        return price;
    }

    Item::operator bool() const {
        return descItem;
    }

    int Item::operator-=(int qty) {
        quantity -= qty;
        return quantity;
    }

    int Item::operator+=(int qty) {
        quantity += qty;
        return quantity;
    }
      
    void Item::linear(bool isLinear) {
        flagLinear = isLinear;
    }

    void Item::clear() {
        state.clear();
    }

    bool Item::linear() const {
        return flagLinear;
    }

    bool Item::operator==(int sku) const {
        return m_sku == sku;
    }

    bool Item::operator==(const char* description) const {
        return description != nullptr && descItem != nullptr && strstr(descItem, description) != nullptr;
    }


    std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (state) {
            ofstr << m_sku << '\t' << descItem << '\t' << quantity << '\t' << nQuantity << '\t'
                << std::fixed << std::setprecision(2) << price;
        }
        return ofstr;
    }

    std::ifstream& Item::load(std::ifstream& ifstr) {
        delete[] descItem;
        descItem = nullptr;

        ifstr >> m_sku;
        ifstr.ignore();

        char tempDesc[1000]{};
        ifstr.getline(tempDesc, 1000, '\t');
        ut.alocpy(descItem, tempDesc);

        ifstr >> quantity;
        ifstr.ignore();

        ifstr >> nQuantity;
        ifstr.ignore();

        ifstr >> price;
        ifstr.ignore();

        if (ifstr.fail()) {
            state = "Input file stream read failed!";
            delete[] descItem;
            descItem = nullptr;
        }
        else {
            clear();
        }

        return ifstr;
    }


    std::ostream& Item::display(std::ostream& ostr) const {
        if (!state) {
            ostr << state;
        }
        else if (flagLinear) {
            ostr << std::setw(5) << std::setfill('0') << m_sku << " | ";

            if (descItem) {
                char buffer[36]{ '\0' };
                strncpy(buffer, descItem, 35);
                buffer[35] = '\0';
                ostr << std::setw(35) << std::left << std::setfill(' ') << buffer << " | ";
            }
            else {
                ostr << std::setw(35) << std::left << std::setfill(' ') << " " << " | ";
            }

            ostr << std::setw(4) << std::right << quantity << " | " << std::setw(4) << nQuantity << " | "
                << std::setw(7) << std::fixed << std::setprecision(2) << price << " |";
        }
        else {
            ostr << "AMA Item:" << std::endl;
            ostr << m_sku << ": " << (descItem ? descItem : "") << std::endl;
            ostr << "Quantity Needed: " << nQuantity << std::endl;
            ostr << "Quantity Available: " << quantity << std::endl;
            ostr << "Unit Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
            ostr << "Needed Purchase Fund: $" << std::fixed << std::setprecision(2) << (nQuantity - quantity) * price << std::endl;
        }
        return ostr;
    }

    bool Item::subString(const char* sub) const {
        return std::strstr(descItem, sub) != nullptr;
    }

    std::istream& Item::read(std::istream& istr) {

        std::cout << "AMA Item:" << std::endl;
        std::cout << "SKU: " << m_sku << std::endl;

        delete[] descItem;
        descItem = nullptr;
        char tmp[1000]{ '\0' };
        std::cout << "Description: ";
        istr.getline(tmp, 1000, '\n');
        ut.alocpy(descItem, tmp);

        nQuantity = ut.getint(1, 9999, "Quantity Needed: ");
        quantity = ut.getint(0, nQuantity, "Quantity On Hand: ");
        price = ut.getdouble(0.0, 9999.0, "Unit Price: $");

        return istr;
    }

    int Item::readSku(std::istream& istr) {
        m_sku = ut.getint(40000, 99999, "SKU: ");
        return m_sku;
    }

}
 