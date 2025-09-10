#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> line_to_int_vector(const std::string &line)
{
	std::vector<int> result;
	size_t pos = 0;
	size_t found;
	while ((found = line.find(' ', pos)) != std::string::npos)
	{
		result.push_back(std::stoi(line.substr(pos, found - pos)));
		pos = found + 1;
	}
	if (pos < line.size())
		result.push_back(std::stoi(line.substr(pos)));
	return result;
}

std::vector<int> remove_at_index(const std::vector<int> &numbers, size_t index)
{
	std::vector<int> result;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (i != index)
			result.push_back(numbers[i]);
	}
	return result;
}

bool line_is_valid(const std::vector<int> &numbers, bool is_second_attempt = false)
{
	bool is_decreasing = numbers[0] > numbers[1];
	for (size_t i = 0; i < numbers.size() - 1; i++)
	{
		bool check_decreasing = numbers[i] > numbers[i + 1];
		int diff = abs(numbers[i] - numbers[i + 1]);
		if (diff > 3 || check_decreasing != is_decreasing || diff == 0)
		{
			if (is_second_attempt)
				return false;
			std::vector<int> v1 = remove_at_index(numbers, i);
			std::vector<int> v2 = remove_at_index(numbers, i + 1);

			return line_is_valid(v1, true) || line_is_valid(v2, true) || line_is_valid(remove_at_index(numbers, 0), true);
		}
	}
	return true;
}


int main(int argc, char const *argv[])
{
	std::ifstream		data;
	std::string			line;
	std::vector<std::string>	levels;
	size_t				line_number = 0;
	int					not_safe = 0;
	data.open("reports.txt", std::ios::in);
	while (std::getline(data, line))
	{
		line_number++;
		std::vector<int> numbers = line_to_int_vector(line);
		if (!line_is_valid(numbers))
			not_safe++;
	}
	std::cout << "Number of safe reports: " << (line_number - not_safe) << std::endl;
	data.close();
	return 0;
}
