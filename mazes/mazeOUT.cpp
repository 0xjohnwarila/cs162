#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::string;
	using std::ifstream;

	ifstream in(argv[1]);

	string str[1024];
	int i = 0;

	while(getline(in, str[i])){
		cout << str[i] << endl;
		i++;
	}

	
	return 0;
}