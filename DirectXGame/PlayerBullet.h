#pragma once
#include"KamataEngine.h"
#include"ModelProject.h"
class PlayerBullet {

public:
	void Initialize(KamataEngine::ModelProject* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity);
	void Update();
	void Draw(const KamataEngine::Camera& camera);
	bool IsDead() const { return isDead_; }
	void OnCollision();
	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();
	float GetRadius() { return radius_; }

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::ModelProject* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Vector3 velocity_;
	uint32_t texture_ = 0u;
	// 寿命
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
	// 半径
	float radius_ = 1.0f;
};
