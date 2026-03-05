#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>

class StatisticsCollector {
private:
	std::map<std::string, std::vector<double>> data;
public:
	void addData(const std::string& category, double value)
	{
		if (value > 100.0)
			std::cout << "warning: too big value in " << category << "\n";
		else
			data[category].push_back(value);
	}

	double getAverage(const std::string& category) const
	{
		auto it = data.find(category);

		if (it == data.end() || it->second.empty())
			return 0.0;

		double sum = std::accumulate(it->second.begin(), it->second.end(), 0.0);

		return sum / it->second.size();
	}

	double getMax(const std::string& category) const
	{
		auto it = data.find(category);

		if (it == data.end() || it->second.empty())
			return 0.0;

		return *std::max_element(it->second.begin(), it->second.end());
	}

	void SaveToFile(const std::string& filename) const
	{
		std::ofstream file(filename);
		for (const auto& it : data)
		{
			file << it.first;
			for (double val : it.second)
				file << "," << val;

			file << "\n";
		}
	}
};

int main()
{

	return 0;
}
