/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 52 - Status.cpp
Date : 12/06/2023
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Status.h"
#include "Utils.h"

using namespace std;

namespace sdds {


	Status::Status(const char* description) {
		descStatus = nullptr;
		statCode = 0;

		ut.alocpy(descStatus, description);

	}

	// RO3
	
	Status::Status(const Status& other) {

		descStatus = nullptr;
		statCode = other.statCode;

		ut.alocpy(descStatus, other.descStatus);
	}

	Status& Status::operator=(const Status& other) {
		if (this != &other) {
			statCode = other.statCode;
			ut.alocpy(descStatus, other.descStatus);
		}
		return *this;
	}

	Status::~Status() {
		delete[] descStatus;
	}

	Status& Status::operator=(int newCode) {
		statCode = newCode;
		return *this;
	}

	Status& Status::operator=(const char* newDesc) {
		ut.alocpy(descStatus, newDesc);
		return *this;
	}

	Status::operator int() const {
		return statCode;
	}

	Status::operator const char* () const {
		return descStatus;
	}

	Status::operator bool() const {
		return descStatus == nullptr;
	}

	Status& Status::clear() {
		delete[] descStatus;
		descStatus = nullptr;
		statCode = 0;
		return *this;
	}

	ostream& operator<<(ostream& os, const Status& st) {
		if (!st) {
			int stcode = st;
			if (stcode != 0) {
				os << "ERR#" << stcode << ": ";
			}

			const char* desc = st;
			if (desc != nullptr) {
				os << desc;
			}
		}
		return os;
	}
}