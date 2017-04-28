#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H
#include <vector>
#include "EntityRenderer.h"
#include "RiggedEntityRenderer.h"
#include "Player.h"
#include "Wall.h"
#include "AnimatedEntity.h"
#include "FBXLoader.h"

class EntityHandler
{
private:
	std::vector<Entity*> mEntities;
	AnimatedEntity* mRiggedTest;
	Player* mPlayer;
	FBXLoader mLoader;

	//Will be removed in GraphicsHandler
	EntityRenderer* mEntityRenderer;
	RiggedEntityRenderer* mRiggedEntityRenderer;

	int mNrOfKeys;

public:
	EntityHandler();
	virtual ~EntityHandler();

	void setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera);
	void setupEntities(ID3D11Device* device);

	void update();

	EntityRenderer* getEntityRenderer();
	RiggedEntityRenderer* getRiggedEntityRenderer();
	Player* getPlayer();
};


#endif