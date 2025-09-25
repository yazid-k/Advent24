#include <iostream>
#include <fstream>
#include <set>

void display_positions(const std::vector<std::vector<int>> &points, int rows = 7, int cols = 11)
{
	std::vector<std::string> grid(rows, std::string(cols, '.'));
	for (const auto &p : points)
		grid[p[1]][p[0]] = '#';
	for (const auto &row : grid)
		std::cout << row << std::endl;

}

int safety_factor(std::vector<std::vector<int>> &points, int rows, int cols)
{
	int first_quadrant = 0, second_quadrant = 0, third_quadrant = 0, fourth_quadrant = 0;
	for (const auto &p : points)
	{
		if (p[0] == cols / 2 || p[1] == rows / 2)
			continue;
		if (p[0] < cols / 2 && p[1] < rows / 2)
			first_quadrant++;
		else if (p[0] >= cols / 2 && p[1] < rows / 2)
			second_quadrant++;
		else if (p[0] < cols / 2 && p[1] >= rows / 2)
			third_quadrant++;
		else
			fourth_quadrant++;
	}
	return first_quadrant * second_quadrant * third_quadrant * fourth_quadrant;
}

void move(std::vector<std::vector<int>> &points, int rows, int cols, int n_steps)
{
	for (auto &p : points)
	{
		p[0] = (p[0] + p[2] * n_steps) % cols;
		p[1] = (p[1] + p[3] * n_steps) % rows;
		if (p[0] < 0)
			p[0] += cols;
		if (p[1] < 0)
			p[1] += rows;
	}
}

int main(int argc, char const *argv[])
{
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::vector<int>> points;
	while (std::getline(input, line))
	{
		int px, py, vx, vy;
		std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
		points.push_back({px, py, vx, vy});
	}
	std::vector<std::vector<int>> points_p2 = points;
	move(points, 103, 101, 100);
	display_positions(points, 103, 101);
	std::cout << safety_factor(points, 103, 101) << std::endl;
	//PART 2

	for (int i = 0; i < 10000; i++)
	{
		std::cout << "After " << i << " steps:" << std::endl;
		display_positions(points_p2, 103, 101);
		move(points_p2, 103, 101, 1);
	}
	return 0;
}
