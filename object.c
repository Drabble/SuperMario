/*
Super Mario Bros

object.c

Antoine Drabble

Création: 24.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "object.h"

void AfficherObject(SDL_Surface* screen, Object* shroom, int xscroll, int yscroll)
{
    int i;
    SDL_Rect position[50];

    for (i=1; i<=shroom->nb_objet; i++){
        position[i].x = shroom->position[i].x - xscroll;
        position[i].y = shroom->position[i].y - yscroll;
        position[i].w = Size_Sprite;
        position[i].h = Size_Sprite;
    }

    for (i=1; i<=shroom->nb_objet; i++){
        if (shroom->used[i]==0){
            SDL_BlitSurface(shroom->image,NULL,screen,&position[i]);
        }
    }
}

Object* ChargerObject()
{
    Object* shroom;
    shroom = malloc(sizeof(Object));

    shroom->image = IMG_Load("images/shroom.png");
    shroom->nb_objet = 0;

    return shroom;
}

void LibererObject (Object* shroom)
{
    SDL_FreeSurface(shroom->image);
    free(shroom);
}
