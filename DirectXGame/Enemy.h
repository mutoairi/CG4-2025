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
	void OnCollision();
	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();
	float GetRadius() { return radius_; }
	float GetHp() { return hp; }
	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	KamataEngine::ModelProject* model_ = nullptr;
	KamataEngine::ModelProject* model2 = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Vector2 velocity_ = {0.5f, 0.5f};

	// 発射タイマー
	int32_t shotTimer_ = 0;
	//自キャラ
	Player* player_ = nullptr;
	float radius_ = 10.0f;
	bool isDead = false;
	GameScene* gameScene_ = nullptr;
	float hp = 500;
};
