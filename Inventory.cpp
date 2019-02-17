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

	//디버그용
	//for (int i = 0; i < WEAPON_MAX_ARR; ++i)
	//{
	//	_weaponInv[i] = WEAPONTYPE::IRON_SPEAR;
	//}
	//for (int i = 0; i < ARMOR_MAX_ARR; ++i)
	//{
	//	_armorInv[i] = ARMORTYPE::IRON_ARMOR;
	//}
	//for (int i = 0; i < POTION_MAX_ARR; ++i)
	//{
	//	_potionInv[i] = POTIONTYPE::SMALL;
	//}
	//for (int i = 0; i < ACCESSORY_MAX_ARR; ++i)
	//{
	//	//_accessoryInv[i] = ACCESSORYTYPE::LEEF;
	//}


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

	//종료시 초기화
	inventoryReBooting();
}

void Inventory::render()
{
	//char str[120];
	//sprintf_s(str, "%d  %d  %d  %d", _weaponCount, _armorCount, _accessoryCount, _potionCount);
	//TextOut(getMemDC(), 300, 600, str, strlen(str));

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

	_currentWeapon = WEAPONTYPE::NONE;
	_currentArmor = ARMORTYPE::NONE;
	_currentAccessory = ACCESSORYTYPE::NONE;

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
				break;
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
				break;
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
				break;
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
				break;
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

void Inventory::inventorySave()
{
	HANDLE file;
	DWORD save;

	file = CreateFile("saveFile/inventory.inv", GENERIC_WRITE, NULL, NULL,
						CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _weaponInv, sizeof(WEAPONTYPE) * WEAPON_MAX_ARR, &save, NULL);
	WriteFile(file, _armorInv, sizeof(ARMORTYPE) * ARMOR_MAX_ARR, &save, NULL);
	WriteFile(file, _accessoryInv, sizeof(ACCESSORYTYPE) * ACCESSORY_MAX_ARR, &save, NULL);
	WriteFile(file, _potionInv, sizeof(POTIONTYPE) * POTION_MAX_ARR, &save, NULL);

	CloseHandle(file);
}

void Inventory::inventoryLoad()
{
	HANDLE file;
	DWORD lode;

	file = CreateFile("saveFile/inventory.inv", GENERIC_READ, NULL, NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _weaponInv, sizeof(WEAPONTYPE) * WEAPON_MAX_ARR, &lode, NULL);
	ReadFile(file, _armorInv, sizeof(ARMORTYPE) * ARMOR_MAX_ARR, &lode, NULL);
	ReadFile(file, _accessoryInv, sizeof(ACCESSORYTYPE) * ACCESSORY_MAX_ARR, &lode, NULL);
	ReadFile(file, _potionInv, sizeof(POTIONTYPE) * POTION_MAX_ARR, &lode, NULL);

	CloseHandle(file);
}

void Inventory::inventoryReBooting()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		inventoryReset();
		inventorySave();
	}
}
