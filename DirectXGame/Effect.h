#pragma once
#include <KamataEngine.h>
class Effect {
public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Vector3 scale,KamataEngine::Vector3 rotation);
	void Update();
	void Draw(KamataEngine::Camera&);

private:
	KamataEngine::WorldTransform wordTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Vector3 scale_;
	/*存続時間*/
	static inline const float kDuration = 2.0f;
	/*終了フラグ*/
	bool isFinished_ = false;
	/*カウンター*/
	float count_ = 0.0f;
	/*カラー*/
	KamataEngine::ObjectColor objectColor;
	KamataEngine::Vector4 color;
};
