#include "GUI.h"
#include "System.h"
#include "Logger.h"
#include "GameScene.h"
using namespace Logger;



GameScene::GameScene(void) :	easyButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.5f + 50, SCREEN_WIDTH*0.27f, SCREEN_HEIGHT*0.12f, string("EASY")),
								mediumButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.97f + 50, SCREEN_WIDTH*0.27f, SCREEN_HEIGHT*0.12f, string("MEDIUM")),
								hardButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.6f + 50, SCREEN_WIDTH*0.27f, SCREEN_HEIGHT*0.12f, string("HARD")),
								backButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.4f + 50, SCREEN_WIDTH*0.27f, SCREEN_HEIGHT*0.12f, string("BACK")),
								continueButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.5f + 50, SCREEN_WIDTH*0.27f, SCREEN_HEIGHT*0.12f, string("CONTINUE")),
								exitButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.97f + 50, SCREEN_WIDTH*0.27f, SCREEN_HEIGHT*0.12f, string("EXIT")){
	currentState = DIFFICULTY_MENU;
}


void GameScene::Setup() {
	player = new Player(Vector2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 30, 39, playerLifes);
	asteroidsManager = new AsteroidsManager(numAsteroids, *player, asteroidsVelocity, incrementalSpeed, targetLevelAsteroid);
	ovniManager = new OvniManager(*player, ovniSpeed, ovniSpawnTime);
	inGameMenu = false;
}

GameScene::~GameScene(void) {
	//delete[] player;
	//delete[] asteroidsManager;
}

void GameScene::OnEntry(void) {
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {
	
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
	}
	else mouseCoords.x = 0;

	if (!inGameMenu) {
		switch (currentState)
		{
		case PLAY:
			if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>())inGameMenu = true;
			//ovniManager->Update(asteroidsManager->GetLevel());
			asteroidsManager->Update();
			player->Update(TM.GetDeltaTime() / 100000);
			break;

		case DIFFICULTY_MENU:
			if (easyButton.ClickButton(mouseCoords.x, mouseCoords.y)) {
				ReadFromFile("./../res/lvl/easy.xml");
				Setup();
				currentState = PLAY;
			}
			if (mediumButton.ClickButton(mouseCoords.x, mouseCoords.y)) {
				ReadFromFile("./../res/lvl/medium.xml");
				Setup();
				currentState = PLAY;
			}
			if (hardButton.ClickButton(mouseCoords.x, mouseCoords.y)) {
				ReadFromFile("./../res/lvl/hard.xml");
				Setup();
				currentState = PLAY;
			}
			break;
		}
	}
	else {
		if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>())inGameMenu = false;
		if (continueButton.ClickButton(mouseCoords.x, mouseCoords.y)) {
			inGameMenu = false; 
			mouseCoords.x = 0;
		}
		if (exitButton.ClickButton(mouseCoords.x, mouseCoords.y)) exit(0);
		
	}
}



void GameScene::ReadFromFile(std::string path)
{
	rapidxml::xml_document<> doc;
	std::ifstream file(path);
	if (file.is_open()) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		std::cout << "Reading:" << doc.first_node()->name() << "\n";
		rapidxml::xml_node<> *pRoot = doc.first_node();

		for (rapidxml::xml_node<> *pNode = pRoot->first_node("attribute"); pNode; pNode = pNode->next_sibling()) {

			std::cout << pNode->name() << ':' << '\n';
			for (rapidxml::xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {

				std::string attribute = pNodeI->name();
				std::string value = pNodeI->value();

				if (attribute == "velocity")asteroidsVelocity = stof(value, NULL);
				else if (attribute == "numAsteroids") numAsteroids = stof(value, NULL);
				else if (attribute == "incrementalSpeed") incrementalSpeed = stof(value, NULL);
				else if (attribute == "targetLevelAsteroid") targetLevelAsteroid = stof(value, NULL);
				else if (attribute == "ovniSpeed") ovniSpeed = stof(value, NULL);
				else if (attribute == "ovniSpawnTime") ovniSpawnTime = stof(value, NULL);
				else if (attribute == "lifes") playerLifes = stof(value, NULL);
				std::cout << pNodeI->name() << ':' << pNodeI->value() << '\n';
			}
		}
	}
}
void GameScene::Draw(void)
{
	switch (currentState) {
	case PLAY:
		GUI::DrawTextBlended<FontID::HYPERSPACE>(std::to_string(player->score),
		{ 100, 40, 1, 1 },
		{ 255, 255, 255 });

		for (int i = 0; i < player->lifes; i++) {
			lifeCounter = { { 20 + i * 50, 100, 30, 39 }, 0, ObjectID::PLAYER };
			lifeCounter.Draw();
		}

		asteroidsManager->Draw();
		ovniManager->Draw();
		player->Draw();
		if (inGameMenu) {
			GUI::DrawTextBlended<FontID::HYPERSPACE>("PAUSE",
			{ SCREEN_WIDTH / 2 - 75, 135, 2, 2 },
			{ 255, 255, 255 });

			continueButton.Draw();
			exitButton.Draw();
		}
		break;

	case DIFFICULTY_MENU:
		GUI::DrawTextBlended<FontID::HYPERSPACE>("ASTEROIDS",
		{ SCREEN_WIDTH / 2 - 135, 135, 2, 2 },
		{ 255, 255, 255 });
		easyButton.Draw();
		mediumButton.Draw();
		hardButton.Draw();
		break;
	}
}