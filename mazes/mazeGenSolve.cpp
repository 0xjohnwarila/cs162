#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <fstream>
#include <thread>
#include <fstream>
using namespace std;

const int n=60; // horizontal size of the map
const int m=80; // vertical size size of the map
const int m1 = 20;
const int n1 = 20;
static int map[n][m];
static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
static int dir_map[n][m]; // map of directions
const int dir=4; 
static int dx[dir]={1, 0, -1, 0};
static int dy[dir]={0, 1, 0, -1};


class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

    public:
        node(int xp, int yp, int d, int p) 
            {xPos=xp; yPos=yp; level=d; priority=p;}
    
        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i) // i: direction
        {
             level+=(dir==8?(i%2==0?10:14):10);
        }
        
        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;         

            // Euclidian Distance
            //d=static_cast<int>(sqrt(xd*xd+yd*yd));

            // Manhattan distance
            //d=abs(xd)+abs(yd);
            
            // Chebyshev distance
            d=max(abs(xd), abs(yd));

            return(d);
        }
};

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
void clearScreen() {
        cout << "\033[2J\033[1;1H";
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

void dumpMazeToFile() {
        ofstream file ("mazeInternal");
        for (int y = 1; y < 21; ++y)
        {
                for (int x = 1; x < 21; ++x)
                {
                        file << "1";
                        if (maze[y][x].north == true) file << "00";
                        else file << "11";
                        file << "1";
                }
                file << endl;
                for (int x = 1; x < 21; ++x)
                {
                        if (maze[y][x].west == true) file << "0";
                        else file << "1";
                        if (maze[y][x].north == true || maze[y][x].east == true || maze[y][x].south == true || maze[y][x].west == true) file << "00";
                        else file << "11";
                        if (maze[y][x].east == true) file << "0";
                        else file << "1";
                }
                file << endl;
                for (int x = 1; x < 21; ++x)
                {
                        file << "1";
                        if (maze[y][x].south == true) file << "00";
                        else file << "11";
                        file << "1";
                }
                file << endl;
        }
        file.close();
}

void recursiveBackTrack() {
        makeEdge();

        unsigned int randomStartX = 0;
        unsigned int currentX = (rand()%n1 + 1);
        unsigned int randomStartY = 0;
        unsigned int currentY = (rand()%m1 + 1);

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
                clearScreen();
                printMaze();
                getchar();
        }
        dumpMazeToFile();
}

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string pathFind( const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish )
{
        static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
        static int pqi; // pq index
        static node* n0;
        static node* m0;
        static int i, j, x, y, xdx, ydy;
        static char c;
        pqi=0;

        // reset the node maps
        for(y=0;y<m;y++) {
                for(x=0;x<n;x++) {
                        closed_nodes_map[x][y]=0;
                        open_nodes_map[x][y]=0;
                }
        }

        // create the start node and push into list of open nodes
        n0=new node(xStart, yStart, 0, 0);
        n0->updatePriority(xFinish, yFinish);
        pq[pqi].push(*n0);
        open_nodes_map[x][y]=n0->getPriority(); // mark it on the open nodes map

        // A* search
        while(!pq[pqi].empty()) {
                // get the current node w/ the highest priority
                // from the list of open nodes
                n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), 
                             pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

                x=n0->getxPos(); y=n0->getyPos();

                pq[pqi].pop();
                open_nodes_map[x][y]=0;
                closed_nodes_map[x][y]=1;
                if(x==xFinish && y==yFinish) {
                        // generate the path from finish to start
                        // by following the directions
                        string path="";
                        while(!(x==xStart && y==yStart)) {
                                j=dir_map[x][y];
                                c='0'+(j+dir/2)%dir;
                                path=c+path;
                                x+=dx[j];
                                y+=dy[j];
                        }

                        // garbage collection
                        delete n0;
                        // empty the leftover nodes
                        while(!pq[pqi].empty()) pq[pqi].pop();           
                                return path;
                }

                // generate moves (child nodes) in all possible directions
                for(i=0;i<dir;i++) {
                        xdx=x+dx[i]; ydy=y+dy[i];

                        if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1 
                                || closed_nodes_map[xdx][ydy]==1)) {
                                // generate a child node
                                m0=new node( xdx, ydy, n0->getLevel(), 
                                        n0->getPriority());
                                m0->nextLevel(i);
                                m0->updatePriority(xFinish, yFinish);

                                // if it is not in the open list then add into that
                                if(open_nodes_map[xdx][ydy]==0) {
                                        open_nodes_map[xdx][ydy]=m0->getPriority();
                                        pq[pqi].push(*m0);
                                        // mark its parent node direction
                                        dir_map[xdx][ydy]=(i+dir/2)%dir;
                                }
                                else if(open_nodes_map[xdx][ydy]>m0->getPriority()) {
                                        // update the priority info
                                        open_nodes_map[xdx][ydy]=m0->getPriority();
                                        // update the parent direction info
                                        dir_map[xdx][ydy]=(i+dir/2)%dir;

                                        // replace the node
                                        // by emptying one pq to the other one
                                        // except the node to be replaced will be ignored
                                        // and the new node will be pushed in instead
                                        while(!(pq[pqi].top().getxPos()==xdx && 
                                                pq[pqi].top().getyPos()==ydy)) {                
                                                pq[1-pqi].push(pq[pqi].top());
                                                pq[pqi].pop();       
                                        }
                                        pq[pqi].pop(); // remove the wanted node
                            
                                        // empty the larger size pq to the smaller one
                                        if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                                        while(!pq[pqi].empty()) {                
                                                pq[1-pqi].push(pq[pqi].top());
                                                pq[pqi].pop();       
                                        }
                                        pqi=1-pqi;
                                        pq[pqi].push(*m0); // add the better node instead
                                }
                        else delete m0; // garbage collection
                        }
                }
                delete n0; // garbage collection
        }
        return ""; // no route found
}



int main(int argc, char const *argv[])
{
        srand(time(NULL));

        recursiveBackTrack();
        // create empty map
        for(int y=0;y<m;y++)
        {
                for(int x=0;x<n;x++) map[x][y]=0;
        }

        ifstream in("mazeInternal");

        string line;
        vector<string> lines;

        while(getline(in, line)) {
                lines.push_back(line);
        }

        for(int y = 0; y < m; y++){
                for(int x=0;x<n;x++){
                        if(lines[x][y]=='0'){
                                map[x][y] = 0;
                        }
                        else if(lines[x][y]=='1'){
                                map[x][y] = 1; //obstacle
                        }
                        else if(lines[x][y]=='2'){
                                map[x][y] = 2; //start
                        }
                        else if(lines[x][y]=='3'){
                                map[x][y] = 3; //route
                        }
                        else if(map[x][y]=='4'){
                                map[x][y] = 4; //finish
                        }
                }
        }

        for(int y=0;y<m;y++) {
                for(int x=0;x<n;x++)
                        if(map[x][y]==0)
                                cout<<" ";
                        else if(map[x][y]==1)
                                cout<<"█"; //obstacle
                        else if(map[x][y]==2)
                                cout<<"S"; //start
                        else if(map[x][y]==3)
                                cout<<"*"; //route
                        else if(map[x][y]==4)
                                cout<<"X"; //finish
                        cout<<endl;
        }
 
        // randomly select start and finish locations
        int xA, yA, xB, yB;

        xA = 58;
        yA = 58;
        xB = 1;
        yB = 1;
    

        cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
        cout<<"Start: "<<xA<<","<<yA<<endl;
        cout<<"Finish: "<<xB<<","<<yB<<endl;
        // get the route
        clock_t start = clock();
        string route=pathFind(xA, yA, xB, yB);
        if(route=="") cout<<"An empty route generated!"<<endl;
        clock_t end = clock();
        double time_elapsed = double(end - start);
        cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
        cout<<"Route:"<<endl;
        for(int i=0;i<=route.size();i++){
                if(route[i]=='1')
                        cout<<"D";
                else if(route[i]=='2')
                        cout<<"L";
                else if(route[i]=='3')
                        cout<<"U";
                else if(route[i]=='4')
                        cout<<"R";
        }
        cout<<endl;

        // follow the route on the map and display it 
        if(route.length()>0) {
                int j; char c;
                int x=xA;
                int y=yA;
                map[x][y]=2;
                for(int i=0;i<route.length();i++) {
                        c =route.at(i);
                        j=c-'0'; 
                        x=x+dx[j];
                        y=y+dy[j];
                        map[x][y]=3;
                }
                map[x][y]=4;
    
                // display the map with the route
                for(int y=0;y<m;y++) {
                        for(int x=0;x<n;x++)
                                if(map[x][y]==0)
                                        cout<<" ";
                                else if(map[x][y]==1)
                                        cout<<"█"; //obstacle
                                else if(map[x][y]==2)
                                        cout<<"S"; //start
                                else if(map[x][y]==3)
                                        cout<<"*"; //route
                                else if(map[x][y]==4)
                                        cout<<"F"; //finish
                                cout<<endl;
                        }
                }
        return 0;
}