#include <iostream>
#include <vector>
#include <fstream>

int mul(std::string s)
{
	size_t commaPos = s.find(',');
	size_t closeParenPos = s.find(')');
	if (commaPos == std::string::npos || closeParenPos == std::string::npos)
		return 0;
	std::string firstNumStr = s.substr(0, commaPos);
	std::string secondNumStr = s.substr(commaPos + 1, s.find(')') - (commaPos + 1));
	if (firstNumStr.empty() || secondNumStr.empty() || firstNumStr.size() > 3 || secondNumStr.size() > 3)
			return 0;
	return std::stoi(firstNumStr) * std::stoi(secondNumStr);
}

int main(int argc, char const *argv[])
{
	std::ifstream data;
	std::string line;
	std::string all_lines;
	std::vector<size_t> do_positions;
	std::vector<size_t> dont_positions;
	int res = 0;

	data.open("input.txt", std::ios::in);
	while (data.is_open() && data.peek() != EOF)
		all_lines += (char)data.get();
	data.close();
	size_t pos = std::min(all_lines.find("do()"), all_lines.find("don't()"));
	while (pos != std::string::npos)
	{
		if (all_lines.substr(pos, 4) == "do()")
			do_positions.push_back(pos);
		else
			dont_positions.push_back(pos);
		pos = std::min(all_lines.find("do()", pos + 1), all_lines.find("don't()", pos + 1));
	}
	for (int i = 0; i < all_lines.size(); i++)
	{
		size_t index = all_lines.find("mul(", i);
		if (index != std::string::npos)
		{
			int latest_do = all_lines.rfind("do()", index);
			int latest_dont = all_lines.rfind("don't()", index);
			if (latest_dont == -1 || (latest_do > latest_dont))
				res += mul(all_lines.substr(index + 4, 8));
			i = index + 3;
		}
	}

	std::cout << "Total: " << res << std::endl;
	return 0;
}
