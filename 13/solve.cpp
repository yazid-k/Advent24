#include <iostream>
#include <fstream>
struct Equation
{
	long long a, b, c;
};
struct System
{
	Equation eq1, eq2;
};

long long solve_system(const System& system, bool p2 = false)
{
	long long a1 = system.eq1.a, b1 = system.eq1.b, c1 = system.eq1.c;
	long long a2 = system.eq2.a, b2 = system.eq2.b, c2 = system.eq2.c;
	long long det = a1 * b2 - a2 * b1;
	if (det == 0) return 0;
	if ((c1 * b2 - c2 * b1) % det != 0) return 0;
	if ((a1 * c2 - a2 * c1) % det != 0) return 0;
	long long x, y;
	x = (c1 * b2 - c2 * b1) / det;
	y = (a1 * c2 - a2 * c1) / det;
	if ((x >= 100 || y >= 100 || x < 0 || y < 0) && !p2) return 0;
	return x * 3 + y;
}

int main(int argc, char const *argv[])
{
	std::ifstream infile("input.txt");
	std::string line;
	long long res1 = 0, res2 = 0;
	while (std::getline(infile, line))
	{
		System system;
		sscanf(line.c_str(), "Button A: X+%lld, Y+%lld", &system.eq1.a, &system.eq2.a);
		std::getline(infile, line);
		sscanf(line.c_str(), "Button B: X+%lld, Y+%lld", &system.eq1.b, &system.eq2.b);
		std::getline(infile, line);
		sscanf(line.c_str(), "Prize: X=%lld, Y=%lld", &system.eq1.c, &system.eq2.c);
		std::getline(infile, line);
		res1 += solve_system(system);
		system.eq1.c += 10000000000000;
		system.eq2.c += 10000000000000;
		res2 += solve_system(system, true);
	}
	std::cout << "Total prize 1: " << res1 << "\n";
	std::cout << "Total prize 2: " << res2 << "\n";
	return 0;
}
