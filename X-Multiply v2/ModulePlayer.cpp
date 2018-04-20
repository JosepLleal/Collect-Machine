#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"

#include<stdio.h>


ModulePlayer::ModulePlayer()
{
	// idle animation (just the ship)
	idle.PushBack({ 100, 0, 38, 16 });

	// go upward animation 
	upward.PushBack({ 52, 0, 38, 16 });
	upward.PushBack({ 4, 0, 38, 16 });
	upward.loop = false;
	upward.speed = 0.1f;

	// Move down
	downward.PushBack({ 148, 0, 38, 16 });
	downward.PushBack({ 196, 0, 38, 16 });
	downward.loop = false;
	downward.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Image/Main_Character_Effects.png");

	destroyed = false;
	position.x = 150;
	position.y = 120;
	score = 0;

	playerHitbox = App->collision->AddCollider({position.x, position.y, 32, 16}, COLLIDER_PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	font_score = App->fonts->Load("fonts/rtype_font3.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 2);


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);
	if(playerHitbox)
		playerHitbox->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	position.x += 1; // Automatic movement

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed * 2;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if(current_animation != &downward)
		{
			downward.Reset();
			current_animation = &downward;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if(current_animation != &upward)
		{
			upward.Reset();
			current_animation = &upward;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot, position.x + 28, position.y + 6, COLLIDER_PLAYER_SHOT);
		
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	   && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	playerHitbox->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	if(destroyed == false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	// Draw UI (score) --------------------------------------
	sprintf_s(score_text, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(10, 10, font_score, "rtype");

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == playerHitbox && destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->lvl1, (Module*)App->menu);
		App->particles->AddParticle(App->particles->player_death, position.x, position.y, COLLIDER_NONE);
		

		destroyed = true;
	}
}