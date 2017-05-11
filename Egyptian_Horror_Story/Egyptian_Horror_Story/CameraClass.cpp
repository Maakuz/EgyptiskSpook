#include "CameraClass.h"

CameraClass::CameraClass(ID3D11Device* device, GraphicsData* gData, settings::GraphicSettings settings)
{
	this->mVPBuffer = nullptr;
	this->mGraphicsData = gData;
	float fovAngle = static_cast<float>(M_PI) * settings.fov;
	float aspectRatio = (float)settings.width / (float)settings.height;

	this->mPitch = 0;
	this->mYaw = 0;

	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(
		fovAngle, aspectRatio, 0.1f, settings.farPlane);

	projection = DirectX::XMMatrixTranspose(projection);

	this->mPos = DirectX::SimpleMath::Vector3(0, 0, -1);
	this->mForward = DirectX::SimpleMath::Vector3(0, 0, 1);
	this->mUp = DirectX::SimpleMath::Vector3(0, 1, 0);

	//Might be inverted, think not
	this->mRight = DirectX::XMVector3Cross(this->mUp, this->mForward);

	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(this->mPos, this->mForward, this->mUp);
	view = DirectX::XMMatrixTranspose(view);

	this->mMatrices.projection = projection;
	this->mMatrices.view = view;

	this->createVPBuffer(device);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = &this->mPos;

	gData->createConstantBuffer(CAMPOSKEY, sizeof(DirectX::SimpleMath::Vector4), &data, device, true);
}

CameraClass::~CameraClass()
{
	this->mVPBuffer->Release();
}

void CameraClass::createVPBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = sizeof(camera::VP);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

	data.pSysMem = &this->mMatrices;

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->mVPBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, L"Matrix buffer creation failed", L"error", MB_OK);
	}
}

void CameraClass::update(ID3D11DeviceContext* context)
{
	// per frame
	DirectX::SimpleMath::Matrix view =
		DirectX::XMMatrixLookAtLH(this->mPos, this->mPos + this->mForward, this->mUp);
	view = view.Transpose();
	if (mMatrices.view != view) {
		mMatrices.view = view;

		D3D11_MAPPED_SUBRESOURCE data;
		ZeroMemory(&data, sizeof(D3D11_MAPPED_SUBRESOURCE));
		//Update cBuffer
		context->Map(this->mVPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

		memcpy(data.pData, &this->mMatrices, sizeof(camera::VP));

		context->Unmap(this->mVPBuffer, 0);


		context->Map(this->mGraphicsData->getConstantBuffer(CAMPOSKEY), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

		memcpy(data.pData, &this->mPos, sizeof(DirectX::SimpleMath::Vector4));

		context->Unmap(this->mGraphicsData->getConstantBuffer(CAMPOSKEY), 0);
	}
}

void CameraClass::updateRotation(ID3D11DeviceContext* context) {
	// on mouse motion event (max: 1 per frame)
	using namespace DirectX::SimpleMath;

	if (this->mPitch > 75.f)
		this->mPitch = 75.f;

	else if (this->mPitch < -89.f)
		this->mPitch = -89.f;

	Matrix rotation = Matrix::CreateFromYawPitchRoll(mYaw * static_cast<float> (DEGTORADIANS), mPitch * static_cast<float> (DEGTORADIANS), 0);
	mUp = rotation.Up();
	mForward = rotation.Forward();
	mRight = rotation.Right() * -1; //Right gets inverted, better solution exists nice
}

ID3D11Buffer* CameraClass::getMatrixBuffer()
{
	return this->mVPBuffer;
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
