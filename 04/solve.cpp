#include <iostream>
#include <vector>
#include <fstream>

int check_part_1(const std::vector<std::string> &lines, size_t row, size_t col)
{
	int count = 0;
	if (lines[row].substr(col, 4) == "XMAS")
		count++;
	if (col >= 3)
	{
		if (lines[row].substr(col - 3, 4) == "SAMX")
			count++;
	}
	if (row + 3 < lines.size())
	{
		if (col >= 3)
		{
			if (lines[row][col] == 'X' && lines[row + 1][col - 1] == 'M' && lines[row + 2][col - 2] == 'A' && lines[row + 3][col - 3] == 'S')
				count++;
		}
		if (col + 3 < lines[row].size())
		{
			if (lines[row][col] == 'X' && lines[row + 1][col + 1] == 'M' && lines[row + 2][col + 2] == 'A' && lines[row + 3][col + 3] == 'S')
				count++;
		}
		if (lines[row][col] == 'X' && lines[row + 1][col] == 'M' && lines[row + 2][col] == 'A' && lines[row + 3][col] == 'S')
			count++;
	}
	if (row >= 3)
	{
		if (col >= 3)
		{
			if (lines[row][col] == 'X' && lines[row - 1][col - 1] == 'M' && lines[row - 2][col - 2] == 'A' && lines[row - 3][col - 3] == 'S')
				count++;
		}
		if (col + 3 < lines[row].size())
		{
			if (lines[row][col] == 'X' && lines[row - 1][col + 1] == 'M' && lines[row - 2][col + 2] == 'A' && lines[row - 3][col + 3] == 'S')
				count++;
		}
		if (lines[row][col] == 'X' && lines[row - 1][col] == 'M' && lines[row - 2][col] == 'A' && lines[row - 3][col] == 'S')
			count++;
	}
	return count;
}

bool check_part_2(const std::vector<std::string> &lines, size_t row, size_t col)
{
	std::string corners{lines[row - 1][col - 1], lines[row - 1][col + 1], lines[row + 1][col - 1], lines[row + 1][col + 1]};
	std::vector<std::string> patterns{"MSMS", "MMSS", "SMSM", "SSMM"};
	for (const auto &pattern : patterns)
	{
		if (corners == pattern)
			return true;
	}
	return false;
}

int main(int argc, char const *argv[])
{
	std::ifstream input("input.txt", std::ios::in);
	std::vector<std::string> lines;
	std::string line;
	int res = 0;
	int res2 = 0;
	while (std::getline(input, line))
		lines.push_back(line);
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = lines[i].find("X"); j < lines[i].size(); j = lines[i].find("X", j + 1))
			res += check_part_1(lines, i, j);
	}
	for (size_t i = 1; i < lines.size() - 1; i++)
	{
		for (size_t j = lines[i].find("A", 1); j < lines[i].size() - 1; j = lines[i].find("A", j + 1))
			res2 += check_part_2(lines, i, j);
	}
	std::cout << "Total Part 1: " << res << std::endl;
	std::cout << "Total Part 2: " << res2 << std::endl;
	return 0;
}
