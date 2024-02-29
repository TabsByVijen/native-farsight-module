#pragma once
#include <string>
#include <map>
#include <chrono>
#include <napi.h>
#include <vector>

#include "MemoryLoadable.h"

enum IsChampionState
{
    IS_CHAMPION_UNKNOWN = -1,
    IS_NOT_CHAMPION = 0,
    IS_CHAMPION = 1
};

class GameObject : MemoryLoadable
{
public:
    GameObject(Napi::Env environment) : env(environment) {
        env = environment;
    }
    void LoadFromMemory(DWORD64 base, HANDLE hProcess, bool deepLoad = false);

    bool IsEqualTo(const GameObject &other) const;
    bool IsNotEqualTo(const GameObject &other) const;

public:
    float health;
    float maxHealth;
    float mana;
    float maxMana;

    short objectIndex;
    short team;

    bool isAlive;
    bool isChampion;

    Napi::Env env;

    std::vector<char> name;
    std::vector<char> displayName;
    float position[3];

    DWORD networkId;
    DWORD64 baseAddress;

protected:
    static const SIZE_T sizeBuff = 0x5100;
    static const SIZE_T sizeBuffDeep = 0x1000;

    static BYTE buff[sizeBuff];
    static BYTE buffDeep[sizeBuffDeep];

    // Champion related
public:
    void LoadChampionFromMemory(DWORD64 base, HANDLE hProcess, bool deepLoad = true);
    void LoadChampionData();

    bool IsChampion();

    int level;
    float experience;
    float currentGold;
    float totalGold;

    Napi::Object ToNapiObject();
};