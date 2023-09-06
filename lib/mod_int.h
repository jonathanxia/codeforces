#include <lib/common.h>
#include <lib/nt.h>

struct ModInt {
    ll m_value;
    ll m_mod;
    ModInt(ll init_value = 0LL, ll modulo = MOD)
        : m_value { mod(init_value, modulo) }
        , m_mod { modulo }
    {
    }
    // Update function to keep m_value between [0, modulo - 1]
    void update()
    {
        m_value = mod(m_value, m_mod);
    }
    ModInt inv() const
    {
        return { nt::inv(m_value, m_mod), m_mod };
    }
    friend ModInt inv(const ModInt& param)
    {
        return param.inv();
    }
    ModInt pow(ll exponent) const
    {
        return {nt::pow(m_value, exponent, m_mod), m_mod};
    }
    friend ModInt pow(const ModInt& base, ll exponent)
    {
        return base.pow(exponent);
    }
    template <typename T>
    ModInt operator+(const T& rhs) const
    {
        return { mod(m_value + mod(rhs, m_mod), m_mod), m_mod };
    }
    ModInt operator+(const ModInt& rhs) const
    {
        return *this + rhs.m_value;
    }
    template <typename T>
    friend ModInt operator+(const T& lhs, const ModInt& rhs)
    {
        return rhs + lhs;
    }
    template <typename T>
    const ModInt& operator+=(const T& rhs)
    {
        *this = *this + rhs;
        return *this;
    }
    template <typename T>
    ModInt operator-(const T& rhs) const
    {
        return { mod(m_value - mod(rhs, m_mod), m_mod), m_mod };
    }
    ModInt operator-(const ModInt& rhs) const
    {
        return *this - rhs.m_value;
    }
    ModInt operator-() const
    {
        // Unary operator
        return { -m_value, m_mod };
    }
    template <typename T>
    friend ModInt operator-(const T& lhs, const ModInt& rhs)
    {
        return -rhs + lhs;
    }
    template <typename T>
    const ModInt& operator-=(const T& rhs)
    {
        *this = *this - rhs;
        return *this;
    }
    template <typename T>
    ModInt operator*(const T& rhs) const
    {
        return { mod(m_value * mod(rhs, m_mod), m_mod), m_mod };
    }
    ModInt operator*(const ModInt& rhs) const
    {
        return *this * rhs.m_value;
    }
    template <typename T>
    friend ModInt operator*(const T& lhs, const ModInt& rhs)
    {
        return rhs * lhs;
    }
    template <typename T>
    const ModInt& operator*=(const T& rhs)
    {
        *this = *this * rhs;
        return *this;
    }
    template <typename T>
    ModInt operator/(const T& rhs) const
    {
        return { nt::mdiv(m_value, rhs, m_mod), m_mod };
    }
    ModInt operator/(const ModInt& rhs) const
    {
        return *this / rhs.m_value;
    }
    template <typename T>
    friend ModInt operator/(const T& lhs, const ModInt& rhs)
    {
        return rhs.inv() * lhs;
    }
    template <typename T>
    const ModInt& operator/=(const T& rhs)
    {
        *this = *this / rhs;
        return *this;
    }
    // Increment
    const ModInt& operator++()
    {
        *this += 1;
        update();
        return *this;
    }
    const ModInt operator++(int)
    {
        *this += 1;
        update();
        return *this - 1;
    }
    // Decrement
    const ModInt& operator--()
    {
        *this -= 1;
        update();
        return *this;
    }
    const ModInt operator--(int)
    {
        *this -= 1;
        update();
        return *this + 1;
    }
    // Casting
    template <typename T>
    operator T() const { return static_cast<T>(m_value); };
    // Printing
    friend std::ostream& operator<<(std::ostream& os, const ModInt& rhs)
    {
        return os << rhs.m_value;
    }
    // Input
    friend std::istream& operator>>(std::istream& is, ModInt& rhs)
    {
        is >> rhs.m_value;
        rhs.update();
        return is;
    }
};

typedef ModInt MI;
typedef vector<MI> vMI;
typedef vector<vMI> vvMI;
typedef pair<MI, MI> pMI;
typedef vector<pMI> vpMI;
typedef vector<vpMI> vvpMI;
