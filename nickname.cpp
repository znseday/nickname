#include <iostream>
#include <cassert>

#include "nickname.h"

bool IsExOutput = false;

using namespace std;

//------------------------------------------------------

void RadixTrie::InsertInside(Node * &curNode, string &_name)
{
    MY_DEBUG_ONLY(   cout << "_name = " << _name << endl;   )     // for debugging

    if (!curNode)
    {
        curNode = new Node(_name, true);
        MY_DEBUG_ONLY(cout << "item = " << curNode->name << (curNode->finished?"$":" ") << endl;)
        return;
    }

    auto pos = mismatch(curNode->name.cbegin(), curNode->name.cend(), _name.cbegin(), _name.cend());

    string common{_name.cbegin(), pos.second};
    MY_DEBUG_ONLY(cout << "common = " << common << endl;)     // for debugging

    _name.erase(_name.cbegin(), pos.second);
    MY_DEBUG_ONLY(cout << "_name after erase = " << _name << endl;)    // for debugging

    if (common == curNode->name)
    {
        if(_name.empty())
            curNode->finished = true;
        else
        {
            size_t ind = static_cast<size_t>(*_name.cbegin() - 'a');
            MY_DEBUG_ONLY(cout << "index = " << ind << endl;)  // for debugging
            InsertInside(curNode->next[ind], _name);
        }

    }
    else
    {
        MY_DEBUG_ONLY(cout << "common != curNode->name : " << curNode->name << endl;) // for debugging
        Node *tempNode = new Node(common, _name.empty() );

        //tempNode->name = string{tempNode->name.cbegin(), tempNode->name.cbegin()+common.size()};
        //curNode = new Node(common, _name.empty() );

        //size_t ind = static_cast<size_t>(*curNode->name.cbegin() - 'a');
        size_t ind = static_cast<size_t>(*pos.first - 'a');

        //curNode->next[ind] = tempNode;

        tempNode->next[ind] = curNode;

        MY_DEBUG_ONLY(cout << "item = " << tempNode->name << (tempNode->finished?"$":" ") << endl;)
        if (!_name.empty())
        {
            ind = static_cast<size_t>(*_name.cbegin() - 'a');
            tempNode->next[ind] = new Node(_name, true);
            MY_DEBUG_ONLY(cout << "item = " << tempNode->next[ind]->name << (tempNode->next[ind]->finished?"$":" ") << endl;)

        }

        //string s = tempNode->name;
        //curNode->name = string{curNode->name.cbegin(), curNode->name.cbegin() + s.size()};

        curNode->name.erase(curNode->name.cbegin(), curNode->name.cbegin() + tempNode->name.size());
        curNode = tempNode;
    }
}
//------------------------------------------------------

void RadixTrie::Insert(const string &_name)
{
    string tempName = _name;
    //maxLevel = 0;
    //int level = 0;
    InsertInside(root, tempName);

//    if (!root)
//    {
//        root = new Node;
//        root->name = _name;
//        return;
//    }

//    Node *temp = root;

//   // while (temp)
//   // {

//        auto pos = mismatch(temp->name.cbegin(), temp->name.cend(), _name.cbegin(), _name.cend());

//        if (pos.first != temp->name.cend())
//            cout << "pos.first = " << *pos.first << endl;
//        else
//            cout << "pos.first = end" << endl;

//        if (pos.second != _name.cend())
//            cout << "pos.second = " << *pos.second << endl;
//        else
//            cout << "pos.second = end" << endl;

//        if (temp->name.empty())
//        {
//            Node *newNode = new Node;
//            newNode->name = _name;
//            root->next[(*pos.second)-'a'] = newNode;
//            return;
//        }
//        if (pos.first == temp->name.cbegin()) // mismath in the first symbol
//        {
//            if (temp == root) // if it's root, devide into two nodes
//            {
//                Node *newNode = new Node;
//                newNode->name = _name;
//                Node *newRoot = new Node;
//                newRoot->finished = 0;
//                newRoot->next[(*pos.first)-'a']  = temp;
//                newRoot->next[(*pos.second)-'a'] = newNode;
//                root = newRoot;
//                return;
//            }
//            else
//            {
//            }
//        }
//    }

}
//------------------------------------------------------

void RadixTrie::PrintMe() const
{
    maxLevel = 0;
    PrintMeInside(root, 0);
}
//------------------------------------------------------

void RadixTrie::PrintMeInside(Node *curNode, int level) const
{
    if (curNode != nullptr)
    {
        for (int i = 0; i < level; i++)
            cout << " ";

        cout << curNode->name;
        if (curNode->finished)
            cout << "$";

        cout << endl;

        level++;

        for (int i = 0; i < 26; i++)
            if (curNode->next[i])
                PrintMeInside(curNode->next[i], level);
    }
}
//------------------------------------------------------

void RadixTrie::CalcMaxLevel() const
{
    maxLevel = 0;
    if (root)
        CalcMaxLevelInside(root, maxLevel);
}
//------------------------------------------------------

void RadixTrie::CalcMaxLevelInside(Node *curNode, size_t level) const
{
    level++;
    if(level > maxLevel)
        maxLevel = level;

    int _last = -1;
    for (int i = 0; i < 26; i++)
        if (curNode->next[i])
        {
            CalcMaxLevelInside(curNode->next[i], level);
            _last = i;
        }

    if (_last >= 0)
        curNode->next[_last]->last = true;
}
//------------------------------------------------------

void RadixTrie::PrintMePro() const
{
    //setlocale(0, "English"); // doesn't work in Qt
    vector<bool> opens;
    opens.resize(maxLevel, false);
    PrintMeInsidePro(root, 0, opens);
}
//------------------------------------------------------

void RadixTrie::PrintMeInsidePro(Node *curNode, int level, vector<bool> &opens) const
{
    if (curNode != nullptr)
    {
        for (int i = 0; i < level; i++)
        {
            if (opens[(size_t)i] && i < level-1)
            {
                cout << "|";
                //wcout << wchar_t(0x2502);  // doesn't work
            }
            else if (i == level-1)
            {
                if (curNode->last)
                {
                    cout << "\\";  // back slash
                    //wcout << wchar_t(0x2514);     // doesn't work

                    opens[(size_t)i] = false;
                }
                else
                {
                    cout << "+";
                    //wcout << wchar_t(0x251c);   // doesn't work
                    opens[(size_t)i] = true;
                }
            }
            else
            {
                cout << " ";
            }
        }

        cout << "\"" << string(curNode->name) << "\"";

        if (curNode->finished)
            wcout << "$";

        MY_EX_OUTPUT(
            cout << "   ------>";
            for (int i = 0; i < 26; i++)
                if (curNode->next[i])
                   cout << "   " << char(i+'a');

            if (curNode->last)
                cout << "   ------> last";
        )

        cout << endl;

        level++;

        for (int i = 0; i < 26; i++)
        {
            if (curNode->next[i])
            {
                PrintMeInsidePro(curNode->next[i], level, opens);
            }
        }
    }
}
//------------------------------------------------------

void RadixTrie::PrintNamePrefixes(const vector<string> &srcData) const
{
    for (auto s : srcData)
    {
        cout << s << " ";
        MY_EX_OUTPUT(cout << " ---> ";)
        cout << FindMinPrefix(s) <<  endl;
    }
}
//------------------------------------------------------

string RadixTrie::FindMinPrefix(std::string _name) const
{
    string res;
    FindMinPrefixInside(root, _name, res);
    return res;
}
//------------------------------------------------------

void RadixTrie::FindMinPrefixInside(const Node *curNode, string &_name, string &res) const
{
    if (!curNode)
        return;

    auto pos = mismatch(curNode->name.cbegin(), curNode->name.cend(), _name.cbegin(), _name.cend());

    string common{_name.cbegin(), pos.second};
    //MY_DEBUG_ONLY(cout << "common = " << common << endl;)     // for debugging

    if (common == _name)
    {
       res += common[0];
    }
    else
    {
        size_t ind = static_cast<size_t>(*pos.second - 'a');
        //MY_DEBUG_ONLY(cout << "index = " << ind << endl;)         // for debugging

        res += common;
        _name.erase(_name.cbegin(), _name.cbegin() + curNode->name.size());

        curNode = curNode->next[ind];

        FindMinPrefixInside(curNode, _name, res);
    }
}



















