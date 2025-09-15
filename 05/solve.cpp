#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>

int fix_ordering(const std::vector<std::pair<int,int>>& constraints, const std::vector<int>& ordering) {
	std::unordered_set<int> nodes(ordering.begin(), ordering.end());

	std::unordered_map<int, std::vector<int>> graph;
	std::unordered_map<int, int> indegree;

	for (int node : nodes)
		indegree[node] = 0;

	for (auto& [a, b] : constraints) {
		if (nodes.count(a) && nodes.count(b)) {
			graph[a].push_back(b);
			indegree[b]++;
		}
	}

	std::queue<int> q;
	for (auto& [node, deg] : indegree)
		if (deg == 0) q.push(node);

	std::vector<int> result;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		result.push_back(u);

		for (int v : graph[u]) {
			if (--indegree[v] == 0)
				q.push(v);
		}
	}

	return result[result.size() / 2];
}

bool check_ordering(const std::vector<std::pair<int,int>>& constraints, const std::vector<int>& order)
{
	std::unordered_map<int,int> pos;
	for (int i = 0; i < (int)order.size(); i++)
		pos[order[i]] = i;

	for (auto &pair : constraints) {
		if (pos.find(pair.first) == pos.end() || pos.find(pair.second) == pos.end())
			continue;
		if (pos[pair.first] >= pos[pair.second])
			return false;
	}
	return true;
}


int main(int argc, char const *argv[])
{
	std::ifstream constraints_input("constraints.txt", std::ios::in);
	std::ifstream orderings_input("orderings.txt", std::ios::in);
	std::set<int> all_points;
	std::vector<std::pair<int, int>> points;
	std::string line;
	int res1 = 0, res2 = 0;

	while (std::getline(constraints_input, line))
	{
		int x, y;
		char delimiter;
		std::istringstream ss(line);
		while (ss >> x >> delimiter >> y)
		{
			all_points.insert(x);
			all_points.insert(y);
			points.emplace_back(x, y);
		}
	}

	while (std::getline(orderings_input, line))
	{
		std::vector<int> ordering;
		int value;
		char delimiter;
		std::istringstream ss(line);
		while (ss >> value >> delimiter)
		{
			if (all_points.find(value) != all_points.end())
				ordering.push_back(value);
		}
		if (!check_ordering(points, ordering))
			res2 += fix_ordering(points, ordering);
		else
			res1 += ordering[ordering.size() / 2];
	}
	std::cout << "Total Part 1: " << res1 << std::endl;
	std::cout << "Total Part 2: " << res2 << std::endl;
	return 0;
}
