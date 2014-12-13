#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Node.h"
#include "PathFinder.h"
#include "repast_hpc/RepastProcess.h"


Pathfinder::Pathfinder(){

}

std::vector<Node*> Pathfinder::findPath( std::vector< std::vector< Node*> > &graphe, Node* depart, Node* arrive ){
	std::vector<Node*> cheminFinal;
	Node* current = NULL;
	Node* node = NULL;
	std::vector<Node*> voisins;
	int max, newG, newH, newF;

	addToOpenList(depart);



	while( m_openList.size() > 0){
		current = getCurrentNode();
		//if(repast::RepastProcess::instance()->rank() == 2){
		//	std::cout << " CURRENT = " << current->getX() << " / " << current->getY() << std::endl;
		//}

		if(current == arrive)
			break;

		addToCloseList(current);

		/*if(repast::RepastProcess::instance()->rank() == 2){
			std::cout << " OpenList size = " << m_openList.size() << std::endl;
			std::cout << " CloseList size = " << m_closeList.size() << std::endl;
			exit(0);
		}*/

		voisins = getNeighbors(current, graphe);
		max = voisins.size();

		for(int i=0;i<max;i++){
			node = voisins[i];
			if(isOnCloseList(node) || !(node->getWalkable()) )
				continue;
			if((std::abs(node->getX() - current->getX()) + std::abs(node->getY() - current->getY())) <= 1){
				newG = node->getParent()->getG() + NODE_DISTANCE_VALUE;
				newH = ( std::abs(arrive->getY() - node->getY()) + std::abs(arrive->getX() - node->getX()) ) * NODE_DISTANCE_VALUE;
			}
			else{
				newG = node->getParent()->getG() + NODE_DISTANCE_DIAG_VALUE;
				newH = ( std::abs(arrive->getY() - node->getY()) + std::abs(arrive->getX() - node->getX()) ) * NODE_DISTANCE_DIAG_VALUE;
			}

			newF = newH + newG;

			if(isOnOpenList(node)){
				if(newG < node->getG()){
					node->setParent(current);
					node->setG(newG);
					node->setH(newH);
					node->setF(newF);
				}

			}
			else{
				addToOpenList(node);
				node->setParent(current);
				node->setG(newG);
				node->setH(newH);
				node->setF(newF);
			}
		}

	}

	if(m_openList.size() == 0){
		m_openList.clear();
		m_closeList.clear();
		return cheminFinal;
	}

	Node* dernier = arrive;
	std::vector<Node*>::iterator it = cheminFinal.begin();
	while(dernier != depart){
		it = cheminFinal.insert(it,dernier);
		dernier = dernier->getParent();
	}
	m_openList.clear();
	m_closeList.clear();
	return cheminFinal;
}

Node* Pathfinder::getCurrentNode(){
	int max = m_openList.size();
	int min = 1000000;
	Node* currentNode = NULL;
	Node* node = NULL;

	//std::random_shuffle(m_openList.begin(), m_openList.end());

	for(int i=0;i<m_openList.size();i++){
		node = m_openList[i];
		//if(repast::RepastProcess::instance()->rank() == 0){
		//std::cout << "Node X/Y = " << node->getX() << "/" << node->getY() << std::endl;
		//}
		if(node->getF() < min){
			min = node->getF();
			currentNode = node;
		}
	}

	return currentNode;

}

void Pathfinder::removeFromCloseList(Node* val){
	int max = m_closeList.size();
	for(int i=0;i<max;i++){
		if(m_closeList[i] == val){
			m_closeList.erase(m_closeList.begin()+i);
		}
	}
}

void Pathfinder::removeFromOpenList(Node* val){
	int max = m_openList.size();
	for(int i=0;i<max;i++){
		if(m_openList[i] == val){
			m_openList.erase(m_openList.begin()+i);
		}
	}
}


void Pathfinder::addToCloseList(Node* val){
	removeFromOpenList(val);
	m_closeList.push_back(val);
}

void Pathfinder::addToOpenList(Node* val){
	removeFromCloseList(val);
	m_openList.push_back(val);
}

bool Pathfinder::isOnOpenList(Node* val){
	int max = m_openList.size();
	for(int i=0;i<max;i++){
		if(m_openList[i] == val)
			return true;
	}
	return false;
}

bool Pathfinder::isOnCloseList(Node* val){
	int max = m_closeList.size();
	for(int i=0;i<max;i++){
		if(m_closeList[i] == val)
			return true;
	}
	return false;
}

std::vector<Node*> Pathfinder::getNeighbors(Node* val,std::vector< std::vector< Node*> > &graphe){
	std::vector<Node*> voisins;

	int maxCol = graphe[0].size();
	int maxLigne = graphe.size();

	int indiceUp = val->getY() - 1;
	int indiceBot = val->getY() + 1;
	int indiceLeft = val->getX() - 1;
	int indiceRight = val->getX() + 1;


	/*if(repast::RepastProcess::instance()->rank() == 0){
		std::cout << "Nombre de lignes = " << graphe.size() << std::endl;
		std::cout << "Nombre de colones = " << graphe[0].size() << std::endl;
	}*/


	if(indiceUp > -1){
		if(indiceLeft > -1)
			voisins.push_back(graphe[indiceUp][indiceLeft]); // Diagonale HAUT GAUCHE
		if(indiceRight < maxCol)
			voisins.push_back(graphe[indiceUp][indiceRight]); // Diagonale HAUT DROITE
		voisins.push_back(graphe[indiceUp][val->getX()]); // HAUT
	}
	if(indiceBot < maxLigne){
		if(indiceLeft > -1)
			voisins.push_back(graphe[indiceBot][indiceLeft]); // Diagonale BAS GAUCHE
		if(indiceRight < maxCol)
			voisins.push_back(graphe[indiceBot][indiceRight]); // Diagonale BAS DROITE
		voisins.push_back(graphe[indiceBot][val->getX()]);
	}

	if(indiceLeft > -1)
		voisins.push_back(graphe[val->getY()][indiceLeft]);
	if(indiceRight < maxCol)
		voisins.push_back(graphe[val->getY()][indiceRight]);

	return voisins;

}
