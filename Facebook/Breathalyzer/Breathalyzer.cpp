#include "Breathalyzer.h"
#include <cassert>

using namespace Exercises::Facebook;

uint32_t Breathalyzer::go(const std::string &sentence, const std::string &dictionaryFilename, BkTree::match_m *results)
{
  /// Error checking
  if (!results) { return 0; }

  /// Create B-K Tree from dictionary of words
  Dictionary dictionary(dictionaryFilename);
  BkTree bkTree(dictionary);

  /// Tokenize input string
  uint32_t sum = 0;
  Dictionary::string_v tokens;
  std::string delimiters = " ";
  assert (Dictionary::Utility::split(sentence, &tokens, delimiters) > 0);

  /// Sum over nearest match(es) for all input tokens
#pragma omp parallel for
  for (uint32_t i = 0; i < tokens.size(); ++i)
  {
    BkTree::match_m tokenMatches;
    BkTree::match_p tokenCandidate;
    bkTree.find(tokens[i], &tokenMatches);

    BkTree::match_m::const_iterator
      iter = tokenMatches.begin(),
      end = tokenMatches.end();

    if (BkTree::getClosest(tokenMatches, &tokenCandidate))
    {
      results->insert(tokenCandidate);
      sum += tokenCandidate.second;
    }
  }
  return sum;
}
