#include <vector>
#include <utility>
#include <fstream>
#include <sstream> // istringstream
#include <cmath>
#include <queue>
#include <deque>
#include <limits>
#include <iostream>
#include <cstdio>

using namespace std;

const int UNIT = 1;

class TSP{
public:
    vector< double > distMatrix ;
    vector< pair<double, double> > cordinates;
    int nnode;
    /* parse the input file to form a vector of cordinate */
    void parse(char* filename){
        //2 read line by line
        //#include <sstream> // istringstream
        //2.1 init variable or space to store input
        string line;
        int nline = 0;
        cordinates.reserve(10);
        //2.2 open file
        ifstream infile(filename);
        //2.3 reading, until ending conditon, store input stuff
        while (getline(infile, line))
        {
            //2.4 change input stuff, so we can process it word by word
            istringstream iss(line);
            //2.5 process
            int node;
            iss >> node;
            double xpos, ypos;
            parseCoordinate(iss,xpos,ypos);
            cordinates[node-1] = pair<double,double>(xpos,ypos);
            nline++;
        }
        //2.6 close file
        infile.close(); //
        nnode = nline;
    }
    
    /* get the x y coordinate of one place in one line of string*/
    void parseCoordinate(istringstream &iss, double& x, double& y){
        char temp;
        iss >> temp;
        while ( temp != '(' ) {
            iss >> temp;
        }
        iss >> x;
        x *= UNIT;
        iss >> temp;
        iss >> y;
        y *= UNIT;
    }
    
    /* form a matrix of distance from a vector of cordinates */
    void calDistance(){
        distMatrix.reserve(nnode*nnode);
        for (int row = 0; row < nnode; row++){
            for (int col = row; col < nnode; col++){
                distMatrix[ row*nnode + col ] = nodesDist(row, col);
                // symatrix matrix
                distMatrix[ col*nnode + row ] = distMatrix[ row*nnode + col ];
            }
        }
    }
    
    /* return distance between two nodes; exp: node start from 0 */
    double nodesDist(int n1, int n2){
        double offx = cordinates[n1].first - cordinates[n2].first;
        double offy = cordinates[n1].second - cordinates[n2].second;
        return sqrt( (offx*offx) + (offy*offy) );
    }
    
    /* print matrix*/
    void printMatrix(){
        for (int i =0; i<nnode; i++){
            for (int j =0; j<nnode; j++)
                cout <<distMatrix[i*nnode + j] << "\t\t" ;
            cout << endl;
        }
    }
    
    /******************************************************************/
    
    /* get lowest distance of each row(start from 0) */
    double lowestDist(int row){
        if (row >= nnode) throw -1;
        int base = nnode*row;
        double min = distMatrix[base];
        for(int i =1; i <nnode; i++){
            if( (distMatrix[base+i] < min) && (distMatrix[base+i] != 0) )
                min = distMatrix[base+i];
            else if (min == 0)
                min = distMatrix[base+i];
        }
        return min;
    }
    
    /* data structure */
    deque<int> path;
    deque<int> smallestPath;
    double smallestDist;
    double currPathDist;
    
    /* find the path */
    void nearestPath(){
        smallestDist = numeric_limits<double>::infinity();
        currPathDist = 0;
        explore(0);
    }
    
    /* explore */
    void explore(int node){
        
        // pre : base on current path, get the succeeding nodes of curr node
        path.push_back(node);
        vector<int> succ;
        getSucc(node,succ);
        for(int i = 0; i < succ.size(); i++){
            if(currPathDist <= smallestDist){
                currPathDist += distMatrix[ node*nnode + succ[i] ];
                explore(succ[i]);
            }
        }
        
        // post: check if form a whole path
        if (path.size() == nnode) {
            //printSeq(path);
            if (currPathDist < smallestDist){
                smallestPath = path;
                smallestDist = currPathDist;
            }
        }
        //cout << "pop: "<< path.back() << endl;
        
        path.pop_back();
        if ( !path.empty() )currPathDist -= distMatrix[path.back()*nnode + node];
    }
    /* given a node, and visted nodes so far,
     return the possible succeeding nodes */
    void getSucc(int node, vector<int> &succ){
        vector<bool> visited(nnode,false);
        for (int i = 0; i < path.size(); i++)
            visited[path[i]] = true;
        for (int i = 1; i < nnode; i++){
            if ( !visited[i] )
                succ.push_back(i);
        }
        
    }
    void printSeq(deque<int> q){
        int static n = 0;
        n++;
        cout << n << ":\t";
        for (int i = 0; i < q.size(); i++)
            cout<< q[i] << "\t";
        cout << endl;
    }
    
};

int main (int argc, char *args[]){
     TSP ins;
     ins.parse(args[1]);
     
     ins.calDistance();
     
     ins.nearestPath();
     
     for (int i = 0; i < ins.smallestPath.size(); i++)
         cout << ins.smallestPath[i]+1 << endl;
}
