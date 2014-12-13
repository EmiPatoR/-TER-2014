#include <sstream>
#include <fstream>
#include <boost/mpi.hpp>
#include <boost/thread.hpp>

#include "relogo/RandomMove.h"
#include "relogo/grid_types.h"
#include "relogo/Patch.h"
#include "relogo/AgentSet.h"
#include "repast_hpc/AgentRequest.h"
#include "TERObserver.h"
#include "Humain.h"
#include "Mur.h"
#include "coordonnes2d.h"

using namespace std;
using namespace repast;
using namespace relogo;

const string HUMAN_COUNT_PROP = "human.count";
const string LEVEL_FILENAME = "level.filename";

void TERObserver::go() {
	static bool continuer = true;
	if (_rank == 0) {
		Log4CL::instance()->get_logger("TER").log(INFO, "Debut du tick : " + boost::lexical_cast<string>(RepastProcess::instance()->getScheduleRunner().currentTick()));
	}

	synchronize<AgentPackage>(*this, *this, *this, RepastProcess::USE_LAST_OR_USE_CURRENT);

	boost::mpi::communicator world;
	int nombre_humains = 0, nombre_survivants = 0;

	AgentSet<Humain> humains;
	get(humains);
	humains.ask(&Humain::step);

	if (world.rank() == 0) {
		std::vector<int> all_survivants;
		std::vector<int> all_humains;
		boost::mpi::gather(world,this->m_survivants,all_survivants,0);
		boost::mpi::gather(world,this->humancount,all_humains,0);
		for(int proc=0;proc<world.size();++proc){
			nombre_humains = nombre_humains + all_humains[proc];
			nombre_survivants = nombre_survivants + all_survivants[proc];
		}
		if(nombre_humains == nombre_survivants && continuer){
			this->dernierTick = repast::RepastProcess::instance()->getScheduleRunner().currentTick();
			continuer = false;
		}
	} else {
		boost::mpi::gather(world, this->m_survivants, 0);
		boost::mpi::gather(world, this->humancount, 0);
	}



	//synchronizeTurtleStates<AgentPackage>(*this,*this);

	this->_fen->clear();
	dessinerDecor(_fen->getCadran());

	if (_rank == 0) {
		Log4CL::instance()->get_logger("TER").log(INFO, "Fin du tick: " + boost::lexical_cast<string>(RepastProcess::instance()->getScheduleRunner().currentTick()));
	}

	this->_fen->dormir(40);

}

void TERObserver::enregisterResultats(){


}

void TERObserver::setup(Properties& props) {
	boost::mpi::communicator world;
	timer.start();
	proprietes = &props;

	//repast::ScheduleRunner& runner = repast::RepastProcess::instance()->getScheduleRunner();
	//repast::MethodFunctor<TERObserver> *functor;
	//functor = new repast::MethodFunctor<TERObserver>(this,&TERObserver::enregisterResultats);

	int i = 0;
	int cadran = 0;
	static bool cree = false;
	bool agent_traite = false;
	std::stringstream titre;
	titre << "Observer : " << "Fenetre du processus " << world.rank();
	AgentSet<Humain>::as_iterator it;
	AgentSet<Mur>::as_iterator itm;
	Coordonnes2D c(0,0);
	m_survivants = 0;

	repast::Timer initTimer;
	initTimer.start();


	map_a_star = new int*[NB_CASES_LARGEUR*2];
	for(int j=0;j<NB_CASES_LARGEUR*2;j++)
		map_a_star[j] = new int [NB_CASES_HAUTEUR*2];

	this->loadMap(props,cadran);
	this->loadMap_a_star(props,m_sorties);

	this->nbSorties = this->m_sorties.size();

	humainType = create<Humain> (humancount);
	wallType = create<Mur>(wallcount);

	AgentSet<Mur> murs;
	get(murs);

	AgentSet<Humain> humains;
	get(humains);
	humains.apply(RandomMove(this));

	cout << "Observer : " << humains.count() << " Humains crees" << endl;
	cout << "Observer : " << murs.count() << " Murs crees" << endl;


	for(it=humains.begin();it!=humains.end();++it){
		Humain* h = *it;
		agent_traite = false;
		c.setX(0);
		c.setY(0);
		//std::cout << "IIIIII = " << i << std::endl;
		i++;

		if(!cree){
			h->randomAngle(props);
			h->left(h->getAngle());
			int posX = (int)h->xCor();
			int posY = (int)h->yCor();

			if(posX < 0 && posY > 0){
				cadran = 0;
			}
			else if(posX>0 && posY > 0){
				cadran = 1;
			}
			else if(posX < 0 && posY < 0){
				cadran = 2;
			}
			else{
				cadran = 3;
			}
			_fen = new Fenetre(titre.str().c_str(),&world,cadran);
			cree = true;
		}

		for(int j = 0;j<20 && !agent_traite;j++){
			for(int k=0;k<20 && !agent_traite;k++){
				if(map[cadran][j][k] == 2){
					c.setX(k);
					c.setY(j);
					c = map2Repast(c,cadran);
					//std::cout << "cadran : " << cadran << "X/Y = " << c.getX() << " / " << c.getY() << std::endl;
					h->setxy((double)c.getX(),(double)c.getY());
					map[cadran][j][k] = 0;
					agent_traite = true;
				}
			}
		}
	}

	for(itm=murs.begin();itm!=murs.end();++itm){
		Mur* m = *itm;
		agent_traite = false;
		c.setX(0);
		c.setY(0);
		for(int j = 0;j<20 && !agent_traite;j++){
			for(int k=0;k<20 && !agent_traite;k++){
				if(map[cadran][j][k] == 1){
					c.setX(k);
					c.setY(j);
					c = map2Repast(c,cadran);
					m->setxy((double)c.getX(),(double)c.getY());
					map[cadran][j][k] = 0;
					agent_traite = true;
				}
			}
		}
	}



	for(it=humains.begin();it!=humains.end();++it){
		Humain* h = *it;
		c.setX(h->xCor());
		c.setY(h->yCor());
		this->graphe = new Graphe(map_a_star,NB_CASES_LARGEUR*2,NB_CASES_HAUTEUR*2,c,m_sorties);
		h->setCheminXY(graphe->Nodes2CheminX(graphe->getChemin()), graphe->Nodes2CheminY(graphe->getChemin()),0,false);
		delete graphe;
	}

	dessinerDecor(_fen->getCadran());

	long double t = initTimer.stop();
	std::stringstream ss;
	ss << t;
	props.putProperty("init.time", ss.str());
}

void TERObserver::loadMap(Properties& props, int process_cadran){
	std::string filename;
	filename = props.getProperty(LEVEL_FILENAME);
	std::ifstream file(filename.c_str());
	std::string line;
	int numLigne = 0, numCol = 0;
	int limiteX1, limiteX2, limiteY1, limiteY2;
	int cadran;
	Coordonnes2D *c = NULL;
	char* buffer;


	if(file.is_open()){
		switch(repast::RepastProcess::instance()->rank()){
		case 0:
			limiteX1 = 0;
			limiteX2 = 20;
			limiteY1 = 20;
			limiteY2 = 40;
			break;
		case 1:
			limiteX1 = 20;
			limiteX2 = 40;
			limiteY1 = 20;
			limiteY2 = 40;
			break;
		case 2:
			limiteX1 = 0;
			limiteX2 = 20;
			limiteY1 = 0;
			limiteY2 = 20;
			break;
		case 3:
			limiteX1 = 20;
			limiteX2 = 40;
			limiteY1 = 0;
			limiteY2 = 20;
			break;
		default :
			break;
		}

		humancount = 0;
		wallcount = 0;

		while( std::getline(file,line) && numLigne < limiteY2){

			while(numLigne < limiteY1){
				std::getline(file,line);
				numLigne++;
			}

			buffer = (char*)line.c_str();
			for(numCol=limiteX1;numCol<limiteX2;numCol++){
				if(numLigne < 20 && numCol < 20){
					cadran = 0;
				}
				else if(numLigne >= 20 && numCol < 20){
					cadran = 2;
				}
				else if(numLigne < 20 && numCol >= 20){
					cadran = 1;
				}
				else{
					cadran = 3;
				}
				if(buffer[numCol] - '0' == 1){
					wallcount++;
				}
				else if(buffer[numCol] - '0' == 2){
					humancount++;
				}

				map[cadran][numLigne%20][numCol%20] = buffer[numCol] - '0';

			}

			numLigne++;
		}
	}
	else{
		std::cout << "Impossible d'ouvrir le fichier : " << filename << std::endl;
		exit(EXIT_FAILURE);
	}
}

void TERObserver::loadMap_a_star(Properties& props, std::vector<Coordonnes2D> &sorties){

	std::string filename;
	filename = props.getProperty(LEVEL_FILENAME);
	std::ifstream file(filename.c_str());
	std::string line;
	int numLigne = 0, numCol = 0;
	int limiteX1, limiteX2, limiteY1, limiteY2;
	int cadran;
	Coordonnes2D *c = NULL;
	char* buffer;

	if(file.is_open()){

		//charge le fichier en memoire pour A*
		while( std::getline(file,line)){ // on parcourre toutes les lignes jusqu'a la fin du fichier
			buffer = (char*)line.c_str(); // on stocke la ligne dans un buffer de char*
			for(numCol=0;numCol<NB_CASES_LARGEUR*2;numCol++){ // et toutes les colonnes
				if(buffer[numCol] == '0')
					map_a_star[numLigne][numCol] = 0;
				else if(buffer[numCol] == '1')
					map_a_star[numLigne][numCol] = 1;
				else if(buffer[numCol] == '2')
					map_a_star[numLigne][numCol] = 0;
				else if(buffer[numCol] == '3'){
					map_a_star[numLigne][numCol] = 0;
					sorties.push_back(Coordonnes2D(numCol,numLigne));
				}

				//if(repast::RepastProcess::instance()->rank() == 1)
				//std::cout << map_a_star[numLigne][numCol];
			}
			//if(repast::RepastProcess::instance()->rank() == 1)
			//std::cout << "\n";
			numLigne++;
		}
	}
	else{
		std::cout << "Impossible d'ouvrir le fichier : " << filename << std::endl;
		exit(EXIT_FAILURE);
	}
}

void TERObserver::dessinerDecor (int cadran){
	AgentSet<Humain> humains;
	get(humains);
	AgentSet<Humain>::as_iterator it;
	AgentSet<Mur> murs;
	get(murs);
	AgentSet<Mur>::as_iterator itm;
	double posX = 0.0 , posY = 0.0;
	Humain *h;
	Mur *m;

	for(it = humains.begin();it != humains.end(); ++it){

		h = *it;
		posX = h->xCor();
		posY = h->yCor();

		switch(cadran){
		case 0:
			posX = -posX;
			posX = 20 - posX;
			posX = posX * 20 + 10;
			posY = posY * 20 + 10;
			//cout << " X = " << posX << "/ Y = " << posY << endl;
			break;
		case 1:
			posX = posX * 20 + 10;
			posY = posY * 20 + 10;
			//cout << " X = " << posX << "/ Y = " << posY << endl;
			break;
		case 2:
			posX = -posX;
			posX = 20 - posX;
			posX = posX * 20 + 10;
			posY = -posY;
			posY = 20 - posY;
			posY = posY * 20 + 10;
			//cout << " X = " << posX << "/ Y = " << posY << endl;

			break;
		case 3:
			posX = posX * 20 + 10;
			posY = -posY;
			posY = 20 - posY;
			posY = posY * 20 + 10;
			//cout << " X = " << posX << "/ Y = " << posY << endl;
			break;
		default:
			break;
		}
		if(!h->getSorti())
			_fen->dessinerTriangle(posX,posY,h->getAngle(),h->getTypePersonne());
	}

	for(itm = murs.begin();itm != murs.end(); ++itm){
		m = *itm;
		posX = m->xCor();
		posY = m->yCor();

		switch(cadran){
		case 0:
			posX = -posX;
			posX = 20 - posX;
			posX = posX * 20;
			posY = posY * 20;
			//cout << " X = " << posX << "/ Y = " << posY << endl;
			break;
		case 1:
			posX = posX * 20;
			posY = posY * 20;
			//cout << " X = " << posX << "/ Y = " << posY << endl;
			break;
		case 2:
			posX = -posX;
			posX = 20 - posX;
			posX = posX * 20;
			posY = -posY;
			posY = 20 - posY;
			posY = posY * 20;
			//cout << " X = " << posX << "/ Y = " << posY << endl;

			break;
		case 3:
			posX = posX * 20;
			posY = -posY;
			posY = 20 - posY;
			posY = posY * 20;
			//cout << " X = " << posX << "/ Y = " << posY << endl;
			break;
		default:
			break;
		}
		_fen->dessinerMur(posX,posY);
	}

	this->_fen->refresh();
}

RelogoAgent* TERObserver::createAgent(const AgentPackage& content) {
	if (content.type == humainType){
		return new Humain(content.getId(), this, content);
	}
	else if(content.type == wallType){
		return new Mur(content.getId(),this,content);
	}
}

void TERObserver::provideContent(const repast::AgentRequest& request, std::vector<AgentPackage>& out) {
	const vector<AgentId>& ids = request.requestedAgents();
	for (int i = 0, n = ids.size(); i < n; i++) {
		AgentId id = ids[i];
		AgentPackage content = { id.id(), id.startingRank(), id.agentType(), id.currentRank() };

		if (id.agentType() == humainType) {
			Humain* humain = who<Humain> (id);
			content.cheminX = humain->getCheminX();
			content.cheminY = humain->getCheminY();
			content.etape = humain->getEtape();
			content.typePersonne = humain->getTypePersonne();
			out.push_back(content);
		}
	}
}

void TERObserver::provideContent(RelogoAgent* agent, std::vector<AgentPackage>& out) {
	AgentId id = agent->getId();
	AgentPackage content = { id.id(), id.startingRank(), id.agentType(), id.currentRank()};
	if (id.agentType() == humainType) {
		Humain* humain = static_cast<Humain*> (agent);
		content.cheminX = humain->getCheminX();
		content.cheminY = humain->getCheminY();
		content.etape = humain->getEtape();
		content.typePersonne = humain->getTypePersonne();
		out.push_back(content);
	}
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
		humain->setCheminXY(package.cheminX,package.cheminY,package.etape,false);
		humain->setTypePersonne(package.typePersonne);
		//humain->set(package.infected, package.infectionTime);
	}
}

Coordonnes2D TERObserver::Fcor2RCor(int posX, int posY){
	//conversion fichier -> repast
	posX = -20 + posX;
	posY = 19 - posY;
	Coordonnes2D c(posX,posY);
	return c;
}

Coordonnes2D TERObserver::Mcor2GLCor(int posX, int posY){
	//conversion fichier -> repast
	posX = posX * 20;
	posY = (19 - posY)*20;
	Coordonnes2D c(posX,posY);
	return c;
}

Coordonnes2D TERObserver::Rcor2GLCor(int posX, int posY, int cadran){
	switch(cadran){
	case 0:
		posX = -posX;
		posX = 20 - posX;
		posX = posX * 20;
		posY = posY * 20;
		//cout << " X = " << posX << "/ Y = " << posY << endl;
		break;
	case 1:
		posX = posX * 20;
		posY = posY * 20;
		//cout << " X = " << posX << "/ Y = " << posY << endl;
		break;
	case 2:
		posX = -posX;
		posX = 20 - posX;
		posX = posX * 20;
		posY = -posY;
		posY = 20 - posY;
		posY = posY * 20;
		//cout << " X = " << posX << "/ Y = " << posY << endl;

		break;
	case 3:
		posX = posX * 20;
		posY = -posY;
		posY = 20 - posY;
		posY = posY * 20;
		//cout << " X = " << posX << "/ Y = " << posY << endl;
		break;
	default:
		break;
	}
	Coordonnes2D c(posX,posY);
	return c;
}

void TERObserver::razMap(){
	for(int i=0;i<NB_PROCESS;i++){
		for(int j=0;j<NB_CASES_HAUTEUR;j++){
			for(int k=0;k<NB_CASES_LARGEUR;k++){
				if(map[i][j][k] == 2)
					map[i][j][k] = 0;
			}
		}
	}
}

void TERObserver::synchronizeMap(){
	Coordonnes2D c(0,0);
	int cadran;
	int x = 0, y = 0;
	AgentSet<Humain> humains;
	get(humains);
	AgentSet<Humain>::as_iterator it;

	razMap();

	for(it=humains.begin();it != humains.end(); ++it){
		Humain *h = *it;
		c.setX((int)h->xCor());
		c.setY((int)h->yCor());

		std::cerr << "AVANT : Agent num " << (h->getId()).startingRank() << " : " << c.getX() << " / " << c.getY() << "\n";

		if(c.getX() < 0 && c.getY() >= 0){
			cadran = 0;
			x = 19 + (c.getX());
			y = 19 - (c.getY());
		}
		else if(c.getX() >= 0 && c.getY() >= 0){
			cadran = 1;
			x = c.getX();
			y = 19 - (c.getY());
		}
		else if(c.getX() < 0 && c.getY() < 0){
			cadran = 2;
			x = 19 + (c.getX());
			y = -c.getY() + 1;
		}
		else{
			cadran = 3;
			x = c.getX();
			y = -c.getY() + 1;
		}

		std::cerr << "APRES : Agent num " << (h->getId()).startingRank() << " : " << x << " / " << y << "\n";

		map[cadran][y][x] = 2;


	}
}

Coordonnes2D TERObserver::map2Repast(Coordonnes2D c,int cadran){
	Coordonnes2D r(0,0);

	switch(cadran){
	case 0:
		r.setX(-20 + c.getX());
		r.setY(19 - c.getY());
		break;

	case 1:
		r.setX(c.getX());
		r.setY(19-c.getY());
		break;

	case 2:
		r.setX(-20 + c.getX());
		r.setY(-1 -c.getY());
		break;

	case 3:
		r.setX(c.getX());
		r.setY(-1 -c.getY());
		break;

	default:

		break;
	}

	return r;
}

void TERObserver::printMap(){
	for(int i=0;i<4;i++){
		std::cerr << "Cadran : " << i << std::endl;
		for(int j=0;j<20;j++){
			for(int k=0;k<20;k++){
				std::cerr << map[i][j][k];
			}
			std::cerr << "\n";
		}
		std::cerr << "\n \n";
	}
}
