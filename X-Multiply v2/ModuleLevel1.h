#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"

struct SDL_Texture;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1();
	~ModuleLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* background = nullptr;
	SDL_Texture* hud = nullptr;
	SDL_Texture* tilemap1 = nullptr;

	SDL_Rect background_parallax;
	SDL_Rect ground_parallax;
};

#endif // __MODULESCENESPACE_H__