#include <sstream>

#include <boost/thread.hpp>

#include "relogo/RandomMove.h"
#include "relogo/grid_types.h"
#include "relogo/Patch.h"
#include "repast_hpc/AgentRequest.h"

#include "TERObserver.h"
#include "Humain.h"

using namespace std;
using namespace repast;
using namespace relogo;

const string HUMAN_COUNT_PROP = "human.count";

void TERObserver::go() {
/*
  if (_rank == 0) {
    Log4CL::instance()->get_logger("root").log(INFO, "TICK BEGINS: " + boost::lexical_cast<string>(RepastProcess::instance()->getScheduleRunner().currentTick()));
  }
  synchronize<AgentPackage>(*this, *this, *this, RepastProcess::USE_LAST_OR_USE_CURRENT);

  AgentSet<Humain> humains;
  get(humains);
  //humains.ask(&Humain::step);

  if (_rank == 0) {
    Log4CL::instance()->get_logger("root").log(INFO, "TICK ENDS: " + boost::lexical_cast<string>(RepastProcess::instance()->getScheduleRunner().currentTick()));
  }
  */
	cout << "test" << endl;
}

void TERObserver::setup(Properties& props) {
  //	Observer::setup(props); // No longer need to call this (SimRunner calls _setup, which calls this after all initialization is done)

  repast::Timer initTimer;
  initTimer.start();

  int humanCount = strToInt(props.getProperty(HUMAN_COUNT_PROP));
  humainType = create<Humain> (humanCount);

  AgentSet<Humain> humains;
  get(humains);
  humains.apply(RandomMove(this));
  cout << humains.count() << " Humains crees" << endl;
  humains.ask(&Humain::getPos);

  long double t = initTimer.stop();
  std::stringstream ss;
  ss << t;
  props.putProperty("init.time", ss.str());
}

RelogoAgent* TERObserver::createAgent(const AgentPackage& content) {
		if (content.type == humainType){
			return new Humain(content.getId(), this, content);
		}
}

void TERObserver::hello_thread (){
	cout << "HELLO" << endl;
}

void TERObserver::provideContent(const repast::AgentRequest& request, std::vector<AgentPackage>& out) {
	const vector<AgentId>& ids = request.requestedAgents();
	for (int i = 0, n = ids.size(); i < n; i++) {
		AgentId id = ids[i];
		AgentPackage content = { id.id(), id.startingRank(), id.agentType(), id.currentRank(), 0, false };
		if (id.agentType() == humainType) {
			Humain* humain = who<Humain> (id);
			//content.burning = humain->;
			//content.infectionTime = human->infectionTime();
		}
		out.push_back(content);
	}
}

void TERObserver::provideContent(RelogoAgent* agent, std::vector<AgentPackage>& out) {
	AgentId id = agent->getId();
	AgentPackage content = { id.id(), id.startingRank(), id.agentType(), id.currentRank(), 0, false };
	if (id.agentType() == humainType) {
		Humain* human = static_cast<Humain*> (agent);
		//content.infected = human->infected();
		//content.infectionTime = human->infectionTime();
	}
	out.push_back(content);
}

void TERObserver::createAgents(std::vector<AgentPackage>& contents, std::vector<RelogoAgent*>& out) {
	for (size_t i = 0, n = contents.size(); i < n; ++i) {
		AgentPackage content = contents[i];
		if (content.type == humainType) {
			out.push_back(new Humain(content.getId(), this, content));
		} else {
			// its a patch.
			out.push_back(new Patch(content.getId(), this));
		}
	}
}

void TERObserver::updateAgent(AgentPackage package){
  repast::AgentId id(package.id, package.proc, package.type);
  if (id.agentType() == humainType) {
    Humain * humain = who<Humain> (id);
    //humain->set(package.infected, package.infectionTime);
  }
}
