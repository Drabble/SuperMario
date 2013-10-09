/*
Super Mario Bros

Menu

event.c

Antoine Drabble

Création: 07.01.13
*/


#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <fmod.h>

#include "event.h"

void UpdateEvents(Input* in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=0;
			break;
		case SDL_QUIT:
			in->quit = 1;
			break;
		default:
			break;
		}
	}
}

int CollisionDecor(Map* m, SDL_Rect* perso, Sprites* S, Chars* mario, int vx, Object* shroom)
{
	int xmin,xmax,ymin,ymax,i,j,indicetile;
	xmin = perso->x / Size_Sprite;
	ymin = perso->y / Size_Sprite;
	xmax = (perso->x + perso->w -1) / Size_Sprite;
	ymax = (perso->y + perso->h -1) / Size_Sprite;
    mario->G=1;

    if (mario->lvlperdu>0){
        mario->lvlperdu--;
        if(mario->invisible==1)
            mario->invisible=0;
        else
            mario->invisible=1;
    }
    else{
        mario->invisible=0;
    }

if (perso->h+perso->y<m->Nb_Block_H*Size_Sprite-10){
    j = (perso->y + perso->h +1) / Size_Sprite;
    for(i=xmin;i<=xmax;i++) //Si il y a un bloc en dessous
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].traverser){
            mario->G=0;
            mario->jump = 1;
        }
        if (indicetile==10){
            if (mario->lvlperdu<1)
            {
                if(mario->lvl==1)
                    mario->lose=1;
                if(mario->lvl==2)
                    audio_play(6);
                    mario->lvl=1;
                    mario->position.y+=10;
                    mario->lvlperdu=400;
            }
        }
        else{ //Si on ne touche pas le sol et que le temps de saut est de plus de 1000, on retombe.
            if(mario->jumptime>1000)
                mario->jump = 0;
        }
    }
}

    j = (perso->y - 1) / Size_Sprite;
	for(i=xmin;i<=xmax;i++) //Si il y a un bloc en dessus
	{
		    indicetile = m->LoadedMap[i][j];
		    if (S[indicetile].traverser)
                mario->jumptime = 1001;
            if (indicetile==3){
                if(S[m->LoadedMap[i][j-1]].traverser==0){
                    if (m->Used[i][j]==0){
                        shroom->nb_objet++; //Creation d'un champignon!
                        shroom->used[shroom->nb_objet]= 0;
                        shroom->position[shroom->nb_objet].x = i*Size_Sprite;
                        shroom->position[shroom->nb_objet].y = (j-1)*Size_Sprite;
                        m->Used[i][j]=1;
                    }
                }
            }
	}

	i= (perso->x + perso->w) / Size_Sprite; //Si on touche un bloc à notre droite,
    for(j=ymin;j<=ymax;j++)
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].traverser){
            perso->x-=vx;
            j=ymax+1;
            }
    }
    i = (perso->x -1) / Size_Sprite; //Si on touche un bloc à note gauche
    for(j=ymin;j<=ymax;j++)
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].traverser){
            perso->x-=vx;
            j=ymax+1;
            }
    }
    for(i=xmin;i<=xmin;i++){
        for(j=ymin;j<=ymax;j++)
        {
            indicetile = m->LoadedMap[i][j];
            if (indicetile==8 || indicetile==9){ //Si on touche le drapeau de la fin
                    mario->win = 1;
                }
        }
    }


	return 0; //Si pas de collision
}

int EssaiDeplacement(Map* m, Chars* mario, int vx, int vy, Sprites* S, Object* shroom)
{
	SDL_Rect test;
	test = mario->position;
	test.x+=vx;
	test.y+=vy;

	int temp;
	temp = CollisionDecor(m, &test, S, mario, vx, shroom);

    if(test.y+test.h>(Size_Sprite*m->Nb_Block_H)+100)
        mario->lose=1;
	if (mario->G==1) // Gravité activée si on ne touche pas le sol
		test.y += 2;
	else
        mario->jumptime = 1;
    if (test.x-1<0) //Si on touche le bord gauche de la map
        test.x-=vx;
    if (test.x + test.w>=m->Nb_Block_W*Size_Sprite-2) //Si on touche le bord droite de la map
        test.x-=vx;
    if (test.y<0){ //Si on touche le haut de la map
        mario->jumptime = 1001;
        test.y+=vy;
    }
	if (temp==0) //Si pas de colision on modifie la position du personnage
	{
		mario->position = test;
		return 1;
	}
	return 0;
}

void Deplace(Map* m, Chars* mario,int vx,int vy, Sprites* S, Object* shroom)
{
	if (vx>=Size_Sprite || vy>=Size_Sprite) //si jamais le vercteur est plus grand qu'un sprite, pour pas qu'on traverse.
	{
		Deplace(m,mario,vx/2,vy/2,S,shroom);
		Deplace(m,mario,vx/3,vy/3,S,shroom);
		Deplace(m,mario,vx/4,vy/4,S,shroom);
		return;
	}
	if (EssaiDeplacement(m,mario,vx,vy,S,shroom)==1) //Si pas de collision
		return;

}

void Evolue(Input* in, Map *m, Chars *mario, Sprites *S, Object* shroom)
{
	int vx,vy;
    int vitesse = 2;
	vx = vy = 0;
	if (!in->key[SDLK_UP]){
        mario->jumptime=1001;
	}
	if (in->key[SDLK_UP]){
        if (mario->jump==1){
            if (mario->jumptime<=1)
                audio_play(2);

            mario->jumptime +=10;
            vy -= 5;

            if(mario->jumptime>1000)
                in->key[SDLK_UP]=0; //Ne pas sautez tout le temps si on laisse la touche haut activée
        }
	}
	if (in->key[SDLK_LEFT]){
        vx = -vitesse;
		mario->directionmario = 1;
	}
	if (in->key[SDLK_RIGHT]){
		vx = vitesse;
		mario->directionmario = 2;
	}

	Deplace(m,mario,vx,vy, S, shroom);
}

void MapScroll(Map* m, Chars* mario)
{
            m->xscroll = mario->position.x + mario->position.w/2 - WindowW/2;
            m->yscroll = mario->position.y + mario->position.h/2 - WindowH/2;
        if (m->xscroll<0)
            m->xscroll=0;
        if (m->yscroll<0)
            m->yscroll=0;
        if (m->xscroll>m->Nb_Block_W*Size_Sprite-WindowW-1)
            m->xscroll=m->Nb_Block_W*Size_Sprite-WindowW-1;
        if (m->yscroll>m->Nb_Block_H*Size_Sprite-WindowH-1)
            m->yscroll=m->Nb_Block_H*Size_Sprite-WindowH-1;
}

int NiveauFini (SDL_Surface* screen, Chars* mario, Map* m)
{
    SDL_Event event;
    int continuer;

    if (mario->win==1)
    {
        audio_play(4);
        SDL_Surface* reussi = IMG_Load("images/win.png");
        SDL_Rect positionreussi ;
        positionreussi.x = WindowW/2-reussi->w/2;
        positionreussi.y = WindowH/2-reussi->h/2;

        SDL_BlitSurface(reussi,NULL,screen,&positionreussi);
        SDL_Flip(screen);
        SDL_Delay(1000);

        while (continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    continuer = 0;
                    break;
            }
        }
    mario->win=0;
    SDL_FreeSurface(reussi);
    return 1;
    }

    if (mario->lose==1)
    {
        audio_play(3);
        SDL_Surface* perdu = IMG_Load("images/lose.png");
        SDL_Rect positionperdu;
        positionperdu.x = WindowW/2-perdu->w/2;
        positionperdu.y = WindowH/2-perdu->h/2;

        SDL_BlitSurface(perdu,NULL,screen,&positionperdu);
        SDL_Flip(screen);

        while (continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    continuer = 0;
                    break;
            }
        }

    mario->lose=0;
    SDL_FreeSurface(perdu);
    return 1;
    }

    return 0;

}
