#include <iostream>
#include <list>
#include <compare>
#include <iterator>
#include "infInt.hpp"

namespace inf{

	InfInt::InfInt(double nb): value{}, positive{true} 
	{
		positive = nb >= 0;
		while(nb > 0){
			value.push_back(nb%10);
			nb/10;
		}
	}

	std::ostream& operator<<(std::ostream &os, const infInt &nb){
		if(!positive) os << '-';
		for (auto it = value.rbegin(), it < value.rend(), it++){
			os << *it;
		}
		return os
	}

	auto operator<=>(const infInt& a, const infInt& b) {
    	return std::lexicographical_compare_three_way(
        	a.value.rbegin(), a.value.rend(),
        	b.value.rbegin(), b.value.rend()
    	);
	}
}
