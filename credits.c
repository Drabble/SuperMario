/*
Super Mario Bros

Credit.c

Antoine Drabble

Création: 07.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "credits.h"


void credits(SDL_Surface* screen)
{
    SDL_Surface *ImgCredits = NULL;
    SDL_Rect positionCredits;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    int tempsPrecedent = 0, tempsActuel = 0;

    ImgCredits = IMG_Load("images/credits.png");
    positionCredits.x = screen->w / 2 - ImgCredits->w / 2;
    positionCredits.y = -200;

    int continuer = 1;

    while (continuer)
        {
            SDL_PollEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;
                    }
            }

    if (positionCredits.y > 400+ImgCredits->h/2)
    {
        continuer = 0;
    }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 10) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            positionCredits.y++; // On déplace les crédits
            tempsPrecedent = tempsActuel; // Le temps "actuel" devient le temps "precedent" pour nos futurs calculs
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 82, 131, 252));
        SDL_BlitSurface(ImgCredits, NULL, screen, &positionCredits);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(ImgCredits);
}
