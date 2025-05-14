#include <cstdio>
#include <vector>
#include <utility>
#include <iostream>
#include "DXObject.h"
#include "DataHandler.h"

using namespace CRANN::DX;
using namespace CRANN::DATA;

void PrintFeatureLvl(D3D_FEATURE_LEVEL lvl);

int main()
{
	DXObject DXO = DXObject();
	DXO.CreateDevice(0, D3D11_CREATE_DEVICE_DEBUG, 0, D3D11_SDK_VERSION, D3D_FEATURE_LEVEL_11_0);

	try
	{
		std::vector<std::vector<std::string>> dataraw = DataHandler::GetData("./DataSets/color-names-master/output/colors.csv", { 0, 3, 4, 5 });
		
		/*/for (std::vector<std::string> dpoint : dataraw)
		{
			for (std::string trgtorfeature : dpoint)
				std::cout << trgtorfeature << ", ";
			std::cout << "\n";
		}/**/
		
		std::vector<std::string> targetkeyvalues = { "red", "green", "blue" };
		std::pair<std::vector<double>, std::vector<double>> targets = DataHandler::CreateTargetSets(dataraw, targetkeyvalues, 0, 4);
		std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> features = DataHandler::CreateFeatureSets(dataraw, targetkeyvalues, 0, { 1, 2, 3 }, 4);
		
		std::cout << targets.first.size() <<  " : " << features.first.size() << "\n";
		std::cout << targets.second.size() << " : " << features.second.size() << "\n";
		
		//for (double t : targets.second)
		//	std::cout << t << "\n";

		/*
		for (std::vector<double> dpoint : features.first)
		{
			for (double feature : dpoint)
				std::cout << feature << ", ";
			std::cout << "\n";
		}*/
	}
	catch (const std::exception& e)
	{
		printf(e.what());
	}
	return 0;
}

void PrintFeatureLvl(D3D_FEATURE_LEVEL lvl)
{
	switch (lvl)
	{
	case D3D_FEATURE_LEVEL_11_0:
		printf("The Device has FEATURE_LEVEL_11_0");
		break;
	case D3D_FEATURE_LEVEL_11_1:
		printf("The Device has FEATURE_LEVEL_11_1");
		break;
	case D3D_FEATURE_LEVEL_12_0:
		printf("The Device has FEATURE_LEVEL_12_0");
		break;
	case D3D_FEATURE_LEVEL_12_1:
		printf("The Device has FEATURE_LEVEL_12_1");
		break;
	case D3D_FEATURE_LEVEL_12_2:
		printf("The Device has FEATURE_LEVEL_12_2");
		break;
	}
}
