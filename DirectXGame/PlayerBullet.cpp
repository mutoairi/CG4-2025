#include "PlayerBullet.h"
using namespace KamataEngine;
using namespace MathUtility;

void PlayerBullet::Initialize(KamataEngine::ModelProject* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity) {
	// NULLポインタチェック
	// assert(model);

	model_ = model;
	// テクスチャ読み込み
	texture_ = TextureManager::Load("uvChecker.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void PlayerBullet::Update() {
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	// 座標を移動させる
	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const KamataEngine::Camera& camera) { model_->Draw(worldTransform_, camera, texture_); }

void PlayerBullet::OnCollision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド座標を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
