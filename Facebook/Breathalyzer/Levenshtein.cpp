#include "Levenshtein.h"
#include <cctype>

using namespace std;
using namespace Exercises::Facebook;

const uint32_t Levenshtein::INVALID_DISTANCE = std::numeric_limits<unsigned char>::max();

uint32_t Levenshtein::distance(const std::string &source, const std::string &target)
{
  /// Get string lengths and test for early-out conditions
	const uint32_t sourceLength = source.size();
	const uint32_t targetLength = target.size();
	if (targetLength == 0) { return sourceLength; }
	else if (sourceLength == 0) { return targetLength; }

	/// Create edit-distance matrix
	matrix_t editDistanceMatrix(sourceLength+1);
	for (uint32_t i = 0; i <= sourceLength; ++i)
	{
	  editDistanceMatrix[i].resize(targetLength+1);
	}

	/// Initialize edit-distance matrix row/column indices
	for (uint32_t i = 0; i <= sourceLength; ++i) { editDistanceMatrix[i][0] = i; }
	for (uint32_t i = 0; i <= targetLength; ++i) { editDistanceMatrix[0][i] = i; }

	/// Flood fill edit distance values
	for (uint32_t i = 1; i <= sourceLength; ++i)
	{
	  const char currentSourceLetter = source[i-1];
	  for (uint32_t j = 1; j <= targetLength; ++j)
	  {
	    const char currentTargetLetter = target[j-1];

	    /// There is only a cost if the current letters are different
	    char cost = (::toupper(currentSourceLetter) == ::toupper(currentTargetLetter)) ? 0 : 1;

	    /// Calculate the values to consider according to the Levenshtein algorithm
	    const uint32_t above = editDistanceMatrix[i-1][j] + 1; /// = deletion
	    const uint32_t left = editDistanceMatrix[i][j-1] + 1; /// = insertion
	    const uint32_t diagonal = editDistanceMatrix[i-1][j-1] + cost; /// = substitution

	    /// Determine the final edit distance for the current cell
	    uint32_t cell = ::min(above, ::min(left, diagonal));

	    /*
	    /// (optional) Consider transposition operations, as well...
	    if ((i > 2) && (j > 2))
	    {
	      uint32_t transpose = editDistanceMatrix[i-2][j-2] + 1;
	      if (source[i-2] != currentTargetLetter) { ++transpose; }
	      if (currentSourceLetter != target[j-2]) { ++transpose; }
	      cell = ::min(cell, transpose);
	    }
	    */

	    /// Store the final value for the current cell
	    editDistanceMatrix[i][j] = cell;
	  }
	}

	/// The total edit distance will be the accumulated value
	/// in the lower-rightmost cell of the edit-distance matrix
	return editDistanceMatrix[sourceLength][targetLength];
}
