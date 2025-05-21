#include "Effect.h"
#include <algorithm>
#include <cassert>
using namespace KamataEngine;
using namespace MathUtility;

void Effect::Initialize(Model* model, Vector3 scale, Vector3 rotation, Vector3 possition, Vector3 velocity, Vector4 color) {
	assert(model);
	model_ = model;
	scale_ = scale;
	velocity_ = velocity;
	objectColor.Initialize();
	color_ = color;

	wordTransform_.Initialize();
	wordTransform_.scale_ = scale;
	wordTransform_.rotation_ = rotation;
	wordTransform_.translation_ = possition;
}

void Effect::Update() {
	// 終了なら早期リターン
	if (isFinished_) {
		return;
	}
	// カウンターを1フレーム分の秒数進める
	count_ += 1.0f / 60.0f;
	if (count_ >= kDuration) {
		count_ = kDuration;
		isFinished_ = true;
	}

	color_.w = std::clamp(1.0f - count_ / kDuration, 0.0f, 1.0f);
	objectColor.SetColor(color_);
	wordTransform_.translation_ += velocity_;
	wordTransform_.rotation_.z += 0.1f;
	wordTransform_.scale_ += {0.0f, 0.5f, 0.0f};
	// ←初期スケール保持してね！
	wordTransform_.UpdateMatrix();
}

void Effect::Draw(Camera& camera) { model_->Draw(wordTransform_, camera, &objectColor); }
