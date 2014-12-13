#ifndef GRAPHE_H
#define GRAPHE_H


/*!
 * \file Graphe.h
 * \brief Classe representant le monde Repast en memoire afin d'appliquer l'algorithme A*
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#include <vector>
#include "Node.h"
#include "coordonnes2d.h"
#include "PathFinder.h"

/*! \class Graphe
 * \brief Classe representant le monde Repast en memoire
 *
 *  La classe est composee de du chemin le plus court, d'une matrice d'objets Node
 */
class Graphe{
public :
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Graphe
	 *
	 *  \param map : matrice d'entiers representant le monde repast en memoire
	 *  \param longueur_map : nombre de colonnes de la matrice
	 *  \param hauteur : nombre de lignes de la matrice
	 *  \param depart : Objet Coordonnes2D representant le point de depart du chemin a calculer
	 *  \param sorties : Tableau de toutes les sorties(points d'arrivees possibles)
	 */
	Graphe(int** map,int longueur_map,int hauteur_map,Coordonnes2D depart, std::vector<Coordonnes2D> &sorties);
	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Graphe
	 *
	 */
	virtual ~Graphe();

	/*!
	 *  \brief Conversion Node -> Entiers (X)
	 *
	 *  Convertie un tableau d'objets Node en tableau d'entier contenant les coordonnes X
	 *
	 *  \param chemin : tableau d'objets Node representant le chemin
	 *  \return tableau d'entier contenant les coordonnes X du chemin
	 */
	std::vector<int> Nodes2CheminX(std::vector<Node*> chemin);

	/*!
	 *  \brief Conversion Node -> Entiers (Y)
	 *
	 *  Convertie un tableau d'objets Node en tableau d'entier contenant les coordonnes Y
	 *
	 *  \param chemin : tableau d'objets Node representant le chemin
	 *  \return tableau d'entier contenant les coordonnes Y du chemin
	 */
	std::vector<int> Nodes2CheminY(std::vector<Node*> chemin);

	/*!
	 *  \brief Getter de l'attribut m_chemin de la classe Graphe
	 *
	 *
	 *  \return l'attribut m_chemin de la classe Graphe
	 */
	std::vector<Node*> getChemin(){return m_chemin;}

	/*!
	 *  \brief Calcule la sortie la plus proche du point de depart
	 *	\param sorties : tableau contenant les coordonnees de toutes les sorties
	 *	\param depart : Node de depart
	 *
	 *  \return un chemin vers la sortie la plus proche de la position de depart
	 */
	std::vector<Node*> calculSortie(std::vector<Coordonnes2D> &sorties, Node* depart);
private:
	Pathfinder* a_star; /*!< Objet Pathfinder pour appliquer l'algorithme A* */
	std::vector<Node*> m_chemin; /*!< chemin calcule par A* */
	std::vector< std::vector< Node*> > m_graphe; /*!< matrices de Node qui representes la carte Repast en memoire */
	int **m_map; /*!< matrice d'entier representant la carte repast en memoire */
	int m_longueur; /*!< nombre de colonnes de la matrice */
	int m_hauteur; /*!< nombre de lignes de la matrice */
	Coordonnes2D m_depart; /*!< objet Coordonnes2D representant le point de depart */
	Coordonnes2D m_arrive; /*!< objet Coordonnes2D representant le point d'arrivee */
};

#endif
