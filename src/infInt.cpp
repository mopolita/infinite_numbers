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
		if (a.abs() > b.abs()) {
			int borrow = 0, diff = 0;
			result.positive = a.positive;
			auto ita = a.value.rbegin();
			auto itb = b.value.rbegin();

			while (itb != b.value.rend()) {
				diff = *ita - (*itb + borrow);
				if (diff < 0) {
					diff += 10;
					borrow = 1;
				}
				else borrow = 0;
				result.value.push_front(diff);
				
				ita++;
				itb++;
			}

			// Handle the remaining digits of 'a' after 'b' is exhausted
			while (ita != a.value.rend()) {
				diff = *ita - borrow;
				if (diff < 0) {
					diff += 10;
					borrow = 1;
				}
				else borrow = 0;
				result.value.push_front(diff);
				++ita;
			}
		}

		// Case 4: If abs(b) > abs(a), reverse the order
		else {
			result = b - a;
			result.positive = !result.positive;  // Sign is same as 'a'
		}

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

		result.positive = (a.positive == b.positive);

		for (auto it = b_temp.value.rbegin(); it != b_temp.value.rend(); ++it) {
			temp = a_temp * (*it);
			temp.value.insert(temp.value.end(), shift, 0);
			result = result + temp;
			shift++;
		}

		return result;
	}

/* Redoing the division operation since I get segmentation fault
	InfInt operator/(const InfInt &a, const InfInt &b){
		if (b == InfInt{0}) throw DivisionByZeroError{};
		if (a == InfInt{0} || a.abs() < b.abs()) return InfInt{0};
		
		if (b == InfInt{1}) return a;
		if (b == InfInt{-1}) return -a;

		InfInt result;
		result.positive = (a.positive == b.positive);
		InfInt a_temp = a.abs(), b_temp = b.abs();
		InfInt remainder = InfInt{0};

		for (int8_t digit : a_temp.value) {
			remainder = remainder * 10 + digit;
			if (remainder < b_temp) {
				result.value.push_back(0);
				continue;
			}

			int8_t quotient = 0;
			while (remainder >= b_temp) {
				remainder = remainder - b_temp;
				quotient++;
			}
			result.value.push_back(quotient);
		}

		result.removeLeadingZeros();
		return result;
	}
*/
	std::strong_ordering operator<=>(const InfInt& a, const InfInt& b) {

		if (a.positive != b.positive) return a.positive <=> b.positive;
		return std::lexicographical_compare_three_way(
    		a.value.begin(), a.value.end(),
        	b.value.begin(), b.value.end()
		);
	}
}
