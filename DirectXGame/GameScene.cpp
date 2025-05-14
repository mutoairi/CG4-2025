#include "GameScene.h"
#include <cassert>
#include <random>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distrubution(-1.0f, 1.0f);
std::uniform_real_distribution<float> scaleDistrubution(0.0f, 5.0f);
std::uniform_real_distribution<float> rotationDistrubution(0.0f, 3.14f);

GameScene::~GameScene() {

	// 3Dモデルデータの解放
	delete modelParticle_;
	delete modelEffect_;
	for (Particle* particle_ : particles_) {
		// パーティクル解放
		delete particle_;
	}
	particles_.clear();
	for (Effect* effect : effects_) {
		delete effect;
	}
	effects_.clear();
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	modelParticle_ = Model::CreateSphere(4, 4);

	modelEffect_ = Model::CreateFromOBJ("efect", true);

	for (int i = 0; i < 10; i++) {
		Effect* effect = new Effect();
		// エフェクトの初期化
		Vector3 scale;
		scale = {0.3f, scaleDistrubution(randomEngine), 1.0f};
		Vector3 rotation;
		rotation = {0.0f, 0.0f, rotationDistrubution(randomEngine)};

		effect->Initialize(modelEffect_, scale, rotation);
		effects_.push_back(effect);
	}
	// カメラの初期化
	camera_.Initialize();

	// 乱数の初期化
	srand((unsigned)time(NULL));
}

void GameScene::Update() {

	//---パーティクル----

	//// 確率で発生
	// if (rand() % 20 == 0) {

	//	/*位置*/
	//	Vector3 position = {distrubution(randomEngine) * 30.0f, distrubution(randomEngine) * 20.0f, 0.0f};

	//	/*パーティクルの生成*/
	//	ParticleBorn(position);
	//}
	// for (Particle* particle_ : particles_) {
	//	// パーティクル
	//	particle_->Update();
	//}
	//// 終了フラグのたったパーティクルを削除
	// particles_.remove_if([](Particle* particle) {
	//	if (particle->GetDeathFlag()) {
	//		delete particle;
	//		return true;
	//	}
	//	return false;
	// });

	// Effect
	for (Effect* effect : effects_) {
		effect->Update();
	}
}

void GameScene::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///

	// for (Particle* particle_ : particles_) {
	//	/*パーティクル*/
	//	particle_->Draw(camera_);
	// }
	for (Effect* effect : effects_) {
		effect->Draw(camera_);
	}
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// void GameScene::ParticleBorn(Vector3 position1) {
//	for (int i = 0; i < 150; i++) {
//
//		/*生成*/
//		Particle* particle_ = new Particle();
//
//		/*移動量*/
//		Vector3 velocity = {distrubution(randomEngine), distrubution(randomEngine), 0.0f};
//		Normalize(velocity);
//		velocity *= distrubution(randomEngine);
//		velocity *= 1.0f;
//		/*初期化*/
//		particle_->Initialize(modelParticle_, position1, velocity);
//		// リストに追加
//		particles_.push_back(particle_);
//	}
// }
