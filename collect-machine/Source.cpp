
#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"
#include <time.h>
#include <string>


#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")


int main(int argc, char* argv[]) {
	
	srand(time(NULL));
	
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Event event;
	//bool for the loop
	bool isRunning = true;

	//Bools for keys
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	
	//bools for player 2
	bool up2 = false;
	bool down2 = false;
	bool left2 = false;
	bool right2 = false;
	

	SDL_Surface *surface;
	//Creating textures
	SDL_Texture *backround;
	SDL_Texture *ship;
	SDL_Texture *ship2;
	

	SDL_Window *window = SDL_CreateWindow("SideScroller Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	//------------------------------------------------------------------------------------------------------------------------------
	//backround
	surface = IMG_Load("space.png");
	if (surface == NULL) {
		isRunning = false;
	}
	backround = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);


	//spaceship
	surface = IMG_Load("spaceship.png");
	if (surface == NULL) {
		isRunning = false;
	}
	ship2 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//spaceship2
	surface = IMG_Load("ship2.png");
	if (surface == NULL) {
		isRunning = false;
	}
	ship = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);


	

	//------------------------------------------------------------------------------------------------------------------------------------
	

	//Creating square
	SDL_Rect rect;
	rect.w = 120;
	rect.h = 120;
	rect.x = 660;
	rect.y = 510;

	//second PLayer
	SDL_Rect rect2;
	rect2.w = 120;
	rect2.h = 120;
	rect2.x = 220;
	rect2.y = 170;

	//creating boxes
	SDL_Rect box;
	box.w = 40;
	box.h = 40;
	box.x = rand() % (1000 - box.h);
	box.y = 0;
	

	//score 1
	unsigned short count1 = 0;

	//score 2
	unsigned short count2 = 0;


	//Starting loop
	while (isRunning) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}


			//if the key is pressed
			else if (event.type == SDL_KEYDOWN)
			{

				if (event.key.keysym.sym == SDLK_UP)
				{
					up = true;

				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					down = true;
				}
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					left = true;
				}
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					right = true;
				}

				//player2
				if (event.key.keysym.sym == SDLK_w)
				{
					up2 = true;

				}
				if (event.key.keysym.sym == SDLK_s)
				{
					down2 = true;
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					left2 = true;
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					right2 = true;
				}



			}

			//if the key is released
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_UP)
				{
					up = false;
				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					down = false;
				}
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					left = false;
				}
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					right = false;
				}
				//player2

				if (event.key.keysym.sym == SDLK_w)
				{
					up2 = false;
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					down2 = false;
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					left2 = false;
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					right2 = false;
				}

			}
		}



		//if key is pressed move the spaceship
		if (up == true) {
			rect.y -= 1;
		}

		if (down == true) {
			rect.y += 1;
		}

		if (left == true) {
			rect.x -= 1;
		}

		if (right == true) {
			rect.x += 1;
		}

		if (up2 == true) {
			rect2.y -= 1;
		}

		if (down2 == true) {
			rect2.y += 1;
		}

		if (left2 == true) {
			rect2.x -= 1;
		}

		if (right2 == true) {
			rect2.x += 1;
		}
		
		if (box.y <= 800) {
		box.y++;
		}

		else if (box.y >= 800) {
			box.y = 0;
			box.x = rand() % (1000 - box.h);
		}
		
		if (box.x >= rect.x && box.x < (rect.x + rect.w) && box.y > rect.y && box.y < (rect.y + rect.h)) {
			box.y = 0;
			box.x = rand() % (1000 - box.h);
			count1++;
		}

		if (box.x >= rect2.x && box.x < (rect2.x + rect2.w) && box.y > rect2.y && box.y < (rect2.y + rect2.h)) {
			box.y = 0;
			box.x = rand() % (1000 - box.h);
			count2++;
		}
		
		//limits of movement
		if (rect.x < 0) {
			rect.x = 0;
		}
		else if (rect.x > 1000 - rect.w) {
			rect.x = 1000 - rect.w;
		}
		if (rect.y < 0) {
			rect.y = 0;
		}
		else if (rect.y > 800 -rect.h) {
			rect.y = 800 - rect.h;
		}

		//limints player 2

		if (rect2.x < 0) {
			rect2.x = 0;
		}
		else if (rect2.x > 1000 - rect2.w) {
			rect2.x = 1000 - rect2.w;
		}
		if (rect2.y < 0) {
			rect2.y = 0;
		}
		else if (rect2.y > 800 - rect2.h) {
			rect2.y = 800 - rect2.h;
		}


		SDL_RenderCopy(renderer, backround, NULL, NULL);
		SDL_RenderCopy(renderer, ship, NULL, &rect);
		SDL_RenderCopy(renderer, ship2, NULL, &rect2);
		SDL_RenderCopy(renderer, ship, NULL, &box);
		

		SDL_RenderPresent(renderer);

		SDL_Delay(1);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	
	
	return 0;
}

