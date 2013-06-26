#include <iostream>
#include <fstream>

using namespace std;

bool bOccuresA(int index, int len, string &line){
    int i = 0, j = index+1;
    while ( (i!=index) && (j!=len) && (index-i)>=(len-j) ){
        if (line[i] == line[j]) {
            i++;
            j++;
        } else {
            i++;
            j = index+1;
        }
    }
    return ( j == len );
}

int main(int argc, const char * argv[])
{
    ifstream file;
    file.open(argv[1]);
    while (!file.eof())
    {
        string lineBuffer;
        getline(file, lineBuffer);
        if (lineBuffer.length() == 0){
            continue; //ignore all empty lines
        } else {
            string a,b;
            int i = 0;
            while(lineBuffer[i] != ',') 
                i++;
            if ( bOccuresA(i, lineBuffer.size(), lineBuffer) )
                cout << 1 << endl;
            else
                cout << 0 << endl;
        }
    }

    
    return 0;
}
