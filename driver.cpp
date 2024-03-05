#include <fstream>
#include <iostream>
#include <sstream>
#include "TileManager.h"
int main(int argc, char* argv []){
    using namespace std;
    ifstream myfile;
    string str;
    string width;
    string height;
    if(argc ==1 || argc > 4){
        cout << "Incorrect number of arguments.";
        return 1;
    }
    if(stoi(argv[1])%2==0){
        cout << "Grid size must be an odd number.";
        return 1;
    }
    if(stoi(argv[2])<1){
        cout << "Number of moves should be greater than 0.";
        return 1;
    }
    myfile.open(argv[3], ios::binary);
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
    TileManager tileManager(stoi(argv[2]),stoi(argv[1]),(stoi(argv[1])*stoi(argv[1])), widthVal, heightVal, buffer);
    return 0;
}