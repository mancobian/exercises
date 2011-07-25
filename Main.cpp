#include <iostream>
#include "Facebook/Breathalyzer/Breathalyzer.h"

using namespace Exercises::Facebook;

int main(int argc, char **argv)
{
  /// Local vars
  std::string input,
    inputFile("Facebook/Breathalyzer/Resources/input.txt"),
    dictionaryFile("Facebook/Breathalyzer/Resources/twl06.txt");
  BkTree::match_m results;

  std::cout << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << "EXERCISES > FACEBOOK > BREATHALYZER" << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << std::endl;
  std::cout << "[SETUP] Input file: " << inputFile << std::endl;
  std::cout << "[SETUP] Dictionary file: " << dictionaryFile << std::endl;

  /// Build search tree
  std::cout << std::endl;
  std::cout << "[EXECUTE] Reading input file..." << std::endl;

  Dictionary::Utility::read(inputFile, &input);

  /// Analyze input
  std::cout << std::endl;
  std::cout << "[EXECUTE] Building B-K Tree from the specified dictionary and analyzing input for edit distances..." << std::endl;

  Breathalyzer::go(input, dictionaryFile, &results);

  /// Display result output
  std::cout << std::endl;
  std::cout << "[REPORT] Calculated the following output: " << std::endl;
  std::cout << "\tNearest Match" << " => " << "Edit Distance" << std::endl;

  uint32_t result = 0;
  BkTree::match_m::iterator
    iter = results.begin(),
    end = results.end();
  for (; iter != end; ++iter)
  {
    std::cout << "\t" << iter->first << " => " << iter->second << std::endl;
    result += iter->second;
  }

  /// Display solution
  std::cout << std::endl;
  std::cout << "[REPORT] Minimum edit distance: " << result << std::endl;
  return 0;
}
