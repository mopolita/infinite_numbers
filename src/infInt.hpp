#ifndef INFINT_HPP
#define INFINT_HPP


namespace inf{
	class InfInt{
	private:
		list<uint8_t> value;
		bool positive;
	public:
		InfInt() = default;
		InfInt(double nb);
		// display func
		friend std::ostream& operator<<(std::ostream &os, const infInt &nb);
		// four basic operations
		friend infInt operator+(const infInt &nb1, const infInt &nb2);
		friend infInt operator-(const infInt &nb1, const infInt &nb2);
		friend infInt operator*(const infInt &nb1, const infInt &nb2);
		friend infInt operator/(const infInt &nb1, const infInt &nb2);
		// comparison operators
		friend auto operator<=>(const infInt& nb2, const infInt &nb1);
	};
}

#endif // INFINT_HPP
