#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H
#include "Direct3DHeader.h"
#include "SimpleMath.h"
#include <vector>
#include "Structs.h"

class AnimationHandler
{
private:
	std::vector<animation::Bone> skeleton;

public:
	AnimationHandler();
	virtual ~AnimationHandler();

	void calculateBoneMatrices();

};


#endif