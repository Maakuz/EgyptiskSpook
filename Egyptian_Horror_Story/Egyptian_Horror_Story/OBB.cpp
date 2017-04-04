#include "OBB.h"

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

OBB::~OBB()
{
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
bool OBB::obbVsObb(const OBB& other)
{
	return true;
}