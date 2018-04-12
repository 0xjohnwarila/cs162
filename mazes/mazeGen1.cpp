// Make a blank maze
// Put walls around the maze
// Make random North West passages
// Fix South and East so passages are connected.
// Out put NorthWest Corner
// Ouput North edge
// Output NorthEast corner
// Output West wall
// Output middle
// Output East wall
// Ouput SouthWest corner
// Output South edge
// output SouthEast corner

#include <iostream>
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

const int n = 10;
const int m = 10;

class node {
public:
	bool north, east, south, west;
	node(): north(false), east(false), south(false), west(false) {}
};



int main(int argc, char const *argv[]) {
	srand(time(NULL));
	node maze[m][n];

	// Set the top wall and the left wall to be a passage to the top left
	// corner.
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < m; x++) {
			if(y == 0 && x != 0) {
				maze[y][x].west = true;
			}
			else if(x == 0 && y != 0) {
				maze[y][x].north = true;
			}
		}
	}

	// For every cell, that is not the top or left wall, give a random
	// passable direction west or north.
	for(int y = 1; y < n; y++) {
		for(int x = 1; x < m; x++) {
			if((rand()%2) == 0) {
				maze[y][x].west = true;
			}
			else {
				maze[y][x].north = true;
			}
		}
	}

	for(int y = 0; y < m; y++) {
		for(int x = 0; x < n; x++) {
			if(maze[y][x].south == true) {
				maze[y+1][x].north = true;
			}
			else if(maze[y][x+1].east == true) {
				maze[y][x].west = true;
			}
			else if(maze[y-1][x].north == true) {
				maze[y][x].south = true;
			}
			else if(maze[y][x-1].west == true) {
				maze[y][x].east = true;
			}
		}
	}

	ofstream file("randomMaze1");
	
	for(int y = 0; y < n; ++y) {
		for(int x = 0; x < m; ++x) {
			file << "1";
			if(maze[y][x].north == true) file << "00";
			else file << "11";
			file << "1";
		}
		file << endl;
		for(int x = 0; x < m; ++x) {
			if (maze[y][x].west == true) 
				file << "0";
			else 
				file << "1";
			if (maze[y][x].north == true || maze[y][x].east == true || maze[y][x].south == true || maze[y][x].west == true) 
				file << "00";
			else 
				file << "11";
			if (maze[y][x].east == true) 
				file << "0";
			else 
				file << "1";
		}
		file << endl;
		for(int x = 0; x < m; ++x) {
			file << "1";
			if (maze[y][x].south == true) file << "00";
			else file << "11";
			file << "1";
		}
		file << endl;
	}
	file.close();

	return 0;
}