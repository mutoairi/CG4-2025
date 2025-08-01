#include "Player.h"
#include <cassert>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(ModelProject* model, Input* input) {
	assert(model);
	model_ = model;
	input_ = input;
	worldTransform_.Initialize();
	worldTransform_.rotation_.y += float(std::numbers::pi) / 2.0f;
	worldTransform_.translation_.z -= 30;
}

void Player::Update() {
	if (input_->PushKey(DIK_W)) {
		worldTransform_.translation_.y += velocity_.y;
	}
	if (input_->PushKey(DIK_S)) {
		worldTransform_.translation_.y -= velocity_.y;
	}
	if (input_->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= velocity_.x;
	}
	if (input_->PushKey(DIK_D)) {
		worldTransform_.translation_.x += velocity_.x;
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }