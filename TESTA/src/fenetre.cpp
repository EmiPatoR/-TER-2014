#include <SDL2/SDL.h>
#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>

#include "repast_hpc/io.h"
#include "repast_hpc/RepastProcess.h"
#include "relogo/SimulationRunner.h"
#include "relogo/Patch.h"

#include "fenetre.h"
#include "couleur.h"
#include "TERObserver.h"

using namespace repast;
using namespace relogo;

Fenetre::Fenetre(std::string titre,boost::mpi::communicator *world, unsigned int longueur, unsigned int hauteur)
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
    this->m_ecran = SDL_CreateWindow(titre.c_str(),SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , longueur, hauteur,SDL_WINDOW_SHOWN);
    if(this->m_ecran == NULL)
    {
    	printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
    	exit(EXIT_FAILURE);
    }

    SDL_Delay(3000);

}

Fenetre::~Fenetre()
{
	SDL_DestroyWindow(m_ecran);
    SDL_Quit();
    //dtor
}

void Fenetre::main_loop(){
	/*
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                //COMMUNIQUER AUX AUTRES

        }

        boost::mpi::broadcast(*world,continuer,0);
    }
    */
}

void Fenetre::runTER(std::string propsFile, int argc, char ** argv) {


	Properties props(propsFile, argc, argv, world);

	std::string time;
	repast::timestamp(time);

	props.putProperty("date_time.run", time);

	props.putProperty("process.count", world->size());

	SimulationRunner runner(world);

	if(world->rank() == 0) std::cout << " Starting... " << std::endl;
	repast::Timer timer;
	timer.start();
	runner.run<TERObserver, Patch>(props);

	props.putProperty("run.time", timer.stop());


	if(world->rank() == 0){
		std::vector<std::string> keysToWrite;
		keysToWrite.push_back("run.number");
		keysToWrite.push_back("date_time.run");
		keysToWrite.push_back("process.count");
		keysToWrite.push_back("random.seed");
		keysToWrite.push_back("human.count");
		keysToWrite.push_back("zombie.count");
		keysToWrite.push_back("min.x");
		keysToWrite.push_back("min.y");
		keysToWrite.push_back("max.x");
		keysToWrite.push_back("max.y");
		keysToWrite.push_back("proc.per.x");
		keysToWrite.push_back("proc.per.y");
		keysToWrite.push_back("grid.buffer");
		keysToWrite.push_back("init.time");
		keysToWrite.push_back("stop.at");
		keysToWrite.push_back("run.time");
		props.log("root");
		props.writeToSVFile("TER.csv", keysToWrite);
	}

}

unsigned int Fenetre::getLongueur(){return this->m_largeur;}
unsigned int Fenetre::getHauteur(){return this->m_hauteur;}
SDL_Window* Fenetre::getScreen(){return this->m_ecran;}
