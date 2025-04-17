#pragma once
#include <KamataEngine.h>
#include"Particle.h"




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

	//パーティクル3Dモデルデータ
	KamataEngine::Model* modelParticle_ = nullptr;
	//カメラ
	KamataEngine::Camera camera_;
	//パーティクル
	Particle* particle_ = nullptr;

	
};
