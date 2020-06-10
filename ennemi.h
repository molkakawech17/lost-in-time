

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>

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
typedef struct
{
	// pour l'affichage
	
	SDL_Surface *image;
	SDL_Rect source;
	SDL_Rect dest;

	
	// taille du sprite

	int largeur;
	int hauteur;
	
	// pour le déplacement
	int vitesse;
	// direction dans laquelle se deplace le sprite
	int direction;
	
	//variale pour vitesse
	// 0 ne marche pas et 1 marche 
	int moving;

	float Mass;

 	double velocity;

	double acceleration;
	
	// pour la gestion des animations
	
	// si le sprite est anime
	int anim;
	
	// direction dans laquelle est orienté le sprite
	int orientation;

	// animation courante du sprite
	int anim_courante;

	// le temps que dure une animation
	int temps_anim;

	// le temps de l'animation courante
	int temps_anim_courante;

	// nombre d'animations du sprite
	int total_anims;

}Sprite;

