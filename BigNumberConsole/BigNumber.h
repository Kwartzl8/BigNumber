#pragma once
#include <istream>
#include <vector>

class BigNumber {
/*---------------------------------------------------------
* Author: Alexandru Dobra
* GitHub: https://github.com/Kwartzl8
* Date: 06/10/2021
* 
* A class that allows creation of and operations on integers 
* with arbitrary length (maximum 36 billion digits).
* 
* Currently, only positive integers are supported and the
* operations are limited to addition, multiplication and
* exponentiation.
* 
* TODO: error checking on most inputs
* 
----------------------------------------------------------*/

	std::vector <int> value;
public:
	BigNumber();
	BigNumber(const BigNumber&);
	template <typename integer>
	inline BigNumber(const integer& x) { *this = x; }

	std::istream& read(std::istream& stream);
	std::ostream& write(std::ostream&);

	BigNumber& operator= (const BigNumber&);

	template <typename integer>
	BigNumber& operator=(integer x) {
		value.clear();

		//make sure the components do not exceed 9 digits
		while(x != 0) {
			value.push_back(x % 1000000000);
			x /= 1000000000;
		}
		return *this;
	}

	BigNumber operator+ (const BigNumber&) const;
	BigNumber& operator+= (const BigNumber&);

	template <typename integer>
	BigNumber operator+ (const integer& x) const {
		BigNumber a = x;
		a += *this;
		return a;
	}
	template <typename integer>
	BigNumber& operator+= (const integer& x) {
		BigNumber a = x;
		*this += a;
		return *this;
	}

	BigNumber operator*(const BigNumber&) const;
	BigNumber& operator*= (const BigNumber&);

	template <typename integer>
	BigNumber operator* (const integer& x) const {
		BigNumber a = x;
		a *= *this;
		return a;
	}
	template <typename integer>
	BigNumber& operator*= (const integer& x) {
		BigNumber a = x;
		*this *= a;
		return *this;
	}

	template <typename integer>
	BigNumber operator^ (const integer& x) const {
		BigNumber a = *this;
		for(integer i = 1; i < x; ++i) {
			a *= *this;
		}
		return a;
	}
};

template <typename integer>
BigNumber operator+(const integer& x, const BigNumber& a) {
	BigNumber s = x;
	s += a;
	return s;
}

template <typename integer>
BigNumber operator*(const integer& x, const BigNumber& a) {
	BigNumber p = x;
	p *= a;
	return p;
}

std::istream& operator>>(std::istream& s, BigNumber& a);
std::ostream& operator<<(std::ostream& s, BigNumber& a);