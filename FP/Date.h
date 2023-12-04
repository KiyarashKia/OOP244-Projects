/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 5 - Date.h
Date : 12/03/2023
 */

#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Status.h"
namespace sdds {

	const int MAXIMUM_YEAR_VALUE = 2030;
	const int currentYear = 2023;
	const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	class Date {

		int year{};
		int month{};
		int day{};
		Status State;
		bool format{ true };

		bool validate();
		int uniqueDateValue() const;

	public:

		Date();
		Date(int y, int m, int d);
		~Date();

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		const Status& state() const;

		Date& formatted(bool value);

		operator bool() const;

		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);
	};

	std::ostream& operator<<(std::ostream& os, const Date& date);
	std::istream& operator>>(std::istream& is, Date& date);


}

#endif // !SDDS_DATE_H