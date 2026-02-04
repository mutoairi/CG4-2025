#pragma once
#include<KamataEngine.h>
#include<memory.h>
class Fade {
public:
	enum class State { None, FadeIn, FadeOut };

	void Initialize();
	void Update();
	void Draw();

	void StartFadeIn(float speed = 0.02f);
	void StartFadeOut(float speed = 0.02f);

	bool IsFadeInEnd() const { return (state_ == State::None && alpha_ <= 0.0f); }
	bool IsFadeOutEnd() const { return (state_ == State::None && alpha_ >= 1.0f); }
	bool IsFading() const { return state_ != State::None; }

private:
	State state_ = State::None;
	float alpha_ = 1.0f; // 黒から始まる
	float fadeSpeed_ = 0.02f;

	KamataEngine::Sprite* fadeSprite_ = nullptr;
	uint32_t fadeTexture_ = 0;
};