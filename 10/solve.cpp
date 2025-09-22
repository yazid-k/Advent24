#include <iostream>
#include <fstream>
#include <set>

std::set<std::pair<int,int>> count_reachable(const std::vector<std::string>& grid, int x, int y, int current)
{
	int rows = grid.size(), cols = grid[0].size();
	if (x < 0 || x >= rows || y < 0 || y >= cols) return {};
	if (grid[x][y] - '0' != current) return {};

	if (current == 9)
		return { {x,y} };

	auto s1 = count_reachable(grid, x+1, y, current+1);
	auto s2 = count_reachable(grid, x-1, y, current+1);
	auto s3 = count_reachable(grid, x, y+1, current+1);
	auto s4 = count_reachable(grid, x, y-1, current+1);

	s1.insert(s2.begin(), s2.end());
	s1.insert(s3.begin(), s3.end());
	s1.insert(s4.begin(), s4.end());

	return s1;
}

int count_paths(const std::vector<std::string>& grid, int x, int y, int current)
{
	if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
		return 0;
	if (grid[x][y] - '0' != current)
		return 0;
	if (current == 9)
		return 1;

	return count_paths(grid, x + 1, y, current + 1) +
			count_paths(grid, x - 1, y, current + 1) +
			count_paths(grid, x, y + 1, current + 1) +
			count_paths(grid, x, y - 1, current + 1);
}

int main(int argc, char const *argv[])
{
	std::ifstream in("input.txt");
	std::string line;
	std::vector<std::string> grid;
	while (std::getline(in, line))
		grid.push_back(line);
	int total_reachable = 0;
	int total_paths = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == '0')
			{
				total_paths += count_paths(grid, i, j, 0);
				total_reachable += count_reachable(grid, i, j, 0).size();
			}
		}
	}
	std::cout << total_paths << std::endl;
	std::cout << total_reachable << std::endl;
	return 0;
}
