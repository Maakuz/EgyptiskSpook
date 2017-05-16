#include "Colliders.h"

void OBB::UpdateMatrix() {
	mInvWorld = mInvWorld.CreateWorld(this->mPoint, this->mDir, this->mUp);
	mInvWorld = mInvWorld.Invert();
}

OBB::OBB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale) {
	//this->mPoint = point;
	//this->mLengthU = lengthU;
	//this->mLengthV = lengthV;
	//this->mLengthW = lengthW;
	//this->mU = point + lengthU;
	//this->mV = point + lengthV;
	//this->mW = point + lengthW;

	this->mPoint = point;
	this->mDir = dir;
	this->mUp = up;
	this->mScale = scale;

	this->UpdateMatrix();

	//this->mPoint = DirectX::SimpleMath::Vector3(0,0,0);
	//this->mDir = DirectX::SimpleMath::Vector3(0, 0, 1);
	//this->mDir.Normalize();
	//this->mUp = DirectX::SimpleMath::Vector3(0,1,0);
	//this->mScale = DirectX::SimpleMath::Vector3(2, 1, 1);
	//this->UpdateMatrix();

	//bool bajs = this->obbVSPoint(DirectX::SimpleMath::Vector3(1.5,0,0));
	
}

OBB::~OBB() {
}

DirectX::SimpleMath::Vector3 OBB::getNormal(Capsule & other) {
	
	//this->mPoint = DirectX::SimpleMath::Vector3(0,0,0);
	//this->mDir = DirectX::SimpleMath::Vector3(1, 0, 2);
	//this->mDir.Normalize();
	//this->mUp = DirectX::SimpleMath::Vector3(0, 1, 0);
	//this->mScale = DirectX::SimpleMath::Vector3(1, 1, 1);
	//this->UpdateMatrix();
	//
	//other.mPoint = DirectX::SimpleMath::Vector3(-2, 1, 0);
	//other.mHeight = 2;

	//REMOVE ABOVE

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
	//DirectX::SimpleMath::Vector3 diff = this->mPoint - point;
	//if (abs(diff.x) > this->mLengthU.Length())
	//	return false;
	//
	//if (abs(diff.y) > this->mLengthV.Length())
	//	return false;
	//
	//if (abs(diff.z) > this->mLengthW.Length())
	//	return false;
	//
	//if (abs(this->mU.x - point.x) > this->mLengthU.Length())
	//	return false;
	//
	//if (abs(this->mV.y - point.y) > this->mLengthV.Length())
	//	return false;
	//
	//if (abs(this->mW.z - point.z) > this->mLengthW.Length())
	//	return false;
	//

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


	//float sadijasidj = DirectX::SimpleMath::Vector3(0, 1, 0).Dot(DirectX::SimpleMath::Vector3(0, -1, 0));

	//temp = -other.mLengthU;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 1;
	//	max = result;
	//}
	//temp = -other.mLengthV;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 2;
	//	max = result;
	//}
	//temp = other.mLengthV;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 3;
	//	max = result;
	//}
	//temp = other.mLengthU;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 4;
	//	max = result;
	//}
	//temp = other.mLengthW;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 5;
	//	max = result;

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

	//DirectX::SimpleMath::Vector3 midPoint = (other.mLengthU + other.mLengthV + other.mLengthW) / 2;
	//midPoint += other.mPoint;

	////TEST

	//DirectX::SimpleMath::Vector3 temp;

	////TEST

	//DirectX::SimpleMath::Vector3 capsuleMidPoint = DirectX::SimpleMath::Vector3(this->mPoint.x, this->mPoint.y + (this->mHeight / 2), this->mPoint.z);
	//DirectX::SimpleMath::Vector3 capToBox = capsuleMidPoint - midPoint;
	//capToBox.Normalize();
	//int face = 0;
	//float result;
	//float max = 0;
	//temp = -other.mLengthW;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	max = result;
	//}

	//temp = -other.mLengthU;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 1;
	//	max = result;
	//}
	//temp = -other.mLengthV;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 2;
	//	max = result;
	//}
	//temp = other.mLengthV;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 3;
	//	max = result;
	//}
	//temp = other.mLengthU;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 4;
	//	max = result;
	//}
	//temp = other.mLengthW;
	//temp.Normalize();
	//result = capToBox.Dot(temp);
	//if (result > max) {
	//	face = 5;
	//	max = result;
	//}


	///*DirectX::SimpleMath::Vector3 midPoint = DirectX::SimpleMath::Vector3(this->mPoint.x, this->mPoint.y + this->mHeight / 2, this->mPoint.z);
	//int face = 0;
	//float curr = 0;
	//float total;
	////first face FRONT
	//curr = (other.mPoint - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthV - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthV - midPoint).LengthSquared();
	//total = curr;
	////second face VÄNSTER
	//curr = 0;
	//curr += (other.mPoint - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthV - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthW - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	//if (curr < total) {
	//	face = 1; total = curr;
	//}
	////third face UNDER
	//curr = 0;
	//curr += (other.mPoint - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthW - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	//if (curr < total) {
	//	face = 2; total = curr;
	//}
	////fourth face TOP
	//curr = 0;
	//curr += (other.mPoint + other.mLengthV - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthV + other.mLengthU - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthV + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	//if (curr < total) {
	//	face = 3; total = curr;
	//}
	////fifth face HÖGER
	//curr = 0;
	//curr += (other.mPoint + other.mLengthU - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthV - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	//if (curr < total) {
	//	face = 4; total = curr;
	//}
	////sixth face BACK
	//curr = 0;
	//curr += (other.mPoint + other.mLengthW - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthV - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	//curr += (other.mPoint + other.mLengthU + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	//if (curr < total) {
	//	face = 5;
	//}
	//*/
	//switch (face) {
	//case 0:
	//	return -other.mLengthW;
	//	break;
	//case 1:
	//	return -other.mLengthU;
	//	break;
	//case 2:
	//	return -other.mLengthV;
	//	break;
	//case 3:
	//	return other.mLengthV;
	//	break;
	//case 4:
	//	return other.mLengthU;
	//	break;
	//case 5:
	//	return other.mLengthW;
	//	break;
	//}

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
	
	//DirectX::SimpleMath::Vector3 newPoint = ((other.mLengthU + other.mLengthV + other.mLengthW) / 2);
	//newPoint = ((other.mPoint) + newPoint);
	//
	//if (newPoint.y <= mPoint.y + mHeight && (newPoint.y >= mPoint.y)) {
	//
	//	DirectX::SimpleMath::Vector3 ptop = newPoint - DirectX::SimpleMath::Vector3(this->mPoint.x, newPoint.y, this->mPoint.z);
	//	ptop.Normalize();
	//	ptop = ptop * this->mRadius;
	//	if (other.obbVSPoint(ptop))
	//		return (calculateNormal(other));
	//}
	//
	//DirectX::SimpleMath::Vector3 ptop;
	//ptop = (newPoint - this->mPoint);
	//ptop.Normalize();
	//ptop = ptop * this->mRadius;
	//ptop = ptop + this->mPoint;
	//
	//if (other.obbVSPoint(ptop))
	//	return (calculateNormal(other));
	//
	//ptop = newPoint - (DirectX::SimpleMath::Vector3(this->mPoint.x, this->mPoint.y + this->mHeight, this->mPoint.z));
	//ptop.Normalize();
	//ptop = ptop * this->mRadius;
	//ptop = ptop + this->mPoint;
	//
	//if (other.obbVSPoint(ptop))
	//	return (calculateNormal(other));
	//
	//
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
