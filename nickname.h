#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cassert>
#include <memory>
#include <cstring>


using namespace std;

// __FUNCSIG__ is for VS, but Qt (mingw) works with __PRETTY_FUNCTION__
#if ((defined WIN32) || (defined WIN64)) && (defined _MSC_VER)
#define MY_P_FUNC __FUNCSIG__
#else
#define MY_P_FUNC __PRETTY_FUNCTION__
#endif

#if ((defined NDEBUG) || (defined _NDEBUG))
#define MY_DEBUG_ONLY(x)
#else
#define MY_DEBUG_ONLY(x) {x}
#endif

extern bool IsExOutput;

#define MY_EX_OUTPUT(x) { if(IsExOutput) {x}    }

using namespace std;

class RadixTrie;

void TestBasic();
void MainTask(const RadixTrie &rt, const vector<string> &srcData);
//-----------------------------------------------

struct Node
{
    string name;
    bool finished = true;
    bool last = false;
    //<unique_ptr<Node>, 26> next = {nullptr};
    Node *next[26];
    Node() {memset(next, 0, sizeof(next));}
    Node(string _name, bool _finished) : name(std::move(_name)), finished(_finished) {memset(next, 0, sizeof(next));}
};
//-----------------------------------------------

class RadixTrie
{
private:
    //unique_ptr<Node> root = nullptr;
    Node *root = nullptr;

    void InsertInside(Node * &curNode, string &_name);

    void PrintMeInside(Node *curNode, int level) const;
    void PrintMeInsidePro(Node *curNode, int level, vector<bool> &opens) const;

    void FindMinPrefixInside(const Node *curNode, string &_name, string &res) const;

    mutable size_t maxLevel = 0;
    void CalcMaxLevelInside(Node *curNode, size_t level) const;

public:

    RadixTrie() {}

    void Insert(const string &_name);

    void PrintMe() const;
    void PrintMePro() const;

    void PrintNamePrefixes(const vector<string> &srcData) const;

    string FindMinPrefix(std::string _name) const;

    void CalcMaxLevel() const;
    int GetMaxLevel() const {return maxLevel;}

};















