#pragma once

#include <cstdio>
#define _WIN32_WINNT 0x600

#include <sstream>
#include <winerror.h>
#include <dxgi.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dxgi1_5.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <stdexcept>
#include <libloaderapi.h>

//#include "renderdoc_app.h"

// Link necessary D3D libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace CRANN::DX
{
	class DXObject
	{
		private:
			ID3D11Device* _device = nullptr;
			ID3D11DeviceContext* _context = nullptr;
			IDXGIFactory4* _factory = nullptr;


		public:
			DXObject();
			//no dtor for now.

			HRESULT CreateDevice(HMODULE software, UINT flags, UINT featurelvls, UINT SDKVersion, D3D_FEATURE_LEVEL feature_lvl);
			void ReleaseDevice();
			ID3D11Device* GetDevice();
			ID3D11DeviceContext* GetContext();
	};
}

