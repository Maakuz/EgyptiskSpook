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
#include <ctime>
#include <random>

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
	float mTrapPercentage;
	float mTreasurePercentage;

	struct PosRot
	{
		DirectX::SimpleMath::Vector3 pos;
		float rot;
	};

	std::vector<PosRot> mTrapPositions;
	std::vector<PosRot> mTreasurePositions;

	/* From image space to world space */
	DirectX::SimpleMath::Vector2 toPixelCoord(int x, int z, int w, int h) const;

	void hardcodedMap(ID3D11Device* device);
	void loadEntityModel(std::string modelName, wchar_t* textureName, Entity* entity, ID3D11Device* device);
	void updateAudio();
	void updateCollision();
	void detectCloseTreasures();
	void createAhnk(ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot);
	void createTreasureChest(ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot);
	void createBoulderTrap(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot, float yOffset);

	//At least I tried spelling it!
	void createGuillioutineTrap(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot);

	void setupTreasureAndTraps(AIHandler* ai, ID3D11Device* device);
public:
	EntityHandler();
	virtual ~EntityHandler();

	void loadMap(ID3D11Device* device);

	void setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera);
	void setupEntities(AIHandler* ai, ID3D11Device* device);
	void setupAudioManager(AudioManager* manager);
	void setupDifficulty(settings::DifficultySettings& diff);

	void initializeTreasureAndTraps(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context);
	void initialize();

	void update(ID3D11DeviceContext* context, float dt);
	/* From world space to image space */
	DirectX::SimpleMath::Vector2 getPosition(int x, int y, int w, int h) const;

	EntityRenderer* getEntityRenderer();
	Player* getPlayer();
	Enemy* getEnemy();
};


#endif