#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
	using std::cout;
	using std::endl;
	using std::cin;
	using std::string;
	using std::ifstream;
	using std::vector;

	ifstream in(argv[1]);

	string line;
	vector<string> lines;
	int i = 0;

	while(getline(in, line)) {
		lines.push_back(line);
		i++;
	}

	for(int z = 0; z < i; z++){
		int length = lines[z].length();

		for(int y = 0; y < length; y++){
			if(lines[z][y] == '#'){
				lines[z][y] = 'w';
			}else if(lines[z][y] == 'X') {
				lines[z][y] = 'e';
			}else if(lines[z][y] == '@') {
				lines[z][y] = 'p';
			}else if(lines[z][y] == ' ') {
				lines[z][y] = 'n';
			}
		}
	}


	return 0;
}

for(int x=0;x<n;x++)
	if(lines[x][y]==0)
	    map[x][y] = 0;
	else if(lines[x][y]==1)
	    map[x][y] = 1; //obstacle
	else if(lines[x][y]==2)
	    map[x][y] = 2; //start
	else if(lines[x][y]==3)
	    map[x][y] = 3; //route
	else if(map[x][y]==4)
	    map[x][y] = 4; //finish