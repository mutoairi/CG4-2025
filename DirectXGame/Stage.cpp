#include "Stage.h"
using namespace KamataEngine;
Stage::Stage() {}

Stage::~Stage() {
	delete backGroundSprite_;
	delete backGround2Sprite_;
}

void Stage::Initialise() {
	backGroundTexture_ = TextureManager::Load("sea.dds");
	backGround2Texture_ = TextureManager::Load("sea.dds");
	backGroundSprite_ = Sprite::Create(backGroundTexture_, {pos[0], 0.0f});
	backGround2Sprite_ = Sprite::Create(backGround2Texture_, {pos[1], 0.0f});
}

void Stage::Update() {
	backGroundSprite_->SetSize({1300.0f, 1000.0f});
	backGround2Sprite_->SetSize({1300.0f, 1000.0f});
	for (int i = 0; i < 2; ++i) {
		pos[i] -= moveSpeed_;

		if (pos[i] < -1280.0f) {
			pos[i] = 1280.0f;
		}
	}

	backGroundSprite_->SetPosition({pos[0], 0.0f});
	backGround2Sprite_->SetPosition({pos[1], 0.0f});
}

void Stage::Draw() {
	backGroundSprite_->Draw();
	backGround2Sprite_->Draw();
}