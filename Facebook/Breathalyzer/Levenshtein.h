///
/// @file Levenshtein.h
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
///     this list of conditions and the following disclaimer.
///    * Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///    * Neither the name of The Secret Design Collective nor the names of its
///     contributors may be used to endorse or promote products derived from
///     this software without specific prior written permission.
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

#ifndef EXERCISES_FACEBOOK_LEVENSHTEIN_H
#define EXERCISES_FACEBOOK_LEVENSHTEIN_H

#include <string>
#include <vector>
#include <tr1/climits>
#include <tr1/cstdint>

namespace Exercises {
namespace Facebook {

/// @url http://en.wikipedia.org/wiki/Levenshtein_distance
class Levenshtein
{
public:
  typedef std::vector<std::vector<uint32_t> > matrix_t;
  static const uint32_t INVALID_DISTANCE;

	static uint32_t distance(const std::string &source, const std::string &target);

protected:
	static uint32_t NUM_ROWS, NUM_COLS;
	static matrix_t DISTANCE_MATRIX;

	static void resize(matrix_t &matrix, uint32_t rows, uint32_t columns);
}; /// class Levenshtein

} /// namespace Facebook
} /// namespace Exercises

#endif /// EXERCISES_FACEBOOK_LEVENSHTEIN_H
