#pragma once
#include "Scene.h"
#include "Button.h"
#include "Constants.h"
#include "Player.h"
#include "MenuScene.h"

class RankingScene : public Scene{
public:
	RankingScene();
	~RankingScene();
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	std::string name;
	void RequestName();
};

