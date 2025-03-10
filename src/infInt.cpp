#include <iostream>
#include <list>
#include <compare>
#include <iterator>
#include "infInt.hpp"

namespace inf{



	auto operator<=>(const infInt& a, const infInt& b) {
    	return std::lexicographical_compare_three_way(
        	a.valeur.rbegin(), a.valeur.rend(),
        	b.valeur.rbegin(), b.valeur.rend()
    	);
	}
}
