#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>
#include <math.h>

#include "repast_hpc/io.h"
#include "repast_hpc/RepastProcess.h"
#include "relogo/SimulationRunner.h"
#include "relogo/Patch.h"

#include "fenetre.h"
#include "couleur.h"
#include "TERObserver.h"

using namespace repast;
using namespace relogo;

Fenetre::Fenetre(std::string titre,boost::mpi::communicator *world, unsigned int cadran,
		unsigned int longueur, unsigned int hauteur)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf(stderr,"Erreur lors de l'initialisation de SDL : %s",
				SDL_GetError());
		exit(EXIT_FAILURE);
	}

	this->world = world;

	this->m_largeur = longueur;
	this->m_hauteur = hauteur;
	this->m_titre = titre;
	this->m_cadran = cadran;

	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);

	switch(this->m_cadran){
	case 0:
		this->m_ecran = SDL_CreateWindow(titre.c_str(),((mode.w/2) - this->m_largeur),
				((mode.h/2) - this->m_hauteur), longueur, hauteur,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
		break;

	case 1:
		this->m_ecran = SDL_CreateWindow(titre.c_str(),(mode.w/2),
				((mode.h/2) - this->m_hauteur), longueur, hauteur,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
		break;
	case 2:
		this->m_ecran = SDL_CreateWindow(titre.c_str(),((mode.w/2) - this->m_largeur),
				(mode.h/2), longueur, hauteur,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
		break;

	case 3:
		this->m_ecran = SDL_CreateWindow(titre.c_str(),(mode.w/2),
				(mode.h/2), longueur, hauteur,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
		break;

	default :

		break;
	}

	if(this->m_ecran == NULL)
	{
		printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	this->m_context = SDL_GL_CreateContext(this->m_ecran);

	if(this->m_context == 0)//gestion des erreurs
	{
		printf("Erreur lors de la creation d'un contexte OpenGL : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D(0,this->m_largeur,0,this->m_hauteur);
	// Nettoyage de l'écran
	glClearColor(255,255,255,0);
	glClear(GL_COLOR_BUFFER_BIT);

}

Fenetre::~Fenetre()
{
	SDL_GL_DeleteContext(this->m_context);
	SDL_DestroyWindow(this->m_ecran);
	SDL_Quit();
	//dtor
}

void Fenetre::main_loop(){

	int continuer = 1;
	SDL_Event event;

	while (continuer)
	{
		SDL_PollEvent(&event);
		switch(event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			continuer = 0;
			//COMMUNIQUER AUX AUTRES

		}

		boost::mpi::broadcast(*world,continuer,0);
	}
}

void Fenetre::dormir(int val){
	SDL_Event e;
	SDL_PollEvent(&e);
	SDL_Delay(val);

}

void Fenetre::dessinerTriangle(int posX, int posY, double angle, int type){

	const int b = 10; // longueur des cotes du triangle equilateral

	const double h = 20; // hauteur

	Couleur* coul;

	//Initialisation des matrices
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glTranslated(posX,posY,0);
	glRotated(angle,0,0,1);

	switch(type){
	case 0: // ADULTE BLEU
		coul = new Couleur(0,0,255);
		break;
	case 1: // JEUNE ROUGE
		coul = new Couleur(255,0,0);
		break;
	case 2: // AGEE VERT
		coul = new Couleur(0,255,0);
		break;
	case 3: // MALADE VIOLET
		coul = new Couleur(255,0,255);
		break;
	default:
		coul = new Couleur(0,0,0);
		break;
	}

	glBegin(GL_TRIANGLES);
		glColor3ub(coul->getR(),coul->getG(),coul->getB());    glVertex2d(-b/2,-h/2.0);
		glColor3ub(coul->getR(),coul->getG(),coul->getB());    glVertex2d(0,h/2.0);
		glColor3ub(coul->getR(),coul->getG(),coul->getB());    glVertex2d(b/2 ,-h/2.0);
	glEnd();

	glFlush();

	delete coul;

}

void Fenetre::refresh(void){
	// Actualisation de la fenêtre
		SDL_GL_SwapWindow(this->m_ecran);
}

void Fenetre::clear(void){
	// Actualisation de la fenêtre
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Fenetre::dessinerMur(int posX, int posY){

	const int c = 20; // longueur des cotes du carre

	//Initialisation des matrices
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glTranslated(posX,posY,0);


	glBegin(GL_QUADS);
		glColor3ub(0,0,0);    glVertex2d(0.0,0.0);
		glColor3ub(0,0,0);    glVertex2d(0.0,(double)c);
		glColor3ub(0,0,0);    glVertex2d((double)c ,(double)c);
		glColor3ub(0,0,0);    glVertex2d((double)c ,0.0);
	glEnd();

	glFlush();

}

unsigned int Fenetre::getLongueur(){return this->m_largeur;}
unsigned int Fenetre::getHauteur(){return this->m_hauteur;}
SDL_Window* Fenetre::getScreen(){return this->m_ecran;}
SDL_GLContext Fenetre::getGLContext(){return this->m_context;}
int Fenetre::getCadran(){return this->m_cadran;}
