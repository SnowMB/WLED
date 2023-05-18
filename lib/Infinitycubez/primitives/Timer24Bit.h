#pragma once

#include "Counter.h"

/// Is a 24Bit Counter that automatically increments based on passed time
class Timer24Bit
{
public:
  /// Gives a 24 bit counter that counts to it's maximum in N seconds
  static Timer24Bit fadeInNSeconds(uint32_t n, uint32_t startTime = 0){return {Counter24Bit::MAX_VALUE/(n*1000), startTime};}

  /// Gives a 24 bit counter that counts to it's maximum in N milliseconds
  static Timer24Bit fadeInNMillis(uint32_t n, uint32_t startTime = 0){return {Counter24Bit::MAX_VALUE/n, startTime};}
  
  
  /// Gives a 24 bit counter that counts to it's maximum in N milliseconds
  inline constexpr Timer24Bit(uint32_t incrementsPerMillisecond, uint32_t startTime = 0) :
    _increment{incrementsPerMillisecond}, _lastUpdate{startTime} 
  {
    
  }

  /// Increments the counter according to the time passed since the last increment. 
  /// Uses millisecond precision for updating the counter.
  inline Counter24Bit const& update(uint32_t now)
  {
    auto passed = now - _lastUpdate;

    _counter.add(passed * _increment);

    _lastUpdate = now;

    return _counter;
  }

  /// resets the counter and the passed time
  inline void reset(uint32_t restartTime)
  {
    _counter.reset();
    _lastUpdate = restartTime;
  }

  inline void setIncrement(uint32_t incrementsPerMillisecond) { _increment=incrementsPerMillisecond;}
  inline void setFadesPerSecond(uint32_t fadesPerSecond){ _increment = Counter24Bit::MAX_VALUE/1000*fadesPerSecond;}
  inline void setFullFadeinNSeconds(uint32_t n){ _increment = Counter24Bit::MAX_VALUE/(n*1000);}
  inline void setFullFadeinNMillis(uint32_t n){ _increment = Counter24Bit::MAX_VALUE/n;}
  
  inline uint32_t increment() const {return _increment;}

private:
  Counter24Bit _counter;
  uint32_t _increment;
  uint32_t _lastUpdate;
};

