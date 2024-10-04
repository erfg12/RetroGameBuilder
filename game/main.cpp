#include "common.hpp"
#include "shared.hpp"

	void game_loop() {
		SDL_Event e;

		Uint32 ticks = SDL_GetTicks();
#if defined (__3DS__) || defined (__WII__) || defined (__DREAMCAST__) || defined (__WIN9X__) // sdl 1
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 255)); // blue like water (SDL1 might be 0x0000FF)
#else
		SDL_RenderClear(renderer);
#endif
		struct Rectangle playerRec = { playerPosition.x, playerPosition.y, 16, 16 };

		// these should flip depending on which direction shark is facing
		struct Rectangle sharkTailRec = { mrShark.position.x + (64 / 2), mrShark.position.y, 64 / 2, 32 };
		struct Rectangle sharkBiteRec = { mrShark.position.x, mrShark.position.y, 64 / 2, 32 };
		if (sharkDirection == -1) {
			sharkTailRec.x=mrShark.position.x; 
			sharkTailRec.y=mrShark.position.y;
			sharkBiteRec.x=mrShark.position.x + (64 / 2);
			sharkBiteRec.y=mrShark.position.y;
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
			/*if (e.type == SDL_KEYDOWN) {
				printf("keydown:%i\n", e.key.keysym.sym);
				SDL_PumpEvents();
			}*/
			if (e.type == SDL_JOYAXISMOTION) {
				//score = e.jaxis.value;
			}
			if (e.type == SDL_JOYHATMOTION) { // d-pad directions for consoles
				if (PausedGame == 0 && GameOver == 0 && mainMenu == 0) {
					if (e.jhat.value & SDL_HAT_UP) playerMove[0] = 1; else playerMove[0] = 0;
					if (e.jhat.value & SDL_HAT_DOWN) playerMove[2] = 1; else playerMove[2] = 0;
					if (e.jhat.value & SDL_HAT_RIGHT) playerMove[1] = 1; else playerMove[1] = 0;
					if (e.jhat.value & SDL_HAT_LEFT) playerMove[3] = 1; else playerMove[3] = 0;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (PausedGame == 1 || mainMenu == 1) {
					PausedGame = 0;
					mainMenu = 0;
				} else if (GameOver == 1)
					SetVars(SCREEN_WIDTH, SCREEN_HEIGHT);
				else if (playerDead == 1 && PausedGame == 0 && GameOver == 0) {
					Respawn(SCREEN_WIDTH, SCREEN_HEIGHT);
				} else {
					SDL_GetMouseState(&MouseX, &MouseY);
					printf("mouse clicked coords x:%i y:%i\n", MouseX, MouseY);
				}
			}
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
					else if (GameOver == 1) SetVars(SCREEN_WIDTH, SCREEN_HEIGHT);
					else if (PausedGame == 0 && playerDead == 0 && GameOver == 0) if (PauseTimer > 50) { PausedGame = 1; PauseTimer = 0; }
					else if (PausedGame == 1 && playerDead == 0 && GameOver == 0) if (PauseTimer > 50) { PausedGame = 0; PauseTimer = 0; }
					else if (playerDead == 1 && PausedGame == 0 && GameOver == 0) { Respawn(SCREEN_WIDTH, SCREEN_HEIGHT); }
				}
			}
			else if (e.type == SDL_JOYBUTTONUP) {
				if (e.jbutton.button == JOY_UP) playerMove[0] = 0;
				if (e.jbutton.button == JOY_DOWN) playerMove[2] = 0;
				if (e.jbutton.button == JOY_RIGHT) playerMove[1] = 0;
				if (e.jbutton.button == JOY_LEFT) playerMove[3] = 0;
			}
		}

		// click to move
		if (MouseX > 0 && MouseY > 0 && PausedGame == 0 && GameOver == 0) {
			if (abs(playerPosition.x - MouseX) > 2) { // move towards X
				if (MouseX > playerPosition.x) {
					playerPosition.x += playerSpeed;
					playerDirection = -1;
				} 
				else {
					playerPosition.x -= playerSpeed;
					playerDirection = 1;
				}
			}
			if (abs(playerPosition.y - MouseY) > 2) { // move towards Y
				if (MouseY > playerPosition.y)
					playerPosition.y += playerSpeed;
				else
					playerPosition.y -= playerSpeed;
			}
			if (abs(playerPosition.x - MouseX) < 2 && abs(playerPosition.y - MouseY) < 2) // arrived at location
			{
				MouseX = 0;
				MouseY = 0;
			}
		}

		// check for button presses
		if (keys[key_p]) { if (PausedGame == 1 && PauseTimer > 50) { PausedGame = 0; PauseTimer = 0; } else if (PausedGame == 0 && PauseTimer > 50) { PausedGame = 1; PauseTimer = 0; } }
		if ((keys[key_return]) && GameOver == 1) { SetVars(SCREEN_WIDTH, SCREEN_HEIGHT); printf("restarting game"); }
		if (keys[key_return] && playerDead == 1 && PausedGame == 0 && GameOver == 0) { Respawn(SCREEN_WIDTH,SCREEN_HEIGHT); }
		if (mainMenu == 1) {
			if (keys[key_s] || keys[key_return] || keys[key_a]) { mainMenu = 0; }
		}
		if (PausedGame == 0 && GameOver == 0 && mainMenu == 0) {
			if ((keys[key_right] || keys[key_d] || playerMove[1] == 1) && playerPosition.x < SCREEN_WIDTH && playerDead == 0) { playerPosition.x += playerSpeed; playerDirection = -1; MouseX = 0; MouseY = 0; }
			if ((keys[key_left] || keys[key_a] || playerMove[3] == 1) && playerPosition.x > 0 && playerDead == 0) { playerPosition.x -= playerSpeed; playerDirection = 1; MouseX = 0; MouseY = 0; }
			if ((keys[key_up] || keys[key_w] || playerMove[0] == 1) && playerPosition.y > 0 && playerDead == 0) { playerPosition.y -= playerSpeed; MouseX = 0; MouseY = 0; }
			if ((keys[key_down] || keys[key_s] || playerMove[2] == 1) && playerPosition.y < SCREEN_HEIGHT - 15 && playerDead == 0) { playerPosition.y += playerSpeed; MouseX = 0; MouseY = 0; }
		}

		PauseTimer++;

		sprintf(UI_Score_t, "SCORE %d", score);
		UI_Score = TTF_RenderText_Solid(font, UI_Score_t, color_white);
		struct SDL_Rect UI_Score_renderQuad;
		UI_Score_renderQuad.x=10;
		UI_Score_renderQuad.y=10;
		UI_Score_renderQuad.w=(Uint16)UI_Score->w;
		UI_Score_renderQuad.h=(Uint16)UI_Score->h;

		surfaceToScreen(UI_Score, NULL, &UI_Score_renderQuad);

		
		sprintf(UI_Lives_t, "%i LIVES", lives);
		UI_Lives = TTF_RenderText_Solid(font, UI_Lives_t, color_white);
		struct SDL_Rect UI_Lives_renderQuad;
		UI_Lives_renderQuad.x=SCREEN_WIDTH - 120;
		UI_Lives_renderQuad.y=10;
		UI_Lives_renderQuad.w=(Uint16)UI_Lives->w;
		UI_Lives_renderQuad.h=(Uint16)UI_Lives->h;

		surfaceToScreen(UI_Lives, NULL, &UI_Lives_renderQuad);
		if (GameOver) {
			char UI_gameover_t[255];
			sprintf(UI_gameover_t, "GAME OVER! - YOUR SCORE: %4i", score);
			UI_gameover = TTF_RenderText_Solid(font, UI_gameover_t, color_white);
			struct SDL_Rect UI_gameover_renderQuad;
			UI_gameover_renderQuad.x=SCREEN_WIDTH / 2 - 200;
			UI_gameover_renderQuad.y=SCREEN_HEIGHT / 2 - 200;
			UI_gameover_renderQuad.w=(Uint16)UI_gameover->w;
			UI_gameover_renderQuad.h=(Uint16)UI_gameover->h;
			surfaceToScreen(UI_gameover, NULL, &UI_gameover_renderQuad);
		}
		if (PausedGame) {
			surfaceToScreen(UI_pause, NULL, &UI_pause_renderQuad);
		}
		if (playerDead) {
			surfaceToScreen(UI_died, NULL, &UI_died_renderQuad);
		}
		if (mainMenu == 1) {
			surfaceToScreen(UI_mainmenu, NULL, &UI_mainmenu_renderQuad);
		}

		if (CheckCollisionRecs(playerRec, sharkBiteRec) && SharkHealth > 0 && playerDead == 0) { // shark bit player
			PlayerBit();
			if (lives == 0)
				Mix_PlayChannel(-1, gameOverSound, 0);
			else
				Mix_PlayChannel(-1, deadSound, 0);
		}
		else if (CheckCollisionRecs(playerRec, sharkTailRec) && SharkHealth > 0 && playerDead == 0) { // player bit shark on tail
			if (sharkBitten != 1) {
				Mix_PlayChannel(-1, fishBiteSound, 0);
				score = score + 25;
				CheckRankUp();
			}
			sharkBitten = 1;
		}

		// draw player fish
		SDL_Rect PosSize = { (Sint16)playerPosition.x, (Sint16)playerPosition.y, 16, 16 };
		if (playerDirection == 1) { // left
			SDL_Rect fish_left = { 16, 0, 32, (Uint16)PosSize.y };
			surfaceToScreen(fish[playerRank], &fish_left, &PosSize);
		}
		else { // right
			SDL_Rect fish_right = { 0, 0, 16, (Uint16)PosSize.y };
			surfaceToScreen(fish[playerRank], &fish_right, &PosSize);
		}

		// draw shark
		if (SharkSpawnTimer >= 900) {
			Mix_PlayChannel(-1, sharkSpawnSound, 0);
		}
		if (mrShark.active) {
			SDL_Rect GoTo = { (Sint16)mrShark.position.x, (Sint16)mrShark.position.y, 64, 32 };

			if (SharkHealth > 0) {
				sharkDeathAudioPlayed = 0;
				Uint8 r = 0xFF;
				Uint8 g = 0xFF;
				Uint8 b = 0x00;
				if (SharkHurtTimer % 10 && SharkHurtTimer > 0) {
					g = 0x00;
					SDL_SetSurfaceColorMod(shark, r, g, b); // color red eyes
				}
				else {
					SDL_SetSurfaceColorMod(shark, r, g, b); // color yellow eyes
				}
				if (sharkDirection == 1) { // left
					SDL_Rect shark_left = { 0, 0, 64, (Uint16)GoTo.y };
					surfaceToScreen(shark, &shark_left, &GoTo);
				}
				else { // right
					SDL_Rect shark_right = { 64, 0, 128, (Uint16)GoTo.y };
					surfaceToScreen(shark, &shark_right, &GoTo);
				}
			}
			else {
				if (sharkDeathAudioPlayed == 0) {
					Mix_PlayChannel(-1, sharkDeadSound, 0);
					sharkDeathAudioPlayed = 1;
				}
				// restore eye color here: 
				if (sharkDirection == 1) { // left
					surfaceToScreen(shark_dead, NULL, &GoTo);
				}
				else { // right
					surfaceToScreen(shark_dead, NULL, &GoTo);
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
						CheckRankUp();
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
				SDL_Rect tmp;
				tmp.x=(Sint16)(animChange * 16);
				tmp.y=0;
				tmp.w=16;
				tmp.h=16; // 2 frames of animation
				SDL_Rect tmp2;
				tmp2.x=(Sint16)((animChange + 2) * 16);
				tmp2.y=0;
				tmp2.w=16;
				tmp2.h=16; // 2 animations + 2 directions
				if (creatures[i].type == 5) {
					surfaceToScreen(crab, &tmp, &GoTo);
				}
				else if (creatures[i].type == 6) {
					if (creatures[i].origin.x <= 20) { // move right
						surfaceToScreen(lobster, &tmp2, &GoTo);
					}
					else { // move left
						surfaceToScreen(lobster, &tmp, &GoTo);
					}
				}
				else if (creatures[i].type <= 4 && creatures[i].type >= 0) {
					if (creatures[i].origin.x <= 20) {
						SDL_Rect fish_right;
						fish_right.x=0;
						fish_right.y=0;
						fish_right.w=16;
						fish_right.h=(Uint16)GoTo.y; // RIGHT
						surfaceToScreen(fish[creatures[i].type], &fish_right, &GoTo);
					}
					else {
						SDL_Rect fish_left;
						fish_left.x=16;
						fish_left.y=0;
						fish_left.w=32;
						fish_left.h=(Uint16)GoTo.y;  // LEFT
						surfaceToScreen(fish[creatures[i].type], &fish_left, &GoTo);
					}
				}
				else if (creatures[i].type == 7) {
					if (creatures[i].origin.x <= 20) { // move right
						surfaceToScreen(seahorse, &tmp, &GoTo);
					}
					else { // move left
						surfaceToScreen(seahorse, &tmp2, &GoTo);
					}
				}
				else if (creatures[i].type == 8) {
					SDL_Rect GoToJelly = { (Sint16)creatures[i].position.x, (Sint16)creatures[i].position.y, 48, 48 };
					SDL_Rect tmpJelly = { (Sint16)(animChange * 48), 0, 48, 48 };
					surfaceToScreen(jellyfish, &tmpJelly, &GoToJelly);
				}
			}
		}
		RefreshScreen();
//#if !defined(__EMSCRIPTEN__) && !defined (__3DS__) && !defined (__WII__) && !(__DREAMCAST__) && !defined (__WIN9X__)
//		SDL_Delay(time_left()); // causes audio hiccups on devices other than PC, iOS, Android
//#endif
		next_time += TICK_INTERVAL;
	}

int main(int argc, char* args[])
{
#if defined (XBOX)
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT); // must be the very first call
	debugPrint("Shark! Shark! Loading...\n");
#endif
#if defined (__SWITCH__) || defined (__3DS__)
	romfsInit();
#endif
#if defined (__SWITCH__)
    chdir("romfs:/");
#endif
	
	if (TTF_Init() < 0) {
		printf("SDL TTF could not initialize! %s", SDL_GetError());
	}

#if defined (__PS2__)
	SifLoadFileInit();
	SifInitIopHeap();
	sbv_patch_enable_lmb();
#endif
#if !defined(XBOX)
	SDL_InitSubSystem(SDL_INIT_VIDEO);
#endif
#if defined(PSP)
	SDL_Init(SDL_INIT_JOYSTICK);
	if (TTF_Init() < 0)
	{
		printf("SDL2_ttf could not be initialized!\n"
			"SDL2_ttf Error: %s\n",
			SDL_GetError());
		return 0;
	}
#endif
	if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_TIMER) == -1) // Initialize SDL
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
#if (__DREAMCAST__) || defined (__WIN9X__)// SDL1
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
		SDL_WM_SetCaption("SharkShark", NULL);
#elif defined (__3DS__) || defined (__WII__)
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_FULLSCREEN);
		SDL_WM_SetCaption("SharkShark", NULL);
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		SDL_JoystickEventState(SDL_ENABLE);
		SDL_JoystickOpen(0);
#else // SDL2
		gWindow = SDL_CreateWindow("SharkShark", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
#if defined(IOSBUILD) || defined(__XBOXONE__)
		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);
		SCREEN_WIDTH = dm.w;
		SCREEN_HEIGHT = dm.h;
#elif defined (ANDROID)
		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);
		SDL_SetWindowSize(gWindow, dm.w, dm.h);
		SCREEN_WIDTH = dm.w;
		SCREEN_HEIGHT = dm.h;
#endif
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			exitApp();
			return 0;
		}
#if defined (__3DS__) || defined (__WII__) || defined (__DREAMCAST__) || defined (__WIN9X__) // sdl 1
		screen = SDL_GetWindowSurface(gWindow);
		if (screen == NULL) {
			printf("screen is null! SDL_Error: %s\n", SDL_GetError());
			exitApp();
			return 0;
		}
#else
		renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			printf("renderer is null! SDL_Error: %s\n", SDL_GetError());
			exitApp();
			return 0;
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
#endif

#endif

		next_time = SDL_GetTicks() + TICK_INTERVAL;

		shark = SDL_LoadBMP(RealPath("res/sprites/shark.bmp"));
		if (!shark) { // check if resources are where they're supposed to be
#if defined (XBOX)
			debugPrint("Failed to load res/sprites/shark.bmp file!\n");
#endif
			printf("Failed to load image: %s%s %s\n", SDL_GetBasePath(), RealPath("res/sprites/shark.bmp"), SDL_GetError());
			//printf("Failed to load image: %s %s\n", RealPath("res/sprites/shark.bmp"), SDL_GetError());
			return 0;
		}

		SDL_SetColorKey(shark, colorkey, SDL_MapRGB(shark->format, 0xFF, 0x0, 0xFF)); // NOTE: (SDL1) Images must be 24 bit depth to work with color keys
		shark_dead = SDL_LoadBMP(RealPath("res/sprites/shark_dead.bmp"));
		SDL_SetColorKey(shark_dead, colorkey, SDL_MapRGB(shark_dead->format, 0xFF, 0x0, 0xFF));
		seahorse = SDL_LoadBMP(RealPath("res/sprites/seahorse.bmp"));
		SDL_SetColorKey(seahorse, colorkey, SDL_MapRGB(seahorse->format, 0xFF, 0x0, 0xFF));
		jellyfish = SDL_LoadBMP(RealPath("res/sprites/jellyfish.bmp"));
		SDL_SetColorKey(jellyfish, colorkey, SDL_MapRGB(jellyfish->format, 0xFF, 0x0, 0xFF));
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

		font = TTF_OpenFont(RealPath("res/pixantiqua.ttf"), 25);

#if !defined (__3DS__) && !defined (__WII__) && !defined (__DREAMCAST__) && !defined (__WIN9X__)
			SDL_InitSubSystem(SDL_INIT_JOYSTICK);
			SDL_JoystickEventState(SDL_ENABLE);
			SDL_JoystickOpen(0);
			keys = SDL_GetKeyboardState(NULL);
#endif
			
			//if (Mix_Init(MIX_INIT_MOD | MIX_INIT_MID) == 0) {
			//	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL_mixer.\n");
			//}

			MixerOpenAudio();

			sharkSpawnSound = Mix_LoadWAV(RealPath("res/audio/shark.wav"));
			fishBiteSound = Mix_LoadWAV(RealPath("res/audio/eat.wav"));
			gameOverSound = Mix_LoadWAV(RealPath("res/audio/gameover.wav"));
			deadSound = Mix_LoadWAV(RealPath("res/audio/dead.wav"));
			sharkDeadSound = Mix_LoadWAV(RealPath("res/audio/shark_dead.wav"));
			fishRankUp = Mix_LoadWAV(RealPath("res/audio/bigger.wav")); // NOTE: (SDL1) Game can crash on startup if audio bit-rate is too high

			bgMusic = Mix_LoadMUS(RealPath("res/audio/bg_music.wav"));

			SetVars(SCREEN_WIDTH, SCREEN_HEIGHT);

			UI_pause = TTF_RenderText_Solid(font, "PAUSED !", color_white);
			
			UI_pause_renderQuad.x=SCREEN_WIDTH / 2 - 50;
			UI_pause_renderQuad.y=SCREEN_HEIGHT / 2 - 50;
			UI_pause_renderQuad.w=(Uint16)UI_pause->w;
			UI_pause_renderQuad.h=(Uint16)UI_pause->h;

			UI_died = TTF_RenderText_Solid(font, "PLAYER DIED - PRESS ENTER TO SPAWN", color_white);
			
			UI_died_renderQuad.x=SCREEN_WIDTH / 2 - 250;
			UI_died_renderQuad.y=SCREEN_HEIGHT / 2 - 50;
			UI_died_renderQuad.w=(Uint16)UI_died->w;
			UI_died_renderQuad.h=(Uint16)UI_died->h;

			UI_mainmenu = TTF_RenderText_Solid(font, "SHARK! SHARK! - [S]tart Game", color_white);
			
			UI_mainmenu_renderQuad.x=SCREEN_WIDTH / 2 - 150;
			UI_mainmenu_renderQuad.y=SCREEN_HEIGHT / 2 - 90;
			UI_mainmenu_renderQuad.w=(Uint16)UI_mainmenu->w;
			UI_mainmenu_renderQuad.h=(Uint16)UI_mainmenu->h;

			if (Mix_PlayingMusic() == 0)
				Mix_PlayMusic(bgMusic, -1);

#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop(game_loop, 0, 1);
#else
			while (quit == 0) {
				game_loop();
			}
#endif
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
	SDL_FreeSurface(jellyfish);

	exitApp();

	return 0;
}
