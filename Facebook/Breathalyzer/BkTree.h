#ifndef BKTREE_H_
#define BKTREE_H_

#include <map>
#include <queue>
#include "Dictionary.h"
#include "Levenshtein.h"

namespace Exercises {
namespace Facebook {

/// @url http://blog.notdot.net/2007/4/Damn-Cool-Algorithms-Part-1-BK-Trees
class BkTree
{
protected:
  struct Node
  {
  public:
    Node(const std::string &data, const uint32_t distance);
    ~Node();

    std::string data;
    uint32_t distance; /// to parent
    Node *child;
    Node *sibling;
  }; /// class Node

public:
  typedef std::map<std::string, uint32_t> match_m;
  typedef std::pair<std::string, uint32_t> match_p;
  typedef std::queue<BkTree::Node*> node_q;

  static const uint32_t DEFAULT_TOLERANCE = 3;

  BkTree(Dictionary &dictionary);
  ~BkTree();
  static bool getClosest(const match_m &matches, BkTree::match_p *result = NULL);
  bool insert(const std::string &data);
  uint32_t find(const std::string &center, match_m *results = NULL, uint32_t tolerance = DEFAULT_TOLERANCE);

protected:
  Node *mRoot;
  uint32_t mSize;

  Node* createNode(const std::string &data, const uint32_t distance, Node *parent = NULL);
}; /// class BkTree

} /// namespace Facebook
} /// namespace Exercises

#endif // BKTREE_H_
