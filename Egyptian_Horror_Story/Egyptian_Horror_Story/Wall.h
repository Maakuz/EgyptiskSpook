#pragma once

#include "Entity.h"

class Wall : public Entity
{
private:

public:
	Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W);
	virtual ~Wall();

};