#pragma once

#include "Entity.h"

class Wall : public Entity
{
private:
	DirectX::SimpleMath::Vector3 mNormal;

public:
	Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale, int graphicsKey);
	virtual ~Wall();


	DirectX::SimpleMath::Vector3 getNormal() const;

};