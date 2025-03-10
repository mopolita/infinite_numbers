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

	std::ostream& operator<<(std::ostream &os, const InfInt &nb) {
		if (!nb.positive) os << '-';

		for (auto it = nb.value.begin(); it != nb.value.end(); ++it) {
			os << static_cast<int>(*it);
		}
		
		return os;
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
