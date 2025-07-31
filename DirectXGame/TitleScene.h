#pragma once
#include <KamataEngine.h>
class TitleScene {
public:
	TitleScene();
	~TitleScene();
	void Initialize();
	void Update();
	void Draw();

private:
	KamataEngine::Sprite* titleSprite_ = nullptr;
	KamataEngine::Sprite* startSprite_ = nullptr;
	uint16_t titleTexture_ = 0u;
	uint16_t startTexture_ = 0u;
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;

};
