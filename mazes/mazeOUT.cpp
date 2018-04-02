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

	for(int x = 0; x <= i; x++){
		cout << lines[x] << endl;
	}

	return 0;
}