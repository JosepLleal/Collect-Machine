#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	explosion_enemy.anim.PushBack({ 17, 244, 30, 29 });
	explosion_enemy.anim.PushBack({ 50, 247, 29, 25 });
	explosion_enemy.anim.PushBack({ 79, 240, 48, 36 });
	explosion_enemy.anim.PushBack({ 131, 242, 41, 31 });
	explosion_enemy.anim.PushBack({ 177, 241, 45, 34 });
	explosion_enemy.anim.PushBack({ 21, 287, 42, 39 });
	explosion_enemy.anim.PushBack({ 69, 286, 40, 38 });
	explosion_enemy.anim.PushBack({ 116, 287, 39, 37 });
	explosion_enemy.anim.PushBack({ 163, 286, 43, 43 });
	explosion_enemy.anim.loop = false;
	explosion_enemy.anim.speed = 0.3f;

	enemy_shot.anim.PushBack({ 253, 9, 10, 10 });
	enemy_shot.anim.PushBack({ 271, 10, 10, 10 });
	enemy_shot.anim.PushBack({ 254, 25, 10, 10 });
	enemy_shot.anim.PushBack({ 271, 25, 10, 10 });
	enemy_shot.anim.speed = 0.1f;
	enemy_shot.anim.loop = true;
	enemy_shot.speed.x = -2;
	enemy_shot.speed.y = 1;
	enemy_shot.life = 4000;

	player_death.anim.PushBack({ 112, 144, 16, 16 });
	player_death.anim.PushBack({ 96, 144, 16, 16 });
	player_death.anim.PushBack({ 80, 144, 16, 16 });
	player_death.anim.PushBack({ 64, 144, 16, 16 });
	player_death.anim.PushBack({ 48, 144, 16, 16 });
	player_death.anim.PushBack({ 32, 144, 16, 16 });
	player_death.anim.PushBack({ 16, 144, 16, 16 });
	player_death.anim.PushBack({ 0, 144, 16, 16 });
	player_death.anim.speed = 0.5f;
	player_death.anim.loop = false;

	shot.anim.PushBack({ 64, 38, 16, 5 });
	shot.anim.speed = 0.1f;
	shot.speed.x = 7;
	shot.life = 950;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("image/particles.png");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	// Unload fx

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// play the audio SFX
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

