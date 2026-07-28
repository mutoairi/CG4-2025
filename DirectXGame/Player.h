#pragma once
#include "KamataEngine.h"
#include "ModelProject.h"
#include"PlayerBullet.h"
#include<list>
class Player {
public:
	~Player();
	void Initialize(KamataEngine::ModelProject* model, KamataEngine::Input* input);

	void Update();

	void Draw(KamataEngine::Camera& camera);
	void Attack();
	void Move();
	void OnCollision();
	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();
	KamataEngine::Vector3 GetWorldRotate();
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	float GetRadius() { return radius_; }
	void SetParent(const KamataEngine::WorldTransform* parent);
	float GetHp() { return hp; }

private:
	KamataEngine::ModelProject* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Vector2 velocity_ = {0.5f, 0.5f};
	std::list<PlayerBullet*> bullets_;
	bool isHolding_ = false;
	int32_t bulletCount_ = 3;
	int32_t Timer_;
	int32_t interval_ = 10;
	float radius_ = 1.0f;
	bool isDead_ = false;
	float hp = 100;
};
