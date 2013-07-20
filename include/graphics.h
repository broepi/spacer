
#ifndef GRAPHICS_H
#define GRAPHICS_H

double modulo (double x, int y);
double fmodulo (double x, double y);
double radtodeg (double r);

class Display
{
public:
	int width, height;
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	Display ();
	~Display ();
	void clear ();
	void present ();
};

class Drawable
{
public:
	virtual void draw (Display *display) {};
};

class Image
{
public:
	bool texture;
	int width, height;
	int cols, rows;
	SDL_Surface *surf;
	SDL_Texture *tex;
public:
	Image (Display *display, char *filename, bool texture, int cols, int rows);
	Image ();
	void draw (Display *, int, int, int = 0, int = 0, int = 0, double = 0.0, double = 1.0);
};

class Camera
{
public:
	double x, y;
	double cx, cy;
public:
	Camera ();
};

class Sprite : public Drawable
{
public:
	double x, y;
	double w, h;
	int cx, cy;
	double graphangle;
	double alpha;
	Image *img;
	int frame;
	Camera *cam;

	Sprite (Image *img);
	void draw (Display *display);
};

class Star
{
public:
	int x, y;
	float brightness;
	Star (int x, int y, float b);
};

class Starfield : public Drawable
{
public:
	int numstars;
	int width, height;
	int x, y;
	Camera *cam;
	Star **stars;

	Starfield ();
	void draw (Display *display);
private:
	void draw_star (Display *display, int x, int y, float fb);
};

class Font
{
private:
	TTF_Font *font;
public:
	Font (char *filename, int ptsize);
	Image *create_text (Display *display, char *text, unsigned int fgcol);
};

#endif
