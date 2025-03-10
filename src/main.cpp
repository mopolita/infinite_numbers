#include <iostream>
#include <list>
#include <compare>
#include <iterator>
#include <cstdint>
#include "infInt.hpp"

using namespace inf;

void testCout(){
	InfInt val{85};
	std::cout << "nombre : " << val << std::endl;
}

void testCompare(){
	InfInt val1{1};
	InfInt val2{-1};
	std::cout << "val1 : " << val1 << std::endl;
	std::cout << "val2 : " << val2 << std::endl;
	std::cout << "val1 == val2 : " << (val1 == val2) << std::endl;
	std::cout << "val1 != val2 : " << (val1 != val2) << std::endl;
	std::cout << "val1 < val2 : " << (val1 < val2) << std::endl;
	std::cout << "val1 > val2 : " << (val1 > val2) << std::endl;
	std::cout << "val1 <= val2 : " << (val1 <= val2) << std::endl;
	std::cout << "val1 >= val2 : " << (val1 >= val2) << std::endl;
}

int main(){
	//testCout();
	testCompare();
	return 0;
}
