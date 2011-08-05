#include "Dictionary.h"
#include <cassert>
#include <climits>
#include <cstring>
#include <algorithm>

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

  /// Uppercase everything!
  std::transform(data->begin(), data->end(), data->begin(), ::toupper);
  return data->size();
}

uint32_t Dictionary::Utility::split(const std::string &text, Dictionary::string_v *results, const std::string &delimiters)
{
  /// Tokenize the input string
  const uint32_t BUFFER_SIZE = text.size() + 1;
  char copy[BUFFER_SIZE];
  memset(copy, '\0', BUFFER_SIZE);
  memcpy(copy, text.c_str(), text.size());

  char *token = NULL;
  token = ::strtok(copy, delimiters.c_str());
  while (token != NULL)
  {
    results->push_back(token);
    token = ::strtok(NULL, delimiters.c_str());
  }
  return results->size();
}
