#ifndef __ENEMY_SHRIMP_H__
#define __ENEMY_SHRIMP_H__

#include "Enemy.h"

class Enemy_Shrimp : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Shrimp(int x, int y);
	iPoint original_position;

	// Enemy Hitbox
	int Width;
	int Height;

	void Move();
};

#endif // __ENEMY_EXAMPLE_H__
