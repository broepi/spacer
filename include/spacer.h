
class Drawable;
class Game;
class Display;
class Starfield;
class Star;
class PlayerShip;

class Drawable
{
	virtual void draw (Display *display) {};
};

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

class PlayerShip : public Drawable
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

