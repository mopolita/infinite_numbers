#include <iostream>
#include <list>
#include <compare>
#include <iterator>
#include <cstdint>
#include "infInt.hpp"

namespace inf{

	InfInt::InfInt(int64_t nb) : value{}, positive{} {
		positive = nb >= 0;
		if (!positive) nb = -nb;
		if (nb == 0) {
			value.push_back(0);  // Cas particulier pour 0
			return;
		}

		while (nb > 0) {
			value.push_front(nb % 10);  // Ajout en début pour garder l’ordre
			nb /= 10;
		}
	}

	InfInt InfInt::abs() const {
		InfInt result = *this;
		result.positive = true;
		return result;
	}

	std::ostream& operator<<(std::ostream &os, const InfInt &nb) {
		if (!nb.positive) os << '-';

		for (auto it = nb.value.begin(); it != nb.value.end(); ++it) {
			os << static_cast<int>(*it);
		}
		
		return os;
	}

	InfInt operator+(const InfInt &nb1, const InfInt &nb2){
		InfInt result;
		if (nb1.positive == nb2.positive) {
			result.positive = nb1.positive;
			auto it1 = nb1.value.rbegin();
			auto it2 = nb2.value.rbegin();
			uint8_t carry = 0;
			while (it1 != nb1.value.rend() || it2 != nb2.value.rend() || carry) {
				uint8_t sum = carry;
				if (it1 != nb1.value.rend()) {
					sum += *it1;
					++it1;
				}
				if (it2 != nb2.value.rend()) {
					sum += *it2;
					++it2;
				}
				carry = sum / 10;
				result.value.push_front(sum % 10);
			}
		}
		else {
			InfInt absnb1 = nb1.abs();
			InfInt absnb2 = nb2.abs();
			if (absnb1 < absnb2) {
				result = absnb2 - absnb1;
				result.positive = nb2.positive;
			}
			else {
				result = absnb1 - absnb2;
				result.positive = nb1.positive;
			}
		}
		return result;
	}

	/* what i want to do :
	if (a and b are different signs){
		sign of result is sign of a
		value of result is abs value of a + abs value of b
	}
	else{
		if (abs of a > abs of b){
			sign of result is sign of a
			starting with the last number till the first (rbegin -> to rend)
			add the carry to b
			set the carry to 0
			if the number of a is bigger just do (nb1 - nb2), else do (nb1+10 - nb2 and add 1 to the carry)
			push the number to the front of result
		}
		else{
			sign of result is sign of b
			same thing than before, but invert a and b
		}
	}

	*/
	InfInt operator-(const InfInt &nb1, const InfInt &nb2){
		InfInt result;
		if (nb1.positive == nb2.positive) {
			if (nb1 > nb2) {
				result.positive = nb1.positive;
				auto it1 = nb1.value.rbegin();
				auto it2 = nb2.value.rbegin();
				uint8_t carry = 0;
				while (it1 != nb1.value.rend() || it2 != nb2.value.rend() || carry) {
					uint8_t diff = carry;
					if (it1 != nb1.value.rend()) {
						diff += *it1;
						++it1;
					}
					if (it2 != nb2.value.rend()) {
						diff -= *it2;
						++it2;
					}
					if (diff < 0) {
						diff += 10;
						carry = 1;
					}
					else carry = 0;
					result.value.push_front(diff);
				}
			}
			else {
				result = nb2 - nb1;
				result.positive = !nb1.positive;
			}
		}
		else {
			result = nb1.abs() + nb2.abs();
		}
		return result;
	}

	InfInt operator*(const InfInt &nb1, const InfInt &nb2){

	}

	InfInt operator/(const InfInt &nb1, const InfInt &nb2){

	}


	std::strong_ordering operator<=>(const InfInt& a, const InfInt& b) {
    	
		if (a.positive == b.positive) {
			return std::lexicographical_compare_three_way(
        		a.value.rbegin(), a.value.rend(),
        		b.value.rbegin(), b.value.rend()
    		);
		}
		else {
			return a.positive <=> b.positive;
		}
	}

	bool operator==(const InfInt& a, const InfInt& b) {
		return a <=> b == 0;
	}

	bool operator!=(const InfInt& a, const InfInt& b) {
		return a <=> b != 0;
	}
}
