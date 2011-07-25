#include "Dictionary.h"
#include <cassert>
#include <climits>

using namespace Exercises::Facebook;

Dictionary::Dictionary(const std::string &filename)
{
  std::string data;
  if (Dictionary::Utility::read(filename, &data) > 0)
  {
    Dictionary::Utility::split(data, &this->mEntries);
  }
}

Dictionary::~Dictionary()
{

}

uint32_t Dictionary::Utility::getFileSize(std::ifstream &ifile)
{
  ifile.seekg (0, std::ios::end);
  uint32_t size = static_cast<uint32_t>(ifile.tellg());
  assert(size < std::numeric_limits<uint32_t>::max());
  ifile.seekg (0, std::ios::beg);
  return size;
}

uint32_t Dictionary::Utility::read(const std::string &filename, std::string *data)
{
  /// Error checking
  if (!data) { return 0; }

  /// Open file
  std::ifstream ifile(filename.c_str(), std::ios_base::in);
  if (!ifile.is_open()) { /* @todo Add exception handling... */ }
  uint32_t fileSize = Dictionary::Utility::getFileSize(ifile);

  /// Read file
  char* buffer = new char[fileSize];
  ifile.read (buffer, fileSize);
  ifile.close();

  /// Write file into memory
  data->assign(buffer, fileSize);
  delete[] buffer;
  return data->size();
}

uint32_t Dictionary::Utility::split(const std::string &text, Dictionary::string_v *results, const std::string &delimiters)
{
  /// Tokenize the input string
  int index;
  std::string copy(text);
  while ((index = copy.find_first_of(delimiters)) != std::string::npos)
  {
    if (index > 0)
    {
      /// Find the next token
      /// @note Dispose of tokens that are also delimiters...
      std::string token = copy.substr(0, index);
      if ((token.size() > 1) || (delimiters.find(token) != std::string::npos))
      {
        results->push_back(token);
      }
    }
    copy = copy.substr(index + 1);
  }

  /// Check for off-by-one case...
  if (copy.length() > 0) { results->push_back(copy); }
  return results->size();
}

