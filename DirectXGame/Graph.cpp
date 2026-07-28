#include "Graph.h"
using namespace KamataEngine;
Graph::~Graph() {
	delete graphSprite1_;
	delete graphSprite2_;
}

void Graph::initialize() {

	graphTextureHandle1_ = TextureManager::Load("red.dds");
	graphTextureHandle2_ = TextureManager::Load("green.dds");

	graphSprite1_ = Sprite::Create(graphTextureHandle1_, {100.0f, 100.0f});
	graphSprite2_ = Sprite::Create(graphTextureHandle2_, {100.0f, 100.0f});

	graphSprite1_->SetSize({300.0f, 48.0f});
	graphSprite1_->SetColor({1.0f, 1.0f, 1.0f, 0.8f});
	graphSprite2_->SetSize({300.0f, 48.0f});
	graphSprite2_->SetColor({1.0f, 1.0f, 1.0f, 0.8f});
}

void Graph::Update() {
	
	graphSprite2_->SetSize({max, 48.0f});
}

void Graph::Draw() {
	graphSprite1_->Draw();
	graphSprite2_->Draw();
}
