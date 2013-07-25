
#ifndef GRAPHICS_H
#define GRAPHICS_H

double modulo (double x, int y);
double radtodeg (double r);
double degtorad (double d);
double sind (double d);
double cosd (double d);

/**************************************************************************************************/

class Image;

/**************************************************************************************************/

class Display
{
public:
	int w, h;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Display ();
	~Display ();
	void clear ();
	void present ();
	void resize (int w, int h);
	void set_target (Image *img);
};

/**************************************************************************************************/

class Drawable
{
public:
	virtual void draw () {};
};

/**************************************************************************************************/

class Image
{
public:
	Display *display;
	int w, h;
	int cols, rows;
	int fw, fh;
	SDL_Texture *tex;

	Image (Display *display, char *filename = 0, int cols = 1, int rows = 1);
	Image (Display *display, int width, int height);
	~Image ();
	void draw (int x = 0, int y = 0, double sx = 1.0, double sy = 1.0, int frame = 0,
		double angle = 0.0, double alpha = 1.0);
};

/**************************************************************************************************/

class Camera
{
public:
	double x, y; // midpoint
	int w, h;

	Camera (int w, int h);
};

/**************************************************************************************************/

class Sprite : public Drawable
{
public:
	double x, y;
	double sx, sy; // scaling 0..1
	double cx, cy; // ranged 0..1
	double angle; // 0.0 means looking along negative y-axis, walking clockwise
	double alpha;
	int frame;
	Image *img;
	Camera *cam;

	Sprite (Image *img, Camera *cam = 0);
	void draw ();
	int get_screen_x ();
	int get_screen_y ();
};

/**************************************************************************************************/

class Mob : public Sprite
{
public:
	double vx, vy;
	
	Mob (Image *img, Camera *cam = 0);
	void advance ();
};

/**************************************************************************************************/

struct Star
{
	int x, y;
	double b;
};

/**************************************************************************************************/

class Starfield : public Drawable
{
public:
	int w, h;
	int numstars;
	Camera *cam;
	Star *stars;
	Display *display;

	Starfield (Display *display, Camera *cam = 0, int w = 1024, int h = 1024, int numstars = 1024);
	void draw ();
	void draw_star (int x, int y, double b);
};

/**************************************************************************************************/

class Font
{
public:
	TTF_Font *font;

	Font (char *filename, int ptsize);
	Image *create_text (Display *display, char *text, unsigned int fgcol);
};

#endif

