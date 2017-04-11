#ifndef FBXLOADER_H
#define FBXLOADER_H
#include "Direct3DHeader.h"

#include <fbxsdk.h>
#include <vector>

class FBXLoader
{
private:

public:
	FBXLoader();
	virtual ~FBXLoader();

	bool loadMesh();
	

};


#endif // !FBXLOADER_H
