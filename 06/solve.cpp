#include <iostream>
#include <vector>
#include <fstream>
#include <set>

int pathing_obstacles(int x, int y,const std::vector<std::string>& grid, int dir, std::set<std::tuple<int, int, int>>& states)
{
	std::vector<std::pair<int,int>> directions = {{0,-1},{1,0},{0,1},{-1,0}};
	if (states.count({x,y,dir}) > 0)
		return 1;
	states.insert({x,y,dir});
	if (x + directions[dir].first < 0 || x + directions[dir].first >= (int)grid[0].size() ||
		y + directions[dir].second < 0 || y + directions[dir].second >= (int)grid.size())
		return 0;
	while (grid[y + directions[dir].second][x + directions[dir].first] == '#')
		dir = (dir + 1) % 4;
	return pathing_obstacles(x + directions[dir].first, y + directions[dir].second, grid, dir, states);
}

int pathing(int x, int y, const std::vector<std::string>& grid, int dir, std::set<std::pair<int,int>>& visited)
{
	std::vector<std::pair<int,int>> directions = {{0,-1},{1,0},{0,1},{-1,0}};
	visited.insert({x,y});
	if (x + directions[dir].first < 0 || x + directions[dir].first >= (int)grid[0].size() ||
		y + directions[dir].second < 0 || y + directions[dir].second >= (int)grid.size())
		return visited.size();
	if (grid[y + directions[dir].second][x + directions[dir].first] == '#')
		dir = (dir + 1) % 4;
	return pathing(x + directions[dir].first, y + directions[dir].second, grid, dir, visited);
}

int main(int argc, char const *argv[])
{
	std::ifstream map("map.txt");
	std::vector<std::string> grid;
	std::string line;
	int n_obstacles = 0;
	std::set<std::pair<int,int>> visited, potential_obstacles;

	int x, y;
	while (std::getline(map, line))
		grid.push_back(line);
	for (size_t i = 0; i < grid.size(); i++)
	{
		if (grid[i].find('^') != std::string::npos)
		{
			x = grid[i].find('^');
			y = i;
			break;
		}
	}
	std::cout << "Start: " << x << "," << y << std::endl;
	pathing(x, y, grid, 0, visited);
	std::cout << "Visited: " << visited.size()  << std::endl;
	potential_obstacles = visited;
	potential_obstacles.erase({x,y});
	for (const auto& p : potential_obstacles)
	{
		std::vector<std::string> temp_grid = grid;
		std::set<std::tuple<int,int,int>> states = {};
		temp_grid[p.second][p.first] = '#';
		int obstacle = pathing_obstacles(x, y, temp_grid, 0, states);
		if (obstacle == 1)
		{
			n_obstacles++;
			std::cout << "Obstacle at: " << p.first << "," << p.second << std::endl;
		}
	}
	std::cout << "Obstacles: " << n_obstacles << std::endl;
	return 0;
}
