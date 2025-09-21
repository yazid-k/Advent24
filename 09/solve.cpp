#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

long long check_sum(std::vector<int> input)
{
	long long sum = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] != -1)
			sum += input[i] * i;
	}
	return sum;
}

struct BlockInfo {
	int start;
	int length;
};

std::vector<int> get_block_p2(const std::string &input)
{
	std::vector<int> res;
	std::vector<BlockInfo> blocks;

	int pos = 0;
	for (int i = 0; i < (int)input.size(); i++)
	{
		int len = input[i] - '0';
		if (i % 2 == 0)
		{
			blocks.push_back({pos, len});
			res.insert(res.end(), len, i/2);
		}
		else
			res.insert(res.end(), len, -1);
		pos += len;
	}

	for (int b = (int)blocks.size()-1; b >= 1; b--)
	{
		int id = b;
		int len = blocks[b].length;

		int free_count = 0;
		for (int i = 0; i < blocks[b].start; i++)
		{
			if (res[i] == -1) free_count++;
			else free_count = 0;
			if (free_count == len)
			{
				int start = i - len + 1;
				std::fill(res.begin()+start, res.begin()+start+len, id);
				std::fill(res.begin()+blocks[b].start, res.begin()+blocks[b].start+len, -1);
				break;
			}
		}
	}

	return res;
}


std::vector<int> get_block(std::string input)
{
	std::vector<int> res;
	for (int i = 0; i < input.size(); i++)
		res.insert(res.end(), input[i] - 48, i%2 ? -1 : i / 2);
	for (size_t i = 0; i < res.size(); i++)
	{
		while (res[res.size() - 1] == -1)
			res.pop_back();
		if (res[i] == -1)
		{
			res[i] = res[res.size() - 1];
			res.pop_back();
		}
	}
	return res;
}

int main(int argc, char const *argv[])
{
	std::ifstream in("input.txt");
	std::string line;
	std::getline(in, line);
	in.close();
	std::cout << check_sum(get_block(line)) << std::endl;
	std::cout << check_sum(get_block_p2(line)) << std::endl;
	return 0;
}
