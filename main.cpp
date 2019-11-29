#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <cassert>

#include "nickname.h"

using namespace std;


int main()
{
#if (defined WIN32) || (defined WIN64)
    cout << "Homework nickname" << endl << endl;    // for debugging
    cout << MY_P_FUNC << endl;                      // for debugging
#else
    // some
#endif

    MY_DEBUG_ONLY(cout << "Homework nickname (DEBUG detected)" << endl);

    cout << "Hello, nickname!" << endl;

    TestBasic();

    TestMainTask();

    return 0;
}

