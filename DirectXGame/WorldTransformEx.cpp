#include "WorldTransform.h"
#include "Matrix4x4.h"
#include "ObjectColor.h"


void WorldTransform::UpdateMatrix() 
{
	matWorld_ = Matrix4x4::MakeAffineMatrix(scale_, rotation_, translation_);

	WorldTransform::TransferMatrix();
}