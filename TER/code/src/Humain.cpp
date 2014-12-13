#include "relogo/AgentSet.h"
#include "relogo/Patch.h"
#include "Observer.h"
#include "TERObserver.h"

#include "repast_hpc/RepastProcess.h"
#include "repast_hpc/initialize_random.h"
#include "Humain.h"
#include "Mur.h"
#include "fenetre.h"
#include "SDL2/SDL.h"
#include "coordonnes2d.h"
#include <math.h>

#define MAX_ANGLE 359

using namespace repast::relogo;
using namespace repast;

void Humain::getPos(){
	std::cout << " [ " << RepastProcess::instance()->rank()<< "] : Position X = " << pxCor()
																																																			<< std::endl << " [ " << RepastProcess::instance()->rank()<< "] : Position Y = "
																																																			<< pyCor() << std::endl ;
}

int Humain::randomType(Properties& props){
	boost::mpi::communicator world;
	initializeRandom(props, &world);
	return(repast::Random::instance()->nextDouble() * 100);
}

void Humain::randomAngle(Properties& props){
	boost::mpi::communicator world;
	initializeRandom(props, &world);
	this->m_angle = repast::Random::instance()->nextDouble() * MAX_ANGLE; // nombre entre 0 et 359
}

void Humain::step(){
	//std::cout << "Humain " << RepastProcess::instance()->rank() << " , " << this->_id.id() << " : test " << std::endl;
	double angle;
	double destinationX;
	double destinationY;
	double distance;

	double deplacement = 0.0;


	if(this->typePersonne == PERSONNE_ADULTE){
		deplacement = (0.1/100.0) * 40.0;
	}
	else if(this->typePersonne == PERSONNE_JEUNE){
		deplacement = (0.1/100.0) * 70.0;
	}
	else if(this->typePersonne == PERSONNE_AGEE){
		deplacement = (0.1/100.0) * 5.0;
	}
	else if(this->typePersonne == PERSONNE_MALADE){
		deplacement = (0.1/100.0) * 5.0;
	}
	else{
		deplacement = (0.1/100.0) * 50.0;
	}

	Patch* d = NULL, *g = NULL, *f = NULL;
	Humain* h = NULL;
	AgentSet <Mur> murVoisins;
	AgentSet <Humain> HumainEnFace,HumainAGauche,HumainADroite;
	bool sortie = false;

	if((etape == this->getCheminX().size()) && !sortie){
		((TERObserver*)_observer)->setSurvivant(((TERObserver*)_observer)->getSurvivants() + 1);
		die();
		sortie = true;
		//sorti = true;
	}

	if(!sortie){
		if(etape < this->getCheminX().size()){
			destinationX = this->getCheminX().at(etape);
			destinationY = this->getCheminY().at(etape);
		}

		distance = sqrt( pow( (destinationX - this->xCor()),2) + pow( (destinationY- this->yCor()),2));
/*
		if(repast::RepastProcess::instance()->rank() == 2){
			//std::cout << "Taille chemin X = " << this->getCheminX().size() << std::endl;
			//std::cout << "Taille chemin Y = " << this->getCheminX().size() << std::endl;
			std::cout << "Pos X/Y = " << this->xCor() << " / " << this->yCor() << std::endl;
			std::cout << "Destination X/Y = " << destinationX << " / " << destinationY << std::endl;
			std::cout << "Distance Objectif= " << distance << std::endl;
			//exit(0);
		}
*/
		g = patchLeftAndAhead<Patch>(5,1.5);
		d = patchRightAndAhead<Patch>(5,1.5);
		f = patchAtHeadingAndDistance<Patch>(this->heading(),1.5);
				if(d!=NULL && g!=NULL && f!=NULL){
					g->turtlesOn<Humain>(HumainAGauche);
					d->turtlesOn<Humain>(HumainADroite);
					f->turtlesOn<Humain>(HumainEnFace);
				}

		if ( distance > 0.15){
			angle = this->tournerVers(destinationX,destinationY);
			angle = this->rad2deg(angle);
			this->setAngle(angle);
			this->heading(-angle);
			if(HumainEnFace.size() == 0 && HumainADroite.size() == 0 && HumainAGauche.size() == 0){
				this->move(0.10 + deplacement);
			}
			else{
				HumainEnFace.clear();
				HumainADroite.clear();
				HumainAGauche.clear();
			}
		}
		else{
			if(etape <= this->getCheminX().size()-1)
				etape++;
		}

	}


}

double Humain::getAngle(){return this->m_angle;}

double Humain::rad2deg(double theta){
	return (theta*180.0)/PI;
}

double Humain::tournerVers(double x, double y){
	double x1 = this->xCor();
	double y1 = this->yCor();

	double dx = fabs(x1 - x);
	double dy = fabs(y1 - y);

	double theta;

	if(x1 < x && y1 < y){
		theta = atan(dx/dy);
		theta = 2.0*PI - theta;
	}
	else if(x1 > x && y1 < y){
		theta = atan(dx/dy);
	}
	else if(x1 > x && y1 > y){
		theta = atan(dx/dy);
		theta = PI - theta;
	}
	else if(x1 < x && y1 > y){
		theta = atan(dx/dy);
		theta = PI + theta;
	}
	else if(x1 == x && y1 > y){
		theta = PI;
	}
	else if(x1 == x && y1 < y){
		theta = 0.0;
	}
	else if(x1 > x && y1 == y){
		theta = PI/2.0;
	}
	else if(x1 < x && y1 == y){
		theta = (3.0*PI)/2.0;
	}

	return theta;
}
