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
#include "ModuleAudio.h"

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

	shot = App->audio->LoadFX("Sound/xmultipl-122.wav"); //Loading FX of shot
	death = App->audio->LoadFX("Sound/xmultipl-044.wav"); //Loading FX when player dies

	destroyed = false;
	godmode = false;

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

	//Unloading FX
	App->audio->UnloadFX(shot);
	App->audio->UnloadFX(death);

	/*if(playerHitbox)
		playerHitbox->to_delete = true;*/

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	position.x += 1; // Automatic movement

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed * 2;
	}

	if(App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if(current_animation != &downward)
		{
			downward.Reset();
			current_animation = &downward;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
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
		App->audio->ChunkPlay(shot);
		
	}

	if(App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
	   && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	// Prevent Player from leaving bordrer -------------------------------------
	//x lim
	if (position.x <= abs(App->render->camera.x) / SCREEN_SIZE)
	{
		position.x = 1 + (abs(App->render->camera.x) / SCREEN_SIZE);
	}
	else if (position.x >= ((abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH - 38)))
	{
		position.x = -1 + ((abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH - 38));
	}

	//y lim

	if (position.y <= abs(App->render->camera.y) / SCREEN_SIZE)
	{
		position.y = 1 + abs(App->render->camera.y) / SCREEN_SIZE;
	}
	else if (position.y >= (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 45) 
	{
		position.y = -1 + (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 45;
	}

	//GOD MODE FUNCTION ---------------------------------------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
	{
		godmode = !godmode;

		if (godmode == true)
		{
			LOG("GodMode on");
			playerHitbox->to_delete = true;
			playerHitbox = nullptr;
		}
		else if (godmode == false)
		{
			LOG("GodMode off");
			playerHitbox = App->collision->AddCollider({ position.x, position.y, 36, 16 }, COLLIDER_PLAYER, this);
		}
	}


	//-----------------------------------------------------------------------------------------------------------------------
	if(godmode == false)
		playerHitbox->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	if(destroyed == false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), true);
	
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
		App->particles->AddParticle(App->particles->player_death, position.x, position.y, COLLIDER_NONE);
		App->audio->ChunkPlay(death);
		playerHitbox->to_delete = true;
		App->fade->FadeToBlack((Module*)App->lvl1, (Module*)App->menu, 2.0f);
		

		destroyed = true;
	}
}