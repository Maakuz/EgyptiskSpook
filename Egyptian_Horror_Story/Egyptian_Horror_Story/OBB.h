#pragma once

#include "Direct3DHeader.h"

#include "SimpleMath.h"
class OBB
{
private:
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

};