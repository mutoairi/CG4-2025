#pragma once
#include <KamataEngine.h>
class TitleScene {
public:
	TitleScene();
	~TitleScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsFinished() const { return finished; }

private:
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Sprite* titleSprite_ = nullptr;
	KamataEngine::Sprite* backGroundSprite_ = nullptr;
	KamataEngine::Sprite* startSprite_ = nullptr;
	uint32_t titleTexture_ = 0;
	uint32_t startTexture_ = 0;
	uint32_t backGroundTexture_ = 0;
	bool finished = false;

	float mainTime_ = 0.0f;
	float startTime_ = 0.0f;
};
