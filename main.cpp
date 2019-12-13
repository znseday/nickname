#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <fstream>

#include "nickname.h"

using namespace std;


int main()
{
#if (defined WIN32) || (defined WIN64)
    cout << MY_P_FUNC << endl;              // for debugging

    //MY_DEBUG_ONLY(TestBasic());           // for debugging

    ifstream i_stream = ifstream("my_own_test.txt");
    if (!i_stream)
    {
        cout << "My error: the input file not found" << endl;
        exit(0);
    }
#else
    istream &i_stream = cin;
#endif

    MY_DEBUG_ONLY(cout << "Homework nickname (DEBUG detected)" << endl);

    RadixTrie rt;

    vector<string> srcData;

    string line;
    while (getline(i_stream, line))
    {
        #if (defined WIN32) || (defined WIN64)
            cout << line << endl; // just echo
        #else
            // nothing
        #endif

        rt.Insert(line);
        srcData.emplace_back(line);
    }

    // temp
    rt.Insert("aleksey"); cout << endl;
    rt.Insert("sasha");   cout << endl;
    rt.Insert("aleks");   cout << endl;
    rt.Insert("alek");    cout << endl;
    rt.Insert("alesha");  cout << endl;
    rt.Insert("maksim");  cout << endl;

    MainTask(rt, srcData);

    return 0;
}

void TestBasic()
{
    cout << endl << "TestBasic" << endl;

    RadixTrie rt;

//    rt.Insert("serg");    cout << endl;
//    rt.Insert("sergoga"); cout << endl;
//    rt.Insert("masha");   cout << endl;
//    rt.Insert("sergey");  cout << endl;

    rt.Insert("aleksey"); cout << endl;
    rt.Insert("sasha");   cout << endl;
    rt.Insert("aleks");   cout << endl;
    rt.Insert("alek");    cout << endl;
    rt.Insert("alesha");  cout << endl;
    rt.Insert("maksim");  cout << endl;

    cout << "//-------------------" << endl;
}

void MainTask(const RadixTrie &rt, const vector<string> &srcData)
{
    cout << endl << "TestMainTask" << endl;

    rt.PrintMe();
    cout << endl;

    rt.CalcMaxLevel();
    cout << "maxLevel = " << rt.GetMaxLevel() << endl;

    cout << endl;
    rt.PrintMePro();
    cout << endl;

   // rt.PrintNamePrefixes(srcData); // 11111111111111111

    vector<string> t{"aleksey", "maksim"};

    //rt.PrintNamePrefixes(t);

    //cout << endl;
    //rt.PrintMe();
    //cout << endl;

    cout << "//-------------------" << endl;
}

