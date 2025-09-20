#include <iostream>
#include <fstream>
#include <vector>
#include <string>

long long concat(long long a, long long b)
{
	long long pow10 = 1;
	long long tmp = b;
	while (tmp > 0)
	{
		pow10 *= 10;
		tmp /= 10;
	}
	return a * pow10 + b;
}

bool canCompute(const std::vector<long long>& nums, int index, long long current, long long target)
{
	if (index == nums.size())
		return current == target;
	long long next = nums[index];
	if (canCompute(nums, index + 1, current + next, target)) return true;
	if (canCompute(nums, index + 1, current * next, target)) return true;
	if (canCompute(nums, index + 1, concat(current, next), target)) return true;
	return false;
}

long long check_operation(const std::string& operation)
{
	size_t sep = operation.find(':');
	long long target = std::stoll(operation.substr(0, sep));

	std::vector<long long> nums;
	size_t start = sep + 2;
	size_t end;
	while ((end = operation.find(' ', start)) != std::string::npos)
	{
		nums.push_back(std::stoll(operation.substr(start, end - start)));
		start = end + 1;
	}
	nums.push_back(std::stoll(operation.substr(start)));

	if (canCompute(nums, 1, nums[0], target))
		return target;
	return 0;
}

int main() {
	std::ifstream input("input.txt");
	std::string line;
	long long res = 0;

	while (std::getline(input, line))
		res += check_operation(line);

	std::cout << "Total: " << res << std::endl;
	return 0;
}
