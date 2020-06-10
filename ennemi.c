#include "ennemi.h" 
#include "background.h"
SDL_Surface *loadBmp(const char *fichier)
{
	SDL_Surface *image;

	/* Chargement du bitmap "fichier" en memoire dans la surface image */
	image = SDL_LoadBMP(fichier);
	if ( image == NULL )
	{
		fprintf(stderr, "Echec de chargement du fichier %s : %s.\n", fichier, SDL_GetError());
		return NULL;
	}
	
	/* Verification du format de l'image */
	if ( (image->w != 128) || (image->h != 128) )
	if ( image == NULL )
	{
		fprintf(stderr, "L'image du fichier %s doit être de taille 96*128 pixels.\n", fichier);
		SDL_FreeSurface(image);
		return NULL;
	}
	
	return image;
}
int chargerSprite( Sprite *sprite, const char *image )
{
	sprite->image = loadBmp( image );
	if ( !sprite->image )
		return 0;
		
	// on fixe la cle de transparance
	SDL_SetColorKey( sprite->image, SDL_SRCCOLORKEY, SDL_MapRGB( sprite->image->format, 255, 0, 0 ) );

	// On definit d'abord les propriétés du sprite :
	
	// le sprite n'est pas animé par defaut
	sprite->anim = 0;

	// on commence par la première animation
	sprite->anim_courante = 0;

	// le sprite dispose de trois animations
	sprite->total_anims = 4;

	// par défaut, le sprite est tourné vers le bas
	sprite->orientation = DROITE;

	// chaque animation dure 5 affichages
	sprite->temps_anim = 8;

	// Le temps qu'il reste à afficher l'animation courante
	sprite->temps_anim_courante = 0;

	// On definit ensuite les dimentions du sprite.
	sprite->largeur = 32;
	sprite->hauteur = 32;
	
	sprite->source.x = sprite->anim_courante * sprite->largeur;
	sprite->source.y = sprite->orientation * sprite->hauteur;
	sprite->source.w = sprite->largeur;
	sprite->source.h = sprite->hauteur;

	sprite->dest.x = 0;
	sprite->dest.y = 0;
	sprite->dest.w = sprite->largeur;
	sprite->dest.h = sprite->hauteur;
	
	// on definit enfin la vitesse et la direction du sprite
	sprite->acceleration = 0;
	sprite->Mass=70 ;
 	sprite->velocity=2; //5km/h
	sprite->moving=0;
	sprite->direction = AUCUNE_DIRECTION;
	
	return 1;
}

void supprimerSprite( Sprite *sprite )
{
	SDL_FreeSurface( sprite->image );
}
void fixerDirectionSprite( Sprite *sprite, int direction )
{
	// On affecte la direction au sprite
	sprite->direction = direction;
	
	// on affecte l'animation correcpondant à la direction au sprite
	if (direction != AUCUNE_DIRECTION)
	{
		sprite->anim = 1;
		switch (direction)
		{
		case DIRECTION_HAUT:
			sprite->orientation = HAUT;
			break;
			
		case DIRECTION_DROITE:
			sprite->orientation = DROITE;
			break;

		case DIRECTION_BAS:
			sprite->orientation = BAS;
			break;

		case DIRECTION_GAUCHE:
			sprite->orientation = GAUCHE;
			break;

		default:
			;
		}
	}
	else
		// si le sprite est areté, on ne l'anime pas
		sprite->anim = 0;

	// on met la première animation
	sprite->anim_courante = 0;
	sprite->temps_anim_courante = 0;

	// on regle la source de l'image à copier
	sprite->source.y = sprite->orientation * sprite->hauteur;
	sprite->source.x = sprite->anim_courante * sprite->largeur;
}

void miseAJourSprite( Sprite *sprite )
{
	// le sprite vas vers le haut
	if (sprite->direction & DIRECTION_HAUT)
	{
		// on monte et on faut attention a ne pas sortie de l'ecran
		sprite->dest.y -= sprite->vitesse;
		if (sprite->dest.y < 0)
			sprite->dest.y = 0;
	}
	else if (sprite->direction & DIRECTION_DROITE)
	{
		// on va à droite et on fait attention a ne pas sortie de l'ecran
		sprite->dest.x += sprite->vitesse;	
		if (sprite->dest.x + sprite->largeur > LARGEUR_ECRAN)	
			sprite->dest.x = LARGEUR_ECRAN - sprite->largeur;
	}
	else if (sprite->direction & DIRECTION_BAS)
	{
		// on descend et on faut attention a ne pas sortie de l'ecran
		sprite->dest.y += sprite->vitesse;	
		if (sprite->dest.y + sprite->hauteur > HAUTEUR_ECRAN)
			sprite->dest.y = HAUTEUR_ECRAN - sprite->hauteur;
	}
	else if (sprite->direction & DIRECTION_GAUCHE)
	{
		// on va à gauche et on fait attention a ne pas sortie de l'ecran
		sprite->dest.x -= sprite->vitesse;	
		if (sprite->dest.x < 0)
			sprite->dest.x = 0;
	}
}

void dessinerSprite( Sprite *sprite, SDL_Surface *destination )// animation
{
	/* si le sprite est animé, on gere l'animation */
	if (sprite->anim)
	{
		// on decremente le temps restant à l'animation courante
		sprite->temps_anim_courante--;
		// et on regarde s'il est temps de changer d'animation
		if ( sprite->temps_anim_courante <= 0 )
		{
			// s'il faut changer, on passe à l'animation suivante
			sprite->anim_courante++;
			// si on était à la dernière animation, on repasse à la première
			if (sprite->anim_courante >= sprite->total_anims)
				sprite->anim_courante = 0;
			
			// on regle la source à copier
			sprite->source.x = sprite->largeur * sprite->anim_courante;
			sprite->temps_anim_courante = sprite->temps_anim;
		}
	}
	
	// enfin, on dessine le sprite à l'ecran
	SDL_BlitSurface( sprite->image, &sprite->source, destination, &sprite->dest );
}
void moveSprite(Sprite *sprite,Background *B,Uint32 dt)
{ SDL_Rect destinationn ;
	/*Dx = vit + ½at2
	 * displacement = initial velocity * time + ½ acceleration * time2
	 * */
sprite->velocity+=0.5*sprite->acceleration*dt;
	B->backgroundPos.x+=sprite->velocity*dt;
		//Partie 1
}

