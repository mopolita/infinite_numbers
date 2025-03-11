#include <iostream>
#include <list>
#include <compare>
#include <iterator>
#include <cstdint>
#include "infInt.hpp"

namespace inf{

	InfInt::InfInt(int64_t nb) : value{}, positive{} {
		positive = nb >= 0;
		if (nb == 0) {
			value.push_back(0);  // Cas particulier pour 0
			return;
		}
		if (!positive) nb = -nb;
		while (nb > 0) {
			value.push_front(nb % 10);  // Ajout en début pour garder l’ordre
			nb /= 10;
		}
	}

	InfInt InfInt::abs() const {
		if (!positive) return -*this;
		return *this;
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
		if (a.positive == b.positive) {
			// Case: Same signs, simply add their absolute values
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
		} else {
			// Case: Different signs, subtract the absolute values
			InfInt absa = a.abs();
			InfInt absb = b.abs();

			if (absa > absb) {
				result = absa - absb;
				result.positive = a.positive;
			} else if (absa < absb) {
				result = absb - absa;
				result.positive = b.positive;
			} else {
				result.positive = true;  // When both have same absolute value, the result is 0
				result.value.push_back(0);
			}
		}
		return result;
	}
	
	InfInt operator-(const InfInt &a, const InfInt &b) {
		InfInt result;

		// Case 1: Different signs, treat as addition of abs values
		if (a.positive != b.positive) {
			result.positive = a.positive;
			result = a.abs() + b.abs();  // Use the addition operator
			return result;
		}

		// Case 2: Same values, return 0
		if (a.abs() == b.abs()) {
			result.positive = true;
			result.value.push_back(0); // 0 result
			return result;
		}

		// Case 3: Absolute value of a bigger than absolute value of b, handle subtraction based on absolute values
		if (a.abs() > b.abs()) {
			result.positive = !a.positive; // Flip the sign since a's absolute value is greater
			auto ita = a.value.rbegin();
			auto itb = b.value.rbegin();
			uint8_t borrow = 0;

			while (itb != b.value.rend()) {
				int diff = *ita - *itb - borrow;
				if (diff < 0) {
					diff += 10;
					borrow = 1;  // Borrow when result is negative
				} else {
					borrow = 0;
				}
				result.value.push_back(diff);
				++ita;
				++itb;
			}

			// Handle the remaining digits of 'a' after 'b' is exhausted
			while (ita != a.value.rend()) {
				int diff = *ita - borrow;
				if (diff < 0) {
					diff += 10;
					borrow = 1;
				} else {
					borrow = 0;
				}
				result.value.push_back(diff);
				++ita;
			}
		}
		// Case 4: If abs(b) > abs(a), reverse the order
		else {
			result = b.abs() - a.abs();
			result.positive = a.positive;  // Sign is same as 'a'
		}

		// Remove leading zeros (if any)
		while (result.value.size() > 1 && result.value.front() == 0) {
			result.value.pop_front();
		}

		return result;
	}

    // Unary negation operator
    InfInt operator-(const InfInt& a) {
        InfInt result = a;
        result.positive = !a.positive; // Flip the sign
        return result;
    }

	InfInt operator*(const InfInt &a, const InfInt &b){
		//TODO
	}

	InfInt operator/(const InfInt &a, const InfInt &b){
		//TODO
	}

	std::strong_ordering operator<=>(const InfInt& a, const InfInt& b) {

		if (a.positive != b.positive) return a.positive <=> b.positive;
		return std::lexicographical_compare_three_way(
    		a.value.rbegin(), a.value.rend(),
        	b.value.rbegin(), b.value.rend()
		);
	}
}
