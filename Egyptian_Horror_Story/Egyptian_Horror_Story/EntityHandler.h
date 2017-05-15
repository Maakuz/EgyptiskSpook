#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H
#include <vector>
#include "EntityRenderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "FBXLoader.h"
#include "AudioManager.h"
#include "AIHandler.h"

#define WALLTEXTURE L"pyramidStone.png"

class EntityHandler
{
private:
	std::vector<Entity*> mEntities;
	std::vector<Trap*> mTraps;
	AudioManager* mAudioManager;
	Entity* mFlashlightModel;
	Entity* mLevel;
	Player* mPlayer;
	Enemy* mEnemy;
	
	FBXLoader mLoader;

	//Will be removed in GraphicsHandler
	EntityRenderer* mEntityRenderer;

	bool footstepsPlaying;
	int mNrOfKeys;

	void hardcodedMap(ID3D11Device* device);
	void loadEntityModel(std::string modelName, wchar_t* textureName, Entity* entity, ID3D11Device* device);
	void updateAudio();
	void updateCollision();

public:
	EntityHandler();
	virtual ~EntityHandler();

	void loadMap(ID3D11Device* device);

	void setupTraps(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context);
	void setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera);
	void setupEntities(ID3D11Device* device);
	void setupAudioManager(AudioManager* manager);

	void update(ID3D11DeviceContext* context, float dt);

	EntityRenderer* getEntityRenderer();
	Player* getPlayer();
	Enemy* getEnemy();
};


#endif