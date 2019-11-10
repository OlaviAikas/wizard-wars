all : source/game.cpp ; g++ source/game.cpp -o game `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

game : source/game.cpp ; g++ source/game.cpp -o game `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

verbose : source/game.cpp ; g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -o game source/game.cpp `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

clean : ; rm -f game
