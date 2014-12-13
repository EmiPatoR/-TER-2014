#ifndef COULEUR_H
#define COULEUR_H


/*!
 * \file couleur.h
 * \brief Classe representant une Couleur
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#include <SDL2/SDL.h>

/*! \class Couleur
 * \brief Classe representant une Couleur
 *
 *  La classe est composee des des quantité de Rouge, Vert et Bleu d'une couleur.
 */
class Couleur {
public:
	/** Default constructor */
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Couleur
	 *
	 *  \param R : quantite de rouge
	 *  \param G : quantite de vert
	 *  \param B : quantite de bleu
	 */
	Couleur(Uint8 R, Uint8 G, Uint8 B);

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Couleur
	 *
	 */
	virtual ~Couleur();
	/** Getters */

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_color_uint32 de la classe Couleur
	 *
	 */
	Uint32 getColor();

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_color de la classe Couleur
	 *
	 */
	SDL_Color getSDLColor();

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_R de la classe Couleur
	 *
	 */
	Uint8 getR();

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_G de la classe Couleur
	 *
	 */
	Uint8 getG();

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_B de la classe Couleur
	 *
	 */
	Uint8 getB();

	/** Setters */

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_color_uint32 de la classe Couleur
	 *	\param val : valeur a attribuer a l'attribut m_color_uint32 de la classe Couleur
	 */
	void setColor(Uint32 val);

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_color de la classe Couleur
	 *	\param val : valeur a attribuer a l'attribut m_color de la classe Couleur
	 */
	void setSDLColor(SDL_Color val);

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_R de la classe Couleur
	 *	\param val : valeur a attribuer a l'attribut m_R de la classe Couleur
	 */
	void setR(Uint8 val);

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_G de la classe Couleur
	 *	\param val : valeur a attribuer a l'attribut m_G de la classe Couleur
	 */
	void setG(Uint8 val);

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_B de la classe Couleur
	 *	\param val : valeur a attribuer a l'attribut m_B de la classe Couleur
	 */
	void setB(Uint8 val);

	/*!
	 *  \brief Setter
	 *
	 *  Setter des attributs m_R , m_G , m_B de la classe Couleur
	 *	\param valR : valeur a attribuer a l'attribut m_R de la classe Couleur
	 *	\param valG : valeur a attribuer a l'attribut m_G de la classe Couleur
	 *	\param valB : valeur a attribuer a l'attribut m_B de la classe Couleur
	 */
	void setRGB(Uint8 valR, Uint8 valG, Uint8 valB);
protected:
	Uint8 m_R; /*!< quantite de rouge */
	Uint8 m_G; /*!< quantite de vert */
	Uint8 m_B; /*!< quantite de bleu */
	SDL_Color m_color; /*!< structure de donnee SDL pour representer une couleur */
	Uint32 m_color_uint32; /*!< structure de donnee SDL pour representer une couleur */
private:
};

#endif // COULEUR_H