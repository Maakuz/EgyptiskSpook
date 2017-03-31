#include "CameraClass.h"

CameraClass::CameraClass(ID3D11Device* device, float width, float height)
{
	this->WVPBuffer = nullptr;

	float fovAngle = M_PI * 0.45;
	float aspectRatio = width / height;

	this->mPitch = 0;
	this->mYaw = 0;

	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(fovAngle, aspectRatio, 0.1f, 50.f);
	projection = DirectX::XMMatrixTranspose(projection);

	this->mPos = DirectX::SimpleMath::Vector3(0, 0, -1);
	this->mForward = DirectX::SimpleMath::Vector3(0, 0, 1);
	this->mUp = DirectX::SimpleMath::Vector3(0, 1, 0);

	//Might be inverted, think not
	this->mRight = DirectX::XMVector3Cross(this->mUp, this->mForward);

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

void CameraClass::update(ID3D11DeviceContext* context)
{
	if (this->mPitch > 75.f)
		this->mPitch = 75.f;

	else if (this->mPitch < -89.f)
		this->mPitch = -89.f;

	this->mForward.x = sin(this->mYaw * DEGTORADIANS) * cos(this->mPitch * DEGTORADIANS);
	this->mForward.y = (sin(this->mPitch * DEGTORADIANS));
	this->mForward.z = cos(this->mYaw * DEGTORADIANS) * cos(this->mPitch * DEGTORADIANS);

	this->mForward.Normalize();


	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(this->mPos, this->mPos + this->mForward, this->mUp);
	view = DirectX::XMMatrixTranspose(view);

	this->matrices.view = view;

	D3D11_MAPPED_SUBRESOURCE data;
	ZeroMemory(&data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//Update cBuffer
	context->Map(this->WVPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &this->matrices, sizeof(WVP));

	context->Unmap(this->WVPBuffer, 0);


}

ID3D11Buffer* CameraClass::getMatrixBuffer()
{
	return this->WVPBuffer;
}

DirectX::SimpleMath::Vector3 CameraClass::getPos() const
{
	return this->mPos;
}

DirectX::SimpleMath::Vector3 CameraClass::getForward() const
{
	return this->mForward;
}

DirectX::SimpleMath::Vector3 CameraClass::getUp() const
{
	return this->mUp;
}

DirectX::SimpleMath::Vector3 CameraClass::getRight() const
{
	return this->mRight;
}

float CameraClass::getYaw() const
{
	return this->mYaw;
}

float CameraClass::getPitch() const
{
	return this->mPitch;
}

void CameraClass::setPos(DirectX::SimpleMath::Vector3 pos)
{
	this->mPos = pos;
}

void CameraClass::setForward(DirectX::SimpleMath::Vector3 forward)
{
	this->mForward = forward;
}

void CameraClass::setUp(DirectX::SimpleMath::Vector3 up)
{
	this->mUp = up;
}

void CameraClass::setRight(DirectX::SimpleMath::Vector3 right)
{
	this->mRight = right;
}

void CameraClass::setYaw(float yaw)
{
	this->mYaw = yaw;
}

void CameraClass::setPitch(float pitch)
{
	this->mPitch = pitch;
}
