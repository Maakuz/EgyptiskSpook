#define PATH "../Resource/Textures/"
#define SCALE 0.5
#define OFFSET_X 9 * SCALE
#define OFFSET_Z -9 * SCALE

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
	int pX = floor(x * SCALE) + OFFSET_X;
	int pY = -(floor(z * SCALE) + OFFSET_Z);

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
			if (x != pTX && getPixel(x, y).r == 0) return false;
		}

		if (y != pTY) {
			y += y < pTY ? 1 : -1;
			if (y != pTY && getPixel(x, y).r == 0) return false;
		}

		if (x == pTX && y == pTY) return true;
	}
}

std::vector<Vector3> NavMesh::getPathToCoord(int x, int z) const {
	//A Star algorithm
	std::vector<Vector3> path;

	path.push_back(Vector3(x, 0, z));

	return path;
}

int NavMesh::getWidth() const {
	return mSurface->w;
}

int NavMesh::getHeight() const {
	return mSurface->h;
}