#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "shared.hpp"

float creatureSpeed[9] = { 1, 1.3f, 1.5f, 1.7f, 2, 0.8f, 0.8f, 2, 1.3f }; // use SC type to get speed
int creatureRank[9] = { 1, 2, 3, 4, 5, 5, 5, 5, 6 }; // use SC type to get rank. Rank determines what a creature can eat. (jellyfish are immune)

struct Vec2 playerPosition;
int lives;
int playerRank;
int playerDirection; // 1 = left, -1 = right
int FishSpawnTimer;
struct Shark mrShark;
int sharkBounces;
int sharkMaxBounces;
int score;
int SharkSpawnTimer;
int SharkHurtTimer;
int SharkHealth;
int LeftClick; // bool
int sharkDirection; // 1 = left, -1 = right
int PausedGame;
int mainMenu;
int GameOver;
int playerDead;
int sharkBitten; // bool
int MouseX = 0;
int MouseY = 0;
struct SeaCreature creatures[27];

int GetRandomNum(int min, int max)
{
    int range, result, cutoff;
    if (min >= max) return min;
    range = max - min + 1;
    cutoff = (RAND_MAX / range) * range;
    do { result = rand(); } while (result >= cutoff);
    return result % range + min;
}

void SetShark(int bitten) {
    mrShark.active = 1;
    mrShark.objective = playerPosition;

    if (bitten == 0) { // set shark direction
        if (mrShark.position.x > mrShark.objective.x)
            sharkDirection = 1;
        else
            sharkDirection = -1;
    }

    float module = sqrt(pow(mrShark.objective.x - mrShark.position.x, 2) + pow(mrShark.objective.y - mrShark.position.y, 2));

    float sideX = (mrShark.objective.x - mrShark.position.x) / module;
    float sideY = (mrShark.objective.y - mrShark.position.y) / module;

    mrShark.speed.x=sideX;
	mrShark.speed.y=sideY;
    //printf("DEBUG: Resetting shark\n");
}

void SetFish() {
    int t = 0; // creature type
    for (int i = 0; i < 27; i++) { // generate 27 sea creatures
        SeaCreature sc;
        sc.position.x=0;
		sc.position.y=0;
        sc.origin.x=0;
		sc.origin.y=0;
        if (t > 8) t = 8;
        sc.type = t;
        sc.active = 0;
        creatures[i] = sc;
        if (i % 3 == 0) t++; // 3 of every type
    }
}

void SetVars(float ScreenWidth, float ScreenHeight) {
    srand(time(NULL));
    LeftClick = 0;
    score = 0;
    playerRank = 0;
    playerPosition.x = ScreenWidth / 2;
    playerPosition.y = ScreenHeight / 2;

    mrShark.position.x=ScreenWidth - 20;
	mrShark.position.y=20;

    PausedGame = 0;
    mainMenu = 1;
    GameOver = 0;
    lives = 5;
    playerDirection = 1;
    playerDead = 0;
    FishSpawnTimer = 0;
    sharkBounces = 0;
    sharkMaxBounces = 5;
    SharkSpawnTimer = 0;
    SharkHurtTimer = 0;
    SharkHealth = 10;
    LeftClick = 0;
    sharkBitten = 0;

    SetShark(0);
    sharkDirection = 1;
    SetFish();
    //printf("DEBUG: SETTING shark coords x:%f y:%f sx:%f sy:%f\n", mrShark.position.x, mrShark.position.y, mrShark.speed.x, mrShark.speed.y);
    //printf("DEBUG: SETTING player coords x:%f y:%f\n", playerPosition.x, playerPosition.y);
}

void HurtShark() {
    if (!sharkBitten || SharkHealth <= 0) return;
    //printf("DEBUG: Shark was bitten. Timer: %i\n", SharkHurtTimer);
    mrShark.position.x=mrShark.position.x;
    mrShark.objective.x=mrShark.position.x; // pause for a sec
    if (SharkHurtTimer >= 60) {
        SharkHealth--;
        sharkDirection = sharkDirection * -1; // change direction
        SetShark(1); // reset exactly where he's headed
        sharkBitten = 0;
        SharkHurtTimer = 0;
        return;
    }
    SharkHurtTimer++;
}

void SharkRoam(float ScreenWidth, float ScreenHeight) {
    if (mrShark.active)
    {
        mrShark.objective = playerPosition;

        if (SharkHealth <= 0 && mrShark.position.y >= ScreenHeight) {
            //printf("************* SHARK DIED **************\n");
            mrShark.position.x = -100;
            mrShark.position.y = -100;
            mrShark.active = 0;
            score = score + 100;
            return;
        }

        HurtShark();
        if (sharkBitten) return;
        if (SharkHealth > 0) {
            mrShark.position.x += mrShark.speed.x;
            mrShark.position.y += mrShark.speed.y;
        }
        else {
            mrShark.position.y++;
            return;
        }

        if (mrShark.position.x <= -20 || mrShark.position.x >= ScreenWidth - 20 || mrShark.position.y <= -20 || mrShark.position.y >= ScreenHeight - 20) {
            SetShark(0);
            if (sharkBounces == sharkMaxBounces) {
                mrShark.position.x = -100;
                mrShark.position.y = -100;
                mrShark.active = 0;
            }
            sharkBounces++;
        }
    }
    else {
        if (SharkSpawnTimer >= 900) { // 15 seconds
            SharkHealth = 10;
            sharkDirection = 1;
            mrShark.active = 1;
            mrShark.position.x=ScreenWidth - 20;
			mrShark.position.y=20;
            SharkSpawnTimer = 0;
        }
        //printf("DEBUG: SharkSpawnTimer: %i\n", SharkSpawnTimer);
        SharkSpawnTimer++;
    }
}

void FishSpawn(float ScreenWidth, float ScreenHeight) {
    int height = 40;
    //if (ScreenHeight < 600) height = 20;
    if (FishSpawnTimer >= 60) {
        int pickCreature = 0;
        pickCreature = GetRandomNum(0, 26);
        if (!creatures[pickCreature].active) {
            if (creatures[pickCreature].type == 8 && playerRank < 3) return; // no need to spawn jellyfish early in the game
            if (creatures[pickCreature].type == 7 && playerRank < 2) return; // seahorses can wait a bit
            creatures[pickCreature].jump = 0;
            creatures[pickCreature].active = 1;
            int pickSide[2] = { 20,(int)(ScreenWidth - 20) };
            float pickHeight = GetRandomNum(20, (int)(ScreenHeight - 50));
            float ps = pickSide[rand() % 2];
            if (creatures[pickCreature].type == 5 || creatures[pickCreature].type == 6) pickHeight = ScreenHeight - height;
            creatures[pickCreature].origin.x=ps;
			creatures[pickCreature].origin.y=pickHeight;
            creatures[pickCreature].position.x=ps;
			creatures[pickCreature].position.y=pickHeight;
            //printf("DEBUG: Spawning Fish coords x:%f y:%f type:%i active:%i\n", ps, pickHeight, creatures[pickCreature].type, creatures[pickCreature].active);
        }
        FishSpawnTimer = 0;
    }
    FishSpawnTimer++;
}

void CrustJump(int CreatureID, float ScreenHeight, int height) {
    //int height = 16; // SDL 16 is perfect, others may require a different number
    int jumpheight = 128;
    //if (ScreenHeight < 600) { height = 20; jumpheight = 64; }
    if (creatures[CreatureID].type != 5 && creatures[CreatureID].type != 6) return; // only crustaceans
    if (creatures[CreatureID].position.y > ScreenHeight - jumpheight && creatures[CreatureID].jump) // go up
        creatures[CreatureID].position.y -= 2.0f;
    else if (creatures[CreatureID].position.y <= ScreenHeight - jumpheight && creatures[CreatureID].jump) // stop going up
        creatures[CreatureID].jump = 0;
    else if (creatures[CreatureID].position.y < ScreenHeight - height && !creatures[CreatureID].jump) // come back down
        creatures[CreatureID].position.y += 2.0f;
}

void FishMoveAndDeSpawn(float ScreenWidth, float ScreenHeight, int CrustHeight) {
    for (int i = 0; i < 27; i++) {
        if (creatures[i].active) {
            // move
            if (creatures[i].origin.x == 20)
                creatures[i].position.x = creatures[i].position.x + creatureSpeed[creatures[i].type];
            else if (creatures[i].origin.x == ScreenWidth - 20)
                creatures[i].position.x = creatures[i].position.x - creatureSpeed[creatures[i].type];
            // crustacean jump
            if (creatures[i].type == 5 || creatures[i].type == 6) {
                if (GetRandomNum(0, 500) == 90) {
                    creatures[i].jump = 1;
                    //printf("DEBUG: JUMP\n");
                }
                CrustJump(i, ScreenHeight, CrustHeight);
            }
            // de-spawn
            if ((creatures[i].origin.x == (ScreenWidth - 20) && creatures[i].position.x < 0) ||
                (creatures[i].origin.x == 20 && creatures[i].position.x > ScreenWidth)) {
                creatures[i].position.x = -10;
                creatures[i].position.y = -10;
                creatures[i].active = 0;
                //printf("DEBUG: DE-Spawning Fish active:%i\n", creatures[i].active);
            }
        }
    }
}

void PlayerBit() {
    lives--;
    playerPosition.x=-200;
	playerPosition.y=-200;
    MouseX = 0;
    MouseY = 0;
    playerDead = 1;
    if (lives <= 0) {
        GameOver = 1;
    }
}

/// <summary>
/// Switch our file paths with system specific ones
/// </summary>
/// <param name="path">Should start with res/</param>
/// <returns></returns>
const char* RealPath(const char* path) {
    static char newPath[255];
#if defined (XBOX)
    int index = 0;
    sprintf(newPath, "D:\\%s", path);
    while (newPath[index])
    {
        if (newPath[index] == '/')
            newPath[index] = '\\';
        index++;
    }
#elif defined (__WII__)
    sprintf(newPath, "sd:/apps/SharkShark/%s", path);
#elif defined (__WIIU__)
    sprintf(newPath, "sd:/wiiu/apps/SharkShark/%s", path);
#elif defined (__3DS__)
    sprintf(newPath, "romfs:/%s", path);
#else
    sprintf(newPath, "%s", path);
#endif
    return newPath;
}