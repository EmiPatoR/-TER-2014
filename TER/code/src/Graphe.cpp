#include <vector>
#include <iostream>
#include "Node.h"
#include "coordonnes2d.h"
#include "Graphe.h"
#include "PathFinder.h"
#include "repast_hpc/RepastProcess.h"

Graphe::Graphe(int** map,int longueur_map,int hauteur_map,Coordonnes2D depart, std::vector<Coordonnes2D> &sorties){
	m_map = map;
	m_longueur = longueur_map;
	m_hauteur = hauteur_map;
	m_depart = depart;
	Coordonnes2D copieDepart,copieArrive;
	a_star = new Pathfinder();

	Node* node = NULL;

	std::vector<Node*> ligne;
	/*
	for(int i=0;i<hauteur_map;i++){
		for(int j=0;j<longueur_map;j++){
			std::cout << map[i][j] ;
		}
		std::cout << "\n";
	}*/

	for(int i=0;i<hauteur_map;i++){
		//std::cout << "Je dois m'afficher 40 fois" << std::endl;
		for(int j=0;j<longueur_map;j++){
			node = new Node();
			if(map[i][j] == 1)
				node->setWalkable(false);
			node->setX(j);
			node->setY(i);
			ligne.push_back(node);
		}
		m_graphe.push_back(ligne);
		ligne.clear();
	}

	copieDepart = Coordonnes2D(20 + depart.getX(), 19 - depart.getY());
	Node* start = m_graphe[copieDepart.getY()][copieDepart.getX()];

	m_chemin = calculSortie(sorties,start);

	//copieArrive = m_arrive;

	/*
	if(repast::RepastProcess::instance()->rank() == 0){
		for(int i=0;i<m_graphe.size();i++){
			for(int j=0;j<m_graphe[0].size();j++){
				if(m_graphe[i][j]->getWalkable())
					std::cout << "0";
				else
					std::cout << "1";
			}
			std::cout << "\n";
		}
	}*/


	//Node* start = m_graphe[copieDepart.getY()][copieDepart.getX()];
	//Node* end = m_graphe[copieArrive.getY()][copieArrive.getX()];

	/*
	if(repast::RepastProcess::instance()->rank() == 2){
		std::cout << "START X/Y = " << start->getX() << " / " << start->getY() << std::endl;
		std::cout << "START (R) X/Y = " << depart.getX() << " / " << depart.getY() << std::endl;
		std::cout << "END X/Y = " << end->getX() << " / " << end->getY() << std::endl;
		std::cout << "END (R) X/Y = " << arrive.getX() << " / " << arrive.getY() << std::endl;
		//m_chemin = a_star->findPath(m_graphe,start,end);
		//exit(0);
	}
	 */

	//m_chemin = a_star->findPath(m_graphe,start,end);
	/*
	if(repast::RepastProcess::instance()->rank() == 2){
		for(int i=0;i<m_chemin.size();i++){
			std::cout << "chemin[" << i << "] = (" << m_chemin[i]->getX() << " ; " << m_chemin[i]->getY() << " )" << std::endl;
		}
	}
	std::cerr << "chemin genere !" << std::endl;
	 */


}

std::vector<Node*> Graphe::calculSortie(std::vector<Coordonnes2D> &sorties, Node* depart){
	double distanceMin = 1000000;
	double distance = 0;
	int numSortie = 0;
	std::vector< std::vector< Node* > > chemin;
	//Node* nodeDepart = m_graphe[depart.getX()][depart.getY()];
	Node* nodeArrivee = NULL;

	if(repast::RepastProcess::instance()->rank() == 1)
		std::cerr << "Nombre de sorties = " << sorties.size() << std::endl;

	for(int i=0;i<sorties.size();i++){
		nodeArrivee = m_graphe[sorties[i].getY()][sorties[i].getX()];
		chemin.push_back(a_star->findPath(m_graphe,depart,nodeArrivee));
		distance = chemin[i].size();
		//distance = sqrt(pow( (depart.getX() - sorties[i].getX()),2 ) + pow((depart.getY() - sorties[i].getY()),2) );
		if(repast::RepastProcess::instance()->rank() == 1){
			std::cerr << "Taille du graphe : " << m_graphe.size() << " x " << m_graphe[0].size() << std::endl;
			std::cerr << "distance " << i << " = " << distance << std::endl;
			std::cerr << "depart : " << depart->getX() << " / " << depart->getY() << std::endl;
			std::cerr << "sortie : " << nodeArrivee->getX() << " / " << nodeArrivee->getY() << std::endl;
			//exit(0);
		}

		if(distance < distanceMin){
			distanceMin = distance;
			numSortie = i;
		}
		//chemin.clear();
	}
	return chemin[numSortie];
}

std::vector<int> Graphe::Nodes2CheminX(std::vector<Node*> chemin){
	std::vector<int> retour;
	for(int i=0;i<chemin.size();i++)
		retour.push_back(chemin[i]->getX() - 20);
	return retour;
}

std::vector<int> Graphe::Nodes2CheminY(std::vector<Node*> chemin){
	std::vector<int> retour;
	for(int i=0;i<chemin.size();i++)
		retour.push_back(19 - chemin[i]->getY());
	return retour;
}

Graphe::~Graphe(){
	for(int i=0; i<m_graphe.size();i++){
		for(int j=0;j<m_graphe[i].size();j++){
			delete (m_graphe[i][j]);
		}
	}
	delete a_star;
}
