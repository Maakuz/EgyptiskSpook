#pragma once

#include "Direct3DHeader.h"

#include "SimpleMath.h"

class Capsule;

class OBB {
public:
	DirectX::SimpleMath::Vector3 mPoint;
	DirectX::SimpleMath::Vector3 mLengthU;
	DirectX::SimpleMath::Vector3 mLengthV;
	DirectX::SimpleMath::Vector3 mLengthW;
	DirectX::SimpleMath::Vector3 mU;
	DirectX::SimpleMath::Vector3 mV;
	DirectX::SimpleMath::Vector3 mW;

public:
	OBB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 lengthU, DirectX::SimpleMath::Vector3 lengthV, DirectX::SimpleMath::Vector3 lengthW);
	virtual ~OBB();


	bool obbVSPoint(DirectX::SimpleMath::Vector3 point);
	bool obbVsObb(const OBB& other);
	bool obbVSCylinder(const Capsule &other);

};

class Capsule {
private:
	DirectX::SimpleMath::Vector3 calculateNormal(OBB other);
public:
	DirectX::SimpleMath::Vector3 mPoint;
	float mRadius;
	float mHeight;
public:
	Capsule(DirectX::SimpleMath::Vector3 point, float height, float radius);
	virtual ~Capsule();

	bool capsuleVSPoint(DirectX::SimpleMath::Vector3 point);
	DirectX::SimpleMath::Vector3 capsuleVSObb(OBB &other);
	bool capsuleVSCCapsule();

};