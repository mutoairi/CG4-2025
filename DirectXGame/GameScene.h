
#pragma once
#include "Effect.h"
#include "ModelProject.h"
#include "Particle.h"
#include <KamataEngine.h>

class GameScene {
public:
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	int32_t texture_ = 0u;
	KamataEngine::ModelProject* model_ = nullptr;
	// カメラ
	KamataEngine::Camera camera_;
	// パーティクル
	std::list<Particle*> particles_;
	// エフェクト
	std::list<Effect*> effects_;
};
