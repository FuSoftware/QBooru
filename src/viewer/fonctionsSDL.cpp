#include "fonctionsSDL.h"

#define TRANSLATION_BASE 20

GLuint textureImage;
int screenH;
int screenW;

int showImageFullScreenSDL(QWidget *parent, char* Imagepath)
{
    double posx = 0;
    double posy = 0;
    double pictureCurrentH;
    double pictureCurrentW;
    double screenCurrentH;
    double screenCurrentW;
    double zoomInitial;

    SDL_Surface *ecran = NULL, *image = NULL;
    SDL_Event event;
    bool continuer = true;
    double zoom = 1.0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        criticalSDLError(parent, SDL_GetError());
    }

    ecran = SDL_SetVideoMode(0, 0, 32, SDL_OPENGL | SDL_FULLSCREEN);
    SDL_WM_SetCaption("Fullscreen Viewer", NULL);

    screenH =ecran->h;
    screenW =ecran->w;

    glEnable(GL_TEXTURE_2D);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0, ecran->w, 0, ecran->h);

    textureImage = loadTexture(Imagepath);
    image = IMG_Load(Imagepath);

    double alignH = (double)ecran->h / (double)image->h;
    double alignW = (double)ecran->w / (double)image->w;

    if(alignH < alignW)
    {
        zoom = alignH;
    }
    else
    {
        zoom = alignW;
    }

    zoomInitial = zoom;

    pictureCurrentH = image->h*zoom;
    pictureCurrentW = image->w*zoom;

    posx = (ecran->w-(pictureCurrentW))/2;
    posy = (ecran->h-(pictureCurrentH))/2;

    Dessiner(image,zoom, posx, posy);

    SDL_EnableKeyRepeat(100, 100); /* Activation de la répétition des touches */

    int tempsActuel=0;
    int tempsPrecedent=0;

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        break;
                    case SDLK_LEFT:
                        posx += TRANSLATION_BASE;
                        break;
                    case SDLK_RIGHT:
                        posx -= TRANSLATION_BASE;
                        break;
                    case SDLK_UP:
                        posy -= TRANSLATION_BASE;
                        break;
                    case SDLK_DOWN:
                        posy += TRANSLATION_BASE;
                        break;
                    default:
                        break;
                }
                std::cout << "Zoom = " << zoom << std::endl;
                std::cout << "X = " << posx << std::endl;
                std::cout << "Y = " << posy << std::endl<< std::endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button)
                    {
                    case SDL_BUTTON_WHEELDOWN:
                        if(zoom <= zoomInitial)
                        {
                            zoom = zoomInitial;
                            posx = (ecran->w-(pictureCurrentW))/2;
                            posy = (ecran->h-(pictureCurrentH))/2;
                        }
                        else
                        {
                            zoom -= (zoom/10);
                            posx = screenCurrentW-(ecran->w*zoom)+posx;
                            posy = screenCurrentH-(ecran->h*zoom)+posy;
                        }
                        if(zoom <= zoomInitial)
                        {
                            zoom = zoomInitial;
                            posx = (ecran->w-(pictureCurrentW))/2;
                            posy = (ecran->h-(pictureCurrentH))/2;
                        }
                        break;
                    case SDL_BUTTON_WHEELUP:
                        zoom += (zoom/10);
                        posx = screenCurrentW-(ecran->w*zoom)+posx;
                        posy = screenCurrentH-(ecran->h*zoom)+posy;
                        break;
                    }
                    pictureCurrentH = image->h*zoom;
                    pictureCurrentW = image->w*zoom;
                    std::cout << "Zoom = " << zoom << std::endl;
                    std::cout << "X = " << posx << std::endl;
                    std::cout << "Y = " << posy << std::endl;
                    std::cout << "Image W = " << pictureCurrentW << std::endl;
                    std::cout << "Image H = " << pictureCurrentH << std::endl << std::endl;

                    break;
        }
        if(posy > 0){posy = 0;}
        if(posy < (ecran->h-(pictureCurrentH))){posy = (ecran->h-(pictureCurrentH));}
        if(posx < (ecran->w-(pictureCurrentW))){posx = (ecran->w-(pictureCurrentW));}
        if(posx > 0){posx = 0;}
        if(ecran->w > pictureCurrentW){posx = (ecran->w-(pictureCurrentW))/2;}
        if(ecran->h > pictureCurrentH){posy = (ecran->h-(pictureCurrentH))/2;}

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 15)
        {
            tempsPrecedent = tempsActuel;
        }
        else /* Si ça fait moins de 30 ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
        {
            SDL_Delay(15 - (tempsActuel - tempsPrecedent));
        }

        Dessiner(image,zoom, posx, posy);

        pictureCurrentH = image->h*zoom;
        pictureCurrentW = image->w*zoom;
        screenCurrentH = ecran->h*zoom;
        screenCurrentW = ecran->w*zoom;
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}

void Dessiner(SDL_Surface *image, double zoom, double posx, double posy)
{
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glTranslated(posx,posy,0);
    dessinerRectangle(image, image->w*zoom,image->h*zoom);

    //glTranslated(-posx,-posy,0);
    //dessinerMiniature(image,1,1);

    glFlush();
    SDL_GL_SwapBuffers();
}

void dessinerRectangle(SDL_Surface *image, double largeur,double hauteur)
{
    int decalageX;
    decalageX = (0);

    glBindTexture(GL_TEXTURE_2D, textureImage);
        glBegin(GL_QUADS);
        glTexCoord2i(0,0); glVertex2d(decalageX,
                                      0);
        glTexCoord2i(0,1); glVertex2d(decalageX,
                                      hauteur);
        glTexCoord2i(1,1); glVertex2d(decalageX+largeur,
                                      hauteur);
        glTexCoord2i(1,0); glVertex2d(decalageX+largeur,
                                      0);
        glEnd();
}

void dessinerMiniature(SDL_Surface *image, double largeur,double hauteur)
{
    double ratioX,ratioY;
    if(image->w > image->h)
    {
        ratioX = ratioImage(image);
        largeur *= ratioX;
    }
    else
    {
        ratioY = 1./ratioImage(image);
        hauteur *= ratioY;
    }

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureImage);
        glBegin(GL_QUADS);
        glTexCoord2i(0,0); glVertex2d(-1,largeur);
        glTexCoord2i(0,1); glVertex2d(-1,1);
        glTexCoord2i(1,1); glVertex2d(-hauteur,1);
        glTexCoord2i(1,0); glVertex2d(-hauteur,largeur);
        glEnd();
    glPopMatrix();
}

/** (-1,1)      (1,1)
  *
  *
  * (-1,-1)     (1,-1)
  */

double ratioImage(SDL_Surface *image)
{
    double ratioImage = 0;
    ratioImage = (double)image->w / (double)image->h;
    return ratioImage;
}

void dessinerRepere(unsigned int echelle)
{
    glPushMatrix();
    glScalef(echelle,echelle,echelle);
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
    glVertex2i(0,0);
    glVertex2i(1,0);
    glColor3ub(0,255,0);
    glVertex2i(0,0);
    glVertex2i(0,1);
    glEnd();
    glPopMatrix();
}
