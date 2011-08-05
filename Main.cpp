#include <iostream>
#include "Utils/Timerr.h"
#include "Facebook/Breathalyzer/Breathalyzer.h"

using namespace Exercises;
using namespace Exercises::Facebook;

int main(int argc, char **argv)
{
  /// Local vars
  std::string input,
    inputFile("Facebook/Breathalyzer/Resources/input.txt"),
    dictionaryFile("Facebook/Breathalyzer/Resources/twl06.txt");
  BkTree::match_m results;
  Timerr timerr;

  std::cout << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << "EXERCISES > FACEBOOK > BREATHALYZER" << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << std::endl;
  std::cout << "[SETUP] Input file: " << inputFile << std::endl;
  std::cout << "[SETUP] Dictionary file: " << dictionaryFile << std::endl;

  /// Read input
  std::cout << std::endl;
  std::cout << "[EXECUTE] Reading input file";

  timerr.start();
  Dictionary::Utility::read(inputFile, &input);
  timerr.stop();
  std::cout << " (" << timerr.elapsed() << ")" << std::endl;
  timerr.reset();

  /// Build search tree
  std::cout << std::endl;
  std::cout << "[EXECUTE] Building B-K Tree from the specified dictionary";
  timerr.start();
  Breathalyzer breathalyzer(dictionaryFile);
  timerr.stop();
  std::cout << " (" << timerr.elapsed() << ")" << std::endl;
  timerr.reset();

  /// Analyze input
  std::cout << std::endl;
  std::cout << "[EXECUTE] Analyzing input for Levenshtein edit distances";
  timerr.start();
  breathalyzer.run(input, &results);
  timerr.stop();
  std::cout << " (" << timerr.elapsed() << ")" << std::endl;
  timerr.reset();

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
