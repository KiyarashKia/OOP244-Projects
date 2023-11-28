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

