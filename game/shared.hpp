#ifndef SHARED_H_   /* Include guard */
#define SHARED_H_

#if defined(__PS2__)
#include "SDL/SDL.h"
#elif defined(__APPLE__) || (defined(__linux__) && !defined(ANDROID)) || defined (__WIIU__) || defined (__PSVITA__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

typedef struct Vec2 {
    float x;
    float y;
} Vec2;

typedef struct Shark {
    Vec2 position;
    Vec2 objective;
    Vec2 speed;
    int active; // bool
    int direction;
} Shark;

typedef struct AudioFile {
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
} AudioFile;

typedef struct SeaCreature {
    Vec2 position; // current positioning
    Vec2 origin; // helps determine which direction to head when spawned
    int active; // bool
    int direction;
    int type; // 0-4 = fish ranked, 5 = seahorse, 6 = crab, 7 = lobster, 8 = jellyfish (use for creatureSize and creatureSpeed)
    int jump;
} SeaCreature;

extern Vec2 playerPosition;
extern int lives;
extern int playerRank;
extern int playerDirection; // 1 = left, -1 = right
extern int FishSpawnTimer;
extern Shark mrShark;
extern int sharkBounces;
extern int sharkMaxBounces;
extern int score;
extern int SharkSpawnTimer;
extern int SharkHurtTimer;
extern int SharkHealth;
extern int LeftClick; // bool
extern int sharkDirection; // 1 = left, -1 = right
extern int PausedGame;
extern int mainMenu;
extern int GameOver;
extern int playerDead;
extern int sharkBitten; // bool
extern SeaCreature creatures[27];
extern int creatureRank[9];
extern float creatureSpeed[9];

extern int GetRandomNum(int min, int max);
extern void SetShark(int bitten);
extern void SetFish();
extern void SetVars(float ScreenWidth, float ScreenHeight);
extern void HurtShark();
extern void SharkRoam(float ScreenWidth, float ScreenHeight);
extern void FishSpawn(float ScreenWidth, float ScreenHeight);
extern void CrustJump(int CreatureID, float ScreenHeight, int height);
extern void FishMoveAndDeSpawn(float ScreenWidth, float ScreenHeight, int CrustHeight);
extern void PlayerBit();
extern void RealPath(char* target, const char* path);

#endif