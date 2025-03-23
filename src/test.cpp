#include <iostream>
#include <compare>
#include <iterator>
#include <cstdint>
#include <chrono>
#include "DivisionByZero.hpp"
#include "infInt.hpp"
#include "infIntQ.hpp"

using namespace std;
using namespace std::chrono;
using namespace inf;

void testCoutList(){
	InfInt val{85};
	cout << "nombre : " << val << endl;
}

void testComparisonsList(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val2 : " << val2 << endl;
	
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
	cout << "val1 >= val3 : " << (val1 >= val3) << endl;
}

void testPlusList(){
	InfInt val1{15};
	InfInt val2{40};
	InfInt val3{-30};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val1 + val2 : " << val1 + val2 << endl;
	cout << "val1 + val3 : " << val1 + val3 << endl;
	cout << "val3 + val3 : " << val3 + val3 << endl;
}

void testMinusList(){
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
	cout << "val3 - val1 : " << val3 - val1 << endl;
}

void testMultList(){
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
	cout << "val3 * val6 : " << val3 * val6 << endl;
}

void testDivisionList(){
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
}

void testBigNumbersList(){
	InfInt val1{INT64_MAX-1};
	InfInt val2{INT64_MAX-10};
	InfInt val3{INT64_MIN+1};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val1 + val2 : " << val1 + val2 << endl;
	cout << "val1 - val2 : " << val1 - val2 << endl;
	cout << "val1 * val2 : " << val1 * val2 << endl;
	cout << "val1 / val2 : " << val1 / val2 << endl;
	cout << "val1 + val3 : " << val1 + val3 << endl;
	cout << "val1 - val3 : " << val1 - val3 << endl;
	cout << "val1 * val3 : " << val1 * val3 << endl;
	cout << "val1 / val3 : " << val1 / val3 << endl;
}

void testAllList(){
	cout << "List" << endl;
	testCoutList();
	testComparisonsList();
	testPlusList();
	testMinusList();
	testMultList();
	testDivisionList();
	testBigNumbersList();
}

void testCoutDeque(){
	InfIntQ val{85};
	cout << "nombre : " << val << endl;
}

void testComparisonsDeque(){
	InfIntQ val1{15};
	InfIntQ val2{40};
	InfIntQ val3{-30};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val2 : " << val2 << endl;
	
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
	cout << "val1 >= val3 : " << (val1 >= val3) << endl;
}

void testPlusDeque(){
	InfIntQ val1{15};
	InfIntQ val2{40};
	InfIntQ val3{-30};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val1 + val2 : " << val1 + val2 << endl;
	cout << "val1 + val3 : " << val1 + val3 << endl;
	cout << "val3 + val3 : " << val3 + val3 << endl;
}

void testMinusDeque(){
	InfIntQ val1{15};
	InfIntQ val2{40};
	InfIntQ val3{-30};
	InfIntQ val4{-15};

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
	cout << "val3 - val1 : " << val3 - val1 << endl;
}

void testMultDeque(){
	InfIntQ val1{15};
	InfIntQ val2{40};
	InfIntQ val3{-30};
	InfIntQ val4{-15};
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
	cout << "val3 * val6 : " << val3 * val6 << endl;
}

void testDivisionDeque(){
	InfIntQ val1{15};
	InfIntQ val2{40};
	InfIntQ val3{-30};
	InfIntQ val4{-15};

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
	cout << "val1 / 1 : " << val1 / InfIntQ{1} << endl;
	cout << "val1 / -1 : " << val1 / InfIntQ{-1} << endl;
	cout << "val3 / 1 : " << val3 / InfIntQ{1} << endl;
	cout << "val3 / -1 : " << val3 / InfIntQ{-1} << endl;

	// division by 0
	try{
		cout << "val1 / 0 : " << val1 / InfIntQ{0} << endl;
	}
	catch(DivisionByZeroError &e){
		cerr << "Erreur : " << e.what() << endl;
	}
}

void testBigNumbersDeque(){
	InfIntQ val1{INT64_MAX-1};
	InfIntQ val2{INT64_MAX-10};
	InfIntQ val3{INT64_MIN+1};
	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	cout << "val3 : " << val3 << endl;
	cout << "val1 + val2 : " << val1 + val2 << endl;
	cout << "val1 - val2 : " << val1 - val2 << endl;
	cout << "val1 * val2 : " << val1 * val2 << endl;
	cout << "val1 / val2 : " << val1 / val2 << endl;
	cout << "val1 + val3 : " << val1 + val3 << endl;
	cout << "val1 - val3 : " << val1 - val3 << endl;
	cout << "val1 * val3 : " << val1 * val3 << endl;
	cout << "val1 / val3 : " << val1 / val3 << endl;
}

void testAllDeque(){
	cout << "Deque" << endl;
	testCoutDeque();
	testComparisonsDeque();
	testPlusDeque();
	testMinusDeque();
	testMultDeque();
	testDivisionDeque();
	testBigNumbersDeque();
}

int main(){
    auto startL = high_resolution_clock::now();
    testAllList();
    auto endL = high_resolution_clock::now();
    
    auto startQ = high_resolution_clock::now();
    testAllDeque();
    auto endQ = high_resolution_clock::now();
	
	cout << "List : " << duration_cast<milliseconds>(endL - startL).count() << " ms\n";
    cout << "Deque   : " << duration_cast<milliseconds>(endQ - startQ).count() << " ms\n";
	return 0;
}
