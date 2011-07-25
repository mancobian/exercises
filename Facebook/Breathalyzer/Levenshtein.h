/*
 * Levenshtein.h
 *
 *  Created on: Jul 24, 2011
 *      Author: arris
 */

#ifndef LEVENSHTEIN_H_
#define LEVENSHTEIN_H_

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
};

}
}

#endif /* LEVENSHTEIN_H_ */
