#ifndef HUMAIN_H_
#define HUMAIN_H_

/*!
 * \file Humain.h
 * \brief Classe representant un agent Humain
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#define TAUX_PERSONNES_AGEES 5
#define TAUX_PERSONNES_JEUNES 70
#define TAUX_PERSONNES_ADULTES 20
#define TAUX_PERSONNES_MALADES 5

#define PERSONNE_ADULTE 0
#define PERSONNE_JEUNE 1
#define PERSONNE_AGEE 2
#define PERSONNE_MALADE 3

#include "relogo/Turtle.h"
#include "repast_hpc/RepastProcess.h"
#include "AgentPackage.h"
#include "fenetre.h"
#include "repast_hpc/Properties.h"

class Humain : public repast::relogo::Turtle {
	/*! \class Humain
	 * \brief classe representant un agent humain
	 *
	 *  La classe herite de la classe Turtle de repast, elle gere tout ce qui
	 *  concerne le deplacement et l'orientation des humains, la communication entre humains, etc...
	 */
private:
	double m_angle; /*!< Angle d'orientation de l'agent */
	int posXFichier; /*!< Position X de l'agent dans le fichier (colonne) */
	int posYFichier; /*!< Position Y de l'agent dans le fichier (ligne) */
	int posXGL; /*!< Position X de l'agent dans la fenetre (pixels) */
	int posYGL; /*!< Position Y de l'agent dans la fenetre (pixels) */
	std::vector<int> cheminX; /*!< Tableau des positions X a suivre par l'agent  */
	std::vector<int> cheminY; /*!< Tableau des positions Y a suivre par l'agent  */
	int etape; /*!< indice pour se situer dans le tableau du chemin a suivre  */
	int typePersonne; /*!< Type de personne (JEUNE,ADULTE,PERSONNE AGEE ou MALADE) */
	bool sorti; /*!< Booleen qui indique si un humain est sorti du batiment  */

public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Humain
	 *
	 *  \param id : Id de l'agent
	 *  \param obs : pointeur vers l'Observer qui gere les agents
	 */
	Humain(repast::AgentId id, repast::relogo::Observer* obs): repast::relogo::Turtle(id, obs) {
		int rndType;
		etape=0;
		sorti=false;

		if( (std::atoi((((TERObserver*)obs)->getProps()->getProperty("simulation.diff_age")).c_str())) == 1){
			//((TERObserver*)obs)->setDiffAge(1);
			rndType = randomType( *(((TERObserver*)obs)->getProps()) );
			if(rndType <= TAUX_PERSONNES_ADULTES)
				this->typePersonne = PERSONNE_ADULTE;
			else if(rndType <= (TAUX_PERSONNES_JEUNES + TAUX_PERSONNES_ADULTES) && rndType > TAUX_PERSONNES_ADULTES)
				this->typePersonne = PERSONNE_JEUNE;
			else if(rndType <= (TAUX_PERSONNES_JEUNES + TAUX_PERSONNES_ADULTES + TAUX_PERSONNES_AGEES) && rndType > (TAUX_PERSONNES_JEUNES + TAUX_PERSONNES_ADULTES))
				this->typePersonne = PERSONNE_AGEE;
			else
				this->typePersonne = PERSONNE_MALADE;
		}
		else{
			this->typePersonne = -1;
		}
	}

	/*!
	 *  \brief Constructeur pour le transfert d'agents
	 *
	 *  Constructeur de la classe Humain
	 *
	 *  \param id : Id de l'agent
	 *  \param obs : pointeur vers l'Observer qui gere les agents
	 *  \param package : archive serialisee qui contient toutes les donnees necessaire pour creer un agent.
	 */
	Humain(repast::AgentId id, repast::relogo::Observer* obs, const AgentPackage& package): repast::relogo::Turtle(id, obs),cheminX(package.cheminX),
			cheminY(package.cheminY),etape(package.etape),typePersonne(package.typePersonne){sorti=false;}
	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Humain
	 *
	 */
	virtual ~Humain() {}

	/*!
	 *  \brief affiche la position d'un humain(coordonnees repast)
	 *
	 */
	void getPos();

	/*!
	 *  \brief fonction principale decrivant le comportement de l'agent (execute a chaque tick)
	 *
	 */
	void step();

	/*!
	 *  \brief genere un angle aleatoire compris entre 0 et 359 (en degre)
	 *
	 *	\param props : pointeur sur les proprietes de la simulation(pour le random seed)
	 */
	void randomAngle(repast::Properties& props);

	/*!
	 *  \brief genere un type de personne aleatoire
	 *  \param props : pointeur sur les proprietes de la simulation(pour le random seed)
	 *
	 *	\return le typedepersonne genere.
	 */
	int randomType(repast::Properties& props);

	void afficherPos(Fenetre* fen);

	/*!
	 *  \brief recupere l'angle actuel d'un agent
	 *
	 *	\return l'angle de l'agent
	 */
	double getAngle();

	/*!
	 *  \brief conversion d'un angle de radians en degre
	 *  \param theta : angle en radians
	 *
	 *	\return angle en degre.
	 */
	double rad2deg(double theta);

	/*!
	 *  \brief Calcule l'angle a prendre pour aller au point de coordonnees x/y
	 *  \param x : coordonne x de l'emplacement ou on veut aller
	 *	\param y : coordonne y de l'emplacement ou on veut aller
	 *	\return angle vers le point de destination.
	 */
	double tournerVers(double x, double y);

	/*!
	 *  \brief Getter
	 *	\return l'attribut posXFichier de la classe Humain
	 */
	int getXFichier(void) const{
		return this->posXFichier;
	}

	/*!
	 *  \brief Getter
	 *	\return l'attribut posYFichier de la classe Humain
	 */
	int getYFichier(void) const{
		return this->posYFichier;
	}

	/*!
	 *  \brief Getter
	 *	\return l'attribut posXGL de la classe Humain
	 */
	int getXGL(void) const{
		return this->posXGL;
	}

	/*!
	 *  \brief Getter
	 *	\return l'attribut posYGL de la classe Humain
	 */
	int getYGL(void) const{
		return this->posYGL;
	}

	/*!
	 *  \brief Setter
	 *	\param val : nouvelle valeur pour l'attribut posXFichier de la classe Humain
	 */
	void setXFichier(int val){
		this->posXFichier = val;
	}

	/*!
	 *  \brief Setter
	 *	\param val : nouvelle valeur pour l'attribut posYFichier de la classe Humain
	 */
	void setYFichier(int val){
		this->posYFichier = val;
	}

	/*!
	 *  \brief Setter
	 *	\param val : nouvelle valeur pour l'attribut posXGL de la classe Humain
	 */
	void setXGL(int val){
		this->posXGL = val;
	}

	/*!
	 *  \brief Setter
	 *	\param val : nouvelle valeur pour l'attribut posYGL de la classe Humain
	 */
	void setYGL(int val){
		this->posYGL = val;
	}

	/*!
	 *  \brief Setter
	 *	\param val : nouvelle valeur pour l'attribut m_angle de la classe Humain
	 */
	void setAngle(double val){
		this->m_angle = val;
	}

	/*!
	 *  \brief Getter
	 *	\return l'attribut typePersonne de la classe Humain
	 */
	int getTypePersonne(){return this->typePersonne;}
	void setTypePersonne(int val){this->typePersonne = val;}

	/*!
	 *  \brief Getter
	 *	\return l'attribut etape de la classe Humain
	 */
	int getEtape(){return this->etape;}

	/*!
	 *  \brief Getter
	 *	\return l'attribut sorti de la classe Humain
	 */
	bool getSorti(){return this->sorti;}

	/*!
	 *  \brief Getter
	 *	\return l'attribut cheminX de la classe Humain
	 */
	std::vector<int> getCheminX(){return this->cheminX;}

	/*!
	 *  \brief Getter
	 *	\return l'attribut cheminY de la classe Humain
	 */
	std::vector<int> getCheminY(){return this->cheminY;}

	/*!
	 *  \brief Setter
	 *	\param cheminX : nouvelle valeur pour l'attribut cheminX de la classe Humain
	 *	\param cheminY : nouvelle valeur pour l'attribut cheminY de la classe Humain
	 *	\param etape : nouvelle valeur pour l'attribut etape de la classe Humain
	 *	\param sorti : nouvelle valeur pour l'attribut sorti de la classe Humain
	 */
	void setCheminXY(std::vector<int> cheminX, std::vector<int> cheminY,int etape, bool sorti){
		this->cheminX = cheminX;
		this->cheminY = cheminY;
		this->etape = etape;
	}

};

#endif /* HUMAIN_H_ */
