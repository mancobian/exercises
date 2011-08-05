#include "Levenshtein.h"
#include <cctype>
#include <iostream>

using namespace std;
using namespace Exercises::Facebook;

const uint32_t Levenshtein::INVALID_DISTANCE = std::numeric_limits<unsigned char>::max();
uint32_t Levenshtein::NUM_ROWS = 0;
uint32_t Levenshtein::NUM_COLS = 0;
Levenshtein::matrix_t Levenshtein::DISTANCE_MATRIX = Levenshtein::matrix_t();

void Levenshtein::resize(matrix_t &matrix, uint32_t rows, uint32_t columns)
{
  if (((rows + 1) > Levenshtein::NUM_ROWS) || ((columns + 1) > Levenshtein::NUM_COLS))
  {
    Levenshtein::NUM_ROWS = rows + 1;
    matrix.resize(Levenshtein::NUM_ROWS);

    Levenshtein::NUM_COLS = columns + 1;
    for (uint32_t i = 0; i < Levenshtein::NUM_ROWS; ++i)
    {
      matrix[i].resize(Levenshtein::NUM_COLS);
    }
  }
}

uint32_t Levenshtein::distance(const std::string &source, const std::string &target)
{
  /// Get string lengths and test for early-out conditions
	const uint32_t sourceLength = source.size();
	const uint32_t targetLength = target.size();
	if (targetLength == 0) { return sourceLength; }
	else if (sourceLength == 0) { return targetLength; }

	/// Lazy resize of edit-distance matrix
	Levenshtein::resize(DISTANCE_MATRIX, sourceLength, targetLength);

	/// Initialize edit-distance matrix row/column indices
	for (uint32_t i = 0; i <= sourceLength; ++i) { DISTANCE_MATRIX[i][0] = i; }
	for (uint32_t i = 0; i <= targetLength; ++i) { DISTANCE_MATRIX[0][i] = i; }

	/// Flood fill edit distance values
	for (uint32_t i = 1; i <= sourceLength; ++i)
	{
	  const char currentSourceLetter = source[i-1];
	  for (uint32_t j = 1; j <= targetLength; ++j)
	  {
	    const char currentTargetLetter = target[j-1];

	    /// There is only a cost if the current letters are different
	    char cost = (currentSourceLetter == currentTargetLetter) ? 0 : 1;

	    /// Calculate the values to consider according to the Levenshtein algorithm
	    const uint32_t above = DISTANCE_MATRIX[i-1][j] + 1; /// = deletion
	    const uint32_t left = DISTANCE_MATRIX[i][j-1] + 1; /// = insertion
	    const uint32_t diagonal = DISTANCE_MATRIX[i-1][j-1] + cost; /// = substitution

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
	    DISTANCE_MATRIX[i][j] = cell;
	  }
	}

	/// The total edit distance will be the accumulated value
	/// in the lower-rightmost cell of the edit-distance matrix
	return DISTANCE_MATRIX[sourceLength][targetLength];
}
