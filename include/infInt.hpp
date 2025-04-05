#ifndef INFINT_HPP
#define INFINT_HPP

#include <iostream>
#include <deque>

namespace inf{
	class InfInt{
	private:
		std::deque<uint8_t> value;
		bool positive;
		void removeLeadingZeros();
		InfInt abs() const noexcept;
	public:
		InfInt(): InfInt{0}{}; // default constructor
		InfInt(const InfInt &other) = default; // copy constructor
		InfInt(int64_t nb);
		InfInt operator-() const noexcept;

		// display func
		friend std::ostream& operator<<(std::ostream &os, const InfInt &nb);

		// basic operations
		friend InfInt operator+(const InfInt &a, const InfInt &b);
		friend InfInt operator-(const InfInt &a, const InfInt &b);
		friend InfInt operator*(const InfInt &a, int64_t b);
		friend InfInt operator*(int64_t a, const InfInt &b) { return b*a; }
		friend InfInt operator*(const InfInt &a, const InfInt &b);
		friend InfInt operator/(const InfInt &a, const InfInt &b);

		// comparison operators
		friend std::strong_ordering operator<=>(const InfInt& a, const InfInt& b);
		friend bool operator==(const InfInt& a, const InfInt &b) { return a <=> b == 0; }
		friend bool operator!=(const InfInt& a, const InfInt &b) { return a <=> b != 0; }
	};
}

#endif // INFINT_HPP
