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
	vector<vector<bool>> maze;
	int i = 0;

	while(getline(in, line)) {
		lines.push_back(line);
		i++;
	}

	for(int z = 0; z < i; z++){
		int length = lines[z].length();

		for(int y = 0; y < length; y++){
			if(lines[z][y] == '#'){
				maze[z][y] = true;
			}else if(lines[z][y] == 'X') {
				maze[z][y] = false;
			}else if(lines[z][y] == '@') {
				maze[z][y] = false;
			}else if(lines[z][y] == ' ') {
				maze[z][y] = false;
			}
		}
	}

	for(int x = 0; x < i; x++){
		cout << lines[x] << endl;
	}

	return 0;
}