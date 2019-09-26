#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "PathfinderInterface.h"

using namespace std;

class Pathfinder : public PathfinderInterface {
public:
	Pathfinder();
	~Pathfinder() {}
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
	bool isValidMaze(string file_name);
	bool find_maze_path(int grid[5][5][5], int l, int r, int c);
protected:
	bool read;
	const int ROW_SIZE = 5;
	const int COL_SIZE = 5;
	const int DEP_SIZE = 5;
	const int BACKGROUND = 1;
	const int WALL = 0;
	const int TEMPORARY = 2; // Used to show this path has been explored
	const int PATH = 3;
    int maze_grid[5][5][5]; // To hold values
    vector<string> solution;
    string mazeString;
};
