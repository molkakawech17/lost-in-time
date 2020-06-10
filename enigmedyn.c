#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enigmedyn.h"
#include <time.h>
#include <string.h>



int enig(SDL_Surface *screen )
{
	SDL_Surface  *enigme = NULL;
	SDL_Event event;

	Enigme e,e1;
	int niveau = 3;
	int game=1;

	SDL_Init(SDL_INIT_VIDEO);
        screen= SDL_SetVideoMode(1228, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

        if (screen == NULL)
        {
                fprintf(stderr,"Impossible de charger le mode vidéo : %s\n",SDL_GetError());
                exit(EXIT_FAILURE);
        }

	SDL_Rect positionEnigme[4][4];
	SDL_Rect aux;
	int i,j;
	int espacex=0;
	int espacey=0;
	int test;

	strcpy(e.nomimage,"9alb2.png");

	enigme = IMG_Load(e.nomimage);

	for(i=0; i<niveau; i++)
        {
                for(j=0; j<niveau; j++)
                {
                        e.tab[i][j].x = ((enigme->w)/niveau)*j;
			e.tab[i][j].y = ((enigme->h)/niveau)*i;
			e.tab[i][j].h = ((enigme->h)/niveau);
			e.tab[i][j].w = ((enigme->w)/niveau);

                }
        }

	e1 = e;

	for(i=0; i<niveau; i++)
        {
                for(j=0; j<niveau; j++)
                {
                        e1.tab[i][j] = e.tab[j][i];
                }
        }

	for(i=0; i<niveau; i++)
	{
		for(j=0; j<niveau; j++)
		{
			if (i != 0)
			{
				espacey = 2;
			}

			if (j != 0)
			{
				espacex = 2;
			}

			positionEnigme[i][j].x = screen->w/2 - enigme->w/2 + espacex*j + (enigme->w/niveau)*j;
			positionEnigme[i][j].y = screen->h/2 - enigme->h/2 + espacey*i + (enigme->h/niveau)*i;
		}
	}

	while(game)
	{
		SDL_WaitEvent(&event);

		switch(event.type)
		{
			case SDL_QUIT:
				game = 0;
			break;

			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
						if ((event.button.x >= positionEnigme[0][0].x) && (event.button.x <= positionEnigme[0][0].x + 							     enigme->w) && (event.button.y >= positionEnigme[0][0].y) && 
							(event.button.y <= positionEnigme[0][0].y + enigme->h))
						{
							for(i=0; i<niveau; i++)
							{	
								for(j=0; j<niveau; j++)
								{
									if ((event.button.x>=positionEnigme[i][j].x)&&			  										    (event.button.x<=positionEnigme[i][j].x+(enigme->w)/niveau)&&
									    (event.button.y>=positionEnigme[i][j].y)&&
									    (event.button.y<=positionEnigme[i][j].y+(enigme->h)/niveau))	
									{
										aux = e1.tab[i][j];
										e1.tab[i][j] = e1.tab[1][1];
										e1.tab[1][1] = aux;
									}
								}
							}
						}
						
					break;
				}
			break;
		}

		for(i=0; i<niveau; i++)
		{	
			for(j=0; j<niveau; j++)
			{
				SDL_BlitSurface(enigme, &e1.tab[i][j], screen, &positionEnigme[i][j]);
				SDL_Flip(screen);
			}
		}

		test = 1;

		for(i=0; i<niveau; i++)
		{	
			for(j=0; j<niveau; j++)
			{
				if ((e1.tab[i][j].x == e.tab[i][j].x)&&(e1.tab[i][j].y == e.tab[i][j].y))
				{
					test = 1;
				}
				else
				{
					test = 0;
				}
				
				if (test == 0)
				{
					break;
				}
			}

			if (test == 0)
				{
					break;
				}
		}
		if (test == 1)
		{
			game = 0;
		}
	}

	

	return 1;
}























