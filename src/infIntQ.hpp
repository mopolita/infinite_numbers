#ifndef INFINTQ_HPP
#define INFINTQ_HPP

#include <iostream>
#include <deque>

namespace inf{
	class InfIntQ{
	private:
		std::deque<uint8_t> value;
		bool positive;
		void removeLeadingZeros();
		InfIntQ abs() const noexcept;
	public:
		InfIntQ() = default;
		InfIntQ(int64_t nb);
		InfIntQ operator-() const noexcept;

		// display func
		friend std::ostream& operator<<(std::ostream &os, const InfIntQ &nb);

		// basic operations
		friend InfIntQ operator+(const InfIntQ &a, const InfIntQ &b);
		friend InfIntQ operator-(const InfIntQ &a, const InfIntQ &b);
		friend InfIntQ operator*(const InfIntQ &a, int64_t b);
		friend InfIntQ operator*(int64_t a, const InfIntQ &b) { return b*a; }
		friend InfIntQ operator*(const InfIntQ &a, const InfIntQ &b);
		friend InfIntQ operator/(const InfIntQ &a, const InfIntQ &b);

		// comparison operators
		friend std::strong_ordering operator<=>(const InfIntQ& a, const InfIntQ &b);
		friend bool operator==(const InfIntQ& a, const InfIntQ &b) { return a <=> b == 0; }
		friend bool operator!=(const InfIntQ& a, const InfIntQ &b) { return a <=> b != 0; }
	};
}

#endif // INFINTQ_HPP
