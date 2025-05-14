#include "DataHandler.h"

namespace CRANN::DATA
{
    std::string DataHandler::ReadNecessaryDataFromCSV(std::string csvlocation)
    {
        std::ostringstream oss;
        std::string line; 
        std::ifstream csvfile(csvlocation);

        if(!csvfile.is_open())
            throw std::invalid_argument("The specified file doesn't exist(at the given location)!\n");
       
        while (std::getline(csvfile, line)) { oss << line << "\n"; }

        return oss.str();
    }

    std::vector<std::vector<std::string>> DataHandler::GetData(std::string file, std::vector<int> importantcols)
    {
        std::string data = ReadNecessaryDataFromCSV(file);

        if (data.empty())
            throw std::runtime_error("No data available!\n");

        std::regex delimeter_dpoints("\n");
        std::vector<std::string> dpoints
        {
            std::sregex_token_iterator(data.begin(), data.end(), delimeter_dpoints, -1),
                std::sregex_token_iterator()
        };

        std::vector<std::vector<std::string>> datatable; // the final data as 2D-vector filled with strings
        
        int colcount = importantcols.size();
        for (std::string dpoint : dpoints)
        {
            std::regex delimeter_features(",");
            std::vector<std::string> features
            {
                std::sregex_token_iterator(dpoint.begin(), dpoint.end(), delimeter_features, -1),
                    std::sregex_token_iterator()
            };


            if (colcount == 0)
                datatable.emplace_back(features);

            std::vector<std::string> importantfeatures(colcount);
            for (int i = 0; i < colcount; ++i)
                importantfeatures[i] = features[importantcols[i]];

            datatable.emplace_back(importantfeatures);
        }

        return datatable;
    }

    std::pair<std::vector<double>, std::vector<double>> DataHandler::CreateTargetSets(std::vector<std::vector<std::string>> datapoints, std::vector<std::string> targetkeywords, int targetcol = 0, int testinterval = 10)
    {
        if (datapoints.empty())
            throw std::invalid_argument("No Data available!(Targets)\n");



        int setsize = datapoints.size();
        std::vector<std::string> all_targets(setsize);
        std::vector<double> targetsettraining;
        std::vector<double> targetsettest;
        
        if (targetkeywords.empty())
        {
            for (int i = 0; i < setsize; ++i)
            {
                if (i % testinterval - 1 == 0)
                    targetsettest.emplace_back(i);
                else
                    targetsettraining.emplace_back(i);
            }
            return std::make_pair(targetsettraining, targetsettest);
        }

        std::vector<double> tmptargetcontainer;

        double label = 0.0;
        for (std::string keyword : targetkeywords)
        {
            for (std::vector<std::string> dpoint : datapoints)
            {
                if (dpoint[targetcol].find(keyword) != std::string::npos)
                    tmptargetcontainer.emplace_back(label); //std::cout << dpoint[targetcol] << "\n"; //
            }
            label += 1;
        }

        size_t size_tmptargetcontainer = tmptargetcontainer.size();

        for (size_t i = 0; i < size_tmptargetcontainer; ++i)
        {
            if (i % testinterval - 1 == 0)
                targetsettest.emplace_back(tmptargetcontainer[i]);
            else
                targetsettraining.emplace_back(tmptargetcontainer[i]);
        }
        return std::make_pair(targetsettraining, targetsettest);
    }

    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> DataHandler::CreateFeatureSets(std::vector<std::vector<std::string>> datapoints, std::vector<std::string> targetkeywords, int targetcol, std::vector<int> featurecols, int testinterval)
    {
        if (datapoints.empty() || datapoints[0].empty())
            throw std::invalid_argument("No data available!(Features)\n");

        std::vector<std::vector<double>> featurestraining;
        std::vector<std::vector<double>> featurestest;

        std::vector<std::vector<double>> tmpfeatures;

        for (std::string keyword : targetkeywords)
        {
            for (std::vector<std::string> dpoint : datapoints)
            {
                std::vector<double> featuresofdpoint;
                if (dpoint[targetcol].find(keyword.c_str()) != std::string::npos)
                {
                    for (int columnindex : featurecols)
                    {
                        featuresofdpoint.emplace_back(std::atof(dpoint[columnindex].c_str()));
                    }
                    tmpfeatures.emplace_back(featuresofdpoint);
                }
            }
        }

        std::size_t tmpfeaturessize = tmpfeatures.size();

        for (std::size_t i = 0; i < tmpfeaturessize; ++i)
        {
            if (i % testinterval - 1 == 0)
                featurestest.emplace_back(tmpfeatures[i]);
            else
                featurestraining.emplace_back(tmpfeatures[i]);
        }

        return std::make_pair(featurestraining, featurestest);
    }
}


