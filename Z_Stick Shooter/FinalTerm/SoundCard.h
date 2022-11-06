#pragma once
#include <SDL_mixer.h>

class SoundCard {
public:


	void PmenuMusic() { Mix_PlayMusic(menuMusic, -1); }
	void PplayingMusic() { Mix_PlayMusic(playingMusic, -1); }
	void PdeadMusic() { Mix_PlayMusic(deadMusic, -1); }
	void cutMusic(Mix_Music* music) { Mix_FreeMusic(music); }
	void shootSound(int i) { Mix_PlayChannel(-1, shoot, i); }
	void reloadSound(int i) { Mix_PlayChannel(-1, reload, i); }
	void PzomRoarSound(int i) { Mix_PlayChannel(-1, PzomRoar, i); }
	void zHIt1Sound(int i) { Mix_PlayChannel(-1,zHit1, i); }
	void zHIt2Sound(int i) { Mix_PlayChannel(-1, zHit2, i); }
	void playerHitSound(int i) { Mix_PlayChannel(-1, playerHit, i); }
	
	Mix_Music* menuMusic = NULL;
	Mix_Music* playingMusic = NULL;
	Mix_Music* deadMusic = NULL;
	Mix_Chunk* reload = NULL;
	Mix_Chunk* shoot = NULL;
	Mix_Chunk* PzomRoar = NULL;
	Mix_Chunk* zHit1 = NULL;
	Mix_Chunk* zHit2 = NULL;
	Mix_Chunk* playerHit = NULL;
	static SoundCard* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new SoundCard();
			return s_pInstance;
		}
		return s_pInstance;
	}
private:
	static SoundCard* s_pInstance;
	SoundCard() { Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048), Mix_VolumeMusic(100),
		menuMusic = Mix_LoadMUS("assets/MenuMusic.mp3"),
	playingMusic = Mix_LoadMUS("assets/playMusic.mp3"),
	deadMusic = Mix_LoadMUS("assets/DeadMusic.mp3"),
	reload = Mix_LoadWAV("assets/reload.wav"),
	shoot = Mix_LoadWAV("assets/shot.wav"),
	PzomRoar = Mix_LoadWAV("assets/MaleZombieRoar.wav"),
	zHit1 = Mix_LoadWAV("assets/zHit1.wav"),
	zHit2 = Mix_LoadWAV("assets/zHit2.wav"),
	playerHit = Mix_LoadWAV("assets/pHit.wav"); }

	
};

