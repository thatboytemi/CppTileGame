#include "TileManager.h"
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

//Tile Manager Implementation
TileManager::TileManager(int numMoves, int dimension, int numTiles, int width, int height, unsigned char *image, std::string summaryName): numMoves(numMoves), numTiles(numTiles), dimension(dimension), width(width), height(height){
    int rowCounter =0;
    int tileWidth = width/dimension;
    int tileHeight = height/dimension;
    int newTileWidth = tileWidth*dimension;
    int newTileHeight = tileHeight*dimension;
    int numBlocks = std::sqrt(numMoves+1); //will be used to control the number of images per line on summary image
    for(int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++) //creating tile objects and setting the part of image that tile is responsible for
        {
            Tile* pointer = new Tile(tileWidth*tileHeight, j*tileWidth, j*tileWidth +tileWidth, i*tileHeight, i*tileHeight+tileHeight); 
            tiles.push_back(pointer);
        }
    }
    int counter =0;
    int prevY = 20;
    for (int i = 0; ; i++)
    {
        if(counter>numMoves){break;}
        int prevX = 20;
       
        for (int j = 0; j < numBlocks; j++)
        {
            if(counter>numMoves){break;}
            Board *pointer = new Board(prevX, prevX+newTileWidth, prevY, prevY+newTileHeight);
            boards.push_back(pointer);
            counter++;
            prevX+=newTileWidth+20;
        }
        prevY+= newTileHeight+20;
        
    }
    
    
    for (int i = 0; i < tileHeight*dimension; i++) //reads image into tiles
    {
        for(int j = 0; j < tileWidth*dimension; j++)
        {
            int tile = findTile(i,j);
            int index = tiles[tile]->index;
            if (tile==numTiles-1) {
                tiles[tile]->array[index] = (unsigned char) 0; //blacken rightmost tile
            }
            else {
                tiles[tile]->array[index]=image[(i*width)+j];
            }
            tiles[tile]->index+=1;
            
        }
    }
      
    blackTile = numTiles-1;
    for (int i = 0; i < numTiles; i++) //reset the array index
    {
        tiles[i]->index = 0;
    }
    
    delete [] image; //delete buffer for original image
    writeToFile(tileWidth*dimension, tileHeight*dimension);
    currentMove++;
    for (int i = 1; i < numMoves+1; i++)
    {
        int newBlackTile = generateMove(blackTile);
        unsigned char* temp = tiles[blackTile]->array;
        tiles[blackTile]->array = tiles[newBlackTile]->array;
        tiles[newBlackTile]-> array = temp;
        blackTile = newBlackTile;
        writeToFile(tileWidth*dimension, tileHeight*dimension);
        currentMove++;
    }
    int numY = std::ceil((float)(numMoves+1)/numBlocks);
    writeSummary((newTileWidth+20)*numBlocks+20, (newTileHeight+20)*(numY)+20, summaryName);
    
}
int TileManager::generateMove(int tileNum){
    std::vector<int> moves;
    if(!(tileNum%dimension==0)) moves.push_back(tileNum-1);
    if(!((tileNum+1)%dimension==0)) moves.push_back(tileNum+1);
    if((tileNum+dimension)<numTiles) moves.push_back(tileNum+dimension);
    if((tileNum-dimension)>=0) moves.push_back(tileNum - dimension);
    srand(time(0));
    int tile = std::rand()%moves.size();
    return moves[tile];
}


int TileManager::findTile(int row, int col){
    for (int i = 0; i < numTiles; i++)
    {
        if((tiles[i]->colMin <= col && tiles[i]->colMax> col)&&(tiles[i]->rowMin<=row && tiles[i]->rowMax>row)) return i;
    }
    return -1;
}
void TileManager::writeToFile(int xdim, int ydim){
    std::string filename = "image-"+std::to_string(currentMove)+ ".pgm";
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::binary);
    outputFile << "P5" <<  "\n" <<"#Fix comment later" << "\n" << std::to_string(xdim) + " " + std::to_string(ydim) << "\n" << "255" <<"\n";
    unsigned char* outputBoard = new unsigned char [xdim*ydim];
    for (int i = 0; i < ydim; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
            int tile = findTile(i,j);
            int index = tiles[tile]->index;
            outputBoard[i*(xdim)+j] = tiles[tile]->array[index];
            tiles[tile]->index+=1;
        }
        
    }
    for (int i = 0; i < numTiles; i++) //reset the array pointers
    {
        tiles[i]->index=0;
    }
    outputFile.write((char*) outputBoard, xdim*ydim);
    outputFile.close();
    boards[currentMove]->array=outputBoard;
}

int TileManager::findBoard(int row, int col){
    for (int i = 0; i <= numMoves; i++)
    {
        if((boards[i]->colMin <= col && boards[i]->colMax> col)&&(boards[i]->rowMin<=row && boards[i]->rowMax>row)) return i;
    }
    return -1;
}
void TileManager::writeSummary(int xdim, int ydim, std::string summaryName){
    std::ofstream summary;
    summary.open(summaryName, std::ios::binary);
    if(!summary.is_open()){
        std::cout << "Error creating summary file.";
        return ;
    }
    summary << "P5" <<  "\n" <<"#Fix comment later" << "\n" << std::to_string(xdim) + " " + std::to_string(ydim) << "\n" << "255" <<"\n";
    unsigned char* outputBoard = new unsigned char [xdim*ydim];
    for (int i = 0; i < ydim; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
            int temp = i*(xdim)+j;
            int board = findBoard(i,j);
            //std::cout << "(" << i << ":" <<j << "): "<< board<<"\n";
            if(board == -1){
                outputBoard[i*(xdim)+j] = 255;
                continue;
            }
            int index = boards[board]->index;
            outputBoard[i*(xdim)+j] = boards[board]->array[index];
            boards[board]->index+=1;
        }
     }
    summary.write((char*) outputBoard, xdim*ydim);
    summary.close();
}

TileManager::~TileManager(){
    for (int i = 0; i < numTiles; i++)
    {
        delete tiles[i];
    }
    for (int i = 0; i <= numMoves; i++)
    {
        delete boards[i];
    }
    
    
}
// Tile Implementation
Tile::Tile(int size, int colMin, int colMax, int rowMin, int rowMax): arraySize(size), colMin(colMin), colMax(colMax), rowMin(rowMin), rowMax(rowMax){
    array = new unsigned char [size];
}
unsigned char* Tile::getTile(void){
    return array;
}
void Tile::setTile(unsigned char* tile){
    array = tile;
}
Tile::~Tile(){
    delete [] array;
}

//Board Implementation
Board::Board(int colMin, int colMax, int rowMin, int rowMax): colMin(colMin), colMax(colMax), rowMin(rowMin), rowMax(rowMax){
    //std::cout << colMin << " "   << colMax << " " << rowMin << " " << rowMax << "\n";
};
Board::~Board(){
    delete [] array;
}