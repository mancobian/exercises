///
/// @file BkTree.h
/// @author Mancobian Poemandres
/// @license BSD License
///
/// Copyright (c) MMX by The Secret Design Collective
/// All rights reserved
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
///    * Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///    * Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///    * Neither the name of The Secret Design Collective nor the names of its
///     contributors may be used to endorse or promote products derived from
///     this software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
/// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
/// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
/// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///

#ifndef EXERCISES_FACEBOOK_BKTREE_H
#define EXERCISES_FACEBOOK_BKTREE_H

#include <map>
#include <queue>
#include <tr1/memory>
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
    uint32_t distance; /// @note Edit distance to parent.
    Node *child;
    Node *sibling;
  }; /// class Node

public:
  typedef std::map<std::string, uint32_t> match_m;
  typedef std::pair<std::string, uint32_t> match_p;
  typedef std::queue<BkTree::Node*> node_q;
  typedef std::tr1::shared_ptr<BkTree> Pointer;

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

#endif /// EXERCISES_FACEBOOK_BKTREE_H
