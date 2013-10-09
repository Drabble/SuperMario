/*
Super Mario Bros

objectevent.c

Antoine Drabble

Création: 24.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "objectevent.h"


void objectmove(Object* shroom, Chars* mario, int xscroll, int yscroll, Map* m, Sprites* S)
{
    int i;
    SDL_Rect position[50];

    for (i=1; i<=shroom->nb_objet; i++){
        position[i].x = shroom->position[i].x - xscroll;
        position[i].y = shroom->position[i].y - yscroll;
        position[i].w = Size_Sprite;
        position[i].h = Size_Sprite;
    }

   for (i=1; i<=shroom->nb_objet; i++){ //On passe une fois par champignon
       if (shroom->used[i]==0){
            if((position[i].x >= mario->position.x -xscroll + mario->position.w) //Check si mario touche le champignon
            || (position[i].x + position[i].w <= mario->position.x -xscroll)
            || (position[i].y >= mario->position.y -yscroll + mario->position.h)
            || (position[i].y + position[i].h <= mario->position.y - yscroll)
            ){}
            else{
                audio_play(5);
                if(mario->lvl==1){
                    mario->position.w = 32;
                    mario->position.h = 60;
                    mario->position.y -=20;
                    mario->lvl=2;
                }
                shroom->used[i]=1;
            }
       }
   }

}
