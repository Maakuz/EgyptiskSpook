#define PATH "../Resource/Textures/"
#define SCALE_X 1
#define SCALE_Z -1
#define OFFSET_X 9 * SCALE_X
#define OFFSET_Z -9 * SCALE_Z
#define BLOCKADE 0
#define AVOID 128

#include "NavMesh.h"
#include <string>
#include <math.h>
#include <assert.h>

using namespace DirectX::SimpleMath;

void NavMesh::copy(NavMesh const &navMesh) {
	if (&navMesh != this) {
		deleteMemory();
		
		mSurface = navMesh.mSurface;
		assert(!mSurface); //for testing
		indexArray = new UINT8[getWidth() * getHeight()];

		for (int x = 0; x < getWidth(); x++) {
			for (int y = 0; y < getHeight(); y++) {
				indexArray[x + y * getWidth()] =
					navMesh.indexArray[x + y * getWidth()];
			}
		}
	}
}

void NavMesh::deleteMemory() {
	if (mSurface)
		SDL_FreeSurface(mSurface);
}

NavMesh::NavMesh() {
	mSurface = nullptr;
	indexArray = nullptr;
}

NavMesh::~NavMesh() {
	deleteMemory();
}

NavMesh::NavMesh(NavMesh const &navMesh) {
	copy(navMesh);
}

NavMesh* NavMesh::operator=(NavMesh const &navMesh) {
	copy(navMesh);
	return this;
}

void NavMesh::loadGrid(const char *gridName) {
	std::string str(PATH);
	str += gridName;

	if (mSurface) SDL_FreeSurface(mSurface);
	mSurface = SDL_LoadBMP(str.c_str());
	indexArray = (UINT8*) mSurface->pixels;
}

SDL_Color NavMesh::getPixel(int x, int y) const {
	assert(mSurface);
	return mSurface->format->palette->colors
		[indexArray[x + y * getWidth()]];
}

SDL_Color NavMesh::getPixelAtCoord(int x, int z) const {
	Vector2 pixelCoord = toPixelCoord(x, z);
	int pX = static_cast<int>(pixelCoord.x), 
		pY = static_cast<int>(pixelCoord.y);
	assert(mSurface);
	return mSurface->format->palette->colors
		[indexArray[pX + pY * getWidth()]];
}

Vector2 NavMesh::toPixelCoord(int x, int z) const {
	int pX = floor(x * SCALE_X) + OFFSET_X;
	int pY = -(floor(z * SCALE_Z) + OFFSET_Z);

	pX %= getWidth();
	pY %= getHeight();

	return Vector2(abs(pX), abs(pY));
}

bool NavMesh::canSeeFrom(int fromX, int fromZ, int toX, int toZ) const {
	Vector2 pixelCoordFrom = toPixelCoord(fromX, fromZ);
	Vector2 pixelCoordTo = toPixelCoord(toX, toZ);
	int x = static_cast<int> (pixelCoordFrom.x);
	int y = static_cast<int> (pixelCoordFrom.y);
	int pTX = static_cast<int> (pixelCoordTo.x);
	int pTY = static_cast<int> (pixelCoordTo.y);

	// Walks from x y to toX toY, if any pixels in the way is colliders, x y cant see toX toY
	while (true) { //WARNING: DANGEROUS CODE, CHANGE IT
		if (x != pTX) {
			x += x < pTX ? 1 : -1;
			if (x != pTX && getPixel(x, y).r == BLOCKADE) return false;
		}

		if (y != pTY) {
			y += y < pTY ? 1 : -1;
			if (y != pTY && getPixel(x, y).r == BLOCKADE) return false;
		}

		if (x == pTX && y == pTY) return true;
	}
}

std::vector<Vector3> NavMesh::getPathToCoord(int fromX, int fromZ, int toX, int toZ) const {
	//A Star algorithm ! THIS IS CURRENTLY VERY UNOPTIMIZED !
	Vector2 toPos = toPixelCoord(toX, toZ);
	std::vector<Vector3> path;
	std::vector<Node> openList;
	std::vector<Node> closedList;
	openList.push_back({ toPixelCoord(fromX, fromZ), 0, 0, 0, 0 });

	if (toPos == openList.at(0).node) { // if at same node
		path.push_back(Vector3(toX, 0, toZ));
		return path;
	}

	Vector2 node;
	Node parent;
	bool pathFound = false;
	int nodes = 0;
	
	while (!openList.empty() && !pathFound) {
		parent = getShortestNode(openList);
		closedList.push_back(parent); //add current node to closed list
		nodes++;
	//	SDL_Log("x,y: %f,%f H: %f, Nr: %d. TO x,y: %f,%f", parent.node.x, parent.node.y, parent.H, closedList.size(), toPos.x, toPos.y);
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if ((x != 0 || y != 0)) {
					node = Vector2(
						static_cast<int>(abs(x + parent.node.x)) % getWidth(),
						static_cast<int>(abs(y + parent.node.y)) % getHeight() // so node is in bounds
					);

					float cost = heuristic(node, toPos) + parent.F; //calculate cost of this node

					if (toPos == node) { // adding target node = Done
						pathFound = true;
					}
					else if (isWalkable(node) &&
						contains(closedList, node) == -1) { //can walk through node and is not in closed list
						int index = contains(openList, node);
						if (index == -1) // if not already added
							openList.push_back({ node, closedList.size() - 1,
												cost, parent.F, cost - parent.F //F, G, H
						}); // add new node to open list
						else if (openList[index].F < cost) //If already added but new path is shorter,
							// change to new path
							openList[index] = { node, closedList.size() - 1, cost,
											parent.F, cost - parent.F };
					}
				}
			}
		}
	}

	parent = closedList[closedList.size() - 1]; //node before ending
	path.push_back(Vector3(toX, 0, toZ));
	path.push_back(getPosition(node));
	while (true) {
		path.push_back(getPosition(parent.node));
		if (parent.parentIndex == 0) break;
		parent = closedList[parent.parentIndex];
	}

	for (int i = 0; i < floor(path.size() / 2); i++) {
		std::swap(path[i], path[path.size() - i - 1]);
	}

	SDL_Log("Path started, Size: %d", path.size());
	return path;
}

int NavMesh::getWidth() const {
	return mSurface->w;
}

int NavMesh::getHeight() const {
	return mSurface->h;
}

int NavMesh::contains(std::vector<Node> const &list,
	DirectX::SimpleMath::Vector2 const &vec) const {
	for (int x = 0; x < list.size(); x++) {
		if (list[x].node == vec) return x;
	}

	return -1;
}

inline bool NavMesh::isWalkable(Vector2 const &node) const {
	SDL_Color col = getPixel(node.x, node.y);
	return col.r == BLOCKADE || col.r == AVOID;
}

Vector3 NavMesh::getPosition(Vector2 pixel) const {
	return Vector3(
		(pixel.x - OFFSET_X) / SCALE_X,
		0,
		(pixel.y - OFFSET_Z) / SCALE_Z
	);
}

float NavMesh::heuristic(Vector2 node, Vector2 toPos) const {
	return (toPos - node).Length(); //There is better and more efficient ways to do this! TODO
}

NavMesh::Node NavMesh::getShortestNode(std::vector<Node> &openList) const {
	float shortest = 99999999;
	int index = 0;

	for (int x = 0; x < openList.size(); x++) {
		if (openList[x].F < shortest) {
			shortest = openList[x].F;
			index = x;
		}
	}

	Node node = openList[index];
	std::swap(openList[index], openList[openList.size() - 1]);
	openList.pop_back();

	return node;
}