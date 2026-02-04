#pragma once
#include "KamataEngine.h"

class Graph {
public:
	~Graph();
	void initialize();

	void Update();

	void Draw();
	void SetFlag(bool hit) { Flag = hit; }

private:
	uint32_t graphTextureHandle1_ = 0;
	uint32_t graphTextureHandle2_ = 0;

	KamataEngine::Sprite* graphSprite1_ = nullptr;
	KamataEngine::Sprite* graphSprite2_ = nullptr;
	bool Flag = false;
	float max = 300.0f;
};
