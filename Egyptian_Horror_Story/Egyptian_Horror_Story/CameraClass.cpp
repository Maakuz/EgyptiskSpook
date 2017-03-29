#include "CameraClass.h"

CameraClass::CameraClass(ID3D11Device* device, float width, float height)
{
	this->WVPBuffer = nullptr;

	float fovAngle = M_PI * 0.45;
	float aspectRatio = width / height;

	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(fovAngle, aspectRatio, 0.1f, 50.f);
	projection = DirectX::XMMatrixTranspose(projection);

	this->mPos = DirectX::SimpleMath::Vector3(0, 0, -1);
	this->mForward = DirectX::SimpleMath::Vector3(0, 0, 0);
	this->mUp = DirectX::SimpleMath::Vector3(0, 1, 0);

	//Might be inverted, think not
	this->mRight = DirectX::XMVector3Cross(this->mForward, this->mUp);

	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(this->mPos, this->mForward, this->mUp);
	view = DirectX::XMMatrixTranspose(view);

	this->matrices.projection = projection;
	this->matrices.world = DirectX::XMMatrixIdentity();
	this->matrices.view = view;

	this->createVWPBuffer(device);
}

CameraClass::~CameraClass()
{
	this->WVPBuffer->Release();
}

void CameraClass::createVWPBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = sizeof(WVP);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

	data.pSysMem = &this->matrices;

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->WVPBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, L"Matrix buffer creation failed", L"error", MB_OK);
	}
}

ID3D11Buffer* CameraClass::getMatrixBuffer()
{
	return this->WVPBuffer;
}
