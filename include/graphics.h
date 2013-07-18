
#ifndef GRAPHICS_H
#define GRAPHICS_H

double modulo (double x, int y);

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
	void draw (Display *display, int x, int y, int frame);
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
protected:
	double x, y;
	int w, h;
	int cx, cy;
	Image *img;
	int frame;
	Camera *cam;
public:
	Sprite (Image *img);
	double get_x ();
	double get_y ();
	int get_w ();
	int get_h ();
	void set_pos (double x, double y);
	void set_frame (int frame);
	void set_cam (Camera *cam);
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
private:
	int numstars;
	int width, height;
	int x, y;
	Camera *cam;
	Star **stars;
public:
	Starfield ();
	void draw (Display *display);
	void set_pos (int x, int y);
	void set_cam (Camera *cam);
private:
	void draw_star (Display *display, int x, int y, float fb);
};

#endif
