#include "Effect.h"
#include <cassert>
#include <random>

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distrubution(-1.0f, 1.0f);

void Effect::Initialize(KamataEngine::Model* model) {
	assert(model);
	model_ = model;

	wordTransform_.Initialize();
}

void Effect::Update() {

	wordTransform_.scale_.y = std::abs(distrubution(randomEngine) * 10.0f);
	wordTransform_.rotation_.z = distrubution(randomEngine) * 20.0f;

	wordTransform_.UpdateMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) { model_->Draw(wordTransform_, camera); }
