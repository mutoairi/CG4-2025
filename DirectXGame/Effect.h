#pragma once
#include <KamataEngine.h>
class Effect {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 scale, KamataEngine::Vector3 rotation, KamataEngine::Vector3 possition);
	void Update();
	void Draw(KamataEngine::Camera&);
	bool GetDeathFlag() { return isFinished_; }

private:
	KamataEngine::WorldTransform wordTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Vector3 scale_;
	/*存続時間*/
	static inline const float kDuration = 0.5f;
	/*終了フラグ*/
	bool isFinished_ = false;
	/*カウンター*/
	float count_ = 0.0f;
	/*カラー*/
	KamataEngine::ObjectColor objectColor;
	KamataEngine::Vector4 color;
};
