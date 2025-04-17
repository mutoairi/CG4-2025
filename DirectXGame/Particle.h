#pragma once
#include <KamataEngine.h>

class Particle {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3, KamataEngine::Vector3);
	// 更新
	void Update();
	// 描画
	void Draw(KamataEngine::Camera& camera);

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;
	// 移動量
	KamataEngine::Vector3 velocity_;
};
