#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H
#include <vector>
#include "EntityRenderer.h"
#include "RiggedEntityRenderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "FBXLoader.h"

#define WALLTEXTURE L"pyramidStone.png"

class EntityHandler
{
private:
	std::vector<Entity*> mEntities;
	Entity* mRiggedTest;
	Player* mPlayer;
	Enemy* mEnemy;
	
	FBXLoader mLoader;

	//Will be removed in GraphicsHandler
	EntityRenderer* mEntityRenderer;
	RiggedEntityRenderer* mRiggedEntityRenderer;

	int mNrOfKeys;

	void hardcodedMap(ID3D11Device* device);
public:
	EntityHandler();
	virtual ~EntityHandler();

	void setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera);
	void setupEntities(ID3D11Device* device);

	void update(ID3D11DeviceContext* context);

	EntityRenderer* getEntityRenderer();
	RiggedEntityRenderer* getRiggedEntityRenderer();
	Player* getPlayer();
	Enemy* getEnemy();
};


#endif