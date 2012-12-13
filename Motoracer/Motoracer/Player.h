#ifndef player_class
#define player_class
#include "Bike.h"
#include "Point.h"
#include "Collectable.h"

class Player{
private:
	int playerIndex;
	void initPlayer(Point& position, Point& direction);
	int lapTime;
public:
	Bike* bike;
	Collectable* currentCollectable;
	int collectableTimeLeft;
	int currentLap;
	int bestLap;
	int finishTime;
	bool isWinner;
	bool isDone;
	Camera* camera;
	Player();
	Player(Point position, Point direction);
	void handleKeyboard(unsigned char key, bool keyUp=false);
	void handleSpecial(int key, bool keyUp=false);
	void renderView();
	void draw();
	void DrawHud();
	bool checkLapping(Point lappos);
	void doEffect(Collectable c);
	void undoEffect();
};
#endif