#pragma once
#include "KamataEngine.h"
#include "ModelProject.h"
class Player {
public:
	void Initialize(KamataEngine::ModelProject* model, KamataEngine::Input* input);

	void Update();

	void Draw(KamataEngine::Camera& camera);

private:
	KamataEngine::ModelProject* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Vector2 velocity_ = {0.5f, 0.5f};
};
