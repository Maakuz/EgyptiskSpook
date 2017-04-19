#ifndef NAV_MESH_H
#define NAV_MESH_H

#include <SDL.h>
#include <vector>
#include "Direct3DHeader.h"
#include "SimpleMath.h"

class NavMesh {
private:
	SDL_Surface *mSurface;
	UINT8 *indexArray;

	void copy(NavMesh const &navMesh);
	void deleteMemory();
public:
	NavMesh();
	virtual ~NavMesh();
	NavMesh(NavMesh const &navMesh);

	void loadGrid(const char *gridName);
	SDL_Color getPixel(int x, int y) const;
	SDL_Color getPixelAtCoord(int x, int z) const;

	std::vector<DirectX::SimpleMath::Vector3> getPathToCoord(int x, int z) const;

	int getWidth() const;
	int getHeight() const;

	NavMesh* operator=(NavMesh const &navMesh);
};

#endif