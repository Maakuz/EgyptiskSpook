#include "Colliders.h"

OBB::OBB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 lengthU, DirectX::SimpleMath::Vector3 lengthV, DirectX::SimpleMath::Vector3 lengthW)
{
	this->mPoint = point;
	this->mLengthU = lengthU;
	this->mLengthV = lengthV;
	this->mLengthW = lengthW;
	this->mU = point + lengthU;
	this->mV = point + lengthV;
	this->mW = point + lengthW;
}

OBB::~OBB() {
}

bool OBB::obbVSPoint(DirectX::SimpleMath::Vector3 point)
{
	DirectX::SimpleMath::Vector3 diff = this->mPoint - point;

	if (abs(diff.x) > this->mLengthU.Length())
		return false;

	if (abs(diff.y) > this->mLengthV.Length())
		return false;

	if (abs(diff.z) > this->mLengthW.Length())
		return false;

	if (abs(this->mU.x - point.x) > this->mLengthU.Length())
		return false;

	if (abs(this->mV.y - point.y) > this->mLengthV.Length())
		return false;

	if (abs(this->mW.z - point.z) > this->mLengthW.Length())
		return false;

	return true;
}

//NOT IMPLEMENTED
bool OBB::obbVsObb(const OBB& other) {
	return true;
}

bool OBB::obbVSCylinder(const Capsule & other) {
	return false;
}

DirectX::SimpleMath::Vector3 Capsule::calculateNormal(OBB other) {

	DirectX::SimpleMath::Vector3 midPoint = (other.mLengthU + other.mLengthV + other.mLengthW) / 2;
	midPoint += other.mPoint;

	//TEST

	DirectX::SimpleMath::Vector3 temp;

	//TEST

	DirectX::SimpleMath::Vector3 capsuleMidPoint = DirectX::SimpleMath::Vector3(this->mPoint.x, this->mPoint.y + (this->mHeight / 2), this->mPoint.z);
	DirectX::SimpleMath::Vector3 capToBox = capsuleMidPoint - midPoint;
	capToBox.Normalize();
	int face = 0;
	float result;
	float max = 0;
	temp = -other.mLengthW;
	temp.Normalize();
	result = capToBox.Dot(temp);
	if (result > max) {
		max = result;
	}

	float sadijasidj = DirectX::SimpleMath::Vector3(0, 1, 0).Dot(DirectX::SimpleMath::Vector3(0, -1, 0));

	temp = -other.mLengthU;
	temp.Normalize();
	result = capToBox.Dot(temp);
	if (result > max) {
		face = 1;
		max = result;
	}
	temp = -other.mLengthV;
	temp.Normalize();
	result = capToBox.Dot(temp);
	if (result > max) {
		face = 2;
		max = result;
	}
	temp = other.mLengthV;
	temp.Normalize();
	result = capToBox.Dot(temp);
	if (result > max) {
		face = 3;
		max = result;
	}
	temp = other.mLengthU;
	temp.Normalize();
	result = capToBox.Dot(temp);
	if (result > max) {
		face = 4;
		max = result;
	}
	temp = other.mLengthW;
	temp.Normalize();
	result = capToBox.Dot(temp);
	if (result > max) {
		face = 5;
		max = result;
	}


	/*DirectX::SimpleMath::Vector3 midPoint = DirectX::SimpleMath::Vector3(this->mPoint.x, this->mPoint.y + this->mHeight / 2, this->mPoint.z);
	int face = 0;
	float curr = 0;
	float total;
	//first face FRONT
	curr = (other.mPoint - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthV - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthV - midPoint).LengthSquared();
	total = curr;
	//second face VÄNSTER
	curr = 0;
	curr += (other.mPoint - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthV - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthW - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	if (curr < total) {
		face = 1; total = curr;
	}
	//third face UNDER
	curr = 0;
	curr += (other.mPoint - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthW - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	if (curr < total) {
		face = 2; total = curr;
	}
	//fourth face TOP
	curr = 0;
	curr += (other.mPoint + other.mLengthV - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthV + other.mLengthU - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthV + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	if (curr < total) {
		face = 3; total = curr;
	}
	//fifth face HÖGER
	curr = 0;
	curr += (other.mPoint + other.mLengthU - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthV - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	if (curr < total) {
		face = 4; total = curr;
	}
	//sixth face BACK
	curr = 0;
	curr += (other.mPoint + other.mLengthW - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthV - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthW - midPoint).LengthSquared();
	curr += (other.mPoint + other.mLengthU + other.mLengthV + other.mLengthW - midPoint).LengthSquared();
	if (curr < total) {
		face = 5;
	}
	*/
	switch (face) {
	case 0:
		return -other.mLengthW;
		break;
	case 1:
		return -other.mLengthU;
		break;
	case 2:
		return -other.mLengthV;
		break;
	case 3:
		return other.mLengthV;
		break;
	case 4:
		return other.mLengthU;
		break;
	case 5:
		return other.mLengthW;
		break;
	}

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

DirectX::SimpleMath::Vector3 Capsule::capsuleVSObb(OBB & other) {
	
	DirectX::SimpleMath::Vector3 newPoint = ((other.mLengthU + other.mLengthV + other.mLengthW) / 2);
	newPoint = ((other.mPoint) + newPoint);

	if (newPoint.y <= mPoint.y + mHeight && (newPoint.y >= mPoint.y)) {

		DirectX::SimpleMath::Vector3 ptop = newPoint - DirectX::SimpleMath::Vector3(this->mPoint.x, newPoint.y, this->mPoint.z);
		ptop.Normalize();
		ptop = ptop * this->mRadius;
		if (other.obbVSPoint(ptop))
			return (calculateNormal(other));
	}

	DirectX::SimpleMath::Vector3 ptop;
	ptop = (newPoint - this->mPoint);
	ptop.Normalize();
	ptop = ptop * this->mRadius;
	ptop = ptop + this->mPoint;

	if (other.obbVSPoint(ptop))
		return (calculateNormal(other));

	ptop = newPoint - (DirectX::SimpleMath::Vector3(this->mPoint.x, this->mPoint.y + this->mHeight, this->mPoint.z));
	ptop.Normalize();
	ptop = ptop * this->mRadius;
	ptop = ptop + this->mPoint;

	if (other.obbVSPoint(ptop))
		return (calculateNormal(other));


	return DirectX::SimpleMath::Vector3(0.f,0.f,0.f);
}

bool Capsule::capsuleVSCCapsule()
{
	return false;
}
