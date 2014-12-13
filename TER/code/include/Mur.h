#ifndef MUR_H_
#define MUR_H_

/*!
 * \file Mur.h
 * \brief Classe representant un Mur
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#include "relogo/Turtle.h"
#include "repast_hpc/RepastProcess.h"
#include "AgentPackage.h"
#include "fenetre.h"
#include "repast_hpc/Properties.h"
/*! \class Mur
 * \brief Classe representant un Mur
 *
 */
class Mur : public repast::relogo::Turtle {

private:

public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Mur
	 *
	 *  \param id : Id de l'agent
	 *  \param obs : pointeur vers l'Observer qui gere les agents
	 */
	Mur(repast::AgentId id, repast::relogo::Observer* obs): repast::relogo::Turtle(id, obs) {}
	/*!
	 *  \brief Constructeur pour le transfert d'agents (ici inutile car les murs ne se deplacent pas)
	 *
	 *  Constructeur de la classe Mur
	 *
	 *  \param id : Id de l'agent
	 *  \param obs : pointeur vers l'Observer qui gere les agents
	 *  \param package : archive serialisee qui contient toutes les donnees necessaire pour creer un agent.
	 */
	Mur(repast::AgentId id, repast::relogo::Observer* obs, const AgentPackage& package): repast::relogo::Turtle(id, obs) {}
	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Humain
	 *
	 */
	virtual ~Mur() {}
};

#endif /* MUR_H_ */
