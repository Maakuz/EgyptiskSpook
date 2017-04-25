#include "AnimationHandler.h"

AnimationHandler::AnimationHandler()
{

}

AnimationHandler::~AnimationHandler()
{

}

void AnimationHandler::calculateBoneMatrices()
{
	for (size_t i = 0; i < this->skeleton.size(); i++)
	{
		animation::Bone& bone = this->skeleton[i];

		if (bone.parent == -1)
			bone.absoluteForm = bone.relativeForm;

		else
			bone.absoluteForm = skeleton[bone.parent].absoluteForm * bone.relativeForm;
	}
}
 