#include "OBB.h"

OBB::OBB(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 lengthU, DirectX::SimpleMath::Vector3 lengthV, DirectX::SimpleMath::Vector3 lengthW)
{
	this->mPoint = point;
	this->mLengthU = lengthU;
	this->mLengthV = lengthV;
	this->mLengthW = lengthW;
}

OBB::~OBB()
{
}

bool OBB::obbVSPoint(DirectX::SimpleMath::Vector3 point)
{
	if (abs(this->mPoint.x - point.x) > this->mLengthU.Length())
		return false;

	if (abs(this->mPoint.y - point.y) > this->mLengthV.Length())
		return false;

	if (abs(this->mPoint.z - point.z) > this->mLengthW.Length())
		return false;

	if (abs(this->mPoint.x + this->mLengthU.x - point.x) > this->mLengthU.Length())
		return false;

	if (abs(this->mPoint.y + this->mLengthV.y - point.y) > this->mLengthV.Length())
		return false;

	if (abs(this->mPoint.z + this->mLengthW.z - point.z) > this->mLengthW.Length())
		return false;

	return true;
}

//NOT IMPLEMENTED
bool OBB::obbVsObb(const OBB& other)
{
	return true;
}
