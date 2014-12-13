#ifndef NODE_H
#define NODE_H

/*!
 * \file Node.h
 * \brief Classe representant un Node
 * \author HRUSTIC EMIR
 * \version 0.1
 */

/*! \class Node
 * \brief Classe representant un Node
 *	Un Node est une "case" de la matrice representant le monde Repast, chaque node contient les heuristiques,g,h et f,
 *	une position X et Y , un Node Parent, et un boolean indiquant si le node est un mur ou pas.
 */
class Node{
private:
	int m_g; /*!< Heuristique G representant la valeur totale du chemin parcourru */
	int m_h; /*!< Heuristique H representant la distance a vol d'oiseau de la position actuelle jusqu'au Node d'arrivee */
	int m_f; /*!< Somme de G et H, F = H + G */
	int m_X; /*!< Position X */
	int m_Y; /*!< Position Y */
	bool m_walkable; /*!< Boolean representant si le Node est un mur ou pas */
	Node *m_parent; /*!< pointeur sur le Node parent */

public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Node
	 *
	 */
	Node();

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Node
	 *
	 */
	virtual ~Node();

	/*!
	 *  \brief Compare deux objets de type Node
	 *	\param b : node a comparer au Node actuel
	 *  \return un boolean idiquant si les deux nodes sont egaux.
	 *
	 */
	bool estEgal(Node const& b) const;

	/*!
	 *  \brief Setter de l'attribut Parent de la classe Node
	 *	\param val : valeur de l'attribut a modifier
	 *
	 */
	void setParent(Node* val);

	/*!
	 *  \brief Getter de l'attribut m_parent de la classe Node
	 *	\return valeur de l'attribut m_parent de la classe Node
	 *
	 */
	Node* getParent();

	/*!
	 *  \brief Setter de l'attribut m_walkable de la classe Node
	 *	\param val : valeur de l'attribut a modifier
	 *
	 */
	void setWalkable(bool val){m_walkable = val;}

	/*!
	 *  \brief Setter de l'attribut m_G de la classe Node
	 *	\param val : valeur de l'attribut a modifier
	 *
	 */
	void setG(int val){m_g = val;}

	/*!
	 *  \brief Setter de l'attribut m_F de la classe Node
	 *	\param val : valeur de l'attribut a modifier
	 *
	 */
	void setF(int val){m_f = val;}

	/*!
	 *  \brief Setter de l'attribut m_h de la classe Node
	 *	\param val : valeur de l'attribut a modifier
	 *
	 */
	void setH(int val){m_h = val;}

	/*!
	 *  \brief Setter de l'attribut m_X de la classe Node
	 *	\param val : valeur de l'attribut a modifier
	 *
	 */
	void setX(int val){m_X = val;}

	/*!
	 *  \brief Setter de l'attribut m_Y de la classe Node
	 *	\param val : valeur de l'attribut a modifier
	 *
	 */
	void setY(int val){m_Y = val;}

	/*!
	 *  \brief Getter de l'attribut m_walkable de la classe Node
	 *	\return valeur de l'attribut m_walkable de la classe Node
	 *
	 */
	bool getWalkable(){return m_walkable;}

	/*!
	 *  \brief Getter de l'attribut m_G de la classe Node
	 *	\return valeur de l'attribut m_G de la classe Node
	 *
	 */
	int getG(){return m_g;}

	/*!
	 *  \brief Getter de l'attribut m_F de la classe Node
	 *	\return valeur de l'attribut m_F de la classe Node
	 *
	 */
	int getF(){return m_f;}

	/*!
	 *  \brief Getter de l'attribut m_H de la classe Node
	 *	\return valeur de l'attribut m_H de la classe Node
	 *
	 */
	int getH(){return m_h;}

	/*!
	 *  \brief Getter de l'attribut m_X de la classe Node
	 *	\return valeur de l'attribut m_X de la classe Node
	 *
	 */
	int getX(){return m_X;}

	/*!
	 *  \brief Getter de l'attribut m_Y de la classe Node
	 *	\return valeur de l'attribut m_Y de la classe Node
	 *
	 */
	int getY(){return m_Y;}
};

#endif
