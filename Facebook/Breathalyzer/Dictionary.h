#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <tr1/cstdint>

namespace Exercises {
namespace Facebook {

class Dictionary
{
public:
  typedef std::vector<std::string> string_v;

  class Utility
  {
  public:
    static uint32_t getFileSize(std::ifstream &ifile);
    static uint32_t read(const std::string &filename, std::string *data = NULL);
    static uint32_t split(const std::string &text, Dictionary::string_v *results = NULL, const std::string &delimiters = "\r\n");
  };

  Dictionary(const std::string &filename);
  ~Dictionary();
  const string_v& getEntries() const { return this->mEntries; }

protected:
  string_v mEntries;
};

}
}

#endif // DICTIONARY_H_
