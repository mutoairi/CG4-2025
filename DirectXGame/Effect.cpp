#include "Effect.h"
#include <cassert>

void Effect::Initialize(KamataEngine::Model* model) {
	assert(model);
	model_ = model;

	wordTransform_.Initialize();
}

void Effect::Update() { wordTransform_.UpdateMatrix(); }

void Effect::Draw(KamataEngine::Camera& camera) { model_->Draw(wordTransform_, camera); }
