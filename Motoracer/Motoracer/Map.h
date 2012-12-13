#ifndef map_class
#define map_class
#include <list>
#include "Track.h"
#include "Player.h"
#include "Collectable.h"
#include "Wall.h"
class Map{
private:
	Track track;
	Player player1;
	Player player2;
	list<Collectable> collectables;
	Point Lappos;
	list<Wall> walls;
public:
	Map();
	static int laps;
	static int currentTime;
	void idle();
	void handleKeyboard(unsigned char key, bool keyUp = false);
	void handleSpecial(int key, bool keyUp=false);
	void Draw();
	void renderPlayer1();
	void renderPlayer2();
	void displayMap();
	void checkLapping();
	void reset();
};
#endif