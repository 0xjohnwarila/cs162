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
// output South
#include <iostream>
#include <vector>

using namespace std;

const int n = 10;
const int m = 20;

class node {
public:
	bool n, e, s, w;
	node(): n(true), e(true), s(true), w(true) {}
};



int main(int argc, char const *argv[]) {
	srand(time(NULL));
	node maze[m][n];

	for(int y = 1; y < n-1; y++) {
		for(int x = 1; x < m-1; x++) {
			if(maze[y-1][x].s == true) {
				maze[y][x].n = true;
			}
			else if(maze[y][x+1].w == true) {
				maze[y][x].e = true;
			}
			else if(maze[y+1][x].n == true) {
				maze[y][x].s = true;
			}
			else if(maze[y][x-1].e == true) {
				maze[y][x].w = true;
			}
		}
	}

	for(int y = 1; y < m-1; y++) {
		for(int x = 1; x < n-1; x++) {
			maze[y][x].e = false;
			maze[y][x].s = false;

			if((rand()%2) == 0) {
				maze[y][x].n = false;
			}
			else{
				maze[y][x].w = false;
			}
		}
	}
	
	for(int y = 0; y < m; y++) {
		for(int x = 0; x < n; x++) {
			if(y == 0) {
				maze[y+1][x].w = false;
			}
			else if(x == 0) {
				maze[y][x+1].n = false;
			}
			else if(y == n-1) {
				maze[y-1][x].s = false;
			}
			else if(x == m-1) {
				maze[y][x-1].e = false;
			}
		}
	}

	for(int y = 0; y < n; y++) {
		for(int x = 0; x < m; x++) {
			if(maze[y-1][x] == false || maze[y][x-1]) {
				cout << "+";
			}
			else if(maze[y-1][x] == true && maze[y][x-1]) {
				cout << " ";
			}
			if(maze[y-1][x] == false) {
				cout << "-";
			}
			else if(maze[y-1][x] == true) {
				cout << " ";
			}
			if(maze[])
			{
				/* code */
			}
		}
	}
	return 0;
}