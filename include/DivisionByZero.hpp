#ifndef DIVISIONBYZERO_HPP
#define DIVISIONBYZERO_HPP

#include <stdexcept>

namespace inf{

    class DivisionByZeroError : public std::runtime_error{
        public:
            DivisionByZeroError() : std::runtime_error("Division by zero"){}
        };
}

#endif // DIVISIONBYZERO_HPP
