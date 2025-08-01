#pragma once
#include "KamataEngine.h"
class NumberCount {
public:
	~NumberCount();
	void Initialize();

	void Update();

	void Draw();

private:
	KamataEngine::Vector2 size = {32.0f, 64.0f};
	uint32_t textureHandle_ = 0;
	KamataEngine::Sprite* sprite_[5];
	int number = 0;
};
