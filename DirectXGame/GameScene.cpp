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
	delete stage_;
	delete playerModel;
	delete player_;
	delete graph_;
	delete number_;
	for (EnemyBullet* bullet_ : bullets_) {
		delete bullet_;
	}
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	worldTransform_.Initialize();
	ModelProject::StaticInitialize();
	
	texture_ = TextureManager::Load("uvChecker.dds");
	model_ = ModelProject::CreateRing(32);
	stage_ = new Stage();
	stage_->Initialise();
	// カメラの初期化
	camera_.Initialize();

	playerModel = ModelProject::CreateFromOBJ("player", true);
	player_ = new Player();
	player_->Initialize(playerModel, input_);
	enemyModel = ModelProject::CreateFromOBJ("player", true);
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel);
	enemy_->SetGameScene(this);
	/*敵キャラに自キャラのアドレスを渡す*/
	enemy_->SetPlayer(player_);

	graph_ = new Graph();
	graph_->initialize();
	graph_->Sethp(player_->GetHp());

	number_ = new NumberCount();
	number_->Initialize();
	debugCamera_ = new DebugCamera(1280, 720);

	// 乱数の初期化
	srand((unsigned)time(NULL));
}

void GameScene::Update() {
	if (input_->TriggerKey(DIK_ESCAPE)) {
		finished_ = true;
	}

	if (input_->TriggerKey(DIK_D)) {
		if (!isDebugCameraActive_) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}

	if (isDebugCameraActive_) {

		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;

		camera_.TransferMatrix();
	} else {
		camera_.TransferMatrix();
	}
	stage_->Update();
	player_->Update();
	enemy_->Update();
	graph_->Update();
	number_->Update();
}

void GameScene::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	stage_->Draw();
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
	/// model_->Draw(worldTransform_, camera_, texture_);
	player_->Draw(camera_);
	enemy_->Draw(camera_);

	/// </summary>

	// 3Dオブジェクト描画後処理
	ModelProject::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	graph_->Draw();
	//number_->Draw();
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
void GameScene::CheckAllCollision() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	const std::list<EnemyBullet*>& enemyBullets = bullets_;

	//=========================
	//
	// 自キャラと敵弾
	//
	// ========================

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();
		// posAとposBの距離
		float posC = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

		// 半径の差
		float L = (player_->GetRadius() + bullet->GetRadius()) * (player_->GetRadius() + bullet->GetRadius());
		// 球と球の交差判定
		if (posC <= L) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

	//===========================
	//
	// 自弾と敵キャラ
	//
	//============================

	
		for (PlayerBullet* bullet : playerBullets) {

			// 敵キャラの座標
			posA = enemy_->GetWorldPosition();
			posB = bullet->GetWorldPosition();

			// posAとposBの距離
			float posD = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

			// 半径の差
			float M = (enemy_->GetRadius() + bullet->GetRadius()) * (enemy_->GetRadius() + bullet->GetRadius());
			// 球と球の交差判定
		    if (posD <= M) {
			    // 自キャラの衝突時コールバックを呼び出す
			    enemy_->OnCollision();
			    // 敵弾の衝突時コールバックを呼び出す
			    bullet->OnCollision();
		    }
		}
	}
	void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { bullets_.push_back(enemyBullet); }