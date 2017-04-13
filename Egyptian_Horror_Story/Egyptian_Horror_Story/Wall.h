#pragma once

#include "Entity.h"

class Wall : public Entity
{
private:
	DirectX::SimpleMath::Vector3 mNormal;

public:
<<<<<<< HEAD
	Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W, DirectX::SimpleMath::Vector3 n, int graphicsKey);
=======
	Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale, int graphicsKey);
>>>>>>> 7e58a1c3cdaf767f52eee7a2cec60f0d8d0d0c94
	virtual ~Wall();


	DirectX::SimpleMath::Vector3 getNormal() const;

};