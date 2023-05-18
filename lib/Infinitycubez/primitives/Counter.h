#pragma once

#include <stdint.h>
#include <limits>


template<typename T, T MAX = std::numerical_limits<T>::max()>
class Counter
{
public:
  static constexpr T MAX_VALUE = MAX;

  /// create a counter that reached it's maximum value and is about to wrap around.
  /// Has exactly 1 overflow.
  inline static Counter oneLed() {return {MAX_VALUE};}

  /// create a counter that achieved n overflows and wraps around
  inline static Counter nLeds(T n) { return {n*MAX_VALUE};}

  constexpr Counter() = default;
  constexpr Counter(Counter const& other) = default;
  constexpr Counter(Counter && other) = default;
  inline constexpr Counter(T val): _value(val){}

  virtual ~Counter() = default;

  /// converts the counter value to 8 bit (0-255) only gives full increments (equal to calling floor())
  inline constexpr uint8_t as8bit() const
  {
    return (_value/0x10000)&0xFF; //16bits because 24bits are one full led blend, but we need 1/256th of that
  }

  /// Just resets the leading 8 bits of the counter.
  inline constexpr void resetOverflows() { _value%=MAX_VALUE; }

  /// resets the internal counter to 0. Also resets overflows.
  inline constexpr void reset() {_value=0;}

  /// convinience function. Same as operator+
  inline constexpr void add(T i) {_value+=i;}

  /// convinience function. Same as operator-
  inline constexpr void sub(T i) {_value-=i;}

  /// return the overflows. Usefull to check if the counter wrapped around
  inline constexpr T overflows() const {return _value/MAX_VALUE;}

  /// return the 24bit value
  inline constexpr T value() const {return _value%(MAX_VALUE);}

  /// return the raw 32 bit value including overflows
  inline constexpr T raw() const {return _value;}

  /// Returns if the counter is at least overflown once
  inline constexpr bool isOverflown() const {return overflows()>0;}

  inline constexpr Counter& operator=(Counter const& other) = default;
  inline constexpr Counter& operator=(Counter && other) = default;
  inline constexpr Counter& operator=(T const& other) {_value = other; return *this;}

  inline constexpr Counter& operator+=(Counter const& rhs)
  {                           
    _value+= rhs._value;
    return *this;
  }

  inline constexpr Counter& operator+=(T const& rhs)
  {
    _value+= rhs;
    return *this;
  }


  inline constexpr Counter& operator-=(Counter const& rhs)
  {
    _value-= rhs._value;
    return *this;
  }

  inline constexpr Counter& operator-=(T const& rhs)
  {
    _value-= rhs;
    return *this;
  }

  inline constexpr Counter& operator++()
  {
    _value++;
    return *this;
  }

  inline constexpr Counter operator++(int)
  {
      Counter tmp(*this);
      operator++();
      return tmp;
  }

  inline constexpr Counter& operator--()
  {
    _value--;
    return *this;
  }

  inline constexpr Counter operator--(int)
  {
      Counter tmp(*this);
      operator--();
      return tmp;
  }

  friend inline constexpr Counter operator+(Counter lhs, Counter const& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend inline constexpr Counter operator+(Counter lhs, T rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend inline constexpr Counter operator-(Counter lhs, Counter const& rhs)
  {
    lhs -= rhs;
    return lhs;
  }

  friend inline constexpr Counter operator-(Counter lhs, T rhs)
  {
    lhs -= rhs;
    return lhs;
  }

private:
  T _value = 0; 
};

/// Counter that uses 24 bits of a 32 bit number to count fades or timings.
/// Is aimed at replacing 8 bit counting of fade levels to give better timing precision.
/// The last 8 bits are used to store overflows (up to 255). So this counter can be used 
/// for very fast fades that fade in multiple leds at once or very slow fades that can't be handled
/// by using a byte to count.
using Counter24Bit = Counter<uint32_t, 0x1000000>;
static_assert(sizeof(Counter24Bit) == sizeof(uint32_t));

