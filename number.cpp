/* You can put method and function definitions here, if you like. */

#include "number.hpp"
#include <iostream>
#include <algorithm>

#define max(a, b) ((a) > (b) ? (a) : (b))

number::number() {
    numerator.push_back(0);
    denominator.push_back(1);
}

number::number(int n) {
    if (n < 0) {
        n = n * ( - 1);
        sign = -1;
    }
    std::string temp = std::to_string(n);
    for (int i = temp.size() - 1; i >= 0; --i) {
        int a = temp[i] - '0';
        numerator.push_back(a);
    }
    denominator.push_back(1);
}

number::number(const std::vector<int> &a, const std::vector<int> &b, const int &z) {
    numerator = a;
    denominator = b;
    sign = z;
}

bool number::operator==(number b) const {
    if (numerator.size() == 1 && numerator[0] == 0 && b.numerator.size() == 1 && b.numerator[0] == 0)
	return true;
    return times(numerator, b.denominator) == times(denominator, b.numerator);
}

bool number::operator!=(number b) const { return !(*this == b); }

bool less_than(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() > b.size())
	return false;
    if (a.size() < b.size())
	return true;

    for (long int i = a.size() - 1; i >= 0; --i) {
	if (a[i] < b[i])
	    return true;
	if (b[i] < a[i])
	    return false;
    }
    return false;
}

bool number::operator<(number b) const {
    if (sign < b.sign) { return true; }
    if (sign > b.sign) { return false; }

    if (sign == -1)
        return !less_than(times(numerator, b.denominator), times(denominator, b.numerator));
    return less_than(times(numerator, b.denominator), times(denominator, b.numerator));
}

bool number::operator>(number b) const { return !(*this < b) && !(*this == b); }

bool number::operator<=(number b) const { return (*this < b) || (*this == b); }

bool number::operator>=(number b) const { return (*this > b) || (*this == b); }

number number::operator-() const { return { numerator, denominator, sign * -1 }; }

std::vector<int> times(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> c;
    for (long long unsigned int i = 0; i < a.size(); i++) {
	for (long long unsigned int j = 0, carry = 0; j < b.size() || carry; j++) {
	    if (i + j == c.size()) {
		c.push_back(0);
	    }
	    int cur = c[i+j] + a[i] * (j < b.size() ? b[j] : 0) + carry;
	    c[i+j] = cur % 10;
	    carry = cur / 10;
	}
    }
    while (c.size() > 1 && c.back() == 0)
	c.pop_back();
    return c;
}

number number::operator*(const number& b) const {
    std::vector<int> numerator_result = times(numerator, b.numerator);

    std::vector<int> denominator_result = times(denominator, b.denominator);

    std::vector<int> gcd = find_gcd(numerator_result, denominator_result);
    
    numerator_result = divide(numerator_result, gcd, false);
    denominator_result = divide(denominator_result, gcd, false);

    return { numerator_result, denominator_result, sign * b.sign };
}

number number::operator/(const number& b) const {
    number c(b.denominator, b.numerator, sign);
    return (*this * c);
}

std::vector<int> addition(const std::vector<int>& addend1, const std::vector<int>& addend2) {
    std::vector<int> result;
    int carry = 0;
    for (size_t i = 0; i < max(addend1.size(), addend2.size()) || carry; ++i) {
        if (i == result.size())
            result.push_back (0);
        result[i] = carry + (i < addend1.size() ? addend1[i] : 0) + (i < addend2.size() ? addend2[i] : 0);
        carry = result[i] >= 10;
	if (carry)
            result[i] -= 10;
    }
    return result;
}

number number::operator+(const number& b) const {
    std::vector<int> result_numerator = times(numerator, b.denominator);
    std::vector<int> result_denominator = times(b.numerator, denominator);
    if (sign == b.sign) {
        return { addition(result_numerator, result_denominator), times(denominator, b.denominator), sign };
    } else if (less_than(result_numerator, result_denominator)) {
        return { substraction(result_denominator, result_numerator), times(denominator, b.denominator), b.sign };
    } else {
        return { substraction(result_numerator, result_denominator), times(denominator, b.denominator), sign };
    }
}

std::vector<int> substraction(const std::vector<int>& minuend, const std::vector<int>& subtrahend) {
    std::vector<int> result;
    int carry = 0;
    for (size_t i = 0; i < minuend.size() || carry; ++i) {
        if (i == result.size())
            result.push_back(0);
        result[i] = minuend[i] - carry - (i < subtrahend.size() ? subtrahend[i] : 0);
        carry = result[i] < 0;
	if (carry)
            result[i] += 10;
    }
    while (result.size() > 1 && result.back() == 0)
        result.pop_back();
    return result;
}

number number::operator-(const number& b) const {
    return (*this + (- b));
}

std::vector<int> divide(const std::vector<int>& dividend_vector, int divisor) {
    std::vector<int> result;
    int mod = 0; 
    for (long int i = dividend_vector.size() - 1; i >= 0; --i) {
        mod = mod * 10 + dividend_vector[i];
        int quo = mod / divisor;
        result.push_back(quo);
        mod = mod % divisor;
    }
    
    std::reverse(result.begin(), result.end());

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

std::vector<int> divide(const std::vector<int>& dividend_vector, const std::vector<int>& divisor_vektor, bool return_remainder) {
    bool temp_sign = false;
    std::vector<int> result;
    result.push_back(0);
    std::vector<int> remainder = dividend_vector;

    while(less_than(divisor_vektor, remainder) || divisor_vektor == remainder) {
        std::vector<int> temp(&remainder[divisor_vektor.size() - 1], &remainder[remainder.size()]);
        std::vector r = divide(temp, divisor_vektor[divisor_vektor.size() - 1]);
        if (temp_sign) {
	    result = substraction(result, r);
            temp_sign = !temp_sign;
	} else {
	    result = addition(result, r);
	}
        std::vector<int> c = times(divisor_vektor, result);
        if (less_than(c, dividend_vector) || dividend_vector == c) {
            remainder = substraction(dividend_vector, c);
	} else {
            remainder = substraction(c, dividend_vector);
            temp_sign = !temp_sign;
	}
    }
    if (return_remainder) {
        if (temp_sign) {
            remainder = substraction(divisor_vektor, remainder);
	}
        return remainder;
    }
    while (result.size() > 1 && result.back() == 0)
	result.pop_back();
    return result;
}

std::vector<int> find_gcd(std::vector<int> a, std::vector<int> b) {
    std::vector<int> temp;
    std::vector<int> temp_number_0{0};
    if (less_than(b, a)) {
        while (b != temp_number_0) {
            temp = divide(a, b, true);
	    a = b;
            b = temp;
	}
	return a;
    } else {
        while (a != temp_number_0) {
            temp = divide(b, a, true);
	    b = a;
            a = temp;
	}
	return b;
    }
}

number number::power(int pow) const {
    if (pow > 0) {
        std::vector<int> result_numerator = numerator;
        std::vector<int> result_denominator = denominator;
        return { power_helper(result_numerator, pow), power_helper(result_denominator, pow), pow & 1? sign : 1 };
    } else if (pow < 0) {
        std::vector<int> result_nominator = denominator;
        std::vector<int> result_denominator = numerator;
        return { power_helper(result_nominator, pow * -1), power_helper(result_denominator, pow * -1), pow & 1? sign : 1 };
    } else {
        std::vector<int> result{1};
        return { result, result, 1 };
    }
}

std::vector<int> power_helper(std::vector<int> base, int exponent) {
    std::vector<int> result;
    result.push_back(1);
    while (exponent > 0) {
        if (exponent & 1)
            result = times(result, base);
        exponent = exponent >> 1;
        base = times(base, base);
    } 
    return result;
}

number number::sqrt(int b) const {
    std::vector<int> denominator_precision;
    for (int i = 0; i <= b; ++i)
        denominator_precision.push_back(0);
    denominator_precision.push_back(1);
    number precision(std::vector<int>{1}, denominator_precision, 1);

    std::vector<int> guess_numerator;
    std::vector<int> guess_denominator;
    for (long unsigned int i = 0; i < (guess_numerator.size() + 1) / 2 - 1; ++i)
        guess_numerator.push_back(0);
    guess_numerator.size() % 2 == 0 ? guess_numerator.push_back(2) : guess_numerator.push_back(7);

    for (long unsigned int i = 0; i < (guess_denominator.size() + 1) / 2 - 1; ++i)
        guess_denominator.push_back(0);
    guess_denominator.size() % 2 == 0 ? guess_denominator.push_back(2) : guess_denominator.push_back(7);

    number result(guess_numerator, guess_denominator, 1);
    number prevx;
    number temp_number_2(2);

    number temp = result;
    while (temp > precision) {
        prevx = result;
        result = (prevx + (*this / prevx)) / temp_number_2;
        prevx > result ? temp = prevx - result : temp = result - prevx;
	    
    }   
    return result;
}
