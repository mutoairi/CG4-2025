#pragma once
#include <KamataEngine.h>
class Effect {
public:
	void Initialize(
	    KamataEngine::Model* model, KamataEngine::Vector3 scale, KamataEngine::Vector3 rotation, KamataEngine::Vector3 possition, KamataEngine::Vector3 velocity, KamataEngine::Vector4 color);
	void Update();
	void Draw(KamataEngine::Camera&);
	bool GetDeathFlag() { return isFinished_; }

private:
	KamataEngine::WorldTransform wordTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Vector3 scale_;
	KamataEngine::Vector3 velocity_;
	/*存続時間*/
	static inline const float kDuration = 0.5f;
	/*終了フラグ*/
	bool isFinished_ = false;
	/*カウンター*/
	float count_ = 0.0f;
	/*カラー*/
	KamataEngine::ObjectColor objectColor;
	KamataEngine::Vector4 color_;
};
