#include <iostream>
#include <thread>
#include <vector>

const int m1 = 20;
const int n1 = 20;

struct cell {
        bool north, west, south, east, visited;
        cell(): north(false), west(false), south(false), east(false), visited(false){}
};

struct coordinate {
        double x, y;
        coordinate(double paramy, double paramx): x(paramx), y(paramy){}
};

cell maze[22][22];
std::vector<coordinate> loc;

int chooseDir() {
        // Choose Direction
        // Return a random number from 0-3 to be used for a direction to tunnel
        // John Warila
        return (rand()%3);
}

void moveTo(unsigned int inputY, unsigned int inputX) {
        // Move To Cell
        // Add the next location to the stack and set that location's visited boolean to true
        // John Warila
        loc.push_back(coordinate(inputY, inputX));
        maze[inputY][inputX].visited = true;
}

void makeEdge() {
        // Make Edge
        // Set the east and south wall to edges
        // John Warila
        for(int y = 0; y < 22; y++) {
                for(int x = 0; x < 22; x++) {
                        if(y == 21 || y == 0) {
                                maze[y][x].visited = true;
                        }
                        if(x == 21 || x == 0) {
                                maze[y][x].visited = true;
                        }
                }
        }
}

void printMaze() {
        //Print Maze
        //Stolen from my old binary tree maze generator
        //prints in 3 x 4 squares of corners and walls for each location in the maze
        //Joshua Barringer
        // Stolen from josh's implementation
        using std::cout;
        using std::endl;
        for (int y = 1; y < 21; ++y)
        {
                for (int x = 1; x < 21; ++x)
                {
                        cout << "+";
                        if (maze[y][x].north == true) cout << "  ";
                        else cout << "--";
                        cout << "+";
                }
                cout << endl;
                for (int x = 1; x < 21; ++x)
                {
                        if (maze[y][x].west == true) cout << " ";
                        else cout << "|";
                        if (maze[y][x].north == true || maze[y][x].east == true || maze[y][x].south == true || maze[y][x].west == true) cout << "  ";
                        else cout << "++";
                        if (maze[y][x].east == true) cout << " ";
                        else cout << "|";
                }
                cout << endl;
                for (int x = 1; x < 21; ++x)
                {
                        cout << "+";
                        if (maze[y][x].south == true) cout << "  ";
                        else cout << "--";
                        cout << "+";
                }
                cout << endl;
        }
}

void printMazeMod1() {
        //Print Maze
        //Stolen from my old binary tree maze generator
        //prints in 3 x 4 squares of corners and walls for each location in the maze
        //Joshua Barringer
        // Stolen from josh's implementation
        using std::cout;
        using std::endl;
        for (int y = 1; y < 21; ++y)
        {
                for (int x = 1; x < 21; ++x)
                {
                        cout << "1";
                        if (maze[y][x].north == true) cout << "00";
                        else cout << "11";
                        cout << "1";
                }
                cout << endl;
                for (int x = 1; x < 21; ++x)
                {
                        if (maze[y][x].west == true) cout << "0";
                        else cout << "1";
                        if (maze[y][x].north == true || maze[y][x].east == true || maze[y][x].south == true || maze[y][x].west == true) cout << "00";
                        else cout << "11";
                        if (maze[y][x].east == true) cout << "0";
                        else cout << "1";
                }
                cout << endl;
                for (int x = 1; x < 21; ++x)
                {
                        cout << "1";
                        if (maze[y][x].south == true) cout << "00";
                        else cout << "11";
                        cout << "1";
                }
                cout << endl;
        }
}

int main(int argc, char const *argv[])
{
        using std::vector;
        using std::cout;
        using std::endl;
        srand(time(NULL));

        makeEdge();

        unsigned int randomStartX, currentX = (rand()%n1 + 1);
        unsigned int randomStartY, currentY = (rand()%m1 + 1);

        moveTo(currentY, currentX);

        do {
                cout << "first step" << endl;
                int dirChoice = rand() % 4;

                if(dirChoice == 0) {
                        if(maze[currentY - 1][currentX].visited == false) {
                                maze[currentY][currentX].north = true;
                                maze[currentY - 1][currentX].south = true;
                                currentY--;
                                moveTo(currentY, currentX);
                        }
                }
                else if(dirChoice == 1) {
                        if(maze[currentY][currentX + 1].visited == false) {
                                maze[currentY][currentX].east = true;
                                maze[currentY][currentX + 1].west = true;
                                currentX++;
                                moveTo(currentY, currentX);
                        }
                }
                else if(dirChoice == 2) {
                        if(maze[currentY + 1][currentX].visited == false) {
                                maze[currentY][currentX].south = true;
                                maze[currentY + 1][currentX].north = true;
                                currentY++;
                                moveTo(currentY, currentX);
                        }
                }
                else if(dirChoice == 3) {
                        if (maze[currentY][currentX - 1].visited == false) {
                                maze[currentY][currentX].west = true;
                                maze[currentY][currentX - 1].east = true;
                                currentX--;
                                moveTo(currentY, currentX);
                        }
                }
        } while (currentY == randomStartY && currentX == randomStartX);
        
        while(currentY != randomStartY && currentX != randomStartX) {
                int randDir = rand() % 4;

                if(maze[currentY + 1][currentX].visited
                && maze[currentY][currentX + 1].visited
                && maze[currentY - 1][currentX].visited
                && maze[currentY][currentX - 1].visited) {
                        loc.pop_back();
                        currentY = loc.back().y;
                        currentX = loc.back().x;
                }
                else {
                        if(randDir == 0) {
                                if(maze[currentY - 1][currentX].visited == false) {
                                        maze[currentY][currentX].north = true;
                                        maze[currentY - 1][currentX].south = true;
                                        currentY--;
                                        moveTo(currentY, currentX);
                                }
                        }
                        else if(randDir == 1) {
                                if(maze[currentY][currentX + 1].visited == false) {
                                        maze[currentY][currentX].east = true;
                                        maze[currentY][currentX + 1].west = true;
                                        currentX++;
                                        moveTo(currentY, currentX);
                                }
                        }
                        else if(randDir == 2) {
                                if(maze[currentY + 1][currentX].visited == false) {
                                        maze[currentY][currentX].south = true;
                                        maze[currentY + 1][currentX].north = true;
                                        currentY++;
                                        moveTo(currentY, currentX);
                                }
                        }
                        else if(randDir == 3) {
                                if (maze[currentY][currentX - 1].visited == false) {
                                        maze[currentY][currentX].west = true;
                                        maze[currentY][currentX - 1].east = true;
                                        currentX--;
                                        moveTo(currentY, currentX);
                                }
                        }
                }
        }

        printMaze();
        printMazeMod1();
        return 0;
}

void recursiveBackTrack() {
        makeEdge();

        unsigned int randomStartX, currentX = (rand()%n1 + 1);
        unsigned int randomStartY, currentY = (rand()%m1 + 1);

        moveTo(currentY, currentX);

        do {
                cout << "first step" << endl;
                int dirChoice = rand() % 4;

                if(dirChoice == 0) {
                        if(maze[currentY - 1][currentX].visited == false) {
                                maze[currentY][currentX].north = true;
                                maze[currentY - 1][currentX].south = true;
                                currentY--;
                                moveTo(currentY, currentX);
                        }
                }
                else if(dirChoice == 1) {
                        if(maze[currentY][currentX + 1].visited == false) {
                                maze[currentY][currentX].east = true;
                                maze[currentY][currentX + 1].west = true;
                                currentX++;
                                moveTo(currentY, currentX);
                        }
                }
                else if(dirChoice == 2) {
                        if(maze[currentY + 1][currentX].visited == false) {
                                maze[currentY][currentX].south = true;
                                maze[currentY + 1][currentX].north = true;
                                currentY++;
                                moveTo(currentY, currentX);
                        }
                }
                else if(dirChoice == 3) {
                        if (maze[currentY][currentX - 1].visited == false) {
                                maze[currentY][currentX].west = true;
                                maze[currentY][currentX - 1].east = true;
                                currentX--;
                                moveTo(currentY, currentX);
                        }
                }
        } while (currentY == randomStartY && currentX == randomStartX);
        
        while(currentY != randomStartY && currentX != randomStartX) {
                int randDir = rand() % 4;

                if(maze[currentY + 1][currentX].visited
                && maze[currentY][currentX + 1].visited
                && maze[currentY - 1][currentX].visited
                && maze[currentY][currentX - 1].visited) {
                        loc.pop_back();
                        currentY = loc.back().y;
                        currentX = loc.back().x;
                }
                else {
                        if(randDir == 0) {
                                if(maze[currentY - 1][currentX].visited == false) {
                                        maze[currentY][currentX].north = true;
                                        maze[currentY - 1][currentX].south = true;
                                        currentY--;
                                        moveTo(currentY, currentX);
                                }
                        }
                        else if(randDir == 1) {
                                if(maze[currentY][currentX + 1].visited == false) {
                                        maze[currentY][currentX].east = true;
                                        maze[currentY][currentX + 1].west = true;
                                        currentX++;
                                        moveTo(currentY, currentX);
                                }
                        }
                        else if(randDir == 2) {
                                if(maze[currentY + 1][currentX].visited == false) {
                                        maze[currentY][currentX].south = true;
                                        maze[currentY + 1][currentX].north = true;
                                        currentY++;
                                        moveTo(currentY, currentX);
                                }
                        }
                        else if(randDir == 3) {
                                if (maze[currentY][currentX - 1].visited == false) {
                                        maze[currentY][currentX].west = true;
                                        maze[currentY][currentX - 1].east = true;
                                        currentX--;
                                        moveTo(currentY, currentX);
                                }
                        }
                }
        }
}