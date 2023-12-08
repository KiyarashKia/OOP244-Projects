/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 56 - Perishable.cpp
Date : 12/08/2023
 */

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

#include "Perishable.h"
#include "Utils.h"
#include "Date.h"


namespace sdds {

	Perishable::~Perishable() {
		delete[] m_handling;
	}

	Perishable::Perishable(const Perishable& other) {
		m_handling = nullptr;
		*this = other;
	}

	Perishable& Perishable::operator=(const Perishable& other) {

		if (this != &other) {
			Item::operator=(other);
			delete[] m_handling;

			if (other.m_handling) {
				m_handling = new char[strlen(other.m_handling) + 1];
				strcpy(m_handling, other.m_handling);
			}
			else {
				m_handling = nullptr;
			}
			exDate = other.exDate;
		}
		return *this;
	}


	const Date& Perishable::expiry() const {
		return exDate;
	}

	// Virtuals
	int Perishable::readSku(std::istream& istr) {
		m_sku = ut.getint(10000, 39999, "SKU: ");

		istr.clear();
		istr.ignore();

		return m_sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const {

		if (Item::operator bool()) {
			Item::save(ofstr) << '\t';
			if (m_handling && strlen(m_handling)) ofstr << m_handling;
			Date tempDate = exDate;
			tempDate.formatted(false);
			ofstr << '\t' << tempDate;
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		Item::load(ifstr);

		delete[] m_handling;
		m_handling = nullptr;

		char tmp[1000]{};
		ifstr.getline(tmp, 1000, '\t');
		ut.alocpy(m_handling, tmp);

		ifstr >> exDate;
		ifstr.ignore();

		if (ifstr.fail())
		{
			state = "Input file stream read (perishable) failed!";
			delete[] m_handling;
			m_handling = nullptr;
		}

		else
		{
			state.clear();
		}
		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const {
		if (state) {
			const_cast<Date&>(exDate).formatted(true);
			if (linear()) {
				Item::display(ostr) << ((m_handling && strlen(m_handling)) ? "*" : " ") << exDate;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: " << exDate << std::endl;
				if (m_handling && strlen(m_handling)) {
					ostr << "Handling Instructions: " << m_handling << std::endl;
				}
			}
		}
		else {
			ostr << state;
		}
		return ostr;
	}


	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		delete[] m_handling;
		m_handling = nullptr;

		std::cout << "Expiry date (YYMMDD): ";
		istr >> exDate;
		istr.clear();
		istr.ignore();
		std::cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n')
		{
			char tmp[1000]{ '\0' };
			istr.getline(tmp, 1000, '\n');
			ut.alocpy(m_handling, tmp);
		}
		if (istr.fail())
		{
			Item::state = "Perishable console date entry failed!";
		}
		else
		{
			Item::state.clear();

		}
		return istr;
	}

}
