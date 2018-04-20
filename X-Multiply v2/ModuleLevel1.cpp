#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleLevel1.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleLevel1::ModuleLevel1()
{
	// tilemap
	ground_parallax.x = 0;
	ground_parallax.y = 1;
	ground_parallax.w = 4961;
	ground_parallax.h = 587;

	// Background 
	background_parallax.x = 0;
	background_parallax.y = 0;
	background_parallax.w = 4961;
	background_parallax.h = 587;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("image/background completed.png");
	tilemap1 = App->textures->Load("image/LV1_TilemapCompleted.png");
	hud = App->textures->Load("image/xmultiply_hud.png");

	App->audio->MusicPlay("Sound/04_Into_the_Human_Body_Stage_1_.ogg", 0.5f);

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	
	//--------- TOP LARGER WALL --------- 
	App->collision->AddCollider({ 495, 0, 2025, 14 }, COLLIDER_WALL); //square of all the top wall 

																	  //--------- BOTTOM LARGER WALL --------- 
	App->collision->AddCollider({ 0, 242, 2549, 15 }, COLLIDER_WALL);

	//--------- TOP OBSTACLES --------- 
	App->collision->AddCollider({ 640, 14, 70, 14 }, COLLIDER_WALL); //1st 

	App->collision->AddCollider({ 761, 14, 57, 16 }, COLLIDER_WALL); //2nd 1
	App->collision->AddCollider({ 770, 30, 30, 18 }, COLLIDER_WALL); //2nd 2

	App->collision->AddCollider({ 1010, 14, 75, 29 }, COLLIDER_WALL); //3rd 1
	App->collision->AddCollider({ 1085, 14, 20, 15 }, COLLIDER_WALL); //3rd 2

	App->collision->AddCollider({ 1153, 14, 70, 14 }, COLLIDER_WALL); //4th 

	App->collision->AddCollider({ 1665, 14, 70, 14 }, COLLIDER_WALL); //After first entrance top

	App->collision->AddCollider({ 2425, 14, 57, 16 }, COLLIDER_WALL); //After biggest entrance 1 top
	App->collision->AddCollider({ 2430, 30, 30, 18 }, COLLIDER_WALL); //After biggest entrance 2 top

																	  //--------- BOTTOM OBSTACLES --------- 
	App->collision->AddCollider({ 414, 210, 30, 16 }, COLLIDER_WALL); //1st 1
	App->collision->AddCollider({ 408, 226, 57, 16 }, COLLIDER_WALL); //1st 2

	App->collision->AddCollider({ 497, 215, 75, 27 }, COLLIDER_WALL); //2nd 1
	App->collision->AddCollider({ 572, 227, 20, 15 }, COLLIDER_WALL); //2nd 2

	App->collision->AddCollider({ 1024, 230, 70, 12 }, COLLIDER_WALL); //3rd

	App->collision->AddCollider({ 1263, 215, 104, 27 }, COLLIDER_WALL); //4th

	App->collision->AddCollider({ 1790, 210, 30, 16 }, COLLIDER_WALL); //After first entrance 1 bottom 
	App->collision->AddCollider({ 1784, 226, 57, 16 }, COLLIDER_WALL); //After first entrance 2 bottom

	App->collision->AddCollider({ 2548, 219, 318, 38 }, COLLIDER_WALL); //Just before scroll

	App->collision->AddCollider({ 2657, 253, 225, 133 }, COLLIDER_WALL);

	//-------- First Entrance TOP --------- 
	App->collision->AddCollider({ 1551, 14, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 1545, 63, 15, 15 }, COLLIDER_WALL); //small square 2
	App->collision->AddCollider({ 1423, 14, 128, 27 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 1435, 41, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1446, 56, 100, 15 }, COLLIDER_WALL); // squares are organized from top to bottom
	App->collision->AddCollider({ 1455, 71, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1460, 86, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1475, 101, 65, 8 }, COLLIDER_WALL); //bottom square 

																	  //--------- First Entrance BOTTOM --------- 
	App->collision->AddCollider({ 1475, 147, 65, 8 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 1460, 155, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1455, 170, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1446, 185, 100, 15 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 1435, 200, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1423, 215, 128, 27 }, COLLIDER_WALL); //bottom square
	App->collision->AddCollider({ 1551, 228, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 1545, 176, 15, 15 }, COLLIDER_WALL); //small square 2

																	   //--------- Second Entrance TOP (biggest one) --------- 
	App->collision->AddCollider({ 2009, 14, 190, 28 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 2025, 42, 175, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2040, 57, 140, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2040, 72, 115, 10 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 2015, 82, 135, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2009, 92, 87, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2129, 92, 10, 17 }, COLLIDER_WALL); //bottom square
	App->collision->AddCollider({ 2199, 14, 13, 35 }, COLLIDER_WALL); //smalles square 1
	App->collision->AddCollider({ 2212, 14, 57, 8 }, COLLIDER_WALL); //smallest square 2

																	 //--------- Second Entrance BOTTOM (biggest one) --------- 
	App->collision->AddCollider({ 2129, 147, 10, 17 }, COLLIDER_WALL); // top square
	App->collision->AddCollider({ 2009, 147, 87, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2015, 164, 135, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2040, 174, 115, 10 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 2040, 184, 140, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2025, 199, 175, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2009, 214, 190, 28 }, COLLIDER_WALL); //bottom square 
	App->collision->AddCollider({ 2199, 207, 13, 35 }, COLLIDER_WALL); //smallest square 1 
	App->collision->AddCollider({ 2212, 234, 57, 8 }, COLLIDER_WALL); //smallest square 2

																	  //--------- Before Scroll --------- 
	App->collision->AddCollider({ 2715, 194, 50, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2805, 209, 36, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2882, 247, 105, 73 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2987, 275, 76, 45 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3040, 320, 172, 170 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3212, 354, 72, 137 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3284, 375, 94, 117 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3378, 427, 177, 64 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3552, 461, 131, 53 }, COLLIDER_WALL);

	//--------- TOP SCROLL --------- 
	App->collision->AddCollider({ 2917, 0, 122, 43 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2997, 43, 48, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3045, 43, 200, 33 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3065, 76, 60, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3125, 76, 100, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3170, 106, 100, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3230, 119, 60, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3260, 134, 30, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3291, 130, 100, 33 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3310, 163, 60, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3322, 189, 75, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3397, 163, 90, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3450, 217, 200, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3505, 237, 140, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3600, 255, 50, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3630, 265, 50, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3650, 280, 50, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3675, 290, 50, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3705, 300, 20, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3730, 305, 240, 55 }, COLLIDER_WALL);

	//--------- BOTTOM SCROLL --------- 

	//--------- After Scroll TOP --------- 
	App->collision->AddCollider({ 3800, 293, 1200, 12 }, COLLIDER_WALL);

	//--------- After Scroll BOTTOM --------- 
	App->collision->AddCollider({ 3675, 537, 1300, 13 }, COLLIDER_WALL); //square of all bottom 

	App->collision->AddCollider({ 3955, 510, 75, 27 }, COLLIDER_WALL); //1st obstacle 1 
	App->collision->AddCollider({ 4030, 522, 20, 15 }, COLLIDER_WALL); //1st obstacle 2

	App->collision->AddCollider({ 4225, 525, 70, 12 }, COLLIDER_WALL); //2nd obstacle 

	App->collision->AddCollider({ 4353, 503, 27, 16 }, COLLIDER_WALL); //3rd obstacle 1
	App->collision->AddCollider({ 4345, 519, 57, 18 }, COLLIDER_WALL); //3rd obstacle 2

																	   //--------- After Scroll ENTRANCE TOP --------- 
	App->collision->AddCollider({ 4623, 305, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 4617, 357, 15, 15 }, COLLIDER_WALL); //small square 2
	App->collision->AddCollider({ 4495, 305, 128, 31 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 4507, 336, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4518, 351, 100, 15 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 4527, 366, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4532, 381, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4547, 396, 65, 8 }, COLLIDER_WALL); //bottom square 

	//--------- After Scroll ENTRANCE BOTTOM --------- 
	App->collision->AddCollider({ 4542, 440, 65, 8 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 4532, 448, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4527, 463, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4518, 478, 100, 15 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 4507, 493, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4495, 508, 128, 29 }, COLLIDER_WALL); //bottom square
	App->collision->AddCollider({ 4623, 521, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 4617, 469, 15, 15 }, COLLIDER_WALL); //small square 2

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 665, 80);
	
	/*App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 735, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 750, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 775, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 790, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 890, 100);

	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 900, 195);*/
	
	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);
	App->textures->Unload(tilemap1);
	App->textures->Unload(hud);

	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Move camera forward -----------------------------
	App->render->camera.x += 1 * SCREEN_SIZE;

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, &background_parallax, 0.75f, true); // backround
	App->render->Blit(tilemap1, 0, 0, &ground_parallax, 1.0f, true);
	App->render->Blit(hud, 0, 257, NULL, 0.0f, false);
	
	return UPDATE_CONTINUE;
}