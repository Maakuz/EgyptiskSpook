#define PATH "../Resource/Textures/"
#define SCALE 2
#define OFFSET_X -8
#define OFFSET_Z 8

#include "NavMesh.h"
#include <string>
#include <math.h>
#include <assert.h>

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
	int pX = floor(x * SCALE) + OFFSET_X;
	int pY = floor(z * SCALE) + OFFSET_Z;

	if (pX < 0) pX = 0;
	if (pY < 0) pY = 0;
	if (pX >= getWidth()) pX = getWidth() - 1;
	if (pY >= getHeight()) pY = getHeight() - 1;

	assert(mSurface);
	return mSurface->format->palette->colors
		[indexArray[pX + pY * getWidth()]];
}

std::vector<DirectX::SimpleMath::Vector3>
	NavMesh::getPathToCoord(int x, int z) const {
	using namespace DirectX::SimpleMath;
	//A Star algorithm
	std::vector<Vector3> path;

	path.push_back(Vector3(x, 5, z));

	return path;
}

int NavMesh::getWidth() const {
	return mSurface->w;
}

int NavMesh::getHeight() const {
	return mSurface->h;
}