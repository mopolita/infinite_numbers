#ifndef INFINT_HPP
#define INFINT_HPP


namespace inf{
	class infInt{
	private:
		list<uint8_t> nb;
		bool positive;
	public:
		infInt(double nb);
		friend std::ostream& operator<<(std::ostream &os, const infInt &nb);
		// four basic operations
		friend infInt operator+(const infInt &nb1, const infInt &nb2);
		friend infInt operator-(const infInt &nb1, const infInt &nb2);
		friend infInt operator*(const infInt &nb1, const infInt &nb2);
		friend infInt operator/(const infInt &nb1, const infInt &nb2);
	};
}

#endif // INFINT_HPP
