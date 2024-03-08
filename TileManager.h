#include <vector>
#include <string>
namespace ANXTEM001{
    class Tile{
        private:
            int arraySize;
        public:
            unsigned char* getTile(void);
            void setTile(unsigned char* tile);
            Tile(int size, int colMin, int ColMax, int rowMin, int rowMax);
            ~Tile();
            //MAKE PRIVATE
            unsigned char* array;
            int colMin;
            int colMax;
            int rowMin;
            int rowMax;
            int index = 0;
            
    };
    class Board{
        public:
            unsigned char* array;
            int colMin;
            int colMax;
            int rowMin;
            int rowMax;
            int index = 0;
            Board(int colMin, int colMax, int rowMin, int rowMax);
            ~Board();
        
    };
    class TileManager{
        private:
            std::vector<Tile*> tiles;
            std::vector<Board*> boards;
            int numMoves;
            int width;
            int height;
            int currentMove = 0;
            int numTiles;
            int dimension;
            int blackTile;
        public:
            int generateMove(int tileNum);
            TileManager(int numMoves, int dimension, int numTiles, int width, int height, unsigned char* image, std::string stateName, std::string summaryName);
            int findTile(int row, int col);
            int findBoard(int row, int col);
            void writeToFile(int xdim, int ydim, std::string stateName);
            void writeSummary(int xdim, int ydim, std::string summaryName);
            ~TileManager();

    };
}


