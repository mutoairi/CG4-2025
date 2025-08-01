#pragma once
#include "KamataEngine.h"
class Stage {
public:
	Stage();

	~Stage();

	void Initialise();

	void Update();

	void Draw();

private:
	uint32_t backGroundTexture_ = 0;
	uint32_t backGround2Texture_ = 0;

	KamataEngine::Sprite* backGroundSprite_ = nullptr;
	KamataEngine::Sprite* backGround2Sprite_ = nullptr;

	float moveSpeed_ = 1.0f;

	float pos[2] = {{0.0f}, {1280.0f}};
};
