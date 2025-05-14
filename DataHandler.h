#pragma once

#include <sys/stat.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>


namespace CRANN::DATA
{

	class DataHandler
	{
	private:
		static std::string ReadNecessaryDataFromCSV(std::string csvlocation);
	public:
		static std::vector<std::vector<std::string>> GetData(std::string file, std::vector<int> importantcols);
		static std::pair<std::vector<double>, std::vector<double>> CreateTargetSets(std::vector<std::vector<std::string>> datapoints, std::vector<std::string> targetkeywords, int targetcol, int testinterval);
		static std::pair< std::vector<std::vector<double>>, std::vector<std::vector<double>>> CreateFeatureSets(std::vector<std::vector<std::string>> datapoints, std::vector<std::string> targetkeywords, int targetcol, std::vector<int> featurecols, int testinterval = 10);
	};

}
