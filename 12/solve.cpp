#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

int get_patch_perimeter(const std::set<std::pair<int,int>>& patch, std::vector<std::string>& grid)
{
	int perimeter = 0;
	int rows = grid.size(), cols = grid[0].size();
	for (const auto& cell : patch)
	{
		int x = cell.first;
		int y = cell.second;
		if (x == 0 || !patch.count({x-1, y})) perimeter++;
		if (x == rows-1 || !patch.count({x+1, y})) perimeter++;
		if (y == 0 || !patch.count({x, y-1})) perimeter++;
		if (y == cols-1 || !patch.count({x, y+1})) perimeter++;
	}
	return perimeter;
}

std::set<std::pair<int,int>> get_patch(const std::vector<std::string>& grid, int x, int y, int current, std::set<std::pair<int,int>>& visited)
{
	int rows = grid.size(), cols = grid[0].size();
	if (x < 0 || x >= rows || y < 0 || y >= cols) return {};
	if (grid[x][y] != current) return {};
	if (visited.count({x,y})) return {};

	visited.insert({x, y});
	std::set<std::pair<int,int>> area = {{x, y}};
	auto add_area = [&](int nx, int ny)
	{
		auto sub_area = get_patch(grid, nx, ny, current, visited);
		area.insert(sub_area.begin(), sub_area.end());
	};
	add_area(x+1, y);
	add_area(x-1, y);
	add_area(x, y+1);
	add_area(x, y-1);
	return area;
}

int main(int argc, char const *argv[])
{
	std::vector<std::string> grid;
	std::string line;
	std::ifstream infile("input.txt");
	while (std::getline(infile, line))
		grid.push_back(line);
	int total_price = 0;
	std::set<std::pair<int,int>> visited;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (visited.count({i,j})) continue;
			std::set<std::pair<int,int>> patch_plants = get_patch(grid, i, j, grid[i][j], visited);
			int perimeter = get_patch_perimeter(patch_plants, grid);
			std::cout << "Patch of plant type " << grid[i][j] << " with size " << patch_plants.size() << " has perimeter " << perimeter << "\n";
			total_price += patch_plants.size() * perimeter;
		}
	}
	std::cout << "Total price: " << total_price << "\n";
	return 0;
}

