all : game.cpp ; g++ game.cpp -o game `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

game : game.cpp ; g++ game.cpp -o game `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

mac : game.cpp ; g++ game.cpp -o game `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

clean : ; rm -f game
