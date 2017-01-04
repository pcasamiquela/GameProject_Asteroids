#pragma once
#include "Scene.h"
#include "Button.h"
#include "Constants.h"
#include "Sprite.h"
#include "GameScene.h"

class MenuScene : public Scene{
public:
	explicit MenuScene();
	~MenuScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Button playButton;
	Button rankingButton;
	Button exitButton;
	Button easyButton;
	Button mediumButton;
	Button hardButton;
	Button backButton;
	int m_score{ 0 };
	enum State {
		MAIN_MENU, 
		RANKING_MENU,
		DIFFICULTY_MENU,
	};
	State currentState;

};

