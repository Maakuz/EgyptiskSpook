#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H
#include <vector>
#include "EntityRenderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Treasure.h"
#include "FBXLoader.h"
#include "AudioManager.h"
#include "AIHandler.h"

#define WALLTEXTURE L"pyramidStone.png"

class EntityHandler
{
private:
	std::vector<Entity*> mEntities;
	std::vector<Trap*> mTraps;
	std::vector<Treasure*> mTreasures;
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

	/* From image space to world space */
	DirectX::SimpleMath::Vector2 toPixelCoord(int x, int z, int w, int h) const;

	void hardcodedMap(ID3D11Device* device);
	void loadEntityModel(std::string modelName, wchar_t* textureName, Entity* entity, ID3D11Device* device);
	void updateAudio();
	void updateCollision();
	void detectCloseTreasures();
public:
	EntityHandler();
	virtual ~EntityHandler();

	void loadMap(ID3D11Device* device);

	void setupTraps(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context);
	void setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera);
	void initializeTreasureAndTraps(AIHandler* ai, ID3D11Device* device);
	void setupEntities(AIHandler* ai, ID3D11Device* device);
	void setupAudioManager(AudioManager* manager);

	void initialize();

	void update(ID3D11DeviceContext* context, float dt);
	/* From world space to image space */
	DirectX::SimpleMath::Vector2 getPosition(int x, int y, int w, int h) const;

	EntityRenderer* getEntityRenderer();
	Player* getPlayer();
	Enemy* getEnemy();
};


#endif