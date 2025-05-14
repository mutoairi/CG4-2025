#include "Effect.h"
#include <cassert>

void Effect::Initialize(KamataEngine::Model* model,KamataEngine::Vector3 scale, KamataEngine::Vector3 rotation) {
	assert(model);
	model_ = model;

	wordTransform_.Initialize();
	wordTransform_.scale_ = scale;
	wordTransform_.rotation_ = rotation;
}

void Effect::Update() {

	
	wordTransform_.UpdateMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) { model_->Draw(wordTransform_, camera); }
