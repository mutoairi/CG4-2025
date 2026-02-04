#include "Player.h"
#include <cassert>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;

Player::~Player() {
	for (PlayerBullet* bullet_ : bullets_) {
		delete bullet_;
	}
}

void Player::Initialize(ModelProject* model, Input* input) {
	assert(model);
	model_ = model;
	input_ = input;
	worldTransform_.Initialize();
	worldTransform_.rotation_.y += float(std::numbers::pi) / 2.0f;
	worldTransform_.translation_.z -= 30;
	worldTransform_.translation_.x = -10.0f;
}

void Player::Update() {
	// デスフラグが立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet_) {
		if (bullet_->IsDead()) {
			delete bullet_;
			return true;
		}
		return false;
	});
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
	Attack();
	for (PlayerBullet* bullet_ : bullets_) {
		bullet_->Update();
	}
	
	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera& camera) { 
	model_->Draw(worldTransform_, camera);
	// 弾描画
	for (PlayerBullet* bullet_ : bullets_) {
		bullet_->Draw(camera);
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// 弾の速度
		//const float kBulletSpeed = -1.0f;
		KamataEngine::Vector3 velocity(1.0f, 0, 0);
		// 速度ベクトルを自機の向きに合わせて回転させる
		//velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し初期
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}

	if (input_->PushKey(DIK_SPACE)) {
	};
	
}
