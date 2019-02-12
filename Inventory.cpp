#include "stdafx.h"
#include "Inventory.h"


Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

HRESULT Inventory::init()
{
	inventoryReset();



	_weaponCount = 0;
	_accessoryCount = 0;
	_armorCount = 0;



	//무기
	//방어구
	//악세서리
	//물약

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	//아이템 먹었을경우 이동
	itemMove();


	//인벤토리에 담긴 수
	itemCount();


}

void Inventory::render()
{
}

void Inventory::inventoryReset()
{
	//초기화 함수

	//무기
	for (int i = 0; i < 16; ++i)
	{
		_weaponInv[i] = WEAPONTYPE::NONE;
	}

	//방어구
	for (int i = 0; i < 16; ++i)
	{
		_armorInv[i] = ARMORTYPE::NONE;
	}

	//악세서리
	for (int i = 0; i < 32; ++i)
	{
		_accessoryInv[i] = ACCESSORYTYPE::NONE;
	}

	//물약
	for (int i = 0; i < 32; ++i)
	{
		_potionInv[i] = POTIONTYPE::NONE;
	}

	_tempWeapon = WEAPONTYPE::NONE;
	_tempArmor = ARMORTYPE::NONE;
	_tempAccessory = ACCESSORYTYPE::NONE;
	_tempPorion = POTIONTYPE::NONE;
}

void Inventory::itemMove()
{
	//아이템을 먹었다면 (temp에 NONE이 아닌 다른게 있다면) 템프 -> 인벤토리로 이동 후 다시 NONE으로

	//무기
	if (_tempWeapon != WEAPONTYPE::NONE)
	{
		for (int i = 0; i < WEAPON_MAX_ARR; ++i)
		{
			//아무것도 안담겨있다면
			if (_weaponInv[i] == WEAPONTYPE::NONE)
			{
				_weaponInv[i] = _tempWeapon;
			}
			//다른아이템이 담겨있다면
			else
			{
				continue;
			}
		}

		_tempWeapon = WEAPONTYPE::NONE;
	}

	//방어구
	if (_tempArmor != ARMORTYPE::NONE)
	{
		for (int i = 0; i < ARMOR_MAX_ARR; ++i)
		{
			//아무것도 안담겨있다면
			if (_armorInv[i] == ARMORTYPE::NONE)
			{
				_armorInv[i] = _tempArmor;
			}
			//다른아이템이 담겨있다면
			else
			{
				continue;
			}
		}

		_tempArmor = ARMORTYPE::NONE;
	}

	//악세서리
	if (_tempAccessory != ACCESSORYTYPE::NONE)
	{
		for (int i = 0; i < ACCESSORY_MAX_ARR; ++i)
		{
			//아무것도 안담겨있다면
			if (_accessoryInv[i] == ACCESSORYTYPE::NONE && _potionInv[i] == POTIONTYPE::NONE)
			{
				_accessoryInv[i] = _tempAccessory;
			}
			//다른아이템이 담겨있다면
			else
			{
				continue;
			}
		}

		_tempAccessory = ACCESSORYTYPE::NONE;
	}

	//물약
	if (_tempPorion != POTIONTYPE::NONE)
	{
		for (int i = 0; i < POTION_MAX_ARR; ++i)
		{
			//아무것도 안담겨있다면
			if (_potionInv[i] == POTIONTYPE::NONE && _accessoryInv[i] == ACCESSORYTYPE::NONE)
			{
				_potionInv[i] = _tempPorion;
			}
			//다른아이템이 담겨있다면
			else
			{
				continue;
			}
		}

		_tempPorion = POTIONTYPE::NONE;
	}
}

void Inventory::itemCount()
{
	int weaponNum = 0;
	int armorNum = 0;
	int accessoryNum = 0;
	int potionNum = 0;

	//무기
	for (int i = 0; i < WEAPON_MAX_ARR; ++i)
	{
		//다른게 담겨있다면
		if (_weaponInv[i] != WEAPONTYPE::NONE)
		{
			weaponNum++;
		}
	}

	//방어구
	for (int i = 0; i < ARMOR_MAX_ARR; ++i)
	{
		//다른게 담겨있다면
		if (_armorInv[i] != ARMORTYPE::NONE)
		{
			armorNum++;
		}
	}

	//악세서리
	for (int i = 0; i < ACCESSORY_MAX_ARR; ++i)
	{
		//다른게 담겨있다면
		if (_accessoryInv[i] != ACCESSORYTYPE::NONE)
		{
			accessoryNum++;
		}
	}

	//물약
	for (int i = 0; i < POTION_MAX_ARR; ++i)
	{
		//다른게 담겨있다면
		if (_potionInv[i] != POTIONTYPE::NONE)
		{
			potionNum++;
		}
	}

	_weaponCount = weaponNum;
	_armorCount = armorNum;
	_accessoryCount = accessoryNum;
	_potionCount = potionNum;

}
