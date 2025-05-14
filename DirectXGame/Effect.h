#pragma once
#include "KamataEngine.h"
class Effect {
public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Vector3 scale,KamataEngine::Vector3 rotation);
	void Update();
	void Draw(KamataEngine::Camera&);

private:
	KamataEngine::WorldTransform wordTransform_;
	KamataEngine::Model* model_ = nullptr;
};
