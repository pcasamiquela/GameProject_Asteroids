
#pragma once
#include "Scene.h"
#include "Button.h"
#include "Constants.h"
#include "Player.h"
#include "AsteroidsManager.h"
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
	int m_score{ 0 };
	Player* player;
	AsteroidsManager* asteroidsManager;
};