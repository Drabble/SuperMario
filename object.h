/*
Super Mario Bros

object.h

Antoine Drabble

Création: 24.01.13
*/

#ifndef OBJECT_DEF//ceci permet d'éviter de faire plusieurs fois le même include.
#define OBJECT_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "map.h"
#include "char.h"

typedef struct
{
    SDL_Surface* image;
    SDL_Rect position[50];
    int nb_objet, used[50];
}Object;

Object* ChargerObject();
void AfficherObject(SDL_Surface* screen,Object* shroom, int xscroll, int yscroll);
void LibererObject (Object* shroom);

#endif
