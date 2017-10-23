#include <iostream>
#include "mazeio.h"

using namespace std;

char** read_maze(int* rows, int* cols) { //Read the maze from cin into a
    char** maze = new char*[*rows];      //dynamically allocated array.
    for(int r = 0; r < *rows; r++)
    {
      maze[r] = new char[*cols];
      for(int c = 0; c < *cols; c++)
      {
        cin >> maze[r][c];
        if(cin.fail()) return NULL;
      }
    }
    return maze;
}

void print_maze(char** maze, int rows, int cols) {
    for(int r = 0; r < rows; r++)
    {
      for(int c = 0; c < cols; c++)
      {
        cout << maze[r][c];
      }
      cout << "\n";
    }
}
