#pragma once
#include "gameNode.h"
#include "Bird.h"
#include "Elder.h"
#include "Elle.h"
#include "TownHuman.h"
#include "randomFunction.h"

class npcManager : public gameNode
{
private:
	//²¿²¿
	vector<Bird*> _vBird;
	vector<Bird*>::iterator _viBird;

	vector<Elder*> _vElder;
	vector<Elder*>::iterator _viElder;

	vector<Elle*> _vElle;
	vector<Elle*>::iterator _viElle;

	vector<TownHuman*> _vTownHuman;
	vector<TownHuman*>::iterator _viTownHuman;

	randomFunction* _randomFunction;
	
	int _aiStatePatten;
	int _aiIdleActionPatten;
	int _aiDirectionPatten;
	int _aiStatePattenOldTime;

	bool _randCheck;

public:
	npcManager();
	~npcManager();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);

	void setBird();
	void setElder();
	void setElle();
	void setTownHuman(TOWNHUMAN townHumanName, float x, float y);

	void aiBirdUpdate();
	void aiElderUpdate();

public:
	vector<Bird*> getVBird() { return _vBird; }
	vector<Bird*>* setVBird() { return &_vBird; }

	vector<Elder*> getVElder() { return _vElder; }
	vector<Elder*>* setVElder() { return &_vElder; }

	vector<Elle*> getVElle() { return _vElle; }
	vector<Elle*>* setVElle() { return &_vElle; }

	vector<TownHuman*> getVTownHuman() { return _vTownHuman; }
	vector<TownHuman*>* setVTownHuman() { return &_vTownHuman; }
};

