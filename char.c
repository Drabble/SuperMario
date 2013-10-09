/*
Super Mario Bros

char.c

Antoine Drabble

Création: 17.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "char.h"

void AfficherPerso(Chars* mario, SDL_Surface* screen, int xscroll, int yscroll, Chars* marioimages)
{

	SDL_Rect positionsurecran = mario->position;
	SDL_Surface *mario1, *mario2, *mario3, *mario4, *mario5, *mario6;
	positionsurecran.x -= xscroll; //Empèche de déplacer le perso déplacer en scrollant
	positionsurecran.y -= yscroll; //Empèche de déplacer le perso déplacer en scrollant
	mario->temp++;

	if (mario->lvl==1){
    mario->position.w = 30;
    mario->position.h = 40;
    mario1=marioimages[6].image;
    mario2=marioimages[7].image;
    mario3=marioimages[8].image;
    mario4=marioimages[9].image;
    mario5=marioimages[10].image;
    mario6=marioimages[11].image;
	}
	else{
    mario->position.w = 32;
    mario->position.h = 60;
    mario1=marioimages[0].image;
    mario2=marioimages[1].image;
    mario3=marioimages[2].image;
    mario4=marioimages[3].image;
    mario5=marioimages[4].image;
    mario6=marioimages[5].image;
	}

    if (mario->invisible==0){
        if(mario->directionmario==2){
            mario->dernieredirection=2;
            if (mario->selectedmario==1){
                SDL_BlitSurface(mario1,NULL,screen,&positionsurecran);
                mario->directionmario=0;
                if (mario->temp>30){
                mario->selectedmario = 2;
                mario->temp = 0;
                }
                return;
            }
            if (mario->selectedmario==2){
                SDL_BlitSurface(mario2,NULL,screen,&positionsurecran);
                mario->directionmario=0;
                if (mario->temp>30){
                mario->selectedmario = 3;
                mario->temp = 0;
                }
                return;
            }
            if (mario->selectedmario==3){
                SDL_BlitSurface(mario3,NULL,screen,&positionsurecran);
                mario->directionmario=0;
                if (mario->temp>30){
                mario->selectedmario = 1;
                mario->temp = 0;
                }
                return;
            }
        }
        else if(mario->directionmario==1){
            mario->dernieredirection = 1;
            if (mario->selectedmario==1){
                SDL_BlitSurface(mario4,NULL,screen,&positionsurecran);
                mario->directionmario=0;
                if (mario->temp>30){
                mario->selectedmario = 2;
                mario->temp = 0;
                }
                return;
            }
            if (mario->selectedmario==2){
                SDL_BlitSurface(mario5,NULL,screen,&positionsurecran);
                mario->directionmario=0;
                if (mario->temp>30){
                mario->selectedmario = 3;
                mario->temp = 0;
                }
                return;
            }
            if (mario->selectedmario==3){
                SDL_BlitSurface(mario6,NULL,screen,&positionsurecran);
                mario->directionmario=0;
                if (mario->temp>30){
                mario->selectedmario = 1;
                mario->temp = 0;
                }
                return;
            }
        }
        else{
            if (mario->dernieredirection==1){
                SDL_BlitSurface(mario4,NULL,screen,&positionsurecran);
            }
            else{
                SDL_BlitSurface(mario1,NULL,screen,&positionsurecran);
            }
        }
    }


}

void ChargerChars(Chars* mario, Map* m, Chars* marioimages)
{

    mario->position.w = 30;
    mario->position.h = 40;
    mario->position.x = 150;
    mario->position.y = m->Nb_Block_H*Size_Sprite-2*Size_Sprite-mario->position.h;

    mario->selectedmario = 1;
    mario->lvl = 1;
    mario->lvlperdu=0;

    marioimages[0].image = IMG_Load("images/mario1.png");
    marioimages[1].image = IMG_Load("images/mario2.png");
    marioimages[2].image = IMG_Load("images/mario3.png");
    marioimages[3].image = IMG_Load("images/mario4.png");
    marioimages[4].image = IMG_Load("images/mario5.png");
    marioimages[5].image = IMG_Load("images/mario6.png");

    marioimages[6].image = IMG_Load("images/mario7.png");
    marioimages[7].image = IMG_Load("images/mario8.png");
    marioimages[8].image = IMG_Load("images/mario9.png");
    marioimages[9].image = IMG_Load("images/mario10.png");
    marioimages[10].image = IMG_Load("images/mario11.png");
    marioimages[11].image = IMG_Load("images/mario12.png");

}

void LibererChars (Chars* mario, Chars* marioimages)
{
    SDL_FreeSurface(marioimages[0].image);
    SDL_FreeSurface(marioimages[1].image);
    SDL_FreeSurface(marioimages[2].image);
    SDL_FreeSurface(marioimages[3].image);
    SDL_FreeSurface(marioimages[4].image);
    SDL_FreeSurface(marioimages[5].image);
    SDL_FreeSurface(marioimages[6].image);
    SDL_FreeSurface(marioimages[7].image);
    SDL_FreeSurface(marioimages[8].image);
    SDL_FreeSurface(marioimages[9].image);
    SDL_FreeSurface(marioimages[10].image);
    SDL_FreeSurface(marioimages[11].image);
    free(mario);
    free(marioimages);
}
