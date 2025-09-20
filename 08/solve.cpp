#include <iostream>
#include <fstream>
#include <map>
#include <set>

bool is_valid_position(const std::pair<int, int>& pos, int max_row, int max_col)
{
	return pos.first >= 0 && pos.first < max_row && pos.second >= 0 && pos.second < max_col;
}

std::pair<std::pair<int, int>, std::pair<int, int>> get_antinodes(
	const std::pair<int, int>& p1, const std::pair<int, int>& p2)
{
	int dx = p2.first - p1.first;
	int dy = p2.second - p1.second;

	std::pair<int, int> antinode1 = { p1.first - dx, p1.second - dy };
	std::pair<int, int> antinode2 = { p2.first + dx, p2.second + dy };

	return { antinode1, antinode2 };
}

std::set<std::pair<int, int>> get_all_antinodes_in_line(
	const std::pair<int, int>& p1, const std::pair<int, int>& p2, int max_row, int max_col)
{
	std::set<std::pair<int, int>> antinodes;
	int dx = p2.first - p1.first;
	int dy = p2.second - p1.second;

	std::pair<int, int> current1 = { p1.first - dx, p1.second - dy };
	std::pair<int, int> current2 = { p2.first + dx, p2.second + dy };

	while (is_valid_position(current1, max_row, max_col))
	{
		antinodes.insert(current1);
		current1.first -= dx;
		current1.second -= dy;
	}
	while (is_valid_position(current2, max_row, max_col))
	{
		antinodes.insert(current2);
		current2.first += dx;
		current2.second += dy;
	}
	return antinodes;
}

int main(int argc, char const *argv[])
{
	std::ifstream input("input.txt");
	std::string line;
	std::map<char, std::vector<std::pair<int, int>>> positions;
	std::set<std::pair<int, int>> antinodes_part1, antinodes_part2;
	std::vector<std::string> lines;
	size_t total_positions = 0;

	while (std::getline(input, line))
		lines.push_back(line);
	for (int i = 0; i < lines.size(); i++)
		for (int j = 0; j < lines[i].size(); j++)
			if (lines[i][j] != '.')
			{
				positions[lines[i][j]].emplace_back(i, j);
				antinodes_part2.insert({ i, j });
			}

	for (const auto& p : positions)
	{
		const auto& vec = p.second;
		std::cout << std::endl;

		for (int i = 0; i < vec.size(); i++)
			for (int j = i + 1; j < vec.size(); j++)
			{
				auto res = get_antinodes(vec[i], vec[j]);
				if (is_valid_position(res.first, lines.size(), lines[0].size()))
					antinodes_part1.insert(res.first);
				if (is_valid_position(res.second, lines.size(), lines[0].size()))
					antinodes_part1.insert(res.second);
				auto all_antinodes = get_all_antinodes_in_line(vec[i], vec[j], lines.size(), lines[0].size());
				antinodes_part2.insert(all_antinodes.begin(), all_antinodes.end());
			}
	}
	std::cout << "Number of antinodes_part1: " << antinodes_part1.size() << std::endl;
	std::cout << "Number of antinodes_part2: " << antinodes_part2.size() << std::endl;
	return 0;
}
