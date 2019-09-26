#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PathfinderInterface
{
public:
	PathfinderInterface() {}
	virtual ~PathfinderInterface() {}
	virtual string toString() const = 0;
	virtual void createRandomMaze() = 0;
	virtual bool importMaze(string file_name) = 0;
	virtual vector<string> solveMaze() = 0;
};
