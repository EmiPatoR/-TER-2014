#ifndef FENETRE_H
#define FENETRE_H

/*!
 * \file fenetre.h
 * \brief Classe representant une fenetre SDL
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#include <string>
#include <SDL2/SDL.h>

/*! \class Fenetre
 * \brief Classe representant une Fenetre SDL
 *
 *  La classe est composee des dimensions de la fentre, du titre, du cadran auquel elle appartient, un communicateur avec les
 *  autres processus.
 */
class Fenetre
{
public:
	/** Default constructor */
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Fenetre
	 *
	 *  \param world : canal de communication avec les autres processus
	 *  \param cadran : numero de cadran du monde dont s'occupe le processus qui contient la fenetre
	 *  \param longueur : longueur de la fenetre en pixels(400 par default)
	 *  \param hauteur : hauteur de la fenetre en pixels(400 par default)
	 */
	Fenetre(std::string titre,boost::mpi::communicator *world, unsigned int cadran,
			unsigned int longueur = 400, unsigned int hauteur = 400);
	/** Default destructor */
	virtual ~Fenetre();

	void main_loop();

	/*!
	 *  \brief rafraichissement de la fenetre
	 *
	 *  Methode qui efface et redessine la fentre (mise a jour de l'affichage)
	 *
	 */
	void refresh(void);


	/** Getters and setters */

	/*!
	 *  \brief Getter de l'attribut m_largeur de la classe Fenetre
	 *
	 * \return valeur de l'attribut m_largeur de la classe Fenetre
	 *
	 */
	unsigned int getLongueur();

	/*!
	 *  \brief Getter de l'attribut m_hauteur de la classe Fenetre
	 *
	 * \return valeur de l'attribut m_hauteur de la classe Fenetre
	 *
	 */
	unsigned int getHauteur();

	/*!
	 *  \brief fonction qui dessine un triangle sur la fenetre
	 *	\param posX : position X du centre de gravite du triangle a dessiner
	 *	\param posY : position Y du centre de gravite du triangle a dessiner
	 *	\param posX : valeur de l'angle en degre duquel on doit faire pivoter le triangle (sens trigo)
	 *	\param type : couleur du triangle a dessiner selon le type (ADULTE, JEUNE , PERSONNE AGEE ou MALADE)
	 */
	void dessinerTriangle(int posX, int posY, double angle, int type);

	/*!
	 *  \brief fonction qui dessine un carré 20x20 pixels (Mur) sur la fenetre
	 *	\param posX : position X ou l'on veut dessiner le mur
	 *	\param posY : position Y ou l'on veut dessiner le mur
	 */
	void dessinerMur(int posX, int posY);

	/*!
	 *  \brief Getter de l'attribut m_ecran de la classe Fenetre
	 *
	 * \return valeur de l'attribut m_ecran de la classe Fenetre
	 *
	 */
	SDL_Window* getScreen();

	/*!
	 *  \brief Getter de l'attribut m_context de la classe Fenetre
	 *
	 * \return valeur de l'attribut m_context de la classe Fenetre
	 *
	 */
	SDL_GLContext getGLContext();
	/*!
	 *  \brief Getter de l'attribut m_cadran de la classe Fenetre
	 *
	 * \return valeur de l'attribut m_cadran de la classe Fenetre
	 *
	 */
	int getCadran();

	/*!
	 *  \brief fonction qui redessine en blanc la fenetre (effacement)
	 *
	 *
	 */
	void clear(void);

	/*!
	 *  \brief fonction qui endors le processus qui s'occupe de la fenetre
	 *	\param val : valeur en millisecondes durant laquelle le processus doit s'endormir
	 *
	 */
	void dormir(int val);
protected:
	boost::mpi::communicator *world; /*!< canal de communication inter-processus */
	unsigned int m_largeur; /*!< longueur de la fenetre en pixels */
	unsigned int m_hauteur; /*!< hauteur de la fenetre en pixels */
	unsigned int m_cadran; /*!< cadran duquel s'occupe la fenetre */
	std::string m_titre; /*!< Titre de la fenetre */
	SDL_Window *m_ecran; /*!< structure de donnee pour representer une fenetre en SDL */
	SDL_GLContext m_context; /*!< Contexte de la fenetre SDL (voir doc SDL) */
	Uint32 m_bg_color; /*!< Couleur d'arriere plan de la fenetre */
	SDL_Event m_e; /*!< Evenements de la fenetre */
private:

};

#endif // FENETRE_H
