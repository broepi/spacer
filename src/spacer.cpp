
#include "includes.h"

#define PI 3.14159265359

int main ()
{
	Game *game = new Game ();
	game->run ();
	delete game;
}

Game::Game ()
{
	running = false;
	
	srand (time(0));
	
	if (SDL_Init (SDL_INIT_VIDEO) != 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
	
	if (TTF_Init () != 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		exit (-1);
	}
	
	if (IMG_Init (IMG_INIT_PNG) == 0) {
		cerr << "IMG error: " << IMG_GetError () << endl;
		exit (-1);
	}
	
	display = new Display ();
	cam = new Camera ();
	starfield = new Starfield ();
	playership = new PlayerShip (display);
	starfield->set_cam (cam);
	playership->set_cam (cam);
	cam->cx = display->width/2;
	cam->cy = display->height/2;
}

Game::~Game ()
{
	delete playership;
	delete starfield;
	delete display;
	IMG_Quit ();
	TTF_Quit ();
	SDL_Quit ();
}

void Game::run ()
{
	running = true;
	
	int lasttick = SDL_GetTicks ();
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					display->width = event.window.data1;
					display->height = event.window.data2;
					cam->cx = display->width/2;
					cam->cy = display->height/2;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					playership->start_turn_left ();
					break;
				case SDLK_RIGHT:
					playership->start_turn_right ();
					break;
				case SDLK_UP:
					playership->start_accelerate ();
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					playership->stop_turning ();
					break;
				case SDLK_RIGHT:
					playership->stop_turning ();
					break;
				case SDLK_UP:
					playership->start_float ();
					break;
				}
				break;
			}
		}
		int curtick = SDL_GetTicks ();
		if (curtick-lasttick >= 16) {
			playership->advance ();
			cam->x = playership->get_x ();
			cam->y = playership->get_y ();
			display->clear ();
			starfield->draw (display);
			playership->draw (display);
			display->present ();
			lasttick = SDL_GetTicks ();
		}
	}
}

PlayerShip::PlayerShip (Display *display) : 
	Sprite (new Image (display, "res/spaceship.png", true, 8, 8))
{
	x = 0;
	y = 0;
	velx = 0.0;
	vely = 0.0;
	angle = 0.0; // 0.0 means looking along negative y-axis, walking clockwise
	mode = 0;
	turnmode = 0;
}

void PlayerShip::advance ()
{
	if (turnmode == 1) {
		angle -= (2*PI)/32 * 0.5;
	}
	else if (turnmode == 2) {
		angle += (2*PI)/32 * 0.5;
	}
	frame = modulo ( floor ((angle / (2*PI)) * 32), 32);
	if (mode == 1) {
		frame += 32;
		float dx = sin (angle);
		float dy = -cos (angle);
		velx += dx * 0.1;
		vely += dy * 0.1;
	}
	x += velx;
	y += vely;
}

void PlayerShip::start_accelerate ()
{
	mode = 1;
}

void PlayerShip::start_float ()
{
	mode = 0;
}

void PlayerShip::start_turn_left ()
{
	turnmode = 1;
}

void PlayerShip::start_turn_right ()
{
	turnmode = 2;
}

void PlayerShip::stop_turning ()
{
	turnmode = 0;
}

