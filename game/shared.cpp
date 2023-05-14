#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "common.hpp"

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
int PauseTimer;
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

int sharkDeathAudioPlayed = 0;

int playerMove[4] = { 0,0,0,0 }; // up right down left

SDL_Surface* shark;
SDL_Surface* shark_dead;
SDL_Surface* lobster;
SDL_Surface* crab;
SDL_Surface* seahorse;
SDL_Surface* jellyfish;

SDL_Surface* fish[5];

SDL_Color color_white = { 255,255,255,255 };
SDL_Color color_black = { 0,0,0,255 };

Mix_Chunk* sharkSpawnSound;
Mix_Chunk* sharkDeadSound;
Mix_Chunk* fishBiteSound;
Mix_Chunk* gameOverSound;
Mix_Chunk* deadSound;
Mix_Chunk* fishRankUp;

Mix_Music* bgMusic;

SDL_Surface* screen;

SDL_Surface* UI_Score;
SDL_Rect* UI_Score_renderQuad;

SDL_Surface* UI_Lives;
SDL_Rect* UI_Lives_renderQuad;

SDL_Surface* UI_gameover;
SDL_Rect* UI_gameover_renderQuad;

SDL_Surface* UI_pause;
SDL_Rect UI_pause_renderQuad;

SDL_Surface* UI_died;
SDL_Rect UI_died_renderQuad;

SDL_Surface* UI_mainmenu;
SDL_Rect UI_mainmenu_renderQuad;

TTF_Font* font;
const Uint8* keys;

Uint32 next_time;

// SDL 1
#if defined (__3DS__) || defined (__WII__) || defined (__DREAMCAST__) || defined (__WIN9X__)
int colorkey = SDL_SRCCOLORKEY;
int key_s = SDLK_s;
int key_p = SDLK_p;
int key_w = SDLK_w;
int key_a = SDLK_a;
int key_d = SDLK_d;
int key_return = SDLK_RETURN;
int key_left = SDLK_LEFT;
int key_right = SDLK_RIGHT;
int key_up = SDLK_UP;
int key_down = SDLK_DOWN;
#else // SDL 2
int colorkey = SDL_TRUE;
int key_p = SDL_SCANCODE_P;
int key_w = SDL_SCANCODE_W;
int key_a = SDL_SCANCODE_A;
int key_s = SDL_SCANCODE_S;
int key_d = SDL_SCANCODE_D;
int key_return = SDL_SCANCODE_RETURN;
int key_left = SDL_SCANCODE_LEFT;
int key_right = SDL_SCANCODE_RIGHT;
int key_up = SDL_SCANCODE_UP;
int key_down = SDL_SCANCODE_DOWN;
SDL_Window* gWindow;
#endif

int playerSpeed = 2;
int quit = 0;

#if defined (__PSVITA__)
int SCREEN_WIDTH = 960;
int SCREEN_HEIGHT = 544;
#elif defined (IOSBUILD)
int SCREEN_WIDTH = 920;
int SCREEN_HEIGHT = 430;
#else
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
#endif

int GetRandomNum(int min, int max)
{
    int range, result, cutoff;
    if (min >= max) return min;
    range = max - min + 1;
    cutoff = (RAND_MAX / range) * range;
    do { result = rand(); } while (result >= cutoff);
    return result % range + min;
}

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

int CheckCollisionRecs(Rectangle r1, Rectangle r2) {
    if (r1.x + r1.w >= r2.x &&    // r1 right edge past r2 left
        r1.x <= r2.x + r2.w &&    // r1 left edge past r2 right
        r1.y + r1.h >= r2.y &&    // r1 top edge past r2 bottom
        r1.y <= r2.y + r2.h) {    // r1 bottom edge past r2 top
        return 1;
    }
    return 0;
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

void CheckRankUp() {
    //printf("1000:%i 1025:%i 1050:%i 1075:%i rank:%i\n", score % 1000, score % 1025, score % 1050, score % 1075, playerRank);
    if ((score % 1000 == 0 || (score - 25) % 1000 == 0 || (score - 50) % 1000 == 0 || (score - 75) % 1000 == 0) && int(round(score / 1000)) == (playerRank + 1)) {
        if (playerRank < 4) {
            playerRank++;
            //printf("************** PLAYER RANK IS NOW %i ***************\n", playerRank);
            Mix_PlayChannel(-1, fishRankUp, 0);
        }
        else {
            //printf("************** GAINED +1 LIVE ***************\n");
            Mix_PlayChannel(-1, fishRankUp, 0);
            lives++;
        }
    }
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

void Respawn(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    playerDead = 0; 
    playerRank = 0;
    playerPosition.x = (float)SCREEN_WIDTH / 2; 
    playerPosition.y = (float)SCREEN_HEIGHT / 2;
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
    lives = 2;
    playerDirection = 1;
    playerDead = 0;
    FishSpawnTimer = 0;
    sharkBounces = 0;
    sharkMaxBounces = 5;
    SharkSpawnTimer = 0;
    SharkHurtTimer = 0;
    PauseTimer = 0;
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

void MixerOpenAudio() {
#if defined(__PS2__)
    if (Mix_OpenAudio(44100, AUDIO_S16, 2, 512) < 0)
    {
        printf("Couldn't open audio: %s\n", SDL_GetError());
        return 0;
    }
#else
    if (Mix_OpenAudio(48000, AUDIO_S16LSB, 2, 1024) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
#endif
}

void RefreshScreen() {
#if defined (__3DS__) || defined (__WII__) || (__DREAMCAST__) || defined (__WIN9X__)
    SDL_Flip(screen);
#else
    SDL_BlitSurface(screen, NULL, screen, NULL);
    SDL_UpdateWindowSurface(gWindow);
#endif
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
            CheckRankUp();
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
    int TimeToSpawn = 60;
    if (playerRank > 4) TimeToSpawn = 30; // increase spawns x2
    if (FishSpawnTimer >= TimeToSpawn) {
        int pickCreature = 0;
        pickCreature = GetRandomNum(0, 26);
        int CheckFishEqualPlayerRank = 0;
        if (playerRank < 4) { // spawn at least 1 fish that matches our rank
            for (int i = 0; i <= 4; i++) { // check if we have a fish out that is the same players rank
                if (creatures[i].active == 1 && i == playerRank) // 0-4
                    CheckFishEqualPlayerRank = 1;
            }
            if (CheckFishEqualPlayerRank == 0) {
                //printf("spawning same lvl fish RANK:%i\n", playerRank);
                pickCreature = playerRank;
            }
        }
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
#elif defined (__PS2__)
    int index = 0;
    sprintf(newPath, "cdrom0:\\%s", path);
    while (newPath[index])
    {
        if (newPath[index] == '/')
            newPath[index] = '\\';
        index++;
    }
#else
    sprintf(newPath, "%s", path);
#endif
    return newPath;
}