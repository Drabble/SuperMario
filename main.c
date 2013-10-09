/*
Super Mario Bros

Menu

Main.c

Antoine Drabble

Création: 07.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <fmod.h>

#include "credits.h"
#include "game.h"
#include "audio.h"

int main(int argc, char *argv[])
{
    SDL_Surface* screen = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    audio_init();
    audio_play(1);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("images/Mario.png"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Ouvre la page
    SDL_WM_SetCaption("Super Mario BROS", NULL); //Définit le titre

    menu = IMG_Load("images/menu.jpg"); //Charge l'image du menu
    positionMenu.x = screen->w / 2 - menu->w / 2; //Définit le menu au centre de la fenêtre
    positionMenu.y = 0;


    while (continuer)
    {
        SDL_WaitEvent(&event);
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
                    case SDLK_1:

                        game(screen);
                        screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        break;
                    case SDLK_2:
                        credits(screen);
                        break;
                }
                break;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //Fond noir
        SDL_BlitSurface(menu, NULL, screen, &positionMenu); //Imprime le menu sur la page
        SDL_Flip(screen);
    }

    audio_stop();
    SDL_FreeSurface(menu); //Efface le menu
    SDL_Quit(); //Quitte

    return EXIT_SUCCESS;
}
