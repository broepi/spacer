
CC = g++
CPPFLAGS = -Iinclude -Iinclude/SDL
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image
LDFLAGS = -Llibs
OBJECTS = $(subst src,obj,$(subst .cpp,.o,$(wildcard src/*.cpp)))

build : bin/spacer

rebuild : clean build

bin/spacer : $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

obj/%.o : src/%.cpp
	$(CC) -o $@ $(CPPFLAGS) -c $^

clean:
	rm obj/*.o
	rm bin/spacer

test : bin/test

bin/test : test/test.cpp
	$(CC) -o bin/test test/test.cpp
