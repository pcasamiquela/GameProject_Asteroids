#include "GameEngine.h"
#include "Constants.h"

// Game constants


int main(int argc, char* args[]) {
	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("ASTEROIDS");
	return 0;
}

