#include "Light.h"

Light::Light(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 direction, ID3D11Device* device, ID3D11DeviceContext* context, GraphicsData* gData)
{
	this->mLightInfo.pos = DirectX::SimpleMath::Vector4(pos.x, pos.y, pos.z, 1);
	this->mLightInfo.dir = DirectX::SimpleMath::Vector4(direction.x, direction.y, direction.z, 1);
	this->mLightInfo.flashlightOn = false;

	this->mLightFOV = M_PI * 0.5f;

	this->mMatrices.view = DirectX::XMMatrixLookToLH(pos, direction, DirectX::SimpleMath::Vector3(0, 1, 0));

	this->mMatrices.projection = DirectX::XMMatrixPerspectiveFovLH(mLightFOV, 1, 0.1f, 200);
	this->mMatrices.projection = this->mMatrices.projection.Transpose();

	this->mLightGraphicsKey = 299;
	this->mLightBufferKey = 300;
	this->mMatrixBufferKey = 301;

	this->mGData = gData;
	this->mContext = context;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = &this->mMatrices;

	gData->createConstantBuffer(this->mMatrixBufferKey, sizeof(lightStructs::VP), &data, device, true);


	data.pSysMem = &this->mLightInfo;
	gData->createConstantBuffer(this->mLightBufferKey, sizeof(lightStructs::lightInfo), &data, device, true);
}

Light::~Light()
{
}

void Light::update(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 offset, DirectX::SimpleMath::Vector3 dir)
{
	using namespace DirectX::SimpleMath;

	//Needs to be a little in front of the model
	Vector3 newPos(pos + offset + (dir * 1.25f));

	this->mLightInfo.pos = Vector4(newPos.x, newPos.y, newPos.z, 1);
	this->mLightInfo.dir = Vector4(dir.x, dir.y, dir.z, 1);

	this->mMatrices.view = DirectX::XMMatrixLookToLH(this->mLightInfo.pos, this->mLightInfo.dir, Vector3(0, 1, 0));
	this->mMatrices.view = this->mMatrices.view.Transpose();

	D3D11_MAPPED_SUBRESOURCE data;

	this->mContext->Map(this->mGData->getConstantBuffer(this->mLightBufferKey), 
		0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &this->mLightInfo, sizeof(lightStructs::lightInfo));

	this->mContext->Unmap(this->mGData->getConstantBuffer(this->mLightBufferKey), 0);


	//Matrices
	this->mContext->Map(this->mGData->getConstantBuffer(this->mMatrixBufferKey),
		0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &this->mMatrices, sizeof(lightStructs::VP));

	this->mContext->Unmap(this->mGData->getConstantBuffer(this->mMatrixBufferKey), 0);


	//Transform matrix //THE 1.5 TIMES OFFSET IS A TEMPORARY FIX AND MAY GET TWEAKED
	Matrix transform = Matrix::CreateTranslation(pos + dir + offset);
	transform = transform.Transpose();

	Vector3 d = dir;
	d.Normalize();

	float pitch = asin(-d.y) + (M_PI / 2);

	float yaw = atan2(d.x, d.z);

	Matrix rotation = Matrix::CreateFromYawPitchRoll(yaw, pitch, 0);
	rotation = rotation.Transpose();

	transform *= rotation;


	this->mContext->Map(this->mGData->getConstantBuffer(this->mLightGraphicsKey),
		0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &transform, sizeof(DirectX::XMMATRIX));

	this->mContext->Unmap(this->mGData->getConstantBuffer(this->mLightGraphicsKey), 0);
}

int Light::getGraphicsKey() const
{
	return this->mLightGraphicsKey;
}

void Light::toggleFlashLight(bool onOrOff)
{
	this->mLightInfo.flashlightOn = onOrOff;
}

bool Light::getLightOn() const
{
	return this->mLightInfo.flashlightOn;
}
