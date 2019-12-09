all : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
	g++ -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
	mv Map.o objects/
	g++ -c source/Camera.cpp
	mv Camera.o objects/
	g++ -c source/Player.cpp
	mv Player.o objects/
	g++ -c source/MapObject.cpp
	mv MapObject.o objects/
	g++ -c source/Spells.cpp
	mv Spells.o objects/
	g++ -c source/Rock.cpp
	mv Rock.o objects/
	g++ -c source/Ice.cpp
	mv Ice.o objects/
	g++ -c source/HealP.cpp
	mv HealP.o objects/
	g++ -c source/Projectile.cpp
	mv Projectile.o objects/
	g++ -c source/FirePellet.cpp
	mv FirePellet.o objects/
	g++ -c source/Controlpoint.cpp
	mv Controlpoint.o objects/
	g++ -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Spells.o objects/Rock.o objects/FirePellet.o objects/Projectile.o objects/Ice.o objects/HealP.o objects/Controlpoint.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

symbols : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Spells.cpp
	g++ -g -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
	g++ -c source/Controlpoint.cpp
	mv Controlpoint.o objects/
	g++ -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Controlpoint.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

debug : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
	g++ -c -g source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
	mv Map.o objects/
	g++ -c -g source/Camera.cpp
	mv Camera.o objects/
	g++ -c -g source/Player.cpp
	mv Player.o objects/
	g++ -c -g source/MapObject.cpp
	mv MapObject.o objects/
	g++ -c -g source/Spells.cpp
	mv Spells.o objects/
	g++ -c -g source/Rock.cpp
	mv Rock.o objects/
	g++ -c -g source/Ice.cpp
	mv Ice.o objects/
	g++ -c -g source/HealP.cpp
	mv HealP.o objects/
	g++ -c -g source/Projectile.cpp
	mv Projectile.o objects/
	g++ -c -g source/Controlpoint.cpp
	mv Controlpoint.o objects/
	g++ -g -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Spells.o objects/Rock.o objects/Projectile.o objects/Ice.o objects/HealP.o objects/Controlpoint.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

game : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
	g++ -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
	mv Map.o objects/
	g++ -g -c source/Camera.cpp
	mv Camera.o objects/
	g++ -g -c source/Player.cpp
	mv Player.o objects/
	g++ -g -c source/MapObject.cpp
	mv MapObject.o objects/
	g++ -g -c source/Spells.cpp
	mv Spells.o objects/
	g++ -g -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Spells.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`
	g++ -c source/Controlpoint.cpp
	mv Controlpoint.o objects/
	g++ -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Controlpoint.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

verbose : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
	mv Map.o objects/
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Camera.cpp
	mv Camera.o objects/
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Player.cpp
	mv Player.o objects/
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/MapObject.cpp
	mv MapObject.o objects/
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Controlpoint.cpp
	mv Controlpoint.o objects/
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Controlpoint.o `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

clean :
	rm -f game objects/*.o
