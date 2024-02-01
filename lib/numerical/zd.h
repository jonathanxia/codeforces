#include <lib/common.h>

template <typename F, long long D>
struct ZD {
    F a, b; // Elements of the form a + b√d

    // Default constructor with both parameters set to 0
    ZD() : a(0), b(0) {}

    // Constructor with only 'a' provided, defaults 'b' to 0
    ZD(F a_) : a(a_), b(0) {}

    // Constructor
    ZD(F a_, F b_) : a(a_), b(b_) {}

    // Addition operator
    ZD<F, D> operator+(const ZD<F, D>& other) const {
        return {a + other.a, b + other.b};
    }

    // Subtraction operator
    ZD<F, D> operator-(const ZD<F, D>& other) const {
        return {a - other.a, b - other.b};
    }

    // Multiplication operator
    ZD<F, D> operator*(const ZD<F, D>& other) const {
        F resultA = a * other.a + b * other.b * D;
        F resultB = a * other.b + b * other.a;
        return {resultA, resultB};
    }

    // Division operator
    ZD<F, D> operator/(const ZD<F, D>& other) const {
        F divisor = other.a * other.a - other.b * other.b * D;
        F resultA = (a * other.a + b * other.b * D) / divisor;
        F resultB = (b * other.a - a * other.b) / divisor;
        return {resultA, resultB};
    }

    // Addition assignment operator
    ZD<F, D>& operator+=(const ZD<F, D>& other) {
        a += other.a;
        b += other.b;
        return *this;
    }

    // Subtraction assignment operator
    ZD<F, D>& operator-=(const ZD<F, D>& other) {
        a -= other.a;
        b -= other.b;
        return *this;
    }

    // Multiplication assignment operator
    ZD<F, D>& operator*=(const ZD<F, D>& other) {
        F resultA = a * other.a + b * other.b * D;
        F resultB = a * other.b + b * other.a;
        a = resultA;
        b = resultB;
        return *this;
    }

    // Division assignment operator
    ZD<F, D>& operator/=(const ZD<F, D>& other) {
        F divisor = other.a * other.a - other.b * other.b * D;
        F resultA = (a * other.a + b * other.b * D) / divisor;
        F resultB = (b * other.a - a * other.b) / divisor;
        a = resultA;
        b = resultB;
        return *this;
    }

    // Multiplication by scalar operator (ZD * scalar)
    template<typename T>
    ZD<F, D> operator*(const T& scalar) const {
        return {a * F(scalar), b * F(scalar)};
    }

    // Division by scalar operator (ZD / scalar)
    template <typename T>
    ZD<F, D> operator/(const T& scalar) const {
        return {a / F(scalar), b / F(scalar)};
    }

    // Addition with scalar operator (ZD + scalar)
    template <typename T>
    ZD<F, D> operator+(const T& scalar) const {
        return {a + F(scalar), b};
    }

    // Subtraction with scalar operator (ZD - scalar)
    template <typename T>
    ZD<F, D> operator-(const T& scalar) const {
        return {a - F(scalar), b};
    }

    // Negation operator
    ZD<F, D> operator-() const {
        return {-a, -b};
    }

    // Pow method to raise the ZD to the power of an integer exponent
    ZD<F, D> pow(ll exponent) const {
        if (exponent == 0) {
            return ZD<F, D>(1);
        }

        ZD<F, D> base = *this;
        ZD<F, D> result(1);
        ll e = abs(exponent);
        while (e > 0) {
            if (e & 1) result *= base;
            base *= base;
            e /= 2;
        }

        return (exponent > 0) ? result : ZD<F, D>(1) / result;
    }

    // Conversion operator to cast to another numeric type U
    template <typename U>
    operator ZD<U, D>() const {
        return {static_cast<U>(a), static_cast<U>(b)};
    }

    // Output stream operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const ZD<F, D>& element) {
        os << element.a;
        if (element.b != F(0)) {
            os << "+" << element.b << "√" << D;
        }
        return os;
    }

    // Equality operator
    bool operator==(const ZD<F, D>& other) const {
        return (a == other.a) && (b == other.b);
    }

    // Inequality operator
    bool operator!=(const ZD<F, D>& other) const {
        return !(*this == other);
    }

    // Equality operator with scalar on the left side (scalar == ZD)
    template <typename U>
    friend bool operator==(const U& scalar, const ZD<F, D>& zd) {
        return (scalar == zd.a) && (zd.b == F(0));
    }

    // Equality operator with scalar on the right side (ZD == scalar)
    template <typename U>
    friend bool operator==(const ZD<F, D>& zd, const U& scalar) {
        return (zd.a == scalar) && (zd.b == F(0));
    }

    // Inequality operator with scalar on the left side (scalar != ZD)
    template <typename U>
    friend bool operator!=(const U& scalar, const ZD<F, D>& zd) {
        return !(scalar == zd);
    }

    // Inequality operator with scalar on the right side (ZD != scalar)
    template <typename U>
    friend bool operator!=(const ZD<F, D>& zd, const U& scalar) {
        return !(zd == scalar);
    }
};

