#include "BigNumber.h"
#include <string>

template <typename integer>
int utility_digit_digit_no(integer temp) {
	int digitNo = 0;
	while(temp != 0) {
		temp /= 10;
		++digitNo;
	}

	if(digitNo == 0) digitNo = 1;
	return digitNo;
}

BigNumber::BigNumber() {
	value.push_back(0);
}

BigNumber::BigNumber(const BigNumber& a) {
	value = a.value;
}

BigNumber& BigNumber::operator=(const BigNumber& a) {
	value = a.value;
	return *this;
}

BigNumber BigNumber::operator+(const BigNumber& a) const {
	BigNumber s;
	s.value.clear();
	int d1, d2, carry = 0;
	long long ds;
	for(size_t i = 0; i < value.size() || i < a.value.size() || 0 != carry; ++i) {
		if(i < value.size()) {
			d1 = value[i];
		} else {
			d1 = 0;
		}

		if(i < a.value.size()) {
			d2 = a.value[i];
		} else {
			d2 = 0;
		}

		ds = (long long)d1 + (long long)d2 + (long long)carry;
		carry = 0;
		if(ds > 999999999) {
			carry = 1;
			ds -= 1000000000;
		}
		s.value.push_back((int)ds);
	}

	return s;
}

BigNumber& BigNumber::operator+=(const BigNumber& a) {
	*this = *this + a;
	return *this;
}

BigNumber BigNumber::operator*(const BigNumber& a) const {
	BigNumber p, partialProduct;
	int d1, d2, carry = 0;
	long long dp;
	
	//se inmulteste fiecare componenta cu fiecare componenta, 
	//incepand de la ultima

	for(size_t j = 0; j < a.value.size(); ++j) {
		d2 = a.value[j];
		partialProduct.value.clear();

		//ca si la algoritmul clasic de inmultire, se adauga atatea zerouri
		//cat e ordinul cifrei pe care o inmultim
		for(size_t k = 0; k < j; ++k)
			partialProduct.value.push_back(0);

		for(size_t i = 0; (i < value.size()) || (carry != 0); ++i) {
			if(i < value.size()) {
				d1 = value[i];
			} else {
				d1 = 0;
			}
			//se inmultesc cele 2 componente de cate 9 cifre in containerul long long
			dp = (long long)d1 * (long long)d2 + (long long)carry;
			carry = 0;

			//daca numarul obtinut are mai mult de 9 cifre, este redus si se tine minte
			//restul pentru urmatoarea inmultire
			if(dp > 999999999) {
				carry = dp / 1000000000;
				dp %= 1000000000;
			}

			partialProduct.value.push_back(dp);
		}

		//se adauga fiecare produs partial la rezultat
		p += partialProduct;
	}

	return p;
}

BigNumber& BigNumber::operator*=(const BigNumber& a) {
	*this = *this * a;
	return *this;
}

std::istream& BigNumber::read(std::istream& f) {
	value.clear();
	std::string line;
	f >> line;
	bool doneReading = false;
	int missingLen = 0;
	for(int pos = line.size() - 9; !doneReading; pos -= 9) {
		if(pos < 0) {
			missingLen = pos;
			pos = 0;
			doneReading = true;
		}

		if(missingLen == -9)
			break;
		value.push_back(std::stoi(line.substr(pos, 9 + missingLen)));
	}
	return f;
}

std::ostream& BigNumber::write(std::ostream& f) {
	f << value[value.size() - 1];
	int digitNo;
	for(int i = value.size() - 2; i >= 0; --i) {
		digitNo = utility_digit_digit_no(value[i]);

		while(digitNo < 9) {
			f << 0;
			++digitNo;
		}

		f << value[i];
	}
	return f;
}

std::istream& operator>>(std::istream& s, BigNumber& a) {
	return a.read(s);
}
std::ostream& operator<<(std::ostream& s, BigNumber& a) {
	return a.write(s);
}
