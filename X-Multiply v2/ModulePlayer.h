#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score = 0;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation upward;
	Animation downward;
	iPoint position;
	Collider* playerHitbox;

	uint shot; //fx shot sound
	uint death; //fx when player dies

	bool godmode = false;
	bool destroyed = false;
};

#endif