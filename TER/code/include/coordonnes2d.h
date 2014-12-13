#ifndef COORDONNES2D_H
#define COORDONNES2D_H

/*!
 * \file coordonnes2d.h
 * \brief Classe representant une position(coordonnees) d'un point
 * \author HRUSTIC EMIR
 * \version 0.1
 */

/*! \class Coordonnes2D
 * \brief Classe representant une position(coordonnees) d'un point
 *
 *  La classe est composee des coordonnees x et y d'un point ainsi que le cadran dans lequel il se trouve.
 */
class Coordonnes2D
{
protected:
	int m_X; /*!< position X */
	int m_Y; /*!< position Y */
	int m_cadran; /*!< cadran de la fenetre */

public:
	/** Default constructor */

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Coordonnes2D
	 *
	 */
	Coordonnes2D();

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Coordonnes2D
	 *
	 *  \param X : coordonnee X a stocker
	 *  \param Y : coordonnee Y a stocker
	 */
	Coordonnes2D(int X, int Y);

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de copie de la classe Coordonnes2D
	 *
	 *  \param c : reference sur l'element a copier
	 */
	Coordonnes2D(const Coordonnes2D& c); //cstr de copie
	/** Default destructor */

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Coordonnes2D
	 *
	 */
	virtual ~Coordonnes2D();

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_X de la classe Coordonnes2D
	 *
	 *  \return l'attribut m_X de la classe Coordonnes2D
	 */
	int getX()const{return m_X;}

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_Y de la classe Coordonnes2D
	 *
	 *  \return l'attribut m_Y de la classe Coordonnes2D
	 */
	int getY()const{return m_Y;}

	/*!
	 *  \brief Getter
	 *
	 *  Getter de l'attribut m_cadran de la classe Coordonnes2D
	 *
	 *  \return l'attribut m_cadran de la classe Coordonnes2D
	 */
	int getCadran()const{return m_cadran;}

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_X de la classe Coordonnes2D
	 *
	 */
	void setX(int X){m_X = X;}

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_Y de la classe Coordonnes2D
	 *
	 */
	void setY(int Y){m_Y = Y;}

	/*!
	 *  \brief Setter
	 *
	 *  Setter de l'attribut m_cadran de la classe Coordonnes2D
	 *
	 */
	void setCadran(int val){m_cadran = val;}
private:
};

#endif // COORDONNES2D_H
