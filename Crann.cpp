#include <cstdio>

#include <iostream>
#include "DXObject.h"

using namespace CRANN::DX;


void PrintFeatureLvl(D3D_FEATURE_LEVEL lvl);

int main()
{
	DXObject DXO = DXObject();
	DXO.CreateDevice(0, D3D11_CREATE_DEVICE_DEBUG, 0, D3D11_SDK_VERSION, D3D_FEATURE_LEVEL_11_0);

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
