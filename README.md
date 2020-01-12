# Wizard Wars
### _A CSE201 Project_

This is the repository for our video game Wizard Wars that is heavily inspired by (or a straight up clone of) [Magicka: Wizard Wars](https://magicka.fandom.com/wiki/Wizard_Wars). The game will be implemented using the fantastic game library [Allegro](www.liballeg.org), which is provided free for us to use. Please note that Allegro is a low-ish level library as opposed to a game engine, so there is less stuff to learn and more leeway for us to create the game as we like.

Please do [this tutorial](https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace)    
Please also read [this](https://wiki.allegro.cc/index.php?title=Achieving_Resolution_Independence) AND always implement all drawing stuff with the streched buffer method.

Notice that the files `main` and `game` are in .gitignore, remove if required.

## Project Members (Name, github username, [role])
- Olavi Äikäs, OlaviAikas (or Oulawi sometimes), [Project leader]
- Mihails Valtusovs, valtusovs, [Git master]
- Paul Balavoine, paulbalavoine, [Organisation master]
- Ashish Nayak, anayak99, [IDE Leader]
- Seorim Park, seorimpark
- Damien Briens, DamienBriens
- Uranchimeg Zamidii, uranchimegz
- Johannes Kunz, johannes-kunz
- Wanqi Hong, Wanqi77
- Yasamin Jalalian, yasaminjln
- Ruiyao Jiang, Xtraordinaire9911
- Chloe Semaan, chloe-semaan
- Joci Chen, jocichen


## Team assignments:
### Team 1: Map:
* Paul
* Johannes
* Ruiyao
* Damien

### Team 2: UI/HUD:
* Chloe
* Olavi

### Team 3: Magic:
* Mihails
* Yasamin
* Seorim
* Wanqi <br>
link to the google sheet : https://docs.google.com/spreadsheets/d/1U292Xuc60-sqPbSf0No7_KN3GhcqFwKOEsrraRNXdxw/edit?usp=sharing

### Team 4: Networking:
* Ashish
* Joci
* Uranchimeg

## How to compile the game:
 The game uses the libraries Allegro5 and Boost. To install on ubuntu (CSE201 VM), follow these instructions:
 ### Ubuntu
 * If you are using the virtual machine, increase the RAM, number of processors and video memory as much as possible (on the school computers we used ~24 MB of RAM, 4 processors and 128MB of video memory).
 * Install Allegro5:
 ```Bash
 $ sudo apt install liballegro5-dev
 ```
 * To install Boost we use aptitude:
 ```Bash
 $ sudo apt install aptitude
 $ sudo aptitude install libboost-all-dev
 ```
 Boost requires an older version of Python, so refuse the first upgrade path (which does nothing) with `n` and accept the second upgrade path (which downgrades Python) with `y`.
 * Finally we are ready to clone the repository and make:
 ```Bash
 $ git clone github.com/OlaviAikas/wizard-wars
 $ cd wizard-wars
 $ make
 ```
 * Now you sit back and relax as make compiles the game, and when it's done, it can be executed with
 ```Bash
 $ ./game
 ```
 
 ### MacOS
 * Install Allegro5:
 First we have to install homebrew:
 ```Bash
 $ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
 ```
 Then we can get allegro5 from it :
 ```Bash
 $ brew install allegro 
 ```
 * Install boost: 
 ```Bash
 $ brew install boost 
 ```
 * Finally we are ready to clone the repository and make:
 ```Bash
 $ git clone github.com/OlaviAikas/wizard-wars
 $ cd wizard-wars
 $ make mac
 ```
### Running the game in server mode
* The connection to the server: 
  - Running the server requires running the game as super-user (`sudo ./game`) and pressing the Create game button, entering 2 with the number keys on the next screen (not with the numpad) and pressing Enter (again, not on the numpad). 
  - Once the server is running on one computer, an another player can connect to the server by putting the ip after clicking on "join game".
  - the maximum number of player that can join a game is 2, due to the server capacity (as in, the game has a server no more than 1 client).
* The rule:
  - We have 3 control points on the map : the player should capture all the control points and kill the opponent in order to win the game. There are multiple spells that can kill or heal players, and the player should combine elements with keys to cast spells (life=u, shield=i, fire=o, water=j, ice=k, rock=l). The selected elements are on the bottom right.(see link to the google sheet above for the list of spells)
  
  
  
