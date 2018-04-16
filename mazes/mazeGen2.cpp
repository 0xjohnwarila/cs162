#include <iostream>
#include <thread>
#include <vector>

const int m = 20;
const int n = 30;

struct node {
	bool north, west, south, east, visited;
	node(): north(false), west(false), south(false), east(false), visited(false){}
};

struct coordinate {
	double x, y;
	coordinate(double paramy, double paramx): x(paramx), y(paramy){}
};

node maze[20][30];
std::vector<coordinate> loc;

int chooseDir() {
	return (rand()%3);
}

void moveTo(unsigned int inputY, unsigned int inputX) {
	loc.push_back(coordinate(inputY, inputX));
	maze[inputY][inputX].visited = true;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	unsigned int randomStartX, currentX = (rand()%n);
	unsigned int randomStartY, currentY = (rand()%m);

	loc.push_back(coordinate(randomStartY, randomStartX));
	maze[randomStartY][randomStartX].visited = true;

	while(true) {
		int dirChoice = chooseDir();

		if(dirChoice == 0) {
			if(!(currentY-1)) {
				// Move there
				maze[currentY][currentX].north = true;
				maze[currentY-1][currentX].south = true;
				currentY = currentY - 1;
				moveTo(currentY, currentX);
				break;
			}
		}
		else if(dirChoice == 1) {
			if(!(currentX + 1 >= n)) {
				// Move there
				maze[currentY][currentX].east = true;
				maze[currentY][currentX+1].west = true;
				currentX = currentX + 1;
				moveTo(currentY, currentX);
				break;
			}
		}
		else if(dirChoice == 2) {
			if(!(currentY + 1 >= m)) {
				// Move there
				maze[currentY][currentX].south = true;
				maze[currentY+1][currentX].north = true;
				currentY = currentY + 1;
				moveTo(currentY+1, currentX);
				break;
			}
		}
		else if(dirChoice == 3) {
			if(!(currentX - 1)) {
				// Move there
				maze[currentY][currentX].east = true;
				maze[currentY][currentX-1].west = true;
				currentX = currentX - 1;
				moveTo(currentY, currentX-1);
				break;
			}
		}
	}
	
	

	return 0;
}

