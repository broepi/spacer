.PHONY : all, rebuild, clean
all : build/spacer
rebuild : clean all
clean :
	-rm build/*
build/spacer : build/display.o build/sprite.o build/starfield.o build/radar.o build/font.o build/spacer.o build/enemyship.o build/image.o build/playership.o build/mob.o build/camera.o build/cloud.o build/utils.o
	g++ -o build/spacer build/display.o build/sprite.o build/starfield.o build/radar.o build/font.o build/spacer.o build/enemyship.o build/image.o build/playership.o build/mob.o build/camera.o build/cloud.o build/utils.o -lSDL2 -lSDL2_image -lSDL2_ttf
build/display.o : src/display.cpp src/display.h
	g++ -o build/display.o -c src/display.cpp -Wno-write-strings
build/sprite.o : src/sprite.cpp src/sprite.h src/drawable.h src/image.h src/camera.h
	g++ -o build/sprite.o -c src/sprite.cpp -Wno-write-strings
build/starfield.o : src/starfield.cpp src/starfield.h src/drawable.h src/display.h src/camera.h src/utils.h
	g++ -o build/starfield.o -c src/starfield.cpp -Wno-write-strings
build/radar.o : src/radar.cpp src/radar.h src/sprite.h src/drawable.h src/image.h
	g++ -o build/radar.o -c src/radar.cpp -Wno-write-strings
build/font.o : src/font.cpp src/font.h src/image.h src/display.h
	g++ -o build/font.o -c src/font.cpp -Wno-write-strings
build/spacer.o : src/spacer.cpp src/spacer.h src/display.h src/image.h src/font.h src/camera.h src/radar.h src/sprite.h src/drawable.h src/starfield.h src/drawable.h src/playership.h src/mob.h src/sprite.h src/drawable.h src/cloud.h src/mob.h src/sprite.h src/drawable.h src/utils.h
	g++ -o build/spacer.o -c src/spacer.cpp -Wno-write-strings
build/enemyship.o : src/enemyship.cpp src/playership.h src/mob.h src/sprite.h src/drawable.h src/utils.h src/image.h
	g++ -o build/enemyship.o -c src/enemyship.cpp -Wno-write-strings
build/image.o : src/image.cpp src/image.h src/display.h
	g++ -o build/image.o -c src/image.cpp -Wno-write-strings
build/playership.o : src/playership.cpp src/playership.h src/mob.h src/sprite.h src/drawable.h src/utils.h src/image.h
	g++ -o build/playership.o -c src/playership.cpp -Wno-write-strings
build/mob.o : src/mob.cpp src/mob.h src/sprite.h src/drawable.h
	g++ -o build/mob.o -c src/mob.cpp -Wno-write-strings
build/camera.o : src/camera.cpp src/camera.h
	g++ -o build/camera.o -c src/camera.cpp -Wno-write-strings
build/cloud.o : src/cloud.cpp src/cloud.h src/mob.h src/sprite.h src/drawable.h
	g++ -o build/cloud.o -c src/cloud.cpp -Wno-write-strings
build/utils.o : src/utils.cpp src/utils.h
	g++ -o build/utils.o -c src/utils.cpp -Wno-write-strings
