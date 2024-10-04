#ifndef SHARED_H_   /* Include guard */
#define SHARED_H_

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

typedef struct SeaCreature {
    struct Vec2 position; // current positioning
    struct Vec2 origin; // helps determine which direction to head when spawned
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
extern int MouseX;
extern int MouseY;
extern int PauseTimer;
extern SeaCreature creatures[27];
extern int creatureRank[9];
extern float creatureSpeed[9];

extern char UI_Score_t[255];
extern char UI_Lives_t[255];

extern SDL_Surface* shark;
extern SDL_Surface* shark_dead;
extern SDL_Surface* lobster;
extern SDL_Surface* crab;
extern SDL_Surface* seahorse;
extern SDL_Surface* jellyfish;

extern SDL_Surface* fish[5];

extern SDL_Color color_white;
extern SDL_Color color_black;

extern Mix_Chunk* sharkSpawnSound;
extern Mix_Chunk* sharkDeadSound;
extern Mix_Chunk* fishBiteSound;
extern Mix_Chunk* gameOverSound;
extern Mix_Chunk* deadSound;
extern Mix_Chunk* fishRankUp;

extern Mix_Music* bgMusic;

extern SDL_Surface* UI_Score;
extern SDL_Rect* UI_Score_renderQuad;

extern SDL_Surface* UI_Lives;
extern SDL_Rect* UI_Lives_renderQuad;

extern SDL_Surface* UI_gameover;
extern SDL_Rect* UI_gameover_renderQuad;

extern SDL_Surface* UI_pause;
extern SDL_Rect UI_pause_renderQuad;

extern SDL_Surface* UI_died;
extern SDL_Rect UI_died_renderQuad;

extern SDL_Surface* UI_mainmenu;
extern SDL_Rect UI_mainmenu_renderQuad;

extern const Uint8* keys;
extern TTF_Font* font;

extern Uint32 next_time;

typedef struct Rectangle {
    float x;
    float y;
    float w;
    float h;
} Rectangle;

extern int quit;
extern int playerSpeed;

extern int sharkDeathAudioPlayed;
extern int playerMove[4];

extern int colorkey;
extern int key_s;
extern int key_p;
extern int key_w;
extern int key_a;
extern int key_d;
extern int key_return;
extern int key_left;
extern int key_right;
extern int key_up;
extern int key_down;

// SDL 1
#if defined (__3DS__) || defined (__WII__) || defined (__DREAMCAST__) || defined (__WIN9X__)
extern SDL_Surface* screen;
#else // SDL 2
extern SDL_Window* gWindow;
extern SDL_Renderer* renderer;
#endif

extern void surfaceToScreen(SDL_Surface* surf, SDL_Rect* src, SDL_Rect* dst);

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

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
extern const char* RealPath(const char* path);
extern void CheckRankUp();
extern void Respawn(int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern int CheckCollisionRecs(Rectangle r1, Rectangle r2);
extern Uint32 time_left(void);
extern void RefreshScreen();
extern void MixerOpenAudio();
extern void exitApp();

#endif