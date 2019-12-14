#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <fstream>

#include "nickname.h"

using namespace std;

int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
        if (strcmp(argv[1], "-ext") == 0)
            IsExOutput = true;

#if (defined WIN32) || (defined WIN64)
    cout << MY_P_FUNC << endl;              // for debugging

    MY_DEBUG_ONLY(TestBasic();)           // for debugging

    ifstream i_stream = ifstream("my_own_test.txt");
    if (!i_stream)
    {
        cout << "My error: the input file not found" << endl;
        exit(0);
    }
#else
    istream &i_stream = cin;
#endif

    MY_DEBUG_ONLY(cout << "Homework nickname (DEBUG detected)" << endl;)

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

    MainTask(rt, srcData);

    return 0;
}

void TestBasic()
{
    cout << endl << "TestBasic" << endl;

    RadixTrie rt;

    rt.Insert("serg");    cout << endl;
    rt.Insert("sergoga"); cout << endl;
    rt.Insert("masha");   cout << endl;
    rt.Insert("sergey");  cout << endl;

    rt.Insert("aleksey"); cout << endl;
    rt.Insert("alesha");  cout << endl;
    rt.Insert("sasha");   cout << endl;
    rt.Insert("aleks");   cout << endl;
    rt.Insert("alek");    cout << endl;
    rt.Insert("maksim");  cout << endl;

    cout << endl << "PrintMePro from TestBasic:" << endl;
    rt.CalcMaxLevel();
    rt.PrintMePro();
    cout << endl;

    vector<string> t{"aleksey", "maksim"};
    rt.PrintNamePrefixes(t);

    cout << "//-------------------" << endl;
}

void MainTask(const RadixTrie &rt, const vector<string> &srcData)
{
    cout << endl << "TestMainTask" << endl;

    rt.PrintMe();
    cout << endl;

    rt.CalcMaxLevel();
    MY_EX_OUTPUT( cout << "maxLevel = " << rt.GetMaxLevel() << endl;)

    cout << endl;
    rt.PrintMePro();
    cout << endl;

    rt.PrintNamePrefixes(srcData);

    MY_EX_OUTPUT(
        cout << endl;
        rt.PrintMePro();    // to be sure that it still works)
        cout << endl;
    )

    cout << "//-------------------" << endl;
}

