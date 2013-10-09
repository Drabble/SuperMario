/*
Super Mario Bros

map.h

Antoine Drabble

Création: 07.01.13
*/

#ifndef MAP_DEF//ceci permet d'éviter de faire plusieurs fois le même include.
#define MAP_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>


#define NbSprites 11 // À modifier si on ajouter des sprites
#define Size_Sprite 40 // A modifier si on change taille sprite

typedef struct
{
    int Nb_Block_W, Nb_Block_H;
    Uint16** LoadedMap;
    Uint16** Used;
    long int xscroll,yscroll;
}Map;

typedef struct
{
    SDL_Surface* sprite;
    int traverser;
}Sprites;

Sprites* ChargerImages();
Map* ChargerMap(char* level);
void AfficherMap(Map* m, SDL_Surface* screen, Sprites* S);
void LibererMap(Map* m, Sprites* S);

#endif
