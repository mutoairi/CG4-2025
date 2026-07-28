#include "Enemy.h"
#include <cassert>
#include <numbers>
#include"GameScene.h"
#include"Player.h"
using namespace KamataEngine;
using namespace MathUtility;
void Enemy::Initialize(KamataEngine::ModelProject* model) {
	assert(model);
	model_ = model;
	ApproachInitialize();
	worldTransform_.Initialize();
	worldTransform_.rotation_.y += float(std::numbers::pi)/-2.0f ;
	worldTransform_.rotation_.z = 0.0f;
	worldTransform_.translation_.z -= 30;
	worldTransform_.translation_.y = 0.0f;
	worldTransform_.translation_.x = 5.0f;
	worldTransform_.scale_ = {10.0f, 10.0f, 10.0f};
}

void Enemy::Update() {
	if (hp <= 0) {
		isDead = true;
	}
	if (!isDead) {
		Approach();
		worldTransform_.UpdateMatrix();
		Fire();
	}
}

void Enemy::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

void Enemy::Approach() {
	

	// 発射タイマーカウントダウン
	shotTimer_--;
	// 指定時間に達した
	if (shotTimer_ < 0) {
		Fire();
		shotTimer_ = kFireInterval;
	}
	
}

void Enemy::Fire() {
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 0.7f;
	KamataEngine::Vector3 velocity(0, 0, kBulletSpeed);
	// 自キャラの座標
	KamataEngine::Vector3 playerWorldPos = player_->GetWorldPosition();
	// 敵キャラの座標
	KamataEngine::Vector3 enemyWorldPos = {worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]};

	KamataEngine::Vector3 differentialV = playerWorldPos - enemyWorldPos;

	velocity = Normalize(differentialV);
	velocity* kBulletSpeed;
	// 弾を生成し初期
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾を登録する
	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::ApproachInitialize() {
	// 発射タイマー初期化
	shotTimer_ = kFireInterval;
}

void Enemy::OnCollision() { hp -= 10; }

KamataEngine::Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド座標を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}