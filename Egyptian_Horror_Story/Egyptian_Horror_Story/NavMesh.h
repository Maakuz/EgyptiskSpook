#ifndef NAV_MESH_H
#define NAV_MESH_H

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <thread>

#include "Direct3DHeader.h"
#include "SimpleMath.h"
#include "Enemy.h"

class NavMesh {
private:
	struct Node {
		DirectX::SimpleMath::Vector2 node;
		unsigned int parentIndex;
		float F, G, H;

		bool operator<(Node const &n) {
			return F > n.F; //Sneaky way to make min heap
		}
	};

	SDL_Surface *mSurface, *mCopy;
	UINT8 *indexArray;
	std::thread *mCurrentThread;

	void copy(NavMesh const &navMesh);
	void deleteMemory();

	// For the searching algorithm
	// return -1 for not contains, or returns index of the node
	int contains(std::unordered_map<int, Node> const &list,
		DirectX::SimpleMath::Vector2 const &vec, int w) const;
	bool isWalkable(DirectX::SimpleMath::Vector2 const &node) const;
	float heuristic(DirectX::SimpleMath::Vector2 node,
		DirectX::SimpleMath::Vector2 toPos) const;
	void savePathTest(std::vector<DirectX::SimpleMath::Vector2> &path);
	/* Checks if already added and adds accordingly */
	void openListInsert(DirectX::SimpleMath::Vector2 &node,
		std::vector<Node> &openList, unsigned int parentIndex, float cost, Node &parent) const;
	/* Simple hash method */
	int hashMethod(DirectX::SimpleMath::Vector2 const &pos, int w) const;
	// also removes the node from the list!!!!
	Node getShortestNode(std::vector<Node> &openList) const;

	void loadPathToCoordThread(Enemy *enemy, int fromX, int fromZ, int toX, int toZ);
public:
	NavMesh();
	virtual ~NavMesh();
	NavMesh(NavMesh const &navMesh);

	void loadGrid(const char *gridName);
	SDL_Color getPixel(int x, int y) const;
	SDL_Color getPixelAtCoord(int x, int z) const;
	DirectX::SimpleMath::Vector2 toPixelCoord(int x, int z) const;
	bool canSeeFrom(int fromX, int fromZ, int toX, int toZ) const;

	void loadPathToCoord(Enemy *enemy, int fromX, int fromZ, int x, int z);
	DirectX::SimpleMath::Vector2 getPosition(DirectX::SimpleMath::Vector2 pixel) const;

	int getWidth() const;
	int getHeight() const;

	void* getNavigationTexture() const; //this is for debugging

	NavMesh* operator=(NavMesh const &navMesh);
};

#endif