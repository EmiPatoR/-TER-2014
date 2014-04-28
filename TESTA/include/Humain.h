#ifndef HUMAIN_H_
#define HUMAIN_H_

#include "relogo/Turtle.h"
#include "AgentPackage.h"

class Humain : public repast::relogo::Turtle {

private:
	bool _burning;
	int _burningTime;

public:
	Humain(repast::AgentId id, repast::relogo::Observer* obs): repast::relogo::Turtle(id, obs), _burning(false), _burningTime(0) {}
	Humain(repast::AgentId id, repast::relogo::Observer* obs, const AgentPackage& package): repast::relogo::Turtle(id, obs), _burning(package.burning),
			_burningTime(package.burningTime) {}
	virtual ~Humain() {}

	void step();

	void infect();

	void getPos();

	bool infected() const {
		return _burning;
	}

	int infectionTime() const {
		return _burningTime;
	}

  void set(bool infected, int infectionTime){
	_burning = infected;
    _burningTime = infectionTime;
  }
};

#endif /* HUMAIN_H_ */
