#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Date.h"
#include "Utils.h"
#include <iomanip>

using namespace std;
namespace sdds {

	Date::Date() {
		int y, m, d;
		ut.getSystemDate(&y, &m, &d);
		year = y;
		month = m;
		day = d;
		validate();
		format = true;
	}


	bool Date::validate() {
		bool failure = false;
		if (year < currentYear || year > MAXIMUM_YEAR_VALUE) {
			State = "Invalid year in date";
			State = 1;
			failure = false;
		}
		if (!failure && (month < 1 || month > 12)) {
			State = "Invalid month in date";
			State = 2;
			failure = false;
		}
		if (!failure && (day < 1 || day > ut.daysOfMon(month, year))) {
			State = "Invalid day in date";
			State = 3;
			failure = false;
		}
		if (!failure) {
			State.clear();
		}
		return !failure;
	}


	int Date::uniqueDateValue() const {

		return year * 372 + month * 31 + day;
	}

	Date::Date(int y, int m, int d) {
		year = y;
		month = m;
		day = d;
		format = true;
		validate();
	}

	const Status& Date::state() const {
		return State;
	}

	Date& Date::formatted(bool value) {

		format = value;
		return *this;
	}

	Date::operator bool() const {
		return !State;
	}

	std::ostream& Date::write(std::ostream& os) const {
		if (format) {
			os << setfill('0') << setw(4) << year << '/'
				<< setw(2) << month << '/'
				<< setw(2) << day;
		}
		else {
			os << setfill('0') << setw(2) << (year % 100)
				<< setw(2) << month
				<< setw(2) << day;
		}
		return os;
	}


	std::istream& Date::read(std::istream& is) {
		int input;
		is >> input;

		if (is)
		{
			if (input >= 1 && input <= 9999) {
				year = currentYear;
				month = input / 100;
				day = input % 100;
			}
			else if (input >= 100000 && input <= 999999) {
				year = input / 10000 + 2000;
				month = (input % 10000) / 100;
				day = input % 100;

			}
			else {
				State = "Invalid date value";
				is.setstate(std::ios::failbit);
				return is;
			}

			if (!validate()) {
				is.setstate(std::ios::badbit);
			}
		}
		else {
			State = "Invalid date value";
		}
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& date) {
		return date.write(os);
	}

	std::istream& operator>>(std::istream& is, Date& date) {
		return date.read(is);
	}
	

	bool Date::operator==(const Date& rhs) const {
		return this->uniqueDateValue() == rhs.uniqueDateValue();
	}

	bool Date::operator!=(const Date& rhs) const {
		return this->uniqueDateValue() != rhs.uniqueDateValue();
	}

	bool Date::operator<(const Date& rhs) const {
		return this->uniqueDateValue() < rhs.uniqueDateValue();
	}

	bool Date::operator>(const Date& rhs) const {
		return this->uniqueDateValue() > rhs.uniqueDateValue();
	}

	bool Date::operator<=(const Date& rhs) const {
		return this->uniqueDateValue() <= rhs.uniqueDateValue();
	}

	bool Date::operator>=(const Date& rhs) const {
		return this->uniqueDateValue() >= rhs.uniqueDateValue();
	}

}