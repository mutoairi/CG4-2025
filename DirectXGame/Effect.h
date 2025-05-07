#pragma once
#include "KamataEngine.h"
class Effect {
public:
	void Initialize(KamataEngine::Model* model);
	void Update();
	void Draw();

private:
	KamataEngine::WorldTransform wordTransform_;
	KamataEngine::Model* model_ = nullptr;
};
