#include <iostream>
#include <fstream>
#include <sstream>

long long num_digits(long long n)
{
	if (n > 0)
		return 1 + num_digits(n / 10);
	return 0;
}

std::vector<long long> blink(const std::vector<long long>& numbers)
{
	std::vector<long long> result;
	for (const auto& n : numbers)
	{
		long long digits = num_digits(n);
		if (n == 0)
			result.push_back(1);
		else if (digits % 2 == 0)
		{
			result.push_back(n % static_cast<long long>(std::pow(10, digits / 2)));
			result.push_back(n / static_cast<long long>(std::pow(10, digits / 2)));
		}
		else
			result.push_back(n * 2024);
	}
	return result;
}

std::unordered_map<long long, long long> blink_p2(const std::unordered_map<long long, long long>& numbers)
{
	std::unordered_map<long long, long long> result;
	for (const auto& [n, count] : numbers)
	{
		long long digits = num_digits(n);
		if (n == 0)
			result[1] += count;
		else if (digits % 2 == 0)
		{
			long long power = std::pow(10, digits / 2);
			long long right = n % power;
			long long left = n / power;
			result[right] += count;
			result[left] += count;
		}
		else
			result[n * 2024] += count;
	}
	return result;
}

int main(int argc, char const *argv[])
{
	std::vector<long long> numbers;
	std::unordered_map<long long, long long> number_counts;
	std::ifstream input("input.txt");
	std::string line;
	std::getline(input, line);
	std::istringstream iss(line);
	long long num;
	while (iss >> num)
	{
		numbers.push_back(num);
		number_counts[num]++;
	}
	for (long long i = 0; i < 25; i++)
	{
		numbers = blink(numbers);
		std::cout << "After " << i + 1 << " iterations: ";
		std::cout << numbers.size() << " numbers part 1" << std::endl;
	}
	for (long long i = 0; i < 75; i++)
	{
		number_counts = blink_p2(number_counts);
		long long total = 0;
		for (const auto& [n, count] : number_counts)
			total += count;
		std::cout << "After " << i + 1 << " iterations: ";
		std::cout << total << " numbers part 2" << std::endl;
	}
	return 0;
}
