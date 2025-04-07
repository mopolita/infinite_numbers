#include <iostream>
#include <compare>
#include <iterator>
#include <cstdint>
#include "DivisionByZero.hpp"
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


	InfInt operator/(const InfInt &a, const InfInt &b){
		if (b == 0) throw DivisionByZeroError{};
		if (a == InfInt{0} || a.abs() < b) return InfInt{0};
		
		if (b == 1) return a;
		if (b == -1) return -a;

		InfInt res;
		res.positive = (a.positive == (b >= 0));

		InfInt a_temp = a.abs(), b_temp = b.abs();
		InfInt remainder;

		while (a_temp > b_temp){
			remainder = remainder * 10 + a_temp.value.front();
			a_temp.value.pop_front();
			if (remainder < b_temp) {
				res.value.push_back(0);
				continue;
			}

			int8_t quotient = 0;
			while (remainder >= b_temp) {
				remainder = remainder - b_temp;
				quotient++;
			}
			res.value.push_back(quotient);
		}

		res.removeLeadingZeros();
		return res;
	}

	std::strong_ordering operator<=>(const InfInt& a, const InfInt& b) {

		if (a.positive != b.positive) return a.positive <=> b.positive;
		return std::lexicographical_compare_three_way(
    		a.value.begin(), a.value.end(),
        	b.value.begin(), b.value.end()
		);
	}
}
