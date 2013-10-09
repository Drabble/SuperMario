/*
Super Mario Bros

audio.h

Antoine Drabble

Création: 22.01.13
*/

#ifndef ADUIO_DEF//ceci permet d'éviter de faire plusieurs fois le même include.
#define AUDIO_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

void audio_init();
void audio_play(int song);
void audio_stop();

#endif
