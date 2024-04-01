# C++ Assignment 2

## Author: Temi Aina

This program reads in an image (which has to be a pgm file), carves it up into an nxn grid (where n is a user-inputed odd number), makes the right bottom grid black and randomly shuffles the black grid around k times (where k is user-inputed and k>=0).  

## Class Structure

To make this program, I created three classes:

### 1) Tile

This class contains a dynamically allocated array which stores all the pixels belonging to the tile and other information that is needed to control what parts of the original image belong to the tile.

### 2) Board

This class contains a dynamically allocated array which stores all the pixels belonging to a board (which is a collection of tiles) and other information that is needed to control what parts of the summary image belong to the board. I created this class to facilitate the creation of the summary image (which is part of the mastery work).

### 3) TileManager

This class contains a vector storing pointers to all the Tile objects and a vector storing all the pointers to all the Board objects. It also contains methods for retrieving Tile objects, generating moves and writing images to files.

## File Structure

There are three files needed for the runnning of this program:

### 1) driver.cpp

This file contains the main function which is the entry point into this program.

### 2) TileManager.h

This file contains the class declarations for the Tile, Board and TileManager classes.

### 3) TileManager.cpp

This file contains implementation of the Tile, Board and TileManager classes.

## How To Run This Program

To compile this program, type "make" ensuring that you are within the folder which contains the Makefile.

To run this program, type "./driver -s {size of grid} -n {number of moves} -i {name of output images} -x {name of summary image} {name of input image}". For example "./driver -s 3 -n 3 -i state -x summary steelb.pgm". ONLY ADD THE .pgm EXTENSION WHEN SPECIFYING THE NAME OF THE INPUT IMAGE! What you should expect when running this line is a sequence of summary images named state-0.pgm to state-3.pgm and an image named summary.pgm to be generated. Setting the size to 3 splits the grid into a 3x3 grid and setting the number of moves to 3 resulted in 4 images being generated.
Failure to adhere to this structure will cause an error to be thrown.

You can use an image manipulation tool like GIMP to view the output images.
