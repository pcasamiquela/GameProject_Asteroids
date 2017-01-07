
#pragma once
#include "Scene.h"
#include "Button.h"
#include "Constants.h"
#include "Player.h"
#include "AsteroidsManager.h"
#include "MenuScene.h"
#include <XML\rapidxml.hpp>
#include <sstream>

#define MAX_ASTEROIDS 5

// GameScene class with the main gameplay mode
class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Button easyButton;
	Button mediumButton;
	Button hardButton;
	Button backButton;
	Button mouseControl;
	Button keyboardControl;
	Button continueButton;
	Button exitButton;

	//Level Attributes
	int numAsteroids;
	float asteroidsVelocity;
	float incrementalSpeed;

	int playerLifes;

	void Setup();
	void ReadFromFile(std::string path);

	bool inGameMenu;

	Player* player;

	AsteroidsManager* asteroidsManager;
	Sprite lifeCounter;
	enum State {
		PLAY,
		DIFFICULTY_MENU,
		CONTROL_MENU,
	};
	State currentState;
};