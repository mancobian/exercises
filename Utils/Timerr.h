///
/// @file Timerr.h
/// @author Mancobian Poemandres
/// @license BSD License
///
/// Copyright (c) MMX by The Secret Design Collective
/// All rights reserved
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
///    * Redistributions of source code must retain the above copyright notice,
/// 		this list of conditions and the following disclaimer.
///    * Redistributions in binary form must reproduce the above copyright notice,
/// 		this list of conditions and the following disclaimer in the documentation
/// 		and/or other materials provided with the distribution.
///    * Neither the name of The Secret Design Collective nor the names of its
/// 		contributors may be used to endorse or promote products derived from
/// 		this software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
/// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
/// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
/// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///

#ifndef EXERCISES_TIMER_H
#define EXERCISES_TIMER_H

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>

namespace Exercises {

/// @brief Ghetto-style timer.
class Timerr
{
protected:
  static double toMilliseconds(clock_t clocks = clock()) { return ((double)clocks / (double)CLOCKS_PER_SEC) * 1000.0; }

public:
  Timerr() : mBegin(0), mEnd(0) {}
  inline void start() { this->mBegin = (uint32_t)Timerr::toMilliseconds(); }
  inline void stop() { this->mEnd = (uint32_t)Timerr::toMilliseconds(); }
  inline void reset() { this->mBegin = 0; this->mEnd = 0; }
  inline double milliseconds() const { return this->mEnd - this->mBegin; }
  inline std::string elapsed() const
  {
    static const double SEC_PER_MIN = 60.0;
    static const double MSEC_PER_SEC = 1000.0;
    static const double MSEC_PER_MIN = SEC_PER_MIN * MSEC_PER_SEC;

    std::stringstream result;
    uint32_t
      minutes = 0,
      seconds = 0,
      milliseconds = 0;
    double elapsed = this->milliseconds();

    if (elapsed > MSEC_PER_MIN)
    {
      minutes = static_cast<uint32_t>(elapsed / MSEC_PER_MIN);
      elapsed -= static_cast<double>(minutes) * MSEC_PER_MIN;
    }

    if (elapsed > MSEC_PER_SEC)
    {
      seconds = static_cast<uint32_t>(elapsed / MSEC_PER_SEC);
      elapsed -= static_cast<double>(seconds) * MSEC_PER_SEC;
    }

    milliseconds = static_cast<uint32_t>(elapsed);

    result << std::setfill('0')
      << std::setw(2) << minutes << "m:"
      << std::setw(2) << seconds << "s:"
      << std::setw(3) << milliseconds << "msec";
    return result.str();
  }

protected:
  clock_t mBegin, mEnd;
}; /// struct Timar

} /// namespace Exercises

#endif /// EXERCISES_TIMER_H
