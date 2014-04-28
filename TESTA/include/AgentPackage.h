#ifndef AGENTPACKAGE_H
#define AGENTPACKAGE_H

#include "repast_hpc/AgentId.h"

struct AgentPackage {

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & id;
		ar & proc;
		ar & type;
		ar & currentProc;

		ar & burningTime;
		ar & burning;
	}

	int id, proc, type, currentProc;

	int burningTime;
	bool burning;

	repast::AgentId getId() const {
		return repast::AgentId(id, proc, type, currentProc);
	}
};



#endif /* AGENTCONTENT_H_ */
