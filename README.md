# SDL2 stuff
Stuff I made in SDL2

Many things (like collissions) I made by myself without any outside help or tutorials or guides. 
This is mainly a project made for me to familiarize myself better with stuff and get better

Also don't try to like send pull requests and stuff. I do appreciate a bit of help, but just feedback will work

# How to run:
The compiled executable is present in the root of the repository, if you want to run it you can just
```
./game.o
```
to run it.

If it gives you any errors or problems, you can also try and compile it yourself.

# How to compile:

First of all, you're gonna need g++, SDL2, SDL2-devel, SDL2_image, you can find how to download them easily online, it ain't that hard

After installing the necessary stuff and cloning the repository, run 

```
g++ -c src/.cpp -std=c++14 -m64 -g -Wall -I src && g++.o -o game.o -lSDL2main -lSDL2 -lSDL2_image && ./game.o
```
In the terminal at the root of the repository
