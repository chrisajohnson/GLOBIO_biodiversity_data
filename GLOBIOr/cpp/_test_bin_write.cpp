#include <iostream>
#include <fstream>
#include <vector>

int main() {
		std::vector<double> v1{1.0,2.1,3.5,4.1};
		
		std::ofstream outfile{"test.bin", std::ios::binary};
		outfile.write(reinterpret_cast<const char *>(v1.data()),
			v1.size() * sizeof(decltype(v1)::value_type));
		outfile.close();
		
		std::vector<double> v2(4);
		
		std::ifstream infile{"test.bin", std::ios::binary};
		infile.read(reinterpret_cast<char *>(v2.data()),
			v2.size() * sizeof(decltype(v2)::value_type));
		
		for (double i : v2)
			std::cout << i << ' ';
		std::cout << '\n';
}