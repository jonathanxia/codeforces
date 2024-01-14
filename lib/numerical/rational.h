#include <lib/common.h>

template <typename T=ll>
struct Rational {
    T numerator;
    T denominator;

    // Constructor
    Rational(T num=0, T denom=1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }

        // Simplify the fraction
        simplify();
    }

    // Conversion operators to int, long long, and double
    operator int() const {
        return static_cast<int>(numerator / denominator);
    }

    operator long long() const {
        return static_cast<long long>(numerator / denominator);
    }

    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Overload arithmetic operators for Rational and other types
    template <typename U>
    friend Rational<T> operator+(const Rational<T>& lhs, const U& rhs) {
        return lhs + Rational<T>(rhs, 1);
    }

    template <typename U>
    friend Rational<T> operator+(const U& lhs, const Rational<T>& rhs) {
        return Rational<T>(lhs, 1) + rhs;
    }

    template <typename U>
    friend Rational<T> operator-(const Rational<T>& lhs, const U& rhs) {
        return lhs - Rational<T>(rhs, 1);
    }

    template <typename U>
    friend Rational<T> operator-(const U& lhs, const Rational<T>& rhs) {
        return Rational<T>(lhs, 1) - rhs;
    }

    template <typename U>
    friend Rational<T> operator*(const Rational<T>& lhs, const U& rhs) {
        return lhs * Rational<T>(rhs, 1);
    }

    template <typename U>
    friend Rational<T> operator*(const U& lhs, const Rational<T>& rhs) {
        return Rational<T>(lhs, 1) * rhs;
    }

    template <typename U>
    friend Rational<T> operator/(const Rational<T>& lhs, const U& rhs) {
        return lhs / Rational<T>(rhs, 1);
    }

    template <typename U>
    friend Rational<T> operator/(const U& lhs, const Rational<T>& rhs) {
        return Rational<T>(lhs, 1) / rhs;
    }

    // Overload arithmetic operators for Rational and Rational
    Rational operator+(const Rational& other) const {
        T num = numerator * other.denominator + other.numerator * denominator;
        T denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational operator-(const Rational& other) const {
        T num = numerator * other.denominator - other.numerator * denominator;
        T denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational operator*(const Rational& other) const {
        T num = numerator * other.numerator;
        T denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Cannot divide by zero.");
        }

        T num = numerator * other.denominator;
        T denom = denominator * other.numerator;
        return Rational(num, denom);
    }

    // Overload comparison operators
    bool operator==(const Rational& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }

    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator<=(const Rational& other) const {
        return numerator * other.denominator <= other.numerator * denominator;
    }

    bool operator>(const Rational& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    bool operator>=(const Rational& other) const {
        return numerator * other.denominator >= other.numerator * denominator;
    }

    // Overload unary operators
    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator, denominator);
    }

    // Floor and ceil methods
    double floor() const {
        return std::floor(static_cast<double>(numerator) / denominator);
    }

    double ceil() const {
        return std::ceil(static_cast<double>(numerator) / denominator);
    }

    // Pre-increment operator
    Rational& operator++() {
        numerator += denominator;
        simplify();
        return *this;
    }

    // Pre-decrement operator
    Rational& operator--() {
        numerator -= denominator;
        simplify();
        return *this;
    }

private:
    // Helper function to simplify the fraction
    void simplify() {
        // Use the greatest common divisor (gcd) to simplify the fraction
        T g = std::gcd(numerator, denominator);

        numerator /= g;
        denominator /= g;

        // Ensure the denominator is positive
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
};

// Overload the << operator to easily print Rational numbers
template <typename T>
std::ostream& operator<<(std::ostream& os, const Rational<T>& rational) {
    os << rational.numerator;
    if (rational.denominator != 1) {
        os << "/" << rational.denominator;
    }
    return os;
}
