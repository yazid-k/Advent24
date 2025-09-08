#include <iostream>
#include <fstream>


int distance(std::vector<int> a, std::vector <int> b)
{
	int count = 0;

	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	for (size_t i = 0; i < a.size(); i++)
		count += abs(a[i] - b[i]);
	return count;
}

int similarity(std::vector<int> a, std::vector<int> b)
{
	int result = 0;
	for (size_t i = 0; i < a.size(); i++)
		result += std::count(b.begin(), b.end(), a[i]) * a[i];
	return result;
}

int main(int argc, char const *argv[])
{
	std::ifstream		data;
	std::string			line;
	std::vector<int>	n1;
	std::vector<int>	n2;

	data.open("numbers.txt", std::ios::in);

	while (std::getline(data, line))
	{
		n1.push_back(std::stoi(line));
		n2.push_back(std::stoi(line.substr(7)));
	}

	std::cout << distance(n1, n2) << std::endl;
	std::cout << similarity(n1, n2) << std::endl;
	return 0;
}
