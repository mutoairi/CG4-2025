
#pragma once
#include "Effect.h"
#include "Graph.h"
#include "ModelProject.h"
#include "Particle.h"
#include "Player.h"
#include "Stage.h"

#include <KamataEngine.h>

class GameScene {
public:
	~GameScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsFinished() { return finished_; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	int32_t texture_ = 0u;
	KamataEngine::ModelProject* model_ = nullptr;
	KamataEngine::ModelProject* playerModel = nullptr;
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
	// Graph
	Graph* graph_ = nullptr;

	bool isDebugCameraActive_ = false;
	bool finished_ = false;
};
