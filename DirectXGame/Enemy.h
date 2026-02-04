#pragma once
#include "KamataEngine.h"
#include "ModelProject.h"
#include "EnemyBullet.h"
class Player;
class GameScene;
class Enemy {
public:
	void Initialize(KamataEngine::ModelProject* model);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	void Fire();
	void Approach();
	void ApproachInitialize();
	// 発射間隔
	static const int kFireInterval = 60;

private:
	KamataEngine::ModelProject* model_ = nullptr;
	KamataEngine::ModelProject* model2 = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Vector2 velocity_ = {0.5f, 0.5f};

	// 発射タイマー
	int32_t shotTimer_ = 0;
	//自キャラ
	Player* player_ = nullptr;
	float radius_ = 1.0f;
	bool isDead = false;
	GameScene* gameScene_ = nullptr;
};
