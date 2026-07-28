#include "NumberCount.h"
using namespace KamataEngine;
NumberCount::~NumberCount() {
	for (int i = 0; i < 5; i++) {
		delete sprite_[i];
	}
}

void NumberCount::Initialize() {
	textureHandle_ = TextureManager::Load("number.dds");

	for (int i = 0; i < 5; i++) {
		sprite_[i] = Sprite::Create(textureHandle_, {100.0f + size.x * i, 5});
		sprite_[i]->SetSize(size);
	}
}

void NumberCount::Update() {
	if (number < 10000) {
		number++;
	}

	int32_t tempNumber = number; // オリジナルのnumberを壊さない

	int32_t digit = 10000; // 5桁表示なら10000

	for (int i = 0; i < 5; i++) {
		int nowNumber = tempNumber / digit;
		sprite_[i]->SetTextureRect({size.x * nowNumber, 0}, size);
		tempNumber %= digit;
		digit /= 10;
	}
}

void NumberCount::Draw() {
	for (int i = 0; i < 5; i++) {
		sprite_[i]->Draw();
	}
}
