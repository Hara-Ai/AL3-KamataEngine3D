#include "Skydome.h"

void Skydome::Initialize() {}

void Skydome::Update() {}

void Skydome::Draw(const WorldTransform& skydomeWorldTransform_, const ViewProjection& skydomeViewProjection_, uint32_t textureHadle)
{
	model_->Draw(skydomeWorldTransform_, skydomeViewProjection_, textureHadle);
}


