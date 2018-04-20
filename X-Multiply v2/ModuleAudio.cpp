#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleMenu.h"

#pragma comment (lib, "SDL_mixer/libx86/SDL2_mixer.lib")



ModuleAudio::ModuleAudio() {}

ModuleAudio::~ModuleAudio() {}

bool ModuleAudio::Init()
{
	LOG("Creating the music");
	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		LOG("Broken: %s ", SDL_GetError());
		ret = false;
	}

	else
	{
		// Initialize Audio
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	}

	return ret;
}


bool ModuleAudio::CleanUp()
{
	if (music != nullptr)
	{
		Mix_FreeMusic(music);
	}

	Mix_Quit();

	return true;
}

bool ModuleAudio::MusicPlay(const char* path, float fade_time)
{
	bool ret = true;

	if (music != NULL)
	{
		Mix_FadeOutMusic((int)(fade_time*1000.0f));
	}

	Mix_VolumeMusic(40);
	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Error: %s", path, SDL_GetError());
		ret = false;
	}
	else
	{
		if (Mix_PlayMusic(music, -1) < 0)
		{
			LOG("Cannot play in music %s. Error: %s", path, SDL_GetError());
			ret = false;
		}
	}

	LOG("Playing %s", path);
	return ret;
}

uint ModuleAudio::LoadFX(const char* path)
{
	int ret = LastFx;
	Mix_Chunk* fx = Mix_LoadWAV(path);

	if (fx == nullptr)
	{
		LOG("Cannot load wav %s. Error: %s", path, SDL_GetError());
	}
	else
	{
		FX[LastFx] = fx;
		ret = LastFx++;
	}
	return ret;
}

bool ModuleAudio::UnloadFX(uint last)
{
	bool ret = false;

	if (FX[last] != nullptr)
	{
		Mix_FreeChunk(FX[last]);
		FX[last] = nullptr;
		ret = true;
	}

	return ret;
}

bool ModuleAudio::ChunkPlay(uint last)
{
	bool ret = false;

	if (FX[last] != nullptr)
	{
		Mix_VolumeChunk(FX[last], 128);
		Mix_PlayChannelTimed(-1, FX[last], 0, 500);
		LOG("Playing fx");
		ret = true;
	}


	return ret;
}