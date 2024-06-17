#include "Skydome.h"

void Skydome::Initialize() 
{ 
	model_ = Model::Create();
	worldTransform_->Initialize();
	
}

Skydome::Skydome() {}

Skydome::~Skydome() 
{
	delete model_;
}



void Skydome::Update() {}

void Skydome::Draw(const WorldTransform& skydomeWorldTransform_, const ViewProjection& skydomeViewProjection_)
{
	model_->Draw(skydomeWorldTransform_, skydomeViewProjection_);
}


