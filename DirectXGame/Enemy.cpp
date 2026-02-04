#include "Enemy.h"
#include <cassert>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;
void Enemy::Initialize(KamataEngine::ModelProject* model) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.rotation_.y += float(std::numbers::pi)/-2.0f ;
	worldTransform_.rotation_.z = 0.0f;
	worldTransform_.translation_.z -= 30;
	worldTransform_.translation_.y = 0.0f;
	worldTransform_.translation_.x = 5.0f;
	worldTransform_.scale_ = {10.0f, 10.0f, 10.0f};
}

void Enemy::Update() {
	

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }