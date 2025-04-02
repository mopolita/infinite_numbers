#include <iostream>
#include <cstdint>
#include "DivisionByZero.hpp"
#include "infInt.hpp"

using namespace std;
using namespace inf;

void testCout(){
	InfInt val{85};
	cout << "nombre : " << val << endl << endl;
}

void testComparisons(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val2 : " << val2 << endl << endl;
	
	// same sign
	cout << "val1 == val2 : " << (val1 == val2) << endl;
	cout << "val1 != val2 : " << (val1 != val2) << endl;
	cout << "val1 < val2 : " << (val1 < val2) << endl;
	cout << "val1 > val2 : " << (val1 > val2) << endl;
	cout << "val1 <= val2 : " << (val1 <= val2) << endl;
	cout << "val1 >= val2 : " << (val1 >= val2) << endl;
	
	// different signs
	cout << "val1 == val3 : " << (val1 == val3) << endl;
	cout << "val1 != val3 : " << (val1 != val3) << endl;
	cout << "val1 < val3 : " << (val1 < val3) << endl;
	cout << "val1 > val3 : " << (val1 > val3) << endl;
	cout << "val1 <= val3 : " << (val1 <= val3) << endl;
	cout << "val1 >= val3 : " << (val1 >= val3) << endl << endl;
}

void testPlus(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val1 + val2 : " << val1 + val2 << endl;
	cout << "val1 + val3 : " << val1 + val3 << endl;
	cout << "val3 + val3 : " << val3 + val3 << endl << endl;
}

void testMinus(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	InfInt val4{-15};

	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val4 : " << val4 << endl;
	
	// same sign
	cout << "val1 - val2 : " << val1 - val2 << endl;
	cout << "val2 - val1 : " << val2 - val1 << endl;
	cout << "val3 - val4 : " << val3 - val4 << endl;
	cout << "val4 - val3 : " << val4 - val3 << endl;

	// same value
	cout << "val1 - val1 : " << val1 - val1 << endl;
	cout << "val3 - val3 : " << val3 - val3 << endl;
	
	// different signs
	cout << "val1 - val3 : " << val1 - val3 << endl;
	cout << "val3 - val1 : " << val3 - val1 << endl << endl;
}

void testMult(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	InfInt val4{-15};
	int64_t val5 = 5;
	int64_t val6 = -5;

	// values
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val4 : " << val4 << endl;
	cout << "val5 : " << val5 << endl;
	cout << "val6 : " << val6 << endl;

	// same sign
	cout << "val1 * val2 : " << val1 * val2 << endl;
	cout << "val3 * val4 : " << val3 * val4 << endl;

	// different signs
	cout << "val1 * val3 : " << val1 * val3 << endl;

	// with int64_t
	cout << "val1 * val5 : " << val1 * val5 << endl;
	cout << "val1 * val6 : " << val1 * val6 << endl;
	cout << "val3 * val5 : " << val3 * val5 << endl;
	cout << "val3 * val6 : " << val3 * val6 << endl << endl;
}

/*void testDivision(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	InfInt val4{-15};

	// values
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val4 : " << val4 << endl;

	// same sign
	cout << "val1 / val2 : " << val1 / val2 << endl;
	cout << "val2 / val1 : " << val2 / val1 << endl;
	cout << "val3 / val4 : " << val3 / val4 << endl;

	// different signs
	cout << "val1 / val3 : " << val1 / val3 << endl;
	cout << "val3 / val1 : " << val3 / val1 << endl;

	// divide by 1 and -1
	cout << "val1 / 1 : " << val1 / InfInt{1} << endl;
	cout << "val1 / -1 : " << val1 / InfInt{-1} << endl;
	cout << "val3 / 1 : " << val3 / InfInt{1} << endl;
	cout << "val3 / -1 : " << val3 / InfInt{-1} << endl;

	// division by 0
	try{
		cout << "val1 / 0 : " << val1 / InfInt{0} << endl;
	}
	catch(DivisionByZeroError &e){
		cerr << "Erreur : " << e.what() << endl;
	}
}*/

void testBigNumbers(){
	InfInt val1{INT64_MAX-1};
	InfInt val2{INT64_MAX-10};
	InfInt val3{INT64_MIN+1};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val1 + val2 : " << val1 + val2 << endl;
	cout << "val1 - val2 : " << val1 - val2 << endl;
	cout << "val1 * val2 : " << val1 * val2 << endl;
	//cout << "val1 / val2 : " << val1 / val2 << endl;
	cout << "val1 + val3 : " << val1 + val3 << endl;
	cout << "val1 - val3 : " << val1 - val3 << endl;
	cout << "val1 * val3 : " << val1 * val3 << endl << endl;
	//cout << "val1 / val3 : " << val1 / val3 << endl;
}

int main(){
	testCout();
	testComparisons();
	testPlus();
	testMinus();
	testMult();
	//testDivision();
	testBigNumbers();
}
