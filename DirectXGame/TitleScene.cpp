#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete titleSprite_;
	delete startSprite_;
}

void TitleScene::Initialize() {
	input_ = Input::GetInstance();
	worldTransform_.Initialize();

	titleTexture_ = TextureManager::Load("title.dds");
	startTexture_ = TextureManager::Load("start.dds");
	backGroundTexture_ = TextureManager::Load("backGround.dds");

	titleSprite_ = Sprite::Create(titleTexture_, {300.0f, 200.0f});
	startSprite_ = Sprite::Create(startTexture_, {20.0f, 70.0f});
	backGroundSprite_ = Sprite::Create(backGroundTexture_, {0, 0});
}

void TitleScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {
		OutputDebugStringA("Space pressed\n");

		finished = true;
	}

	mainTime_ += 0.05f;
	float offsetY = std::sin(mainTime_) * 10.0f;
	titleSprite_->SetPosition({10.0f, 0.0f + offsetY});

	// キーガイドをフェードイン・アウトさせる
	startTime_ += 0.05f;
	float alpha = (std::sin(startTime_) + 1.0f) / 2.0f;
	startSprite_->SetColor({1.0f, 1.0f, 1.0f, alpha});
	input_->Update();
}

void TitleScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());
	backGroundSprite_->Draw();
	titleSprite_->Draw();
	startSprite_->Draw();
	Sprite::PostDraw();
}
