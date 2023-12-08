/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 53 - iProduct.cpp
Date : 12/08/2023
 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "iProduct.h"


	std::ostream& sdds::operator<<(std::ostream& ostr, const iProduct& product)
	{
		return product.display(ostr);
	}

	std::istream& sdds::operator>>(std::istream& istr, iProduct& product)
	{
		return product.read(istr);
	}

