#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <string.h>

typedef struct Enigme Enigme;
struct Enigme
{
	SDL_Rect tab[4][4];
	char nomimage[30];
};

int enig(SDL_Surface *screen );






#endif /* FONCTIONS_H_ */
