#include "Skydome.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

void Skydome::Initialize() 
{ 
	model_ = Model::Create();
	worldTransform_ = new WorldTransform; 
	viewProjection_ = new ViewProjection;
	
}

Skydome::Skydome() {}

Skydome::~Skydome() 
{
	delete model_;
	delete worldTransform_;
	delete viewProjection_;
}



void Skydome::Update() {}

void Skydome::Draw(const WorldTransform& WorldTransform, const ViewProjection& ViewProjection)
{
	model_->Draw(WorldTransform, ViewProjection);
}


