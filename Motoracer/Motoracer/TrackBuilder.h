#include <list>
#include "Track.h"
#include "Collectable.h"
#include "Wall.h"
class TrackBuilder{
public:
	list<Collectable> collectables;
	TrackBuilder();
	Track buildTrack();
	list<Wall> buildWalls();
	void buildCollectables(vector<Point> positions);
};