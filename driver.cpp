#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include "TileManager.h"

int main(int argc, char* argv []){
    using namespace std;
    ifstream myfile;
    string str;
    string width;
    string height;
    int gridSize;
    int numMoves;
    string outputName;
    string summaryName;
    if(argc!=10){
        cout << "Incorrect number of arguments.";
        return 1;
    }
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-s")==0){
            gridSize = stoi(argv[i+1]);
             if(gridSize%2==0){
                cout << "Grid size must be an odd number.";
                return 1;
            }
            i++;
            continue;
        }
        if(strcmp(argv[i], "-i")==0){
            outputName = argv[i+1];
            i++;
            continue;
        }
        if(strcmp(argv[i], "-n")==0){
            numMoves = stoi(argv[i+1]);
            if(numMoves<0){
                cout << "Number of moves should be greater than or equal to 0.";
                return 1;
            }
            i++;
            continue;
        }
        if(strcmp(argv[i], "-x")==0){
            summaryName = argv[i+1];
            i++;
            continue;
        }
    } 
    myfile.open(argv[9], ios::binary);
    if (!myfile.is_open()) { 
        cout << "File open failed!"; 
        return 1;
    }
    getline(myfile, str); //read first line (P5)
    while(getline(myfile, str)){ 
        if(str[0]!='#'){
            istringstream s(str);
            s >> width >> height;
            break;
        }
    }
    getline(myfile, str); //read last line before binary block (255)
    int widthVal = stoi(width);
    int heightVal = stoi(height);
    int numEntries = widthVal * heightVal;
    unsigned char * buffer = new unsigned char [numEntries];
    myfile.read((char*)buffer,numEntries);
    ANXTEM001::TileManager tileManager(numMoves ,gridSize , gridSize*gridSize, widthVal, heightVal, buffer,outputName, summaryName);
    return 0;
}

