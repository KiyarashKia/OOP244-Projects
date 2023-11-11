#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <ctime>
#include "Status.h"
namespace sdds {

	const int MAXIMUM_YEAR_VALUE = 2030;
	const int currentYear = 2023;
	const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	class Date {

		int year;
		int month;
		int day;
		Status State;
		bool format;

		bool validate();
		int uniqueDateValue() const;

	public:

		Date();
		Date(int y, int m, int d);

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