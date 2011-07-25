#ifndef BREATHALYZER_H_
#define BREATHALYZER_H_

#include "Facebook/Breathalyzer/Dictionary.h"
#include "Facebook/Breathalyzer/Levenshtein.h"
#include "Facebook/Breathalyzer/BkTree.h"

namespace Exercises {
namespace Facebook {

class Breathalyzer
{
public:
  static uint32_t go(const std::string &sentence, const std::string &dictionaryFilename, BkTree::match_m *results = NULL);
}; /// class Breathalyzer

} /// namespace Facebook
} /// namespace Exercises

#endif /* BREATHALYZER_H_ */
