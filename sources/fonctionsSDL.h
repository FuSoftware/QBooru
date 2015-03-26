#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <QWidget>

#ifndef FONCTIONSSDL_H
#define FONCTIONSSDL_H

int showImageFullScreenSDL(QWidget *parent,char* Imagepath);

double ratioImage(SDL_Surface *image);
void dessinerRectangle(SDL_Surface *image, double largeur, double hauteur);
void dessinerMiniature(SDL_Surface *image, double largeur, double hauteur);
void Dessiner(SDL_Surface *image, double zoom, double posx, double posy);
void dessinerRepere(unsigned int echelle = 1);


#endif // FONCTIONSSDL_H
