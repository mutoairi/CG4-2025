#include "Fade.h"
#include<cassert>

void Fade::Initialize() {
	fadeTexture_ = KamataEngine::TextureManager::Load("white1x1.png"); // 白1x1画像を用意
	fadeSprite_ = KamataEngine::Sprite::Create(fadeTexture_, {0, 0});

	alpha_ = 1.0f; // 最初は真っ黒
	state_ = State::FadeIn;
}

void Fade::Update() {
	switch (state_) {
	case State::FadeIn:
		alpha_ -= fadeSpeed_;
		if (alpha_ <= 0.0f) {
			alpha_ = 0.0f;
			state_ = State::None;
		}
		break;

	case State::FadeOut:
		alpha_ += fadeSpeed_;
		if (alpha_ >= 1.0f) {
			alpha_ = 1.0f;
			state_ = State::None;
		}
		break;
	default:
		break;
	}
}

void Fade::Draw() {
	if (alpha_ <= 0.0f)
		return;

	KamataEngine::DirectXCommon* dxCommon = KamataEngine::DirectXCommon::GetInstance();
	KamataEngine::Sprite::PreDraw(dxCommon->GetCommandList());

	fadeSprite_->SetPosition({0, 0});
	fadeSprite_->SetSize({1280, 720});        // 画面全体に表示
	fadeSprite_->SetColor({0, 0, 0, alpha_}); // 黒フェード
	fadeSprite_->Draw();

	KamataEngine::Sprite::PostDraw();
}

void Fade::StartFadeIn(float speed) {
	fadeSpeed_ = speed;
	state_ = State::FadeIn;
}

void Fade::StartFadeOut(float speed) {
	fadeSpeed_ = speed;
	state_ = State::FadeOut;
}
