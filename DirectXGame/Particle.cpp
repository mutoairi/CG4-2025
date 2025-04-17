#include "Particle.h"
using namespace KamataEngine;
void Particle::Initialize(KamataEngine::Model* model) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
}

void Particle::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Particle::Draw(Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera);
}
