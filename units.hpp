#pragma once

#include <concepts>
#include <ostream>

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

// A wrapper for a base type `T` that allows reinterpretation of the value based on different needs.
// Derive your own class from this one and implement your own unit functions which interpret the inner `val` member in different units/systems.
// View the source code for an example.
template <Numeric T>
class Unit {
protected:
    T val;
public:
    Unit() : val{} {};
    Unit(T i) : val(i) {};

    inline const T& get() { return val; }
    inline void set(T v) { val = v; }

    template <typename U>
    explicit operator Unit<U>() const noexcept(noexcept(std::is_nothrow_convertible_v<T, U>)) { return Unit<U>(static_cast<U>(val)); }

    inline bool operator==(const Unit<T>& rhs) const noexcept requires std::equality_comparable<T> { return val == rhs.val; }
    inline bool operator!=(const Unit<T>& rhs) const noexcept requires std::equality_comparable<T> { return val != rhs.val; }
    inline bool operator<(const Unit<T>& rhs) const noexcept requires std::totally_ordered<T> { return val < rhs.val; }
    inline bool operator>(const Unit<T>& rhs) const noexcept requires std::totally_ordered<T> { return val > rhs.val; }
    inline bool operator<=(const Unit<T>& rhs) const noexcept requires std::totally_ordered<T> { return val <= rhs.val; }
    inline bool operator>=(const Unit<T>& rhs) const noexcept requires std::totally_ordered<T> { return val >= rhs.val; }

    template <typename A, typename B> friend bool operator==(const Unit<A>& lhs, const Unit<B>& rhs) requires std::equality_comparable_with<A, B>;
    template <typename A, typename B> friend bool operator!=(const Unit<A>& lhs, const Unit<B>& rhs) requires std::equality_comparable_with<A, B>;
    template <typename A, typename B> friend bool operator<(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B>;
    template <typename A, typename B> friend bool operator>(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B>;
    template <typename A, typename B> friend bool operator<=(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B>;
    template <typename A, typename B> friend bool operator>=(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B>;

    inline Unit<T> operator+(const Unit<T>& unit) const noexcept(noexcept(T{} + T{})) { return Unit<T>(val + unit.val); }
    inline Unit<T> operator-(const Unit<T>& unit) const noexcept(noexcept(T{} - T{})) { return Unit<T>(val - unit.val); }
    inline Unit<T> operator*(const Unit<T>& unit) const noexcept(noexcept(T{} * T{})) { return Unit<T>(val * unit.val); }
    inline Unit<T> operator/(const Unit<T>& unit) const noexcept(noexcept(T{} / T{})) { return Unit<T>(val / unit.val); }
    inline Unit<T> operator%(const Unit<T>& unit) const noexcept(noexcept(T{} % T{})) requires std::is_integral_v<T> { return Unit<T>(val % unit.val); }

    template <typename A, typename B> friend Unit<decltype(A() + B())> operator+(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} + B{}));
    template <typename A, typename B> friend Unit<decltype(A() - B())> operator-(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} - B{}));
    template <typename A, typename B> friend Unit<decltype(A() * B())> operator*(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} * B{}));
    template <typename A, typename B> friend Unit<decltype(A() / B())> operator/(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} / B{}));
    template <typename A, typename B> friend Unit<decltype(A() % B())> operator%(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} % B{})) requires std::is_integral_v<A> && std::is_integral_v<B>;

    friend std::ostream& operator<<(std::ostream& os, const Unit<T>& u) { return os << u.val; }
};

template <typename A, typename B>
bool operator==(const Unit<A>& lhs, const Unit<B>& rhs) requires std::equality_comparable_with<A, B> {
    return lhs.val == rhs.val;
}

template <typename A, typename B>
bool operator!=(const Unit<A>& lhs, const Unit<B>& rhs) requires std::equality_comparable_with<A, B> {
    return lhs.val != rhs.val;
}

template <typename A, typename B>
bool operator<(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B> {
    return lhs.val < rhs.val;
}

template <typename A, typename B>
bool operator>(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B> {
    return lhs.val > rhs.val;
}

template <typename A, typename B>
bool operator<=(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B> {
    return lhs.val <= rhs.val;
}

template <typename A, typename B>
bool operator>=(const Unit<A>& lhs, const Unit<B>& rhs) requires std::totally_ordered_with<A, B> {
    return lhs.val >= rhs.val;
}

template <typename A, typename B>
Unit<decltype(A() + B())> operator+(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} + B{})) {
    using T = decltype(lhs.val + rhs.val);
    return Unit<T>(static_cast<T>(lhs.val) + static_cast<T>(rhs.val));
}

template <typename A, typename B>
Unit<decltype(A() - B())> operator-(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} - B{})) {
    using T = decltype(lhs.val - rhs.val);
    return Unit<T>(static_cast<T>(lhs.val) - static_cast<T>(rhs.val));
}

template <typename A, typename B>
Unit<decltype(A() * B())> operator*(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} * B{})) {
    using T = decltype(lhs.val * rhs.val);
    return Unit<T>(static_cast<T>(lhs.val) * static_cast<T>(rhs.val));
}

template <typename A, typename B>
Unit<decltype(A() / B())> operator/(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} / B{})) {
    using T = decltype(lhs.val / rhs.val);
    return Unit<T>(static_cast<T>(lhs.val) / static_cast<T>(rhs.val));
}

template <typename A, typename B>
Unit<decltype(A() % B())> operator%(const Unit<A>& lhs, const Unit<B>& rhs) noexcept(noexcept(A{} % B{})) requires std::is_integral_v<A> && std::is_integral_v<B> {
    using T = decltype(lhs.val % rhs.val);
    return Unit<T>(static_cast<T>(lhs.val) % static_cast<T>(rhs.val));
}

#ifdef UNITS_EXAMPLE

// An example of a derived Unit class. 
// This one stores velocity in miles/hr, and allows reinterpretation into kilometers/hr and meters/sec.
// It also implements setter functions that reinterpret the given unit into the base unit.
template <typename T>
class Velocity : public Unit<T> {
public:
    inline T mph() const { return val; }
    inline T kph() const { return val * 1.60934; }
    inline T mps() const { return val / 2.2369362921; }
    inline void mph(T v) { val = v; }
    inline void kph(T v) { val = v / 1.60934; }
    inline void mps(T v) { val = v * 2.2369362921; }
};

// A simple Vector2 struct with x and y components, like ones seen in libraries like Raylib. 
// If a class doesn't support equality/comparison or arithmetic operators, the Unit class will still work with it, as long as you don't try using any of the operators.
struct Vector2 {
    float x;
    float y;
};

// Helper concept, not necessary
template <typename T>
concept Numeric2D = std::derived_from<T, Vector2>;

template <Numeric2D T>
class Unit2D : public Unit<T> {
public:
    inline T pxps() const { return val; }
    inline T pxpf() const { return val / 60; }
    inline void pxps(T v) { val = v; }
    inline void pxpf(T v) { val = v * 60; }
};

#endif