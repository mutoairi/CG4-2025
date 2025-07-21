#include "GameScene.h"
#include <cassert>
#include <random>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distrubution(-1.0f, 1.0f);
std::uniform_real_distribution<float> scaleDistrubution(0.0f, 6.0f);
std::uniform_real_distribution<float> rotationDistrubution(0.0f, 360.0f);
std::uniform_real_distribution<float> colorDistrubution(0.0f, 4.0f);

GameScene::~GameScene() {

	for (Particle* particle_ : particles_) {
		// パーティクル解放
		delete particle_;
	}
	particles_.clear();
	for (Effect* effect : effects_) {
		delete effect;
	}
	effects_.clear();
	ModelProject::StaticFinalize();
	delete model_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	worldTransform_.Initialize();
	ModelProject::StaticInitialize();
	texture_ = TextureManager::Load("uvChecker.png");
	model_ = ModelProject::CreateRing(32);

	// カメラの初期化
	camera_.Initialize();

	// 乱数の初期化
	srand((unsigned)time(NULL));
}

void GameScene::Update() {}

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
	ModelProject::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///
	model_->Draw(worldTransform_, camera_, texture_);

	/// </summary>

	// 3Dオブジェクト描画後処理
	ModelProject::PostDraw();
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
