#pragma once

#include "Direct3DHeader.h"

#include "SimpleMath.h"

class Capsule;

class AABB {
public:
	DirectX::SimpleMath::Vector3 mPoint;
	DirectX::SimpleMath::Vector3 mScale;
public:
	AABB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 scale);
	AABB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 x, DirectX::SimpleMath::Vector3 y, DirectX::SimpleMath::Vector3 z);
	DirectX::SimpleMath::Vector3 calculateNormal(Capsule& other);
	bool aabbVSCapsule(Capsule& other);
	bool aabbVSPoint(DirectX::SimpleMath::Vector3 point);
	void setPosition(DirectX::SimpleMath::Vector3 point);
};

class OBB {
private:
	void UpdateMatrix();
public:
	//DirectX::SimpleMath::Vector3 mPoint;
	//DirectX::SimpleMath::Vector3 mLengthU;
	//DirectX::SimpleMath::Vector3 mLengthV;
	//DirectX::SimpleMath::Vector3 mLengthW;
	//DirectX::SimpleMath::Vector3 mU;
	//DirectX::SimpleMath::Vector3 mV;
	//DirectX::SimpleMath::Vector3 mW;

	//TA BORT OVAN

	DirectX::SimpleMath::Vector3 mPoint;
	DirectX::SimpleMath::Vector3 mDir;
	DirectX::SimpleMath::Vector3 mUp;
	DirectX::SimpleMath::Vector3 mScale;
	
	DirectX::SimpleMath::Matrix mInvWorld;

public:
	OBB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale);
	virtual ~OBB();

	DirectX::SimpleMath::Vector3 getNormal(Capsule& other);
	bool obbVSPoint(DirectX::SimpleMath::Vector3 point);
	bool obbVsObb(OBB& other);
	bool obbVSCapsule(const Capsule &other);
	void setPos(DirectX::SimpleMath::Vector3 point);
	void setDir(DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up);
	void setScale(DirectX::SimpleMath::Vector3 scale);

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
	bool capsuleVSObb(OBB &other);
	bool capsuleVSCapsule();

};