#include "BkTree.h"

using namespace Exercises::Facebook;

BkTree::Node::Node(const std::string &data, const uint32_t distance) :
  data(data),
  distance(distance),
  child(NULL),
  sibling(NULL)
{
}

BkTree::Node::~Node()
{
  if (this->child) { delete this->child; }
  if (this->sibling) { delete this->sibling; }
}

BkTree::BkTree(Dictionary &dictionary) :
  mRoot(NULL),
  mSize(0)
{
  const Dictionary::string_v &entries = dictionary.getEntries();
  for (uint32_t i = 0; i < entries.size(); ++i)
  {
    this->insert(entries[i]);
  }
}

BkTree::~BkTree()
{
  if (this->mRoot) { delete this->mRoot; }
}

bool BkTree::getClosest(const match_m &matches, BkTree::match_p *result)
{
  if (!result) { return false; }

  uint32_t distance = std::numeric_limits<uint32_t>::max();
  BkTree::match_m::const_iterator
    iter = matches.begin(),
    end = matches.end();
  for (; iter != end; ++iter)
  {
    if (iter->second < distance)
    {
      result->first = iter->first;
      distance = result->second = iter->second;
    }
  }
  return true;
}

bool BkTree::insert(const std::string &data)
{
  // std::cout << "BUILD BK-TREE: Inserting node with data: " << data;

  /// Base case; if the tree is empty, create a root node
  if (!this->mRoot)
  {
    // std::cout << " as ROOT" << std::endl;
    this->createNode(data, Levenshtein::INVALID_DISTANCE);
    return true;
  }

  Node *node = this->mRoot;
  while (true)
  {
    /// Determine the edit distance between the input and current node's data
    uint32_t distance = Levenshtein::distance(node->data, data);
    if (!distance) { return false; }

    /// Search for the first available insert point for user-specified value
    Node *child = node->child;
    while (child)
    {
      if (child->distance == distance)
      {
        node = child;
        break;
      }
      child = child->sibling;
    }

    /// ...otherwise, we must create a leaf for the given edit distance
    if (!child)
    {
      this->createNode(data, distance, node);
      // std::cout << " with DISTANCE = " << distance << " and PARENT = " << node->data << std::endl;
      return true;
    }
  }
  return false;
}

uint32_t BkTree::find(const std::string &center, match_m *results, uint32_t tolerance)
{
  if (!this->mRoot || !results) { return 0; }
  results->clear();

  uint32_t count = 0;
  node_q nodes;
  nodes.push(this->mRoot);

  // std::cout << "Finding nearest matches for: " << center << std::endl;
  while (!nodes.empty())
  {
    Node *node = nodes.front();
    nodes.pop();

    uint32_t distance = Levenshtein::distance(node->data, center);
    // std::cout << "\t=> Tested: " << node->data << ":" << distance << ", tolerance=" << tolerance << std::endl;
    uint32_t minIndex = (distance < tolerance) ? 0 : (distance - tolerance);
    uint32_t maxIndex = distance + tolerance;

    /// Store node's data in result set if eligible
    if (distance <= tolerance)
    {
      // std::cout << "\t=> Adding match pair: " << node->data << ":" << distance << std::endl;
      results->insert(std::make_pair(node->data, distance));
      ++count;
    }

    /// Add eligible children to the node queue for further testing
    Node *child = node->child;
    while (child)
    {
      if ((child->distance >= minIndex) && (child->distance <= maxIndex))
      {
        nodes.push(child);
      }
      child = child->sibling;
    }
  }
  return count;
}

BkTree::Node* BkTree::createNode(const std::string &data, const uint32_t distance, BkTree::Node *parent)
{
  Node *child = new Node(data, distance);
  if (parent)
  {
    child->sibling = parent->child;
    parent->child = child;
    ++this->mSize;
  }
  else
  {
    this->mRoot = child;
    this->mSize = 1;
  }
  return child;
}
