#ifndef PATH_FINDER_H
#define PATH_FINDER_H

/*!
 * \file PathFinder.h
 * \brief Classe representant une instance de l'algorithme A*
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#include "Node.h"
#include <vector>


/*! \class Pathfinder
 * \brief Classe representant une instance de l'algorithme A*
 */
class Pathfinder{
private :
	std::vector<Node*> m_openList; /*!< Liste ouverte Y */
	std::vector<Node*> m_closeList; /*!< Liste fermee Y */

	/*!
	 *  \brief Recupere le Node qui a son attribut m_F le plus petit
	 *  \return le Node dont le l'attribut m_F est minimum
	 *
	 *
	 */
	Node* getCurrentNode();

	/*!
	 *  \brief Supprime un Node de la liste ouverte
	 *	\param val : Node à supprimer dans la liste ouverte
	 */
	void removeFromOpenList(Node* val);

	/*!
	 *  \brief Supprime un Node de la liste fermee
	 *	\param val : Node à supprimer dans la liste fermee
	 */
	void removeFromCloseList(Node* val);

	/*!
	 *  \brief Ajoute un Node de la liste ouverte et l'enleve de la liste fermee s'il y figure
	 *	\param val : Node à ajouter dans la liste ouverte
	 */
	void addToCloseList(Node* val);

	/*!
	 *  \brief Ajoute un Node de la liste fermee et l'enleve de la liste ouverte s'il y figure
	 *	\param val : Node à ajouter dans la liste fermee
	 */
	void addToOpenList(Node* val);

	/*!
	 *  \brief Verifie si un Node appartient a la liste fermee
	 *	\param val : Node à verifier la presence dans la liste ouverte
	 *	\return Booleen indiquant la presence du Node.
	 */
	bool isOnOpenList(Node* val);

	/*!
	 *  \brief Verifie si un Node appartient a la liste ouverte
	 *	\param val : Node à verifier la presence dans la liste ouverte
	 *	\return Booleen indiquant la presence du Node.
	 */
	bool isOnCloseList(Node* val);

	/*!
	 *  \brief Recupere tous les Node voisins de val dans un tableau de pointeurs sur Node
	 *	\param val : Node dont on veut recuperer les voisins
	 *	\return tableau de Node contenant les Node voisins de val
	 */
	std::vector<Node*> getNeighbors(Node* val, std::vector < std::vector< Node*> > &graphe);
public:
	static const int NODE_DISTANCE_VALUE = 100; /*!< cout d'un deplacement dans les cases voisines HAUT BAS GAUCHE ou DROITE */
	static const int NODE_DISTANCE_DIAG_VALUE = 140; /*!< cout d'un deplacement dans les cases voisines DIAGONALES */
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Pathfinder
	 *
	 */
	Pathfinder();
	/*!
	 *  \brief Application de l'algorithme A* sur un objet Graphe dans le but de calculer un chemin du node Depart au node Arrivee
	 *
	 *  \param graphe : Objet de type Graphe
	 *  \param depart : Node de depart
	 *  \param arrivee : Node d'arrivee
	 *  \return tableau de node representant le chemin du Node depart au Node arrivee
	 *
	 */
	std::vector<Node*> findPath( std::vector< std::vector< Node*> > &graphe, Node* depart, Node* arrive );

};

#endif
