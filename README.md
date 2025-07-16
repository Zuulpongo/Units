# Units
> [!NOTE]
> I wrote this code in about an hour when I was bored and no I didn't test it

**Units** provides a simple way to create your own classes for units of measurement. The base class `Unit<T>` wraps an instance of `T`, providing all comparison and most arithmetic operators. Everything is fully loaded with C++20 concepts for maximum safety. If you need something compatible with older C++ standards, I'm working on it.

## How to Use
include the file bro

## Creating a Unit
To create your own unit, define your class with a template parameter `T` (or whatever you want, just change accordingly) inheriting from `Unit<T>`. Choose the base unit (this is what system the inner number will use), then implement your conversion getters and setters. Basic examples can be found at the end of `units.hpp`, or are visible right here:
```c++
#include <concepts>
#include "units.hpp"

// An example of a derived Unit class. 
// This one stores velocity in miles per hour, and allows reinterpretation into kilometers per hour and meters per second.
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

// Another example. This one closely resembles what I made that inspired this tiny project.
// This stores any measure of change over time in units per frame, but allows reinterpretation into units per second.
template <typename T>
class Unit1D : public Unit<T> {
    inline T f() const { return val; }
    inline T s() const { return val * 60.0; }
    inline void f(T v) { val = v; }
    inline void s(T v) { val = v / 60.0; }
}

// A simple Vector2 struct with x and y components, like ones seen in libraries like Raylib. 
// If a class doesn't support equality/comparison or arithmetic operators, the Unit class will still work with it,
// as long as you don't try using any of the operators.
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
```
