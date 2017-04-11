#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H
#include <vector>
#include "EntityRenderer.h"
#include "Player.h"
#include "Wall.h"
#include "FBXLoader.h"

class EntityHandler
{
private:
	std::vector<Entity*> mEntities;
	Player* mPlayer;
	FBXLoader mLoader;

	//Will be removed in GraphicsHandler
	EntityRenderer* mEntityRenderer;

	int mNrOfKeys;

public:
	EntityHandler();
	virtual ~EntityHandler();

	void setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera, GraphicsData* gData);
	void setupEntities(ID3D11Device* device);

	void update();

	EntityRenderer* getRenderer();
	Player* getPlayer();
};


#endif