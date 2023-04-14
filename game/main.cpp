#include "common.hpp"
#include "shared.hpp"

#if defined (__PSVITA__)
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 544;
#else
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
#endif

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

Mix_Chunk* sharkSpawnSound = NULL;
Mix_Chunk* sharkDeadSound = NULL;
Mix_Chunk* fishBiteSound = NULL;
Mix_Chunk* gameOverSound = NULL;
Mix_Chunk* deadSound = NULL;
Mix_Chunk* fishRankUp = NULL;

Mix_Music* bgMusic = NULL;

SDL_Surface* screen = NULL;

SDL_Surface* UI_Score;
SDL_Rect* UI_Score_renderQuad;

SDL_Surface* UI_Lives;
SDL_Rect* UI_Lives_renderQuad;

SDL_Surface* UI_gameover;
SDL_Rect* UI_gameover_renderQuad;

SDL_Surface* UI_pause;
SDL_Rect* UI_pause_renderQuad;

SDL_Surface* UI_died;
SDL_Rect* UI_died_renderQuad;

SDL_Surface* UI_mainmenu;
SDL_Rect* UI_mainmenu_renderQuad;

int playerSpeed = 2;
int quit = 0;

TTF_Font* font = NULL;

// SDL1 stuff
//#ifdef main
//#undef main
//#endif

typedef struct Rectangle {
	float x;
	float y;
	float w;
	float h;
} Rectangle;

#define TICK_INTERVAL    20

static Uint32 next_time;

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

#if defined (__3DS__) || defined (__WII__) || defined (__PS2__) || (__DREAMCAST__)
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

	const Uint8* keys = SDL_GetKeyState(NULL);
#else
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

	SDL_Window* gWindow = NULL;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
#endif

#if defined (__3DS__) || defined(__SWITCH__) || defined(__WIIU__)
	#define JOY_START 10
	#define JOY_LEFT  12
	#define JOY_UP    13
	#define JOY_RIGHT 14
	#define JOY_DOWN  15
#endif
#if defined(__PSVITA__)
	#define JOY_START 11
	#define JOY_LEFT  7
	#define JOY_UP	  8
	#define JOY_RIGHT 9
	#define JOY_DOWN  6
#endif

#if defined(__WIN32__) || defined(__APPLE__) || defined(__linux__) || defined(__EMSCRIPTEN__)
#define JOY_START SDL_CONTROLLER_BUTTON_START
#define JOY_LEFT  SDL_CONTROLLER_BUTTON_BACK
#define JOY_UP	  SDL_CONTROLLER_BUTTON_DPAD_UP
#define JOY_RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT
#define JOY_DOWN  SDL_CONTROLLER_BUTTON_DPAD_DOWN
#endif

	void game_loop() {
		SDL_Event e;

		Uint32 ticks = SDL_GetTicks();
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 255)); // blue like water (SDL1 might be 0x0000FF)

		struct Rectangle playerRec = { playerPosition.x, playerPosition.y, 16, 16 };

		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(bgMusic, -1);
		}

		// these should flip depending on which direction shark is facing
		struct Rectangle sharkTailRec = { mrShark.position.x + (64 / 2), mrShark.position.y, 64 / 2, 32 };
		struct Rectangle sharkBiteRec = { mrShark.position.x, mrShark.position.y, 64 / 2, 32 };
		if (sharkDirection == -1) {
			sharkTailRec = { mrShark.position.x, mrShark.position.y, 64 / 2, 32 };
			sharkBiteRec = { mrShark.position.x + (64 / 2), mrShark.position.y, 64 / 2, 32 };
		}

		// NPCs move
		if (PausedGame == 0 && GameOver == 0 && mainMenu == 0) {
			SharkRoam(SCREEN_WIDTH, SCREEN_HEIGHT);
			FishSpawn(SCREEN_WIDTH, SCREEN_HEIGHT);
			FishMoveAndDeSpawn(SCREEN_WIDTH, SCREEN_HEIGHT, 16);
		}

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;
			if (e.type == SDL_JOYBUTTONDOWN) {
				//score = e.jbutton.button;
				if (PausedGame == 0 && GameOver == 0 && mainMenu == 0) {
					if (e.jbutton.button == JOY_UP) playerMove[0] = 1;
					if (e.jbutton.button == JOY_DOWN) playerMove[2] = 1;
					if (e.jbutton.button == JOY_RIGHT) playerMove[1] = 1;
					if (e.jbutton.button == JOY_LEFT) playerMove[3] = 1;
				}
				if (e.jbutton.button == JOY_START) {
					if (mainMenu == 1) mainMenu = 0;
					if (GameOver == 1) SetVars(SCREEN_WIDTH, SCREEN_HEIGHT);
					if (PausedGame == 1) PausedGame = 0;
					if (playerDead == 1 && PausedGame == 0 && GameOver == 0) { playerDead = 0; playerPosition.x = (float)SCREEN_WIDTH / 2; playerPosition.y = (float)SCREEN_HEIGHT / 2; }
				}
			}
			else if (e.type == SDL_JOYBUTTONUP) {
				if (e.jbutton.button == JOY_UP) playerMove[0] = 0;
				if (e.jbutton.button == JOY_DOWN) playerMove[2] = 0;
				if (e.jbutton.button == JOY_RIGHT) playerMove[1] = 0;
				if (e.jbutton.button == JOY_LEFT) playerMove[3] = 0;
			}
	}

		// check for button presses
		if (keys[key_p]) { if (PausedGame == 1) PausedGame = 0; else PausedGame = 1; }
		if ((keys[key_return]) && GameOver == 1) { SetVars(SCREEN_WIDTH, SCREEN_HEIGHT); printf("restarting game"); }
		if (keys[key_return] && playerDead == 1 && PausedGame == 0 && GameOver == 0) { playerDead = 0; playerPosition.x = (float)SCREEN_WIDTH / 2; playerPosition.y = (float)SCREEN_HEIGHT / 2; }
		if (mainMenu == 1) {
			if (keys[key_s]) { mainMenu = 0; }
		}
		if (PausedGame == 0 && GameOver == 0 && mainMenu == 0) {
			if ((keys[key_right] || keys[key_d] || playerMove[1] == 1) && playerPosition.x < SCREEN_WIDTH && playerDead == 0) { playerPosition.x += playerSpeed; playerDirection = -1; }
			if ((keys[key_left] || keys[key_a] || playerMove[3] == 1) && playerPosition.x > 0 && playerDead == 0) { playerPosition.x -= playerSpeed; playerDirection = 1; }
			if ((keys[key_up] || keys[key_w] || playerMove[0] == 1) && playerPosition.y > 0 && playerDead == 0) playerPosition.y -= playerSpeed;
			if ((keys[key_down] || keys[key_s] || playerMove[2] == 1) && playerPosition.y < SCREEN_HEIGHT - 15 && playerDead == 0) playerPosition.y += playerSpeed;
		}

		char UI_Score_t[255];
		sprintf(UI_Score_t, "SCORE %d", score);
		UI_Score = TTF_RenderText_Solid(font, UI_Score_t, color_white);
		UI_Score_renderQuad = new SDL_Rect { 10, 10, (Uint16)UI_Score->w, (Uint16)UI_Score->h };
		SDL_BlitSurface(UI_Score, NULL, screen, UI_Score_renderQuad);
		char UI_Lives_t[255];
		sprintf(UI_Lives_t, "%i LIVES", lives);
		UI_Lives = TTF_RenderText_Solid(font, UI_Lives_t, color_white);
		UI_Lives_renderQuad = new SDL_Rect { SCREEN_WIDTH - 120, 10, (Uint16)UI_Lives->w, (Uint16)UI_Lives->h };
		SDL_BlitSurface(UI_Lives, NULL, screen, UI_Lives_renderQuad);
		if (GameOver) {
			char UI_gameover_t[255];
			sprintf(UI_gameover_t, "GAME OVER! - YOUR SCORE: %4i", score);
			UI_gameover = TTF_RenderText_Solid(font, UI_gameover_t, color_white);
			UI_gameover_renderQuad = new SDL_Rect { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 200, (Uint16)UI_gameover->w, (Uint16)UI_gameover->h };
			SDL_BlitSurface(UI_gameover, NULL, screen, UI_gameover_renderQuad);
		}
		if (PausedGame) {
			SDL_BlitSurface(UI_pause, NULL, screen, UI_pause_renderQuad);
		}
		if (playerDead) {
			SDL_BlitSurface(UI_died, NULL, screen, UI_died_renderQuad);
		}
		if (mainMenu == 1) {
			SDL_BlitSurface(UI_mainmenu, NULL, screen, UI_mainmenu_renderQuad);
		}

		if (CheckCollisionRecs(playerRec, sharkBiteRec) && SharkHealth > 0 && playerDead == 0) { // shark bit player
			PlayerBit();
			if (lives == 0)
				Mix_PlayChannel(-1, gameOverSound, 0);
			else
				Mix_PlayChannel(-1, deadSound, 0);
		}
		else if (CheckCollisionRecs(playerRec, sharkTailRec) && SharkHealth > 0 && playerDead == 0) { // player bit shark on tail
			if (sharkBitten != 1)
				Mix_PlayChannel(-1, fishBiteSound, 0);
			sharkBitten = 1;
		}

		// draw player fish
		SDL_Rect PosSize = { (Sint16)playerPosition.x, (Sint16)playerPosition.y, 16, 16 };
		if (playerDirection == 1) { // left
			SDL_Rect fish_left = { 16, 0, 32, (Uint16)PosSize.y };
			SDL_BlitSurface(fish[playerRank], &fish_left, screen, &PosSize);
		}
		else { // right
			SDL_Rect fish_right = { 0, 0, 16, (Uint16)PosSize.y };
			SDL_BlitSurface(fish[playerRank], &fish_right, screen, &PosSize);
		}

		// draw shark
		if (SharkSpawnTimer >= 900) {
			Mix_PlayChannel(-1, sharkSpawnSound, 0);
		}
		if (mrShark.active) {
			SDL_Rect GoTo = { (Sint16)mrShark.position.x, (Sint16)mrShark.position.y, 64, 32 };

			if (SharkHealth > 0) {
				sharkDeathAudioPlayed = 0;
				if (SharkHurtTimer % 10 && SharkHurtTimer > 0) {
					// color yellow eyes
				}
				else {
					// color red eyes
				}
				if (sharkDirection == 1) { // left
					SDL_Rect shark_left = { 0, 0, 64, (Uint16)PosSize.y };
					SDL_BlitSurface(shark, &shark_left, screen, &GoTo);
				}
				else { // right
					SDL_Rect shark_right = { 64, 0, 128, (Uint16)PosSize.y };
					SDL_BlitSurface(shark, &shark_right, screen, &GoTo);
				}
			}
			else {
				if (sharkDeathAudioPlayed == 0) {
					Mix_PlayChannel(-1, sharkDeadSound, 0);
					sharkDeathAudioPlayed = 1;
				}
				// restore eye color here: 
				if (sharkDirection == 1) { // left
					SDL_BlitSurface(shark_dead, NULL, screen, &GoTo);
				}
				else { // right
					SDL_BlitSurface(shark_dead, NULL, screen, &GoTo);
				}
			}
		}

		// for each fish, check collisions and draw on screen
		int animChange = (ticks / 200) % 2;
		for (int i = 0; i < 27; i++) {
			if (creatures[i].active) {
				if (creatures[i].type < 0 || creatures[i].type > 8) continue;
				int height = 16;
				if (creatures[i].type == 8)
					height = 64;
				struct Rectangle FishRec = { creatures[i].position.x, creatures[i].position.y, 16, (float)height };
				if (CheckCollisionRecs(playerRec, FishRec)) {
					if ((playerRank + 1) >= creatureRank[creatures[i].type]) {
						creatures[i].position.y = -10;
						creatures[i].position.x = -10;
						creatures[i].active = 0;
						score = score + 100;
						Mix_PlayChannel(-1, fishBiteSound, 0);
						Mix_PlayChannel(-1, fishBiteSound, 0);
						if (score % 1000 == 0 && playerRank < 4) {
							playerRank++;
							//printf("************** PLAYER RANK IS NOW %i ***************\n", playerRank);
							Mix_PlayChannel(-1, fishRankUp, 0);
						}
						else if (score % 1000 == 0 && playerRank >= 4) {
							lives++;
						}
					}
					else {
						//printf("**************** BITTEN BY A FISH. X:%f Y:%f ACTIVE:%i TYPE:%i ********************\n", creatures[i].position.x, creatures[i].position.y, creatures[i].active, creatures[i].type);
						PlayerBit();
						if (lives == 0)
							Mix_PlayChannel(-1, gameOverSound, 0);
						else
							Mix_PlayChannel(-1, deadSound, 0);
					}
				}

				SDL_Rect GoTo = { (Sint16)creatures[i].position.x, (Sint16)creatures[i].position.y, 16, 16 };
				SDL_Rect* tmp = new SDL_Rect{ (Sint16)(animChange * 16), 0, 16, 16 }; // 2 frames of animation
				SDL_Rect* tmp2 = new SDL_Rect{ (Sint16)((animChange + 2) * 16), 0, 16, 16 }; // 2 animations + 2 directions
				if (creatures[i].type == 5) {
					SDL_BlitSurface(crab, tmp, screen, &GoTo);
				}
				else if (creatures[i].type == 6) {
					if (creatures[i].origin.x <= 20) { // move right
						SDL_BlitSurface(lobster, tmp2, screen, &GoTo);
					}
					else { // move left
						SDL_BlitSurface(lobster, tmp, screen, &GoTo);
					}
				}
				else if (creatures[i].type <= 4 && creatures[i].type >= 0) {
					if (creatures[i].origin.x <= 20) {
						SDL_Rect* fish_right = new SDL_Rect{ 0, 0, 16, (Uint16)GoTo.y };
						SDL_BlitSurface(fish[creatures[i].type], fish_right, screen, &GoTo); // RIGHT
					}
					else {
						SDL_Rect* fish_left = new SDL_Rect{ 16, 0, 32, (Uint16)GoTo.y };
						SDL_BlitSurface(fish[creatures[i].type], fish_left, screen, &GoTo); // LEFT
					}
				}
				else if (creatures[i].type == 7) {
					if (creatures[i].origin.x <= 20) { // move right
						SDL_BlitSurface(seahorse, tmp, screen, &GoTo);
					}
					else { // move left
						SDL_BlitSurface(seahorse, tmp2, screen, &GoTo);
					}
				}
				else if (creatures[i].type == 8) {
					SDL_Rect GoToJelly = { (Sint16)creatures[i].position.x, (Sint16)creatures[i].position.y, 48, 48 };
					SDL_Rect tmpJelly = { (Sint16)(animChange * 48), 0, 48, 48 };
					SDL_BlitSurface(jellyfish, &tmpJelly, screen, &GoToJelly);
				}
			}
		}
#if defined (__3DS__) || defined (__WII__) || defined (__PS2__) || (__DREAMCAST__)
		SDL_Flip(screen);
#else
		SDL_BlitSurface(screen, NULL, screen, NULL);
		SDL_UpdateWindowSurface(gWindow);
#endif
		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;
	}

int main(int argc, char* args[])
{
#if defined (XBOX)
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT); // must be the very first call
	debugPrint("Shark! Shark! Loading...\n");
#endif
#if defined (__SWITCH__) || defined (__WIIU__)
	romfsInit();
#endif
#if defined (__SWITCH__)
    chdir("romfs:/");
#endif
#if defined (__3DS__) || defined (__WII__) || defined (__PS2__) || (__DREAMCAST__) // SDL1
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	SDL_WM_SetCaption("SharkShark", NULL);
#else // SDL2
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickOpen(0);
	gWindow = SDL_CreateWindow("SharkShark", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	screen = SDL_GetWindowSurface(gWindow);
	printf("Window located");
#endif
	
	next_time = SDL_GetTicks() + TICK_INTERVAL;

	shark = SDL_LoadBMP(RealPath("res/sprites/shark.bmp"));
	if (!shark) { // check if resources are where they're supposed to be
#if defined (XBOX)
		debugPrint("Failed to load res/sprites/shark.bmp file!\n");
#endif
		//printf("Failed to load image: %s%s %s\n", SDL_GetBasePath(), RealPath("res/sprites/shark.bmp"), SDL_GetError());
		printf("Failed to load image: %s %s\n", RealPath("res/sprites/shark.bmp"), SDL_GetError());
		return 0;
	}
	printf("Shark image located.");
	SDL_SetColorKey(shark, colorkey, SDL_MapRGB(shark->format, 0xFF, 0x0, 0xFF)); // NOTE: (SDL1) Images must be 24 bit depth to work with color keys
	shark_dead = SDL_LoadBMP(RealPath("res/sprites/shark_dead.bmp"));
	SDL_SetColorKey(shark_dead, colorkey, SDL_MapRGB(shark_dead->format, 0xFF, 0x0, 0xFF));
	seahorse = SDL_LoadBMP(RealPath("res/sprites/seahorse.bmp"));
	SDL_SetColorKey(seahorse, colorkey, SDL_MapRGB(seahorse->format, 0xFF, 0x0, 0xFF));
	lobster = SDL_LoadBMP(RealPath("res/sprites/lobster.bmp"));
	SDL_SetColorKey(lobster, colorkey, SDL_MapRGB(lobster->format, 0xFF, 0x0, 0xFF));
	crab = SDL_LoadBMP(RealPath("res/sprites/crab.bmp"));
	SDL_SetColorKey(crab, colorkey, SDL_MapRGB(crab->format, 0xFF, 0x0, 0xFF));
	fish[0] = SDL_LoadBMP(RealPath("res/sprites/rank1.bmp"));
	SDL_SetColorKey(fish[0], colorkey, SDL_MapRGB(fish[0]->format, 0xFF, 0x0, 0xFF));
	fish[1] = SDL_LoadBMP(RealPath("res/sprites/rank2.bmp"));
	SDL_SetColorKey(fish[1], colorkey, SDL_MapRGB(fish[1]->format, 0xFF, 0x0, 0xFF));
	fish[2] = SDL_LoadBMP(RealPath("res/sprites/rank3.bmp"));
	SDL_SetColorKey(fish[2], colorkey, SDL_MapRGB(fish[2]->format, 0xFF, 0x0, 0xFF));
	fish[3] = SDL_LoadBMP(RealPath("res/sprites/rank4.bmp"));
	SDL_SetColorKey(fish[3], colorkey, SDL_MapRGB(fish[3]->format, 0xFF, 0x0, 0xFF));
	fish[4] = SDL_LoadBMP(RealPath("res/sprites/rank5.bmp"));
	SDL_SetColorKey(fish[4], colorkey, SDL_MapRGB(fish[4]->format, 0xFF, 0x0, 0xFF));

	if (!shark)
		printf("Error creating texture: %s\n", SDL_GetError());

	if (TTF_Init() < 0) {
		printf("SDL TTF could not initialize! %s", SDL_GetError());
	}

	font = TTF_OpenFont(RealPath("res/pixantiqua.ttf"), 25);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	printf("SDL mixer and ttf initialized");

	sharkSpawnSound = Mix_LoadWAV(RealPath("res/audio/shark.wav"));
	fishBiteSound = Mix_LoadWAV(RealPath("res/audio/eat.wav"));
	gameOverSound = Mix_LoadWAV(RealPath("res/audio/gameover.wav"));
	deadSound = Mix_LoadWAV(RealPath("res/audio/dead.wav"));
	sharkDeadSound = Mix_LoadWAV(RealPath("res/audio/shark_dead.wav"));
	fishRankUp = Mix_LoadWAV(RealPath("res/audio/bigger.wav")); // NOTE: (SDL1) Game can crash on startup if audio bit-rate is too high

	bgMusic = Mix_LoadMUS(RealPath("res/audio/bg_music.wav"));

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)  == -1) // Initialize SDL
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		printf("SDL video and timer initialized");
		if (screen == NULL)
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		else
		{
			SetVars(SCREEN_WIDTH, SCREEN_HEIGHT);

			UI_pause = TTF_RenderText_Solid(font, "PAUSED - PRESS P TO RESUME", color_white);
			UI_pause_renderQuad = new SDL_Rect{ SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, (Uint16)UI_pause->w, (Uint16)UI_pause->h };

			UI_died = TTF_RenderText_Solid(font, "PLAYER DIED - PRESS ENTER TO SPAWN", color_white);
			UI_died_renderQuad = new SDL_Rect{ SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 50, (Uint16)UI_died->w, (Uint16)UI_died->h };

			UI_mainmenu = TTF_RenderText_Solid(font, "SHARK! SHARK! - [S]tart Game", color_white);
			UI_mainmenu_renderQuad = new SDL_Rect{ SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 90, (Uint16)UI_mainmenu->w, (Uint16)UI_mainmenu->h };

#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop(game_loop, 0, 1);
#else
			while (quit == 0) {
				game_loop();
			}
#endif
		}
	}
	Mix_FreeChunk(sharkSpawnSound);
	Mix_FreeChunk(sharkDeadSound);
	Mix_FreeChunk(fishBiteSound);
	Mix_FreeChunk(gameOverSound);
	Mix_FreeChunk(deadSound);
	Mix_FreeChunk(fishRankUp);

	SDL_FreeSurface(fish[0]);
	SDL_FreeSurface(fish[1]);
	SDL_FreeSurface(fish[2]);
	SDL_FreeSurface(fish[3]);
	SDL_FreeSurface(fish[4]);
	SDL_FreeSurface(shark);
	SDL_FreeSurface(shark_dead);
	SDL_FreeSurface(seahorse);
	SDL_FreeSurface(lobster);
	SDL_FreeSurface(crab);

	Mix_FreeMusic(bgMusic);
	TTF_CloseFont(font);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit(); // Quit SDL subsystems
#if defined (__SWITCH__) || defined (__WIIU__)
	romfsExit();
#endif

	return 0;
}
