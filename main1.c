#include <stdbool.h>
#include "camera.h"
#include "ennemi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include "detectCollBB.h"
#include <math.h>
#define HAUT	0
#define DROITE	1
#define BAS	2
#define GAUCHE	3

#define AUCUNE_DIRECTION	0
#define DIRECTION_HAUT		1
#define DIRECTION_DROITE	2
#define DIRECTION_BAS		4
#define DIRECTION_GAUCHE	8

#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 480


/*score initialiser_score();
vie initialiser_vie();
void afficher_score(score s);
void afficher_vie(vie v);
void update_score(score *s , int sens);
void update_vie(vie *v);*/
int main()
{

	SDL_Surface *background;
	SDL_Surface *player;
	SDL_Surface *ecran;
	SDL_Event event;
	int bFin = 0;
	SDL_Rect position={24,300}; 
	Scroll cam={0,0};
	/* On déclare trois sprites, un que l'on controlera
	   et deux qui se déplacerons tout seul */
	Sprite spControlable, spAutonome1, spAutonome2;
	Initialisation_Scroll(&cam,position,800,600);
	SDL_Rect pos_real={0,0};
	SDL_Rect pos={0,0};
        //enigme e ;
 	//enigmeData ed ;
	background=IMG_Load("final.png");
	//e=initEnigme();
	
	
	/* initialisation de SDL_Video */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "Echec d'initialisation de SDL.\n");
		return 1;
	}
	printf("Bonjour le monde, SDL est initialisé avec succès.\n");
	
	
	/* On fixe le mode d'affichage à 640*480*16 plein ecran.*/
	ecran = SDL_SetVideoMode(640, 480, 16, SDL_FULLSCREEN);
	if ( ecran == NULL )
	{
		fprintf(stderr, "Echec de changement du mode video : %s.\n", SDL_GetError());
		return 1;
	}
	
	/* On charge le sprite controlable avec l'image pecheur.bmp */
	if ( !chargerSprite( &spControlable, "pecheur.bmp" ) )
	{
		SDL_Quit();
		return 1;
	}

	/* On charge le premier sprite autonome avec l'image bebe.bmp */
	if ( !chargerSprite( &spAutonome1, "bebe.bmp" ) )
	{
		supprimerSprite( &spControlable );
		SDL_Quit();
		return 1;
	}

	/* On charge le second sprite autonome avec l'image souris.bmp */
	if ( !chargerSprite( &spAutonome2, "souris.bmp" ) )
	{
		supprimerSprite( &spAutonome1 );
		supprimerSprite( &spControlable );
		SDL_Quit();
		return 1;
	}

	spControlable.dest.x = 392;
	spControlable.dest.y =24;
	fixerDirectionSprite( &spControlable, DIRECTION_DROITE );
	fixerDirectionSprite( &spControlable, AUCUNE_DIRECTION );
        spAutonome1.dest.x = 420;
	spAutonome1.dest.y =360;
	

	while (!bFin)
	{       
                Scrolling(&cam,position,800,600);
		SDL_BlitSurface(background,&(cam.scroll),ecran,NULL);
                
		spControlable.dest.x=position.x-cam.scroll.x;
		spControlable.dest.y=360;

		if (spControlable.dest.x>=800)
		{
			spControlable.dest.x=800-161;
		}
		else if (spControlable.dest.x <=0)
		{
			spControlable.dest.x=0;
		}
		//SDL_BlitSurface(&spControlable.image,NULL,ecran,&spControlable.dest);
		//

		SDL_EnableKeyRepeat(5,5);
while(SDL_PollEvent(&event))
{
		
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					bFin = 1;
					break;
					
				// on deplace le sprite au clavier
				case SDLK_UP:
     fixerDirectionSprite( &spControlable, DIRECTION_HAUT );
   position.y-=10;
					break;
				
				case SDLK_RIGHT:
             fixerDirectionSprite( &spControlable, DIRECTION_DROITE );
             position.x+=10;
					break;
				
				case SDLK_DOWN:
	  fixerDirectionSprite( &spControlable, DIRECTION_BAS );
          position.y+=10;
					break;
				
				case SDLK_LEFT:
	fixerDirectionSprite( &spControlable, DIRECTION_GAUCHE );
         position.x-=10;
					break;
				
				default:
					printf("Une touche à été pressée.\n");
				}
				break;
			
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				// on deplace le sprite au clavier
				case SDLK_UP:
					if (spControlable.direction == DIRECTION_HAUT)
						fixerDirectionSprite( &spControlable, AUCUNE_DIRECTION );
position.y-=10;

					break;
				
				case SDLK_RIGHT:
					if (spControlable.direction == DIRECTION_DROITE)
						fixerDirectionSprite( &spControlable, AUCUNE_DIRECTION );
position.x+=10;
					break;
				
				case SDLK_DOWN:
					if (spControlable.direction == DIRECTION_BAS)
						fixerDirectionSprite( &spControlable, AUCUNE_DIRECTION );
position.y+=10;
					break;
				
				case SDLK_LEFT:
					if (spControlable.direction == DIRECTION_GAUCHE)
						fixerDirectionSprite( &spControlable, AUCUNE_DIRECTION );
position.x-=10;
		
					break;
					
				default:
					;
				}
			
	break;

			case SDL_QUIT:
				bFin = 1;
				break;
			
			default:;
			}	


}	
	

			/* On dessine la scene */
			/* On dessine les sprites à l'écran */
			dessinerSprite( &spControlable, ecran );
			dessinerSprite( &spAutonome1,background );
                     
                       miseAJourSprite( &spControlable );
			miseAJourSprite( &spAutonome1 );
			//miseAJourSprite( &spAutonome2 );
	if (detectCollBB(&spControlable,&spAutonome1,spControlable.dest,spAutonome1.dest)==false)
 { 
printf("collision \n");
enig(ecran);
	         
	 }		
						
			/* On met à jour de la zone d'affichage de la fenetre */
			SDL_UpdateRect(ecran, 0, 0, 0, 0); 
                        SDL_Flip(ecran);

		
		
	} 	
	
	supprimerSprite(&spControlable);
        supprimerSprite(&spAutonome1);
     //   SDL_Delay(3000);
	SDL_Quit();
	return 0;
}


