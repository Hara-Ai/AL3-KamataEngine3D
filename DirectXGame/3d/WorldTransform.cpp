#include "WorldTransform.h"

void WorldTransform::UpdateMatrix()
{ matWorld_; }

Vector3 WorldTransform::MakeAffineMatrix(Vector3 scale_, Vector3 rotation_, Vector3 translation_)
{
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	TransferMatrix;
	return Vector3();
}

