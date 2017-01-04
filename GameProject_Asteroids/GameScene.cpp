#include "GUI.h"
#include "System.h"
#include "Logger.h"
#include "GameScene.h"
using namespace Logger;



GameScene::GameScene(void) {
	player = new Player(Vector2D(500, 500), 30, 39);
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry(void) {
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {

	static MouseCoords mouseCoords(0, 0);
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>())exit(0);
	float caca = 0;
	if (TM.GetDeltaTime() > 0) {
		caca = TM.GetDeltaTime();
	}
	player->Update(TM.GetDeltaTime()/100000);
}

void GameScene::Draw(void) {
	player->Draw();
}
