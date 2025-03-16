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

void testPlus(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	std::cout << "val1 : " << val1 << std::endl;
	std::cout << "val2 : " << val2 << std::endl;
	std::cout << "val3 : " << val3 << std::endl;
	std::cout << "val1 + val2 : " << val1 + val2 << std::endl;
	std::cout << "val1 + val3 : " << val1 + val3 << std::endl;
	std::cout << "val3 + val3 : " << val3 + val3 << std::endl;
}

void testMinus(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	InfInt val4{-15};
	std::cout << "val1 : " << val1 << std::endl;
	std::cout << "val2 : " << val2 << std::endl;
	std::cout << "val3 : " << val3 << std::endl;
	std::cout << "val4 : " << val4 << std::endl;
	std::cout << "val1 - val2 : " << val1 - val2 << std::endl;
	std::cout << "val2 - val1 : " << val2 - val1 << std::endl;
	// Commented tests that works
	//std::cout << "val1 - val1 : " << val1 - val1 << std::endl;
	//std::cout << "val1 - val3 : " << val1 - val3 << std::endl;
	//std::cout << "val3 - val3 : " << val3 - val3 << std::endl;
	//std::cout << "val3 - val1 : " << val3 - val1 << std::endl;
	std::cout << "val3 - val4 : " << val3 - val4 << std::endl;
	std::cout << "val4 - val3 : " << val4 - val3 << std::endl;
}

int main(){
	//testCout();
	//testCompare();
	//testPlus();
	testMinus();
	return 0;
}
