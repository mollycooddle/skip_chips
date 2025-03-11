#include <iostream>
#include "sorted_table.h"
#include "polinom.h"


void main()
{
	int i = 0;

	DataBaseVector sql;
	while (i != 3) {
		std::string str;
		std::cout << "Enter an expression: ";
		std::cin >> str;
		Polinom<std::string> pol(str);
		sql.insert(pol);
		i++;
	}
	//sql.erase(2);
	//Polinom<std::string> pol("222x^3y^1z^2+2x^2y^3z^1+2x^1y^2z^3");
	//std::cout << sql.find(pol);
	
	std::cout << sql << std::endl;
}
