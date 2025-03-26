#include <iostream>
#include "unsorted_table.h"
#include "polinom.h"


void main()
{
	try {
		int i = 0;

		DataBaseVector sql;
		while (i != 3) {
			std::string str;
			std::cout << "enter a polynomial of the form (3x^2y^1z^0 -5x^1y^3z^4 7x^1y^0z^9) : ";
			std::getline(std::cin, str);
			Polinom pol(str);
			sql.insert(i, pol);
			i++;
		}

		//sql.erase(2);
		//Polinom<std::string> pol("222x^3y^1z^2+2x^2y^3z^1+2x^1y^2z^3");
		//std::cout << sql.find(pol) << std::endl;

		//std::cout << sql << std::endl;

		Polinom sqll = sql[1] + sql[2];
		std::cout << "\n" << sqll << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

}
