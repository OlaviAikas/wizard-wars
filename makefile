#Where to look for specific extensions (might not actually be required)
vpath %.h headers
vpath %.cpp source
vpath %.o objects

# Lists of files to compile
SRCS := $(wildcard source/*.cpp)
# NAMES := $(SRCS:source/='')
HEADERS := $(wildcard headers/*.hpp)
OBJS := $(patsubst source/%.cpp,objects/%.o,$(SRCS))

# Dependency files (see §6.4 in http://nuclear.mutantstargoat.com/articles/make/)
# DEP = $(OBJS:.o=.d)  # one dependency file for each source

# Compiler and flags
CXX := g++
PKGCONFIG := `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

# -include $(DEP)   # include all dep files in the makefile
# # rule to generate a dep file by using the C preprocessor
# # (see man cpp for details on the -MM and -MT options)
# objects/%.d: %.cpp
# 	$(CXX) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

# Rules
all: game

debug: CFLAGS := -g
debug: clean game
	
verbose: CFLAGS := -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
				   -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs \
				   -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow \
				   -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
				   -Wswitch-default -Wundef -Werror -Wno-unused
verbose: clean game

objects/%.o: %.cpp ${HEADERS}
	$(CXX) $(CFLAGS) -c -o $@ $<

game: ${OBJS} ${HEADERS}
	$(CXX) $(CFLAGS) -o game ${OBJS} $(PKGCONFIG)

clean:
	rm -f ${OBJS} game

# cleandep:
# 	rm -f $(DEP)

# all : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
# 	g++ -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
# 	mv Map.o objects/
# 	g++ -c source/Camera.cpp
# 	mv Camera.o objects/
# 	g++ -c source/Player.cpp
# 	mv Player.o objects/
# 	g++ -c source/MapObject.cpp
# 	mv MapObject.o objects/
# 	g++ -c source/HUDobject.cpp
# 	mv HUDobject.o objects/
# 	g++ -c source/Minimap.cpp
# 	mv Minimap.o objects/
# 	g++ -c source/Spells.cpp
# 	mv Spells.o objects/
# 	g++ -c source/Rock.cpp
# 	mv Rock.o objects/
# 	g++ -c source/Projectile.cpp
# 	mv Projectile.o objects/
# 	g++ -c source/Controlpoint.cpp
# 	mv Controlpoint.o objects/
# 	g++ -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Spells.o objects/Rock.o objects/Projectile.o objects/Controlpoint.o objects/HUDobject.o objects/Minimap.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

# symbols : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Spells.cpp
# 	g++ -g -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
# 	g++ -c source/Controlpoint.cpp
# 	mv Controlpoint.o objects/
# 	g++ -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Controlpoint.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

# debug : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
# 	g++ -c -g source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
# 	mv Map.o objects/
# 	g++ -c -g source/Camera.cpp
# 	mv Camera.o objects/
# 	g++ -c -g source/Player.cpp
# 	mv Player.o objects/
# 	g++ -c -g source/MapObject.cpp
# 	mv MapObject.o objects/
# 	g++ -c -g source/Spells.cpp
# 	mv Spells.o objects/
# 	g++ -c -g source/Rock.cpp
# 	mv Rock.o objects/
# 	g++ -c -g source/Projectile.cpp
# 	mv Projectile.o objects/
# 	g++ -c -g source/Controlpoint.cpp
# 	mv Controlpoint.o objects/
# 	g++ -g -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Spells.o objects/Rock.o objects/Projectile.o objects/Controlpoint.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

# game : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
# 	g++ -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
# 	mv Map.o objects/
# 	g++ -g -c source/Camera.cpp
# 	mv Camera.o objects/
# 	g++ -g -c source/Player.cpp
# 	mv Player.o objects/
# 	g++ -g -c source/MapObject.cpp
# 	mv MapObject.o objects/
# 	g++ -g -c source/Spells.cpp
# 	mv Spells.o objects/
# 	g++ -g -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Spells.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`
# 	g++ -c source/Controlpoint.cpp
# 	mv Controlpoint.o objects/
# 	g++ -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Controlpoint.o `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

# verbose : source/game.cpp source/Map.cpp source/Camera.cpp source/Player.cpp source/MapObject.cpp source/Controlpoint.cpp
# 	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Map.cpp `pkg-config allegro-5 allegro_main-5 allegro_image-5 --libs --cflags`
# 	mv Map.o objects/
# 	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Camera.cpp
# 	mv Camera.o objects/
# 	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Player.cpp
# 	mv Player.o objects/
# 	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/MapObject.cpp
# 	mv MapObject.o objects/
# 	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -c source/Controlpoint.cpp
# 	mv Controlpoint.o objects/
# 	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -o game source/game.cpp objects/Map.o objects/Camera.o objects/MapObject.o objects/Player.o objects/Controlpoint.o `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

# clean :
# 	rm -f game objects/*.o
