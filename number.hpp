/* Here comes the class and toplevel function declarations (if needed). */

#include <vector>
#include <cmath>
#include <string>

class number {
    std::vector<int> numerator;
    std::vector<int> denominator;
    int sign = 1;

public:
    number();

    number(int n);

    number(const std::vector<int> &a, const std::vector<int> &b, const int &z);
    
    bool operator==(number b) const;

    bool operator!=(number b) const;

    bool operator<(number b) const;

    bool operator>(number b) const;

    bool operator<=(number b) const;

    bool operator>=(number b) const;

    number operator+(const number& b) const;

    number operator-() const;

    number operator-(const number& b) const;

    number operator*(const number& b) const;

    number operator/(const number& b) const;

    number power(int exp) const;

    number sqrt(int b) const;
};

bool less_than(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> times(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> divide(const std::vector<int>& a, const std::vector<int>& b, bool prep);
std::vector<int> divide(const std::vector<int> &a, int b);
std::vector<int> find_gcd(std::vector<int> a, std::vector<int> b);
std::vector<int> addition(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> substraction(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> power_helper(std::vector<int> x, int y);
