//
//  main.cpp
//  urly numbers
//
//  Created by Yi Wen on 6/18/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ugly_numbers.h"
using namespace std;

int main (int argc, const char * argv[])
{
    Solution sol;
    cout << "**************\t allPossibleComb \t**************\n";
    // test given a string number "12",
    // return a list of string: {"1+2","12","1-2"}
    sol.allPossibleComb("123");
    sol.print();
    cout << endl;
    ///////////////////////////////////////////////////////
    cout << "**************\t parsingExp \t**************\n";
    // test given a expression
    // return the result
    cout << sol.parsingExp("1-2-3");
    cout << endl;
    ///////////////////////////////////////////////////////
    cout << "**************\t isUgly \t**************\n";
    // test given a number a
    // return true iff a is ugly otherwise fasle
    int a = -19 ;
    if (sol.isUgly(a)) cout<< a << " is ugly";
    else cout << a << " is not ugly";
    cout << endl;
    ///////////////////////////////////////////////////////
    cout << "**************\t unit test \t**************\n";
    // test given a string "123456"
    // return the number of ugly of this string
    string s = "12345";
    Solution son;
    son.allPossibleComb(s);
    cout << "all possible expressions: \n";
    son.print();
    son.countUglyNum();
    cout << "number of combination: " << son.getCombNum() << endl;
    cout << "number of ugly number: " << son.getUglyNum();
    return 0;
}

