#include "Effect.h"
#include<cassert>

void Effect::Initialize(KamataEngine::Model* model) { 
	assert(model);
	model_ = model; 

	wordTransform_.Initialize();
}

void Effect::Update() { 
	wordTransform_.rotation_ = {0.0f,100.0f, 0.0f};
	wordTransform_.UpdateMatrix(); }

void Effect::Draw(KamataEngine::Camera& camera) { model_->Draw(wordTransform_, camera); }
