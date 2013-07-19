
#include "includes.h"

Image *cloudimage = 0;

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
	spacerfont = new Font ("res/upheavtt.ttf", 40);
	cam = new Camera ();
	starfield = new Starfield ();
	playership = new PlayerShip (display);
	starfield->cam = cam;
	playership->cam = cam;
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
			if (playership->mode == 1) {
				Cloud *newcloud = new Cloud (display);
				newcloud->x = playership->x; // + playership->cx;
				newcloud->y = playership->y; // + playership->cy;
				newcloud->cam = cam;
				newcloud->velx = playership->velx - sin (playership->angle)*2;
				newcloud->vely = playership->vely + cos (playership->angle)*2;
				clouds.add (newcloud);
			}
			for (BPNode<Cloud> *c = clouds.first; c; c=c->next) {
				c->data->advance ();
				// TODO: filter out finished clouds
			}
			playership->advance ();
			cam->x = playership->x;
			cam->y = playership->y;
			display->clear ();
			starfield->draw (display);
			for (BPNode<Cloud> *c = clouds.first; c; c=c->next) {
				c->data->draw (display);
			}
			playership->draw (display);
			
			Image *txtimg = spacerfont->create_text (
				display,"Hello World : 0123456789", 0xff00ff00);
			txtimg->draw (display,0,0);
			
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
	graphangle = angle - frame*2*PI/32;
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

Cloud::Cloud (Display *display) :
	Sprite (
		cloudimage == 0 ?
			(cloudimage = new Image (display, "res/cloud.png", true, 1, 1))
			: cloudimage
	)
{
	w /= 8;
	h /= 8;
	cx = w/2;
	cy = h/2;
	velx = 0;
	vely = 0;
}

void Cloud::advance ()
{
	alpha -= 0.005;
	if (alpha < 0) alpha = 0;
	w += 0.5;
	h += 0.5;
	cx = w/2;
	cy = h/2;
	
	x += velx;
	y += vely;
}


