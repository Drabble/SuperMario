/*
Super Mario Bros

event.h

Antoine Drabble

Création: 17.01.13
*/
#ifndef EVENT_DEF//ceci permet d'éviter de faire plusieurs fois le même include.
#define EVENT_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "map.h"
#include "char.h"
#include "object.h"
#include "audio.h"

typedef struct
{
	char key[SDLK_LAST];
    char quit;
}Input;

void UpdateEvents(Input* in);
void Evolue(Input* in, Map *m, Chars *mario, Sprites *S, Object* shroom);
void Deplace(Map* m,Chars* mario,int vx,int vy, Sprites* S, Object* shroom);
int EssaiDeplacement(Map* m,Chars* mario,int vx,int vy, Sprites* S, Object* shroom);
void MapScroll(Map* m, Chars* mario);
int CollisionDecor(Map* m, SDL_Rect* perso, Sprites* S, Chars* mario, int vx, Object* shroom);
int NiveauFini (SDL_Surface* screen, Chars* mario, Map* m);

#endif
