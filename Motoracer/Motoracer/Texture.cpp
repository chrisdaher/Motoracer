#include <iostream>
#include <sstream>
#include "Texture.h"

namespace
{
  static int _engineId = -1;
  static int _seatId = -1;
  static int _fuelId = -1;
  static int _fireId = -1;
  static int _roadId = -1;
	static int _grassId = -1;
	static int _skyId = -1;
	static int _wallId = -1;
	static int _collectable1Id = -1;
	static int _collectable2Id = -1;
	static int _collectable3Id = -1;
}

namespace Texture
{
  void setEngineId(int id)
  {
    _engineId = id;
  }
  
  int getEngineId() { return _engineId; }

  void setSeatId(int id)
  {
    _seatId = id;
  }

  int getSeatId() { return _seatId; }

  void setFuelId(int id)
  {
    _fuelId = id;
  }

  int getFuelId() { return _fuelId; }

  void setFireId(int id)
  {
    _fireId = id;
  }

  int getFireId() { return _fireId; }

  void setRoadId(int id)
  {
    _roadId = id;
  }

  int getRoadId() { return _roadId; }

	void setGrassId(int id)
  {
    _grassId = id;
  }

  int getGrassId() { return _grassId; }

	void setSkyId(int id)
  {
    _skyId = id;
  }

  int getSkyId() { return _skyId; }

	void setWallId(int id)
  {
    _wallId = id;
  }

  int getWallId() { return _wallId; }

	void setCollectable1Id(int id)
  {
    _collectable1Id = id;
  }

  int getCollectable1Id() { return _collectable1Id; }

	void setCollectable2Id(int id)
  {
    _collectable2Id = id;
  }

  int getCollectable2Id() { return _collectable2Id; }

	void setCollectable3Id(int id)
  {
    _collectable3Id = id;
  }

  int getCollectable3Id() { return _collectable3Id; }
}
