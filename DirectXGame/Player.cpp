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
	hp = 100;
}

void Player::Update() {
	if (hp <= 0) {
		isDead_ = true;
	}
	if (!isDead_) {

		// デスフラグが立った弾を削除
		bullets_.remove_if([](PlayerBullet* bullet_) {
			if (bullet_->IsDead()) {
				delete bullet_;
				return true;
			}
			return false;
		});
		Move();
		Attack();
		for (PlayerBullet* bullet_ : bullets_) {
			bullet_->Update();
		}

		worldTransform_.UpdateMatrix();
	}
}

void Player::Draw(Camera& camera) { 
	if (!isDead_) {

		model_->Draw(worldTransform_, camera);
	}
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

void Player::Move() {
	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトル
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	// 移動限界座標
	/*const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 18.0f;*/

	worldTransform_.translation_ += move;
}

void Player::OnCollision() { hp -= 10; }

KamataEngine::Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド座標を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

KamataEngine::Vector3 Player::GetWorldRotate() { return worldTransform_.rotation_; }

void Player::SetParent(const KamataEngine::WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
