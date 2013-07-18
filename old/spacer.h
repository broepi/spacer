
class Drawable;
class Game;
class Image;
class Display;
class Starfield;
class Star;
class PlayerShip;



class Game
{
private:
	bool running;
	Display *display;
	Starfield *starfield;
	PlayerShip *playership;
public:
	Game ();
	~Game ();
	void run ();
};


class Display
{
public:
	int width, height;
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	Display ();
	~Display ();
};



class Drawable
{
public:
	virtual void draw (Display *display) {};
};


class Image
{
private:
	bool texture;
	int width, height;
	int cols, rows;
	SDL_Surface *surf;
	SDL_Texture *tex;
public:
	Image (Display *display, char *filename, bool texture, int cols, int rows);
	void draw (Display *display, int x, int y, int frame);
};


class Sprite : public Drawable
{
private:
	int x, y;
	Image *img;
	int frame;
public:
	Sprite (Image *img);
	int get_x ();
	int get_y ();
	void set_pos (int x, int y);
};


class Starfield : public Drawable
{
private:
	int numstars;
	int width, height;
	Star **stars;
public:
	Starfield ();
	void draw (Display *display, int x, int y);
private:
	void draw_star (Display *display, int x, int y, float fb);
};


class Star
{
public:
	int x, y;
	float brightness;
	Star (int x, int y, float b);
};


class PlayerShip : public Sprite
{
private:
	int x, y;
	int vel;
	float velx, vely;
	float angle;
public:
	PlayerShip ();
	void advance ();
	void accelerate ();
	void turn_left ();
	void turn_right ();
};

