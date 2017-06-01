#include "Colliders.h"

void OBB::UpdateMatrix() {
	mInvWorld = mInvWorld.CreateWorld(this->mPoint, this->mDir, this->mUp);
	mInvWorld = mInvWorld.Invert();
}

OBB::OBB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale) {
	this->mPoint = point;
	this->mDir = dir;
	this->mUp = up;
	this->mScale = scale;

	this->UpdateMatrix();
	
}

OBB::~OBB() {
}

DirectX::SimpleMath::Vector3 OBB::getNormal(Capsule & other) {

	DirectX::SimpleMath::Vector3 tmp = DirectX::SimpleMath::Vector3(other.mPoint.x, other.mPoint.y + (other.mHeight / 2), other.mPoint.z);

	DirectX::SimpleMath::Vector3 btoc = tmp - this->mPoint;

	btoc = DirectX::SimpleMath::Vector3::Transform(btoc, mInvWorld);
	

	DirectX::SimpleMath::Matrix scale;
	scale = scale.CreateScale(this->mScale);
	scale = scale.Invert();

	//btoc = DirectX::SimpleMath::Vector3::Transform(btoc, scale);

	DirectX::SimpleMath::Vector3 res = { btoc.x, 0, 0 };
	float size = mScale.x;
	if (abs(btoc.y) > abs(res.x)) {
		res = DirectX::SimpleMath::Vector3(0, btoc.y, 0);
		size = mScale.y;
	}
	if (abs(btoc.z) > abs(res.x) || abs(btoc.z) > abs(res.y)) {
		res = DirectX::SimpleMath::Vector3(0, 0, btoc.z);
		size = mScale.z;
	}


	DirectX::SimpleMath::Vector3 norm = DirectX::SimpleMath::Vector3::Transform(res, mInvWorld.Invert());
	norm.Normalize();

	return norm * size;
}

bool OBB::obbVSPoint(DirectX::SimpleMath::Vector3 point) {

	point = DirectX::SimpleMath::Vector3::Transform(point, mInvWorld);
	if (point.x > /*mPoint.x*/0 - mScale.x && point.x < /*mPoint.x*/0 + mScale.x) {
		if (point.y > /*mPoint.y*/0 - mScale.y && point.y < /*mPoint.y*/0 + mScale.y) {
			if (point.z > /*mPoint.z*/0 - mScale.z && point.z < /*mPoint.z*/0 + mScale.z) {
				return true;
			}
		}
	}

	return false;
}

//NOT IMPLEMENTED
bool OBB::obbVsObb(OBB& other) {

	if (other.obbVSPoint(this->mPoint + this->mScale))
		return true;
	if (other.obbVSPoint(this->mPoint - this->mScale))
		return true;

	if (other.obbVSPoint(this->mPoint + DirectX::SimpleMath::Vector3(-this->mScale.x, this->mScale.y, this->mScale.z)))
		return true;
	if (other.obbVSPoint(this->mPoint + DirectX::SimpleMath::Vector3(this->mScale.x, -this->mScale.y, this->mScale.z)))
		return true;
	if (other.obbVSPoint(this->mPoint + DirectX::SimpleMath::Vector3(this->mScale.x, this->mScale.y, -this->mScale.z)))
		return true;
	if (other.obbVSPoint(this->mPoint + DirectX::SimpleMath::Vector3(-this->mScale.x, -this->mScale.y, this->mScale.z)))
		return true;
	if (other.obbVSPoint(this->mPoint + DirectX::SimpleMath::Vector3(-this->mScale.x, this->mScale.y, -this->mScale.z)))
		return true;
	if (other.obbVSPoint(this->mPoint + DirectX::SimpleMath::Vector3(this->mScale.x, -this->mScale.y, -this->mScale.z)))
		return true;

	if (this->obbVSPoint(other.mPoint + other.mScale))
		return true;
	if (this->obbVSPoint(other.mPoint - other.mScale))
		return true;

	if (this->obbVSPoint(other.mPoint + DirectX::SimpleMath::Vector3(-other.mScale.x, other.mScale.y, other.mScale.z)))
		return true;
	if (this->obbVSPoint(other.mPoint + DirectX::SimpleMath::Vector3(other.mScale.x, -other.mScale.y, other.mScale.z)))
		return true;
	if (this->obbVSPoint(other.mPoint + DirectX::SimpleMath::Vector3(other.mScale.x, other.mScale.y, -other.mScale.z)))
		return true;
	if (this->obbVSPoint(other.mPoint + DirectX::SimpleMath::Vector3(-other.mScale.x, -other.mScale.y, other.mScale.z)))
		return true;
	if (this->obbVSPoint(other.mPoint + DirectX::SimpleMath::Vector3(-other.mScale.x, other.mScale.y, -other.mScale.z)))
		return true;
	if (this->obbVSPoint(other.mPoint + DirectX::SimpleMath::Vector3(other.mScale.x, -other.mScale.y, -other.mScale.z)))
		return true;

	return false;
}

bool OBB::obbVSCapsule(const Capsule & other) {

	DirectX::SimpleMath::Vector3 newPoint = this->mPoint;
	
	if (newPoint.y <= other.mPoint.y + other.mHeight && (newPoint.y >= other.mPoint.y)) {
	
		DirectX::SimpleMath::Vector3 ptop = newPoint - DirectX::SimpleMath::Vector3(other.mPoint.x, newPoint.y, other.mPoint.z);
		ptop.Normalize();
		ptop = ptop * other.mRadius;
		if (this->obbVSPoint(ptop))
			return true;
	}
	
	DirectX::SimpleMath::Vector3 ptop;
	ptop = (newPoint - other.mPoint);
	ptop.Normalize();
	ptop = ptop * other.mRadius;
	ptop = ptop + other.mPoint;
	
	if (this->obbVSPoint(ptop))
		return true;
	
	ptop = newPoint - (DirectX::SimpleMath::Vector3(other.mPoint.x, other.mPoint.y + other.mHeight, other.mPoint.z));
	ptop.Normalize();
	ptop = ptop * other.mRadius;
	ptop = ptop + other.mPoint;
	
	if (this->obbVSPoint(ptop))
		return true;
	
	return false;
}

void OBB::setPos(DirectX::SimpleMath::Vector3 point) {
	this->mPoint = point;
	this->UpdateMatrix();
}

void OBB::setDir(DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up) {
	this->mDir = dir;
	this->mUp = up;
	this->UpdateMatrix();
}

void OBB::setScale(DirectX::SimpleMath::Vector3 scale) {
	this->mScale = scale;
	this->UpdateMatrix();
}

DirectX::SimpleMath::Vector3 Capsule::calculateNormal(OBB other) {

	return DirectX::SimpleMath::Vector3(0,0,0);
}

Capsule::Capsule(DirectX::SimpleMath::Vector3 point, float height, float radius)
{
	this->mPoint = point;
	this->mHeight = height;
	this->mRadius = radius;
}

Capsule::~Capsule()
{
}

bool Capsule::capsuleVSPoint(DirectX::SimpleMath::Vector3 point) {

	if (point.y > mPoint.y + mHeight + mRadius)
		return false;
	if (point.y < mPoint.y - mRadius)
		return false;


	DirectX::SimpleMath::Vector3 ptop = point - DirectX::SimpleMath::Vector3(this->mPoint.x, point.y, this->mPoint.z);

	if (abs(ptop.Length()) < mRadius)
		return true;

	ptop = point - this->mPoint;
	
	if (abs(ptop.Length()) < this->mRadius)
		return true;

	ptop = point - (DirectX::SimpleMath::Vector3(this->mPoint.x, this->mPoint.y + this->mHeight, this->mPoint.z));

	if (abs(ptop.Length()) < this->mRadius)
		return true;
	


	return false;

}

bool Capsule::capsuleVSObb(OBB & other) {
	return other.obbVSCapsule(*this);
}

bool Capsule::capsuleVSCapsule()
{
	return false;
}

AABB::AABB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 scale) {
	this->mPoint = point; this->mScale = scale;
}

AABB::AABB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 x, DirectX::SimpleMath::Vector3 y, DirectX::SimpleMath::Vector3 z)
{
	this->mPoint = (x + y + z) / 2;
	this->mPoint = point + this->mPoint;
	this->mScale = DirectX::SimpleMath::Vector3(abs(x.x) / 2, abs(y.y) / 2, abs(z.z) / 2);
}

DirectX::SimpleMath::Vector3 AABB::calculateNormal(Capsule & other)
{
	DirectX::SimpleMath::Vector3 tmp = DirectX::SimpleMath::Vector3(other.mPoint.x, other.mPoint.y + (other.mHeight / 2), other.mPoint.z);

	DirectX::SimpleMath::Vector3 btoc = tmp - this->mPoint;

	DirectX::SimpleMath::Vector3 res = { btoc.x, 0, 0 };
	float size = mScale.x;
	if (abs(btoc.y) > abs(res.x)) {
		res = DirectX::SimpleMath::Vector3(0, btoc.y, 0);
		size = mScale.y;
	}
	if (abs(btoc.z) > abs(res.x) || abs(btoc.z) > abs(res.y)) {
		res = DirectX::SimpleMath::Vector3(0, 0, btoc.z);
		size = mScale.z;
	}

	res.Normalize();

	return res;
}

bool AABB::aabbVSCapsule(Capsule & other)
{
	DirectX::SimpleMath::Vector3 newPoint = this->mPoint;
	
	if (newPoint.y <= other.mPoint.y + other.mHeight && (newPoint.y >= other.mPoint.y)) {
	
		DirectX::SimpleMath::Vector3 ptop = newPoint - DirectX::SimpleMath::Vector3(other.mPoint.x, newPoint.y, other.mPoint.z);
		ptop.Normalize();
		ptop = ptop * other.mRadius;
		if (this->aabbVSPoint(ptop))
			return true;
	}
	
	DirectX::SimpleMath::Vector3 ptop;
	ptop = (newPoint - other.mPoint);
	ptop.Normalize();
	ptop = ptop * other.mRadius;
	ptop = ptop + other.mPoint;
	
	if (this->aabbVSPoint(ptop))
		return true;
	
	ptop = newPoint - (DirectX::SimpleMath::Vector3(other.mPoint.x, other.mPoint.y + other.mHeight, other.mPoint.z));
	ptop.Normalize();
	ptop = ptop * other.mRadius;
	ptop = ptop + other.mPoint;
	
	if (this->aabbVSPoint(ptop))
		return true;
	
	
	return false;
}

bool AABB::aabbVSPoint(DirectX::SimpleMath::Vector3 point)
{
	if (point.x > this->mPoint.x - this->mScale.x && point.x < this->mPoint.x + this->mScale.x) {
		if (point.y > this->mPoint.y - this->mScale.y && point.y < this->mPoint.y + this->mScale.y) {
			if (point.z > this->mPoint.z - this->mScale.z && point.z < this->mPoint.z + this->mScale.z) {
				return true;
			}
		}
	}
	return false;
}

void AABB::setPosition(DirectX::SimpleMath::Vector3 point)
{
	this->mPoint = point;
}
