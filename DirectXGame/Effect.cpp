#include "Effect.h"
#include <cassert>
#include<algorithm>
 using namespace KamataEngine;
 using namespace MathUtility;

void Effect::Initialize(Model* model,Vector3 scale, Vector3 rotation) {
	assert(model);
	model_ = model;
	scale_ = scale;
	objectColor.Initialize();
	color = {1.0f, 1.0f, 1.0f, 1.0f};

	wordTransform_.Initialize();
	wordTransform_.scale_ = scale;
	wordTransform_.rotation_ = rotation;
}

void Effect::Update() {
	//終了なら早期リターン
	if (isFinished_) {
		return;
	}
	//カウンターを1フレーム分の秒数進める
	count_ += 1.0f / 60.0f;
	if (count_ >= kDuration) {
		count_ = kDuration;
		isFinished_ = true;
	}
	
	wordTransform_.scale_.y -= 0.05f;
	
	color.w = std::clamp(1.0f - count_ / kDuration, 0.0f, 1.0f);
	objectColor.SetColor(color);
	// 時間の割合（0.0 ～ 1.0）
	float t = count_ / kDuration;

	// スムーズステップ（ふわっと感）
	float eased = t * t * (3 - 2 * t); // 0 → 1 の曲線
	// スケールを徐々に小さく
	float scaleFactor = std::clamp(1.0f - eased, 0.0f, 1.0f);
	wordTransform_.scale_ = scale_ * scaleFactor; // ←初期スケール保持してね！
	wordTransform_.UpdateMatrix();
}

void Effect::Draw(Camera& camera) { 
	model_->Draw(wordTransform_, camera,&objectColor);
}
