#ifndef INFINT_HPP
#define INFINT_HPP


namespace inf{
	class InfInt final{
	private:
		std::list<uint8_t> value;
		bool positive;
		void removeLeadingZeros();
	public:
		InfInt() = default;
		InfInt(int64_t nb);
		InfInt abs() const;
		// display func
		friend std::ostream& operator<<(std::ostream &os, const InfInt &nb);
		// basic operations
		friend InfInt operator+(const InfInt &a, const InfInt &b);
		friend InfInt operator-(const InfInt& a);
		friend InfInt operator-(const InfInt &a, const InfInt &b);
		friend InfInt operator*(const InfInt &a, const InfInt &b);
		friend InfInt operator/(const InfInt &a, const InfInt &b);
		// comparison operators
		friend std::strong_ordering operator<=>(const InfInt& a, const InfInt &b);
		friend bool operator==(const InfInt& a, const InfInt &b) { return a <=> b == 0; }
		friend bool operator!=(const InfInt& a, const InfInt &b) { return a <=> b != 0; }
	};
}

#endif // INFINT_HPP
