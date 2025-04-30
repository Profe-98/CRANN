#include "DXObject.h"

CRANN::DX::DXObject::DXObject(){}

HRESULT CRANN::DX::DXObject::CreateDevice(HMODULE software, UINT flags, UINT featurelvls, UINT SDKVersion, D3D_FEATURE_LEVEL feature_lvl)
{
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, software, flags, nullptr, featurelvls, SDKVersion, &this->_device, &feature_lvl, &this->_context);
	if (FAILED(hr))
	{
		std::ostringstream oss;
		std::string err_msg = "Creation of DX11 device failed! ErrorCode: ";
		oss << err_msg << hr;
		throw std::runtime_error(oss.str());
	}
}

void CRANN::DX::DXObject::ReleaseDevice()
{
	this->_context->Release();
	this->_device->Release();
}

ID3D11Device* CRANN::DX::DXObject::GetDevice()
{
	return this->_device;
}

ID3D11DeviceContext* CRANN::DX::DXObject::GetContext()
{
	return this->_context;
}
