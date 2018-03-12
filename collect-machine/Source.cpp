
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

	// bool to restart the game
	bool space = false; 

	//score 1
	unsigned short count1 = 0;

	//score 2
	unsigned short count2 = 0;
	

	SDL_Surface *surface;
	//Creating textures
	SDL_Texture *backround;
	SDL_Texture *ship;
	SDL_Texture *ship2;
	SDL_Texture *fuel;

	SDL_Texture *img0;
	SDL_Texture *img1;
	SDL_Texture *img2;
	SDL_Texture *img3;
	SDL_Texture *img4;
	SDL_Texture *img5;
	SDL_Texture *img6;
	SDL_Texture *img7;
	SDL_Texture *img8;
	SDL_Texture *img9;

	SDL_Texture *img0red;
	SDL_Texture *img1red;
	SDL_Texture *img2red;
	SDL_Texture *img3red;
	SDL_Texture *img4red;
	SDL_Texture *img5red;
	SDL_Texture *img6red;
	SDL_Texture *img7red;
	SDL_Texture *img8red;
	SDL_Texture *img9red;

	SDL_Texture *win1;
	SDL_Texture *win2;
	

	SDL_Window *window = SDL_CreateWindow("Hommer vs Wiggum", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	//------------------------------------------------------------------------------------------------------------------------------
	//backround
	surface = IMG_Load("clouds.jpg");
	if (surface == NULL) {
		isRunning = false;
	}
	backround = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);


	//spaceship
	surface = IMG_Load("homer.png");
	if (surface == NULL) {
		isRunning = false;
	}
	ship2 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//spaceship2
	surface = IMG_Load("wiggum.png");
	if (surface == NULL) {
		isRunning = false;
	}
	ship = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//Fuel
	surface = IMG_Load("donut.png");
	if (surface == NULL) {
		isRunning = false;
	}
	fuel = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//-------Loading scores ------------
	//0
	surface = IMG_Load("0.png");

	img0 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//1
	surface = IMG_Load("1.png");
	
	img1 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//2
	surface = IMG_Load("2.png");
	
	img2 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//3
	surface = IMG_Load("3.png");
	
	img3 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//4
	surface = IMG_Load("4.png");
	
	img4 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//5
	surface = IMG_Load("5.png");
	
	img5 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//6
	surface = IMG_Load("6.png");

	img6 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//7
	surface = IMG_Load("7.png");

	img7 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//8
	surface = IMG_Load("8.png");

	img8 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//9
	surface = IMG_Load("9.png");

	img9 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//----------red scores----------------

	//0
	surface = IMG_Load("0red.png");

	img0red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//1
	surface = IMG_Load("1red.png");

	img1red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//2
	surface = IMG_Load("2red.png");

	img2red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//3
	surface = IMG_Load("3red.png");

	img3red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//4
	surface = IMG_Load("4red.png");

	img4red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//5
	surface = IMG_Load("5red.png");

	img5red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//6
	surface = IMG_Load("6red.png");

	img6red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//7
	surface = IMG_Load("7red.png");

	img7red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//8
	surface = IMG_Load("8red.png");

	img8red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//9
	surface = IMG_Load("9red.png");

	img9red = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//-----loading winner page--------

	surface = IMG_Load("win1.png");

	win1 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("win2.png");

	win2 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	
	

	//Creating square
	SDL_Rect rect;
	rect.w = 120;
	rect.h = 150;
	rect.x = 660;
	rect.y = 510;

	//second PLayer
	SDL_Rect rect2;
	rect2.w = 120;
	rect2.h = 150;
	rect2.x = 220;
	rect2.y = 510;

	//creating boxes
	SDL_Rect box;
	box.w = 40;
	box.h = 40;
	box.x = rand() % (1000 - box.h);
	box.y = 0;

	//scores
	SDL_Rect score1;
	score1.w = 70;
	score1.h = 70;
	score1.x = 930;
	score1.y = 730;

	SDL_Rect score2;
	score2.w = 70;
	score2.h = 70;
	score2.x = 0;
	score2.y = 730;

	//Final 
	SDL_Rect winner;
	winner.w = 1000;
	winner.h = 800;
	winner.x = 0;
	winner.y = 0;
	


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

				//Restart
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					space = true;
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
				
				//Restart
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					space = false;
				}

			}
		}



		//if key is pressed move 
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
			rect2.x +=1;
		}
		//Restart
		if (space == true) {
			count1 = 0; 
			count2 = 0; 
			rect2.x = 220;
			rect2.y = 510;
			rect.x = 660;
			rect.y = 510;
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

		//in game
		SDL_RenderCopy(renderer, backround, NULL, NULL);
		SDL_RenderCopy(renderer, ship, NULL, &rect);
		SDL_RenderCopy(renderer, ship2, NULL, &rect2);
		SDL_RenderCopy(renderer, fuel, NULL, &box);

		//Score 1
		if (count1 == 0) {
			SDL_RenderCopy(renderer, img0, NULL, &score1);
		}
		if (count1 == 1) {
			SDL_RenderCopy(renderer, img1, NULL, &score1);
		}
		if (count1 == 2) {
			SDL_RenderCopy(renderer, img2, NULL, &score1);
		}
		if (count1 == 3) {
			SDL_RenderCopy(renderer, img3, NULL, &score1);
		}
		if (count1 == 4) {
			SDL_RenderCopy(renderer, img4, NULL, &score1);
		}
		if (count1 == 5) {
			SDL_RenderCopy(renderer, img5, NULL, &score1);
		}
		if (count1 == 6) {
			SDL_RenderCopy(renderer, img6, NULL, &score1);
		}
		if (count1 == 7) {
			SDL_RenderCopy(renderer, img7, NULL, &score1);
		}
		if (count1 == 8) {
			SDL_RenderCopy(renderer, img8, NULL, &score1);
		}
		if (count1 == 9) {
			SDL_RenderCopy(renderer, img9, NULL, &score1);
		}
		
		

		//score2
	
		if (count2 == 0) {
			SDL_RenderCopy(renderer, img0red, NULL, &score2);
		}
		if (count2 == 1) {
			SDL_RenderCopy(renderer, img1red, NULL, &score2);
		}
		if (count2 == 2) {
			SDL_RenderCopy(renderer, img2red, NULL, &score2);
		}
		if (count2 == 3) {
			SDL_RenderCopy(renderer, img3red, NULL, &score2);
		}
		if (count2 == 4) {
			SDL_RenderCopy(renderer, img4red, NULL, &score2);
		}
		if (count2 == 5) {
			SDL_RenderCopy(renderer, img5red, NULL, &score2);
		}
		if (count2 == 6) {
			SDL_RenderCopy(renderer, img6red, NULL, &score2);
		}
		if (count2 == 7) {
			SDL_RenderCopy(renderer, img7red, NULL, &score2);
		}
		if (count2 == 8) {
			SDL_RenderCopy(renderer, img8red, NULL, &score2);
		}
		if (count2 == 9) {
			SDL_RenderCopy(renderer, img9red, NULL, &score2);
		}

		//-------winner is-----------
		if (count2 == 10) {
			SDL_RenderCopy(renderer, win2, NULL, NULL);
			SDL_Delay(50);
		}
		if (count1 == 10) {
			SDL_RenderCopy(renderer, win1, NULL, NULL);
			SDL_Delay(50);
		}


		SDL_RenderPresent(renderer);

		SDL_Delay(1);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	
	
	return 0;
}

