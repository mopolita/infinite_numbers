#include <iostream>
#include <compare>
#include <iterator>
#include <cstdint>
#include "infInt.hpp"

namespace inf{

	InfInt::InfInt(int64_t nb) : value{}, positive{nb >= 0} {
		if (nb == 0) {
			value.push_back(0);
			return;
		}
		if (!positive) nb = -nb;
		while (nb > 0) {
			value.push_front(nb % 10);  // Ajout en début pour garder l’ordre
			nb /= 10;
		}
	}

	InfInt InfInt::abs() const noexcept{
		if (!positive) return -*this;
		return *this;
	}

	void InfInt::removeLeadingZeros(){
		while (value.size() > 1 && value.front() == 0) {
			value.pop_front();
		}
	}

    // Unary negation operator
    InfInt InfInt::operator-() const noexcept{
		InfInt result = *this;
		result.positive = !result.positive;
        return result;
    }

	std::ostream& operator<<(std::ostream &os, const InfInt &nb) {
		if (!nb.positive) os << '-';
		for (auto it = nb.value.begin(); it != nb.value.end(); ++it) {
			os << static_cast<int>(*it);
		}
		return os;
	}

	InfInt operator+(const InfInt &a, const InfInt &b) {
		InfInt result;
		
		// Case: Same signs, simply add their absolute values
		if (a.positive == b.positive) {	
			result.positive = a.positive;
			auto ita = a.value.rbegin();
			auto itb = b.value.rbegin();
			uint8_t carry = 0;
			uint8_t sum = 0;

			while (ita != a.value.rend() || itb != b.value.rend() || carry) {
				sum = carry;
				if (ita != a.value.rend()) {
					sum += *ita;
					++ita;
				}
				if (itb != b.value.rend()) {
					sum += *itb;
					++itb;
				}
				carry = sum / 10;
				result.value.push_front(sum % 10);
			}
			// The last 0 appears because infint is initialized with 0 by default, and we use push to add numbers.
			// So we need to remove it if the result is not 0.
			if (result != InfInt{0}) result.value.pop_back(); // Remove last 0
			return result;
		}

		// Case: Different signs, subtract the absolute values
		return a.abs() - b.abs();
	}

	InfInt operator-(const InfInt &a, const InfInt &b) {
		InfInt result;

		// Case 1: Same values, return 0
		if (a == b) return InfInt{0};

		// Case 2: Different signs, treat as addition of abs values
		if (a.positive != b.positive) {
			result = a.abs() + b.abs();
			result.positive = a.positive;
			return result;
		}

		// Case 3: Absolute value of a is bigger than absolute value of b, handle subtraction based on absolute values
		const InfInt *larger = &a;
		const InfInt *smaller = &b;
		bool resultPositive = a.positive;

		if (a.abs() < b.abs()) {
			larger = &b;
			smaller = &a;
			resultPositive = !b.positive;
		}

		int borrow = 0, diff = 0;
		auto itLarge = larger->value.rbegin();
		auto itSmall = smaller->value.rbegin();

		while (itLarge != larger->value.rend()) {
			diff = *itLarge - borrow;
			if (itSmall != smaller->value.rend()) {
				diff -= *itSmall;
				++itSmall;
			}

			if (diff < 0) {
				diff += 10;
				borrow = 1;
			} 
			else {
				borrow = 0;
			}

			result.value.push_front(diff);
			++itLarge;
		}
		
		// The last 0 appears because infint is initialized with 0 by default, and we use push to add numbers.
		// So we need to remove it if the result is not 0.
		if (result != InfInt{0}) result.value.pop_back(); // Remove last 0
		result.positive = resultPositive;
		result.removeLeadingZeros();
		return result;
	}

	InfInt operator*(const InfInt &a, int64_t b){
		if (a == InfInt{0} || b == 0) return InfInt{0};
		if (a == InfInt{1}) return InfInt{b};
		
		if (b == 1) return a;
		if (b == -1) return -a;

		InfInt result;
		int64_t carry = 0;
		int64_t product = 0;

		if (b < 0) {
			result.positive = !a.positive;
			b = -b;
		}
		else result.positive = a.positive;

		for (auto it = a.value.rbegin(); it != a.value.rend(); ++it) {
			product = *it * b + carry;
			carry = product / 10;
			result.value.push_front(product % 10);
		}

		while (carry) {
			result.value.push_front(carry % 10);
			carry /= 10;
		}

		// The last 0 appears because infint is initialized with 0 by default, and we use push to add numbers.
		// So we need to remove it if the result is not 0.
		if (result != InfInt{0}) result.value.pop_back(); // Remove last 0
		return result;
	}

	InfInt operator*(const InfInt &a, const InfInt &b){
		// use the method learned in primary school (requires a InfInt * int_64t)
		if (a == InfInt{0} || b == InfInt{0}) return InfInt{0};
		
		if (a == InfInt{1}) return b;
		if (a == InfInt{-1}) return -b;
		
		if (b == InfInt{1}) return a;
		if (b == InfInt{-1}) return -a;

		InfInt result, a_temp = a.abs(), b_temp = b.abs(), temp;
		int64_t shift = 0;

		

		for (auto it = b_temp.value.rbegin(); it != b_temp.value.rend(); ++it) {
			temp = a_temp * (*it);
			temp.value.insert(temp.value.end(), shift, 0);
			result = result + temp;
			shift++;
		}
		
		result.positive = (a.positive == b.positive);
		return result;
	}

	/*
	How I would do it :
	1. Check if b is 0, throw an exception if it is.
	2. Check if a is 0 or if a is smaller than b, return 0 in that case.
	3. Check if b is 1 or -1, return a or -a respectively.
	4. Create a new InfInt object to store the result.
	5. While a_temp is greater than b_temp:
		- Pop the first digit of a_temp and add it to the remainder.
		- If the remainder is less than b_temp, push 0 to the result and continue.
		- Otherwise, subtract b_temp from the remainder and increment the quotient.

	*/
	InfInt operator/(const InfInt &a, const InfInt &b){
		if (b == 0) throw DivisionByZeroError{};
		if (a == InfInt{0} || a.abs() < b.abs()) return InfInt{0};
		
		if (b == 1) return a;
		if (b == -1) return -a;

		InfInt res, remainder, a_temp = a.abs(), b_temp = b.abs();
		int8_t quotient = 0;

		while (a_temp.value.size() > 0) {
			remainder.value.push_back(a_temp.value.front());
			a_temp.value.pop_front();
			if (remainder < b_temp) {
				res.value.push_back(0);
				continue;
			}

			quotient = 0;
			while (remainder >= b_temp) {
				remainder = remainder - b_temp;
				quotient++;
			}
			res.value.push_back(quotient);
		}

		res.positive = (a.positive == b.positive);
		res.removeLeadingZeros();
		return res;
	}

	std::strong_ordering operator<=>(const InfInt& a, const InfInt& b) {

		InfInt a_tmp = a, b_tmp = b;
		a_tmp.removeLeadingZeros();
		b_tmp.removeLeadingZeros();
		if (a.positive != b.positive) return a.positive <=> b.positive;
		if (a_tmp.value.size() != b_tmp.value.size()) return a_tmp.value.size() <=> b_tmp.value.size();
		return std::lexicographical_compare_three_way(
    		a_tmp.value.begin(), a_tmp.value.end(),
        	b_tmp.value.begin(), b_tmp.value.end()
		);
	}
}
