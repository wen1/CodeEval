//
//  urgly_numbers.h
//  urly numbers
//
//  Created by Yi Wen on 6/18/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

#ifndef urly_numbers_urgly_numbers_h
#define urly_numbers_urgly_numbers_h
// a node is a character of a string
const int NEDGES = 3; // number of edges of a node
class Solution{
    vector<string> loe;    // a list of expressions
    int nUglyNum;          // number of ugly number
    string sod;            // string of digit get by input
    string exp;            // an expression through one round expanding
    string oper;           // string of operator(by default is "+=_", '_' is none
public:
    // given a string number "12",
    // return a list of string: {"1+2","12","1-2"}
    void allPossibleComb(string s){
        loe.reserve( nExp(s.size()) );
        sod = s;
        oper = "+-_";
        explore(0); // start from first digit of sod;        
    }
    
    // explore sod[index]
    void explore(int index){
        
        if( index < sod.size() ){
            exp.push_back(sod[index]);
            if( index < sod.size()-1 ) {
                for(int i = 0; i <oper.size(); i++){
                    if ( oper[i] != '_' ) {
                        exp.push_back( oper[i] );
                        explore( index + 1 );
                        // pop out last to char: operator and digit
                        int currLen = exp.size();
                        exp.erase(currLen-2,2);
                    } else {
                        explore( index + 1 );
                        int currLen = exp.size();
                        exp.erase(currLen-1,1);
                    }
                }
            } else {
                loe.push_back(exp);
            }
        }
        
    }
    
    // the number of combination
    // ex. a string "123" has 3^(3-1) expressions
    int nExp(int len){         
        return (int)pow( (double)NEDGES, (double)(len-1) );
    }
    
    // print out loe
    void print(){
        for(int i = 0; i<loe.size(); i++)
            cout << loe[i] << " = " << parsingExp(loe[i]) << "\n";
    }
    
    // parsing the expression
    int parsingExp(string ex){
        stringstream ss(ex);
        char op;
        int i,j, res;
        ss >> res;
        while ( !ss.eof() ){
            ss >> op;
            ss >> j;
            if (op == '+'){
                res += j;
            } else {
                res -= j;
            }
        }
        return res;
    }
    // calculate each expression of loe, count the ugly number
    void countUglyNum(){
        nUglyNum = 0;
        for (int i = 0; i < loe.size(); i++){
            int res = parsingExp(loe[i]);
            if (isUgly(res)) nUglyNum++;
        }
    }
    
    bool isUgly(int num){
        return ( (num%2 == 0) || (num%3 == 0) || (num%5 == 0) || (num%7 == 0) );
    }
    
    int getUglyNum(){
        return nUglyNum;
    }
    
    int getCombNum(){
        return loe.size();
    }
};


#endif
