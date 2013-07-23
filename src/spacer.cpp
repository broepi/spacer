
#include "includes.h"

int main ()
{
	Game *game = new Game ();
	game->run ();
	delete game;
}

/**************************************************************************************************/

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
	spaceship_img = new Image (display, "res/spaceship.png", 8, 8);
	cloud_img = new Image (display, "res/cloud.png");
	spaceshiprot_img = new Image (display, "res/spaceship-rot.png");
	spacerfont = new Font ("res/upheavtt.ttf", 40);
	cam = new Camera (display->w, display->h);
	starfield = new Starfield (cam);
	playership = new PlayerShip (spaceship_img, spaceshiprot_img, cam);
}

Game::~Game ()
{
	delete playership;
	delete starfield;
	delete cam;
	delete spacerfont;
	delete cloud_img;
	delete spaceship_img;
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
					display->resize (event.window.data1, event.window.data2);
					cam->w = display->w;
					cam->h = display->h;
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
			lasttick = curtick;
			/*
			if (playership->movemode == 1) {
				Cloud *newcloud = new Cloud (cloud_img, cam);
				newcloud->x = playership->x - sind (playership->angle) * 20;
				newcloud->y = playership->y + cosd (playership->angle) * 20;
				newcloud->vx = playership->vx - sind (playership->angle) * 2;
				newcloud->vy = playership->vy + cosd (playership->angle) * 2;
				clouds.add (newcloud);
			}
			BPNode<Cloud> *node = clouds.first;
			int i = 0;
			while (node) {
				node->data->advance ();
				if (node->data->alpha == 0) {
					BPNode<Cloud> *next = node->next;
					clouds.del (i);
					node = next;
					continue;
				}
				node = node->next;
				i++;
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
			
			/*
			char txtbuf [64];
			sprintf (txtbuf, "Position: %d ; %d", (int)playership->x, (int)playership->y);
			Image *txtimg = spacerfont->create_text (
				display,txtbuf, 0xff00ff00);
			txtimg->draw (display,0,0);
			*/
			
			//
			// ACTING
			//
			if (playership->movemode == 1) {
				Cloud *newcloud = new Cloud (cloud_img, cam);
				newcloud->x = playership->x - sind (playership->angle) * 20;
				newcloud->y = playership->y + cosd (playership->angle) * 20;
				newcloud->vx = playership->vx - sind (playership->angle) * 2;
				newcloud->vy = playership->vy + cosd (playership->angle) * 2;
				clouds.add (newcloud);
			}
			BPNode<Cloud> *node = clouds.first;
			int i = 0;
			while (node) {
				node->data->advance ();
				if (node->data->alpha == 0) {
					BPNode<Cloud> *next = node->next;
					clouds.del (i);
					node = next;
					continue;
				}
				node = node->next;
				i++;
			}
			playership->advance ();
			cam->x = playership->x;
			cam->y = playership->y;
			
			
			//
			// DRAWING
			//
			display->clear ();
			starfield->draw (display);
			for (BPNode<Cloud> *c = clouds.first; c; c=c->next) {
				c->data->draw (display);
			}
			playership->draw (display);
			char txtbuf [64];
			sprintf (txtbuf, "Position: %d ; %d", (int)playership->x, (int)playership->y);
			Image *txtimg = spacerfont->create_text (
				display,txtbuf, 0xff00ff00);
			txtimg->draw (display,0,0);
			delete txtimg;
			display->present ();
		}
	}
}

/**************************************************************************************************/

PlayerShip::PlayerShip (Image *img, Image *rotimg, Camera *cam) :
	Mob (img, cam)
{
	this->rotimg = rotimg;
	rotalpha = 0.0;
	rotation = 0.0;
	movemode = 0;
	turnmode = 0;
}

void PlayerShip::advance ()
{
	double turnfac = 11.25 * 0.04;
	//	rotation -= (2*PI)/32 * turnfac;
	if (turnmode == 1) {
		rotation -= turnfac;
	}
	else if (turnmode == 2) {
		rotation += turnfac;
	}
	else if (turnmode == 0) {
		if (rotation > 0) {
			rotation -= turnfac;
			if (rotation < 0)
				rotation = 0;
		}
		else if (rotation < 0) {
			rotation += turnfac;
			if (rotation > 0)
				rotation = 0;
		}
	}
	angle += rotation;
	frame = modulo ( floor (angle / 360 * 32), 32);
	if (movemode == 1) {
		frame += 32;
		vx += sind (angle) * 0.1;
		vy += -cosd (angle) * 0.1;
	}
	alpha = 1.0 - max (0.0, min (0.75, (abs(rotation)-20) / 40));
	rotalpha = 1.0 - alpha;
	Mob::advance ();
}

void PlayerShip::draw (Display *display)
{
	double tmp = angle;
	angle = angle - frame*11.25;
	Mob::draw (display);
	angle = tmp;
	rotimg->draw (display, get_screen_x (), get_screen_y (), sx, sy, 0, 0, rotalpha);
}

void PlayerShip::start_accelerate ()
{
	movemode = 1;
}

void PlayerShip::start_float ()
{
	movemode = 0;
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

/**************************************************************************************************/

Cloud::Cloud (Image *img, Camera *cam) :
	Mob (img, cam)
{
	sx = sy = 1.0/8.0;
	cx = cy = 0.5;
}

void Cloud::advance ()
{
	alpha *= 0.975;
	if (alpha < 0.01) alpha = 0;
	sx += 0.01;
	sy += 0.01;
	
	Mob::advance ();
}

