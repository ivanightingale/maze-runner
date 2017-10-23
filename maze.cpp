#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

int maze_search(char**, int, int); //finds the shortest path, marks it with *

int main() {
   int rows, cols, result;
   char** mymaze;

   cin >> rows >> cols;
   if(cin.fail())
   {
     cerr << "***Error: wrong format.***" << endl;
     return 1;
   }
   mymaze = read_maze(&rows, &cols);

   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   result = maze_search(mymaze, rows, cols);

   if (result == 1) {       //path found
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { //no path
      cout << "No path could be found!" << endl;
   }
   else {
      cout << "Invalid maze." << endl;
   }

   for(int i = 0; i < rows; i++) delete[] mymaze[i];
   delete[] mymaze;

   return 0;
}


int maze_search(char** maze, int rows, int cols) {
    Location f, s;
    bool fOne = false, sOne = false;
    for(int r = 0; r < rows; r++)
    {
      for(int c = 0; c < cols; c++)
      {
        if(maze[r][c] == 'S')
        {
          if(sOne) return -1;
          else{
            s.row = r;
            s.col = c;
            sOne = true;
          }
        }
        else if(maze[r][c] == 'F')
        {
          if(fOne) return -1;
          else{
            f.row = r;
            f.col = c;
            fOne = true;
          }
        }
      }
    }
    if (!fOne || !sOne) {
      return -1;
    }

    bool** visited = new bool*[rows];
    Location** pre = new Location*[rows];
    for(int i = 0; i < rows; i++)
    {
      visited[i] = new bool[cols];
      for(int j = 0; j < cols; j++) visited[i][j] = false;
      pre[i] = new Location[cols];
    }

    Queue q(rows * cols);
    q.add_to_back(s);
    bool finished = false;
    while(!q.is_empty() && !finished)
    {
      Location curLoc = q.remove_from_front();
      for(int i = -1; i < 2; i++)
      {
        for(int j = -1; j < 2; j++)
        {
          int r = curLoc.row + i;
          int c = curLoc.col + j;
          if(i != j && i + j != 0 && r >= 0 && c >= 0 && r < rows && c < cols)
          {
            if(maze[r][c] != '#' && !visited[r][c])
            {
              if(maze[r][c] == 'F')
              {
                f.row = r;
                f.col = c;
                finished = true;
              }
              Location newLoc;
              newLoc.row = r;
              newLoc.col = c;
              q.add_to_back(newLoc);
              visited[r][c] = true;
              pre[r][c] = curLoc;
            }
          }
        }
      }
    }
    if(finished)
    {
      f = pre[f.row][f.col];
      while(maze[f.row][f.col] != 'S')
      {
        maze[f.row][f.col] = '*';
        f = pre[f.row][f.col];
      }
    }

    for(int i = 0; i < rows; i++)
    {
      delete[] visited[i];
      delete[] pre[i];
    }
    delete[] visited;
    delete[] pre;

    return finished;
}
