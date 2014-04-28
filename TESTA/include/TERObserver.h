#ifndef ZOMBIEOBSERVER_H_
#define ZOMBIEOBSERVER_H_

#include "relogo/Observer.h"
#include "repast_hpc/AgentRequest.h"
#include "repast_hpc/Properties.h"

#include "AgentPackage.h"
#include "fenetre.h"

class TERObserver : public repast::relogo::Observer {

private:
	repast::Properties props;
	int humainType;
	Fenetre *_fen;

public:
	TERObserver() { _fen = NULL;}
	virtual ~TERObserver() { if(_fen != NULL) delete _fen;}

	void go();
	virtual void setup(repast::Properties& props); // NOTE: 'virtual' needed by some compilers

	// create and provide for agents moving between processes
	repast::relogo::RelogoAgent* createAgent(const AgentPackage& content);
	void provideContent(const repast::AgentRequest& request, std::vector<AgentPackage>& out);

	// create and provide for buffer sync
	void createAgents(std::vector<AgentPackage>& content, std::vector<repast::relogo::RelogoAgent*>& out);
	void provideContent(repast::relogo::RelogoAgent* agent, std::vector<AgentPackage>& out);

	void updateAgent(AgentPackage package);

	void hello_thread();
};

#endif /* ZOMBIEOBSERVER_H_ */
