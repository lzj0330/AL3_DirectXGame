﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {  
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	// 3D xyz
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};//xtz倍率
	worldTransform_.rotation_ = {XMConvertToRadians(45.0f), XMConvertToRadians(45.0f), 0.0f}; // xyz旋转
	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};//xyz平行移动

	//3D
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

}

void GameScene::Update() { 

	debugText_->SetPos(50, 70);
	debugText_->Printf("translation:(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
	  worldTransform_.translation_.z);

	debugText_->SetPos(50, 90);
	debugText_->Printf("rotation:(%f,%f,%f)", 
		worldTransform_.rotation_.x,
		worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);

	debugText_->SetPos(50, 110);
	debugText_->Printf("scale:(%f,%f,%f)",
		worldTransform_.scale_.x,
		worldTransform_.scale_.y,
	  worldTransform_.scale_.z);

}

void GameScene::Draw() {

	// コマンドリストの取得
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
	/// </summary>
	//3Dモデル描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
