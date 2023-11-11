#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Status.h"

using namespace std;

namespace sdds {

	Status::Status(const char* description) {
		descStatus = nullptr;
		statCode = 0;

		if (description)
		{
			descStatus = new char[strlen(description) + 1];
			strcpy(descStatus, description);
		}

	}

	// RO3
	
	Status::Status(const Status& other) {
		statCode = other.statCode;

		if (other.descStatus != nullptr)
		{
			descStatus = new char[strlen(other.descStatus) + 1];
			strcpy(descStatus, other.descStatus);
		}
		else
		{
			descStatus = nullptr;
		}
	}

	Status& Status::operator=(const Status& other) {
		if (this != &other)
		{
			statCode = other.statCode;
		}
		delete[]  descStatus;	// check here 

		if (other.descStatus)
		{
			descStatus = new char[strlen(other.descStatus) + 1];
			strcpy(descStatus, other.descStatus);
		}
		else
		{
			descStatus = nullptr;
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
		delete[] descStatus;
		if (newDesc)
		{
			descStatus = new char[strlen(newDesc) + 1];
			strcpy(descStatus, newDesc);
		}
		else
		{
			descStatus = nullptr;
		}
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