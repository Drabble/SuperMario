/*
Super Mario Bros

char.h

Antoine Drabble

Création: 17.01.13
*/

#ifndef CHAR_DEF//ceci permet d'éviter de faire plusieurs fois le même include.
#define CHAR_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "map.h"
#include "object.h"

typedef struct
{
SDL_Surface* image;
SDL_Rect position;
int jump, jumptime, G, selectedmario;
int directionmario, temp, dernieredirection, win, lose, lvl, lvlperdu, invisible;
}Chars;

void ChargerChars(Chars* mario, Map* m, Chars* marioimages);
void AfficherPerso(Chars* mario, SDL_Surface* screen, int xscroll, int yscroll, Chars* marioimages);
void LibererChars (Chars* mario, Chars* marioimages);

#endif
