#ifndef TEXTURE_NAMESPACE
#define TEXTURE_NAMESPACE

namespace Texture
{
  void setEngineId(int id);
  void setSeatId(int id);
  void setFuelId(int id);
  void setFireId(int id);
  void setRoadId(int id);
	void setGrassId(int id);
	void setSkyId(int id);
	void setWallId(int id);
	void setCollectable1Id(int id);
	void setCollectable2Id(int id);
	void setCollectable3Id(int id);

  int getEngineId();
  int getSeatId();
  int getFuelId();
  int getFireId();
  int getRoadId();
	int getGrassId();
	int getSkyId();
	int getWallId();
	int getCollectable1Id();
	int getCollectable2Id();
	int getCollectable3Id();
};

#endif
