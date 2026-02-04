#include "GameScene.h"
#include "TitleScene.h"
#include"Fade.h"
#include <KamataEngine.h>
#include <Windows.h>

using namespace KamataEngine;

enum class Scene {
	kUnkown = 0,

	kTitle,
	kGame,
};

Scene scene = Scene::kUnkown;
GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;
Fade* fade = nullptr;
bool isChanging = false;
Input* input = nullptr;
// シーン切り替え
void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kGame;
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene();
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene();
			titleScene->Initialize();
		}
		break;
	}
}
// シーンの更新
void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	}
}
// シーンの描画
void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	}
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3C_25_ムトウ_アイリ_CG4");
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// ゲームシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();
	// 最初のシーンの初期化
	scene = Scene::kTitle;
	fade = new Fade();
	fade->Initialize();
	// メインループ
	while (true) {

		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		if (!isChanging) {
			if (scene == Scene::kTitle && titleScene->IsFinished()) {
				fade->StartFadeOut(0.03f);
				isChanging = true;
			} else if (scene == Scene::kGame && gameScene->IsFinished()) {
				fade->StartFadeOut(0.03f);
				isChanging = true;
			}
		} else {
			// フェードアウト完了時に一度だけ切り替え
			if (fade->IsFadeOutEnd()) {
				ChangeScene();
				fade->StartFadeIn(0.03f);
				isChanging = false;
			}
		}

		// 現在シーン更新
		UpdateScene();
		fade->Update();
		// 描画開始
		dxCommon->PreDraw();
		// 現在シーンの描画
		DrawScene();
		fade->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}
	// 各種解放
	delete titleScene;
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	// エンジンの終了処理
	KamataEngine::Finalize();
	return 0;
}
