#ifndef AGENTPACKAGE_H
#define AGENTPACKAGE_H

/*!
 * \file AgentPackage.h
 * \brief Classe representant une archive serialisee
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#include "repast_hpc/AgentId.h"
#include "boost/serialization/vector.hpp"

/**
 * \struct AgentPackage
 * \brief Objet servant d'archive pour le transfert d'attribut des agents d'un processus à un autre.
 *
 */
struct AgentPackage {

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & id;
		ar & proc;
		ar & type;
		ar & currentProc;

		ar & cheminX;
		ar & cheminY;
		ar & etape;
		ar & typePersonne;
	}

	int id; /*!< id de l'agent */
	int proc; /*!< id processus createur de l'agent */
	int type; /*!< type d'agent */
	int currentProc; /*!< id du processus courant */
	std::vector<int> cheminX; /*!< attribut cheminX de la classe Humain */
	std::vector<int> cheminY; /*!< attribut cheminY de la classe Humain */
	int etape; /*!< attribut etape de la classe Humain */
	int typePersonne; /*!< attribut typePersonne de la classe Humain */

	repast::AgentId getId() const {
		return repast::AgentId(id, proc, type, currentProc);
	}
};



#endif /* AGENTCONTENT_H_ */
