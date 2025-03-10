#ifndef INFINT_HPP
#define INFINT_HPP


namespace inf{
	class InfInt final{
	private:
		std::list<uint8_t> value;
		bool positive;
	public:
		InfInt() = default;
		InfInt(int64_t nb);
		InfInt abs() const;
		// display func
		friend std::ostream& operator<<(std::ostream &os, const InfInt &nb);
		// four basic operations
		friend InfInt operator+(const InfInt &nb1, const InfInt &nb2);
		friend InfInt operator-(const InfInt &nb1, const InfInt &nb2);
		friend InfInt operator*(const InfInt &nb1, const InfInt &nb2);
		friend InfInt operator/(const InfInt &nb1, const InfInt &nb2);
		// comparison operators
		friend std::strong_ordering operator<=>(const InfInt& nb1, const InfInt &nb2);
		friend bool operator==(const InfInt& nb1, const InfInt &nb2);
		friend bool operator!=(const InfInt& nb1, const InfInt &nb2);
	};
}

#endif // INFINT_HPP
