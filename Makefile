.PHONY : all, rebuild, clean
all : build/spacer
rebuild : clean all
clean :
	-rm -R build/*.*
	-rm -R build/*/*.*	
build/spacer : build/spacer.o build/enemyship.o build/starfield.o build/radar.o build/cloud.o build/playership.o build/framework/mixer.o build/framework/font.o build/framework/vector2d.o build/framework/camera.o build/framework/utils.o build/framework/sprite.o build/framework/image.o build/framework/game.o build/framework/sound.o build/framework/stage.o build/framework/rect.o build/framework/display.o build/framework/rgba.o build/framework/label.o build/framework/mob.o
	g++ -o build/spacer build/spacer.o build/enemyship.o build/starfield.o build/radar.o build/cloud.o build/playership.o build/framework/mixer.o build/framework/font.o build/framework/vector2d.o build/framework/camera.o build/framework/utils.o build/framework/sprite.o build/framework/image.o build/framework/game.o build/framework/sound.o build/framework/stage.o build/framework/rect.o build/framework/display.o build/framework/rgba.o build/framework/label.o build/framework/mob.o -lSDL2 -lSDL2_image -lSDL2_ttf
build/spacer.o : build/ src/spacer.cpp src/spacer.h src/framework/game.h src/framework/stage.h src/framework/vector2d.h
	g++ -o build/spacer.o -c src/spacer.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/enemyship.o : build/ src/enemyship.cpp src/enemyship.h src/framework/mob.h src/framework/sprite.h src/framework/drawable.h src/framework/vector2d.h src/framework/vector2d.h src/spacer.h src/framework/game.h src/framework/stage.h src/framework/vector2d.h src/framework/utils.h src/framework/image.h src/framework/drawable.h src/framework/vector2d.h
	g++ -o build/enemyship.o -c src/enemyship.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/starfield.o : build/ src/starfield.cpp src/starfield.h src/framework/drawable.h src/framework/display.h src/framework/vector2d.h src/framework/camera.h src/framework/vector2d.h src/framework/rect.h src/framework/vector2d.h src/framework/utils.h
	g++ -o build/starfield.o -c src/starfield.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/radar.o : build/ src/radar.cpp src/radar.h src/framework/sprite.h src/framework/drawable.h src/framework/vector2d.h src/framework/image.h src/framework/drawable.h src/framework/vector2d.h
	g++ -o build/radar.o -c src/radar.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/cloud.o : build/ src/cloud.cpp src/cloud.h src/framework/mob.h src/framework/sprite.h src/framework/drawable.h src/framework/vector2d.h src/framework/vector2d.h
	g++ -o build/cloud.o -c src/cloud.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/playership.o : build/ src/playership.cpp src/spacer.h src/framework/game.h src/framework/stage.h src/framework/vector2d.h src/playership.h src/framework/mob.h src/framework/sprite.h src/framework/drawable.h src/framework/vector2d.h src/framework/vector2d.h src/spacer.h src/framework/game.h src/framework/stage.h src/framework/vector2d.h src/framework/utils.h src/framework/image.h src/framework/drawable.h src/framework/vector2d.h
	g++ -o build/playership.o -c src/playership.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/mixer.o : build/ src/framework/mixer.cpp src/framework/mixer.h
	g++ -o build/framework/mixer.o -c src/framework/mixer.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/font.o : build/ src/framework/font.cpp src/framework/font.h src/framework/rgba.h src/framework/image.h src/framework/drawable.h src/framework/vector2d.h src/framework/display.h src/framework/vector2d.h
	g++ -o build/framework/font.o -c src/framework/font.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/vector2d.o : build/ src/framework/vector2d.cpp src/framework/vector2d.h
	g++ -o build/framework/vector2d.o -c src/framework/vector2d.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/camera.o : build/ src/framework/camera.cpp src/framework/camera.h src/framework/vector2d.h src/framework/rect.h src/framework/vector2d.h
	g++ -o build/framework/camera.o -c src/framework/camera.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/utils.o : build/ src/framework/utils.cpp src/framework/utils.h
	g++ -o build/framework/utils.o -c src/framework/utils.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/sprite.o : build/ src/framework/sprite.cpp src/framework/sprite.h src/framework/drawable.h src/framework/vector2d.h src/framework/image.h src/framework/drawable.h src/framework/vector2d.h src/framework/camera.h src/framework/vector2d.h src/framework/rect.h src/framework/vector2d.h
	g++ -o build/framework/sprite.o -c src/framework/sprite.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/image.o : build/ src/framework/image.cpp src/framework/image.h src/framework/drawable.h src/framework/vector2d.h src/framework/display.h src/framework/vector2d.h src/framework/utils.h
	g++ -o build/framework/image.o -c src/framework/image.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/game.o : build/ src/framework/game.cpp src/framework/game.h src/framework/stage.h src/framework/vector2d.h src/framework/display.h src/framework/vector2d.h
	g++ -o build/framework/game.o -c src/framework/game.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/sound.o : build/ src/framework/sound.cpp src/framework/sound.h
	g++ -o build/framework/sound.o -c src/framework/sound.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/stage.o : build/ src/framework/stage.cpp src/framework/stage.h
	g++ -o build/framework/stage.o -c src/framework/stage.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/rect.o : build/ src/framework/rect.cpp src/framework/rect.h src/framework/vector2d.h
	g++ -o build/framework/rect.o -c src/framework/rect.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/display.o : build/ src/framework/display.cpp src/framework/display.h src/framework/vector2d.h
	g++ -o build/framework/display.o -c src/framework/display.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/rgba.o : build/ src/framework/rgba.cpp src/framework/rgba.h
	g++ -o build/framework/rgba.o -c src/framework/rgba.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/label.o : build/ src/framework/label.cpp src/framework/label.h src/framework/display.h src/framework/vector2d.h src/framework/image.h src/framework/drawable.h src/framework/vector2d.h src/framework/sprite.h src/framework/drawable.h src/framework/vector2d.h src/framework/font.h src/framework/rgba.h
	g++ -o build/framework/label.o -c src/framework/label.cpp $(shell freetype-config  --cflags) -Wno-write-strings
build/framework/mob.o : build/ src/framework/mob.cpp src/framework/mob.h src/framework/sprite.h src/framework/drawable.h src/framework/vector2d.h src/framework/vector2d.h
	g++ -o build/framework/mob.o -c src/framework/mob.cpp $(shell freetype-config  --cflags) -Wno-write-strings
