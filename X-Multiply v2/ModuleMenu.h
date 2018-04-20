#ifndef __MODULEMENU_H__
#define __MODULEMENU_H__

#include "Module.h"

struct SDL_Texture;

class ModuleMenu : public Module
{
public:
	ModuleMenu();
	~ModuleMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* background = nullptr;
	uint fx = 0;
};

#endif // __MODULESCENEINTRO_H__