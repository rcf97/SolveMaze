//#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <time.h>
using namespace std;

#include "Pathfinder.h"

Pathfinder::Pathfinder() {
	srand(time(NULL));
	for (int i = 0; i < DEP_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {
			for (int k = 0; k < COL_SIZE; k++) {
				maze_grid[k][j][i] = 1;
			}
		}
	}
}

string Pathfinder::toString() const
{
	stringstream ss;
    for (int level = 0; level < DEP_SIZE; level++) {
    	for(int row = 0; row < ROW_SIZE; row++) {
       		for(int col = 0; col < COL_SIZE; col++) {
       	    	ss << maze_grid[col][row][level];
   	        	if (col != 4) {
            		ss << " ";
           		}
   	    	}
       		ss << endl;
   		}
    	if (level != DEP_SIZE - 1) {
   			ss << endl;
   		}
    }
    return ss.str();
}

void Pathfinder::createRandomMaze() {
	for (int i = 0; i < DEP_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {
			for (int k = 0; k < COL_SIZE; k++) {
				maze_grid[k][j][i] = rand()%2;
			}
		}
	}
	maze_grid[0][0][0] = 1;
	maze_grid[4][4][4] = 1;
}

bool Pathfinder::importMaze(string file_name)
{
	if (!Pathfinder::isValidMaze(file_name)) {
		return false;
	}
	cout << "importMaze from "<<file_name<<endl;
	ifstream file (file_name.c_str());
	if (file.is_open()) {
		string line;
		int row_count = 0;
		for (int level = 0; level < DEP_SIZE; level++) {
			for(int row = 0; row < ROW_SIZE; row++) {
				getline(file, line);
				stringstream ss(line);
				//row_count++;
				for(int col = 0; col < COL_SIZE; col++) {
					int value;
					ss >> value;
					if (value != 1 && value != 0) {
						//return false;
					}
					cout << "["<<col<<"]["<<row<<"]["<<level<<"]="<<value<<endl;
					maze_grid[col][row][level] = value;
				}
				int check;			//to check if extra 1s or 0s on a line
				ss >> check;
				if (check == 1 || check == 0) {
					//return false;
				}
			}
			getline(file, line);
			if (file.eof() && level != 4) {
				//return false;
			}
		}
		if (!file.eof()) {
			//return false;
		}
	}
	else {
		//return false;
	}
	if (maze_grid[0][0][0] != 1 || maze_grid[4][4][4] != 1) {
		//return false;
	}
	
    return true;
}
bool Pathfinder::isValidMaze(string file_name) {
	ifstream file (file_name.c_str());
	if (file.is_open()) {
		string line;
		string input;
		while (!file.eof()) {
			getline(file, input);
			line += input;
		}
		while (line.find(' ') != string::npos) {
			line.erase(line.find(' '),1);
		}
		int i = 0;
		for (i = 0; i < line.length(); i++) {
			if (isalpha(line.at(i))) {
				//cout << "1";
				return false;
			}
		}
		if (line.size() != 125) {
			return false;
		}
		if (line.front() != '1' || line.back() != '1') {
			//cout << "3";
			return false;
		}
	}
	else {
		return false;
	}
	
    return true;
}

bool Pathfinder::find_maze_path(int grid[5][5][5], int l, int r, int c) {
	if (l < 0 || r < 0 || c < 0 ||l >= DEP_SIZE || r >= ROW_SIZE || c >= COL_SIZE)
		return false;      // Cell is out of bounds.
	else if (grid[c][r][l] != BACKGROUND)
	    return false;      // Cell is on barrier or dead end.
	else if (l == 0 && r == 0 && c == 0) {
	    grid[c][r][l] = PATH;         // Cell is on path
	    solution.push_back("("+to_string(c)+", "+to_string(r)+", "+to_string(l)+")");
	    return true;               // and is maze exit.
	}
	else { 
	    // Recursive case.
	    // Attempt to find a path from each neighbor.
	    // Tentatively mark cell as on path.
	    grid[c][r][l] = PATH;
	    if (find_maze_path(grid, l, r - 1, c) // Up
	        || find_maze_path(grid, l, r + 1, c) // Down
	        || find_maze_path(grid, l, r, c - 1) // Left
	        || find_maze_path(grid, l, r, c + 1 )
	        || find_maze_path(grid, l - 1, r, c)
	        || find_maze_path(grid, l + 1, r, c)) { // Right
	    	solution.push_back("("+to_string(c)+", "+to_string(r)+", "+to_string(l)+")");
	    	return true;
	    }
	    else {
	    	grid[c][r][l] = TEMPORARY;  // Dead end.
	    	return false;
	    }
	}
}
vector<string> Pathfinder::solveMaze() {
	int solve[5][5][5];
	for (int i = 0; i < DEP_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {
			for (int k = 0; k < COL_SIZE; k++) {
				solve[k][j][i] = maze_grid[k][j][i];
			}
		}
	}
	this->solution.clear();
	find_maze_path(solve, 4, 4, 4);
	for(auto s:solution) {
		cout <<s<<endl;
	}
	return this->solution;
}


