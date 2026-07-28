
#pragma once
#include "Effect.h"
#include "Graph.h"
#include "ModelProject.h"
#include "NumberCount.h"
#include "Particle.h"
#include "Player.h"
#include "Stage.h"
#include"Enemy.h"
#include"EnemyBullet.h"


#include <KamataEngine.h>

class GameScene {
public:
	~GameScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsFinished() { return finished_; }
	void AddEnemyBullet(EnemyBullet* enemyBullet);
	// 衝突判定と応答
	void CheckAllCollision();
	
	
	

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	int32_t texture_ = 0u;
	KamataEngine::ModelProject* model_ = nullptr;
	KamataEngine::ModelProject* playerModel = nullptr;
	KamataEngine::ModelProject* enemyModel = nullptr;
	// カメラ
	KamataEngine::Camera camera_;
	// パーティクル
	std::list<Particle*> particles_;
	// エフェクト
	std::list<Effect*> effects_;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	// ステージ
	Stage* stage_ = nullptr;
	// プレイヤー
	Player* player_ = nullptr;
	//エネミー
	Enemy* enemy_ = nullptr;
	// Graph
	Graph* graph_ = nullptr;

	// number
	NumberCount* number_ = nullptr;

	bool isDebugCameraActive_ = false;
	bool finished_ = false;
	std::list<EnemyBullet*> bullets_;
	//std::list<Enemy*> enemys_;



	
	
	
	/*bool waitFlag = false;
	int32_t waitTimer;*/
};
