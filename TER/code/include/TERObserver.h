#ifndef TEROBSERVER_H_
#define TEROBSERVER_H_

/*!
 * \file TERObserver.h
 * \brief Classe representant un TERObserver
 * \author HRUSTIC EMIR
 * \version 0.1
 */

#include <boost/mpi.hpp>
#include "relogo/Observer.h"
#include "repast_hpc/AgentRequest.h"
#include "repast_hpc/Properties.h"
#include "coordonnes2d.h"
#include "Graphe.h"
#include <list>

#include "AgentPackage.h"
#include "fenetre.h"

#define NB_PROCESS 4
#define NB_CASES_HAUTEUR 20
#define NB_CASES_LARGEUR 20

/*! \class TERObserver
 * \brief Classe representant un observateur, qui s'occupe de la gestion des agents dans ce processus
 */
class TERObserver : public repast::relogo::Observer {

private:
	repast::Properties* proprietes; /*!< proprietes de la simulations */
	int humainType, wallType; /*!< Type des agents */
	Fenetre *_fen; /*!< Fenetre SDL */
	int map[NB_PROCESS][NB_CASES_HAUTEUR][NB_CASES_LARGEUR]; /*!< liste de matrices par cadran*/
	int** map_a_star; /*!< matrice representant la carte pour appliquer A* */
	std::vector<Coordonnes2D> m_sorties; /*!< Liste des sorties */
	int humancount,wallcount; /*!< nombre d'agents */
	int m_survivants; /*!< nombre de survivants a la simulation */
	repast::Timer timer; /*!< Timer pour recuperer le temps de simulation */
	Graphe* graphe; /*!< Graphe pour l'application d'A* */
	double dernierTick; /*!< Dernier tick d'evacuation */
	int ageDiff; /*!< avec ou sans prise en compte de la difference d'age dans la simulation */
	int nbSorties; /*!< nombre de sorties */

public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe TERObserver
	 *
	 */
	TERObserver() { _fen = NULL;dernierTick = -1;nbSorties = 0;}

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Pathfinder
	 *
	 */
	virtual ~TERObserver() {
		if(_fen != NULL) delete _fen;
		//liberation memoire
		for(int j=0;j<NB_CASES_LARGEUR*2;j++)
			delete map_a_star[j];
		delete map_a_star;

		std::vector<double> all_last_ticks;
		int nombre_humains = 0;
		int nombre_survivants = 0;
		double tickEvacutaion = -1, max = 0;
		bool evacuation_reussi = true;

		if(this->dernierTick == -1)
			evacuation_reussi = false;

		boost::mpi::communicator world;

		if (world.rank() == 0) {
			std::vector<int> all_survivants;
			std::vector<int> all_humains;
			std::vector<int> all_sorties;
			boost::mpi::gather(world,this->m_survivants,all_survivants,0);
			boost::mpi::gather(world,this->humancount,all_humains,0);
			for(int proc=0;proc<world.size();++proc){
				nombre_humains = nombre_humains + all_humains[proc];
				nombre_survivants = nombre_survivants + all_survivants[proc];
			}
		} else {
			boost::mpi::gather(world, this->m_survivants, 0);
			boost::mpi::gather(world, this->humancount, 0);
		}

		if(repast::RepastProcess::instance()->rank() == 0){
			if(evacuation_reussi){
				proprietes->putProperty("evacuation","reussie");
				proprietes->putProperty("dernier.tick.evacuation",this->dernierTick);
			}
			else{
				proprietes->putProperty("evacuation","echouee");
				proprietes->putProperty("dernier.tick.evacuation","evacuation echouee");
			}

			proprietes->putProperty("run.time", timer.stop());
			proprietes->putProperty("nombre.humains",nombre_humains);
			proprietes->putProperty("nombre.survivants",nombre_survivants);
			proprietes->putProperty("nombre.morts", (nombre_humains - nombre_survivants));
			proprietes->putProperty("nombre.sorties",this->nbSorties);
			//proprietes->putProperty("simulation.age_diff")

			std::vector<std::string> keysToWrite;
			keysToWrite.push_back("date_time.run");
			keysToWrite.push_back("process.count");
			keysToWrite.push_back("random.seed");
			keysToWrite.push_back("min.x");
			keysToWrite.push_back("min.y");
			keysToWrite.push_back("max.x");
			keysToWrite.push_back("max.y");
			keysToWrite.push_back("proc.per.x");
			keysToWrite.push_back("proc.per.y");
			keysToWrite.push_back("grid.buffer");
			keysToWrite.push_back("init.time");
			keysToWrite.push_back("stop.at");
			keysToWrite.push_back("run.time");
			keysToWrite.push_back("nombre.humains");
			keysToWrite.push_back("nombre.survivants");
			keysToWrite.push_back("nombre.morts");
			keysToWrite.push_back("evacuation");
			keysToWrite.push_back("dernier.tick.evacuation");
			keysToWrite.push_back("simulation.diff_age");
			keysToWrite.push_back("nombre.sorties");
			proprietes->log("TER");
			proprietes->writeToSVFile("./results/TER.csv", keysToWrite);
		}
	}

	/*!
	 *  \brief Fonction heritee qui est appelee a chaque tick de la simulation
	 *
	 *
	 */
	void go();

	/*!
	 *  \brief Fonction heritee qui est appelee a l'initialisation de l'objet Observer
	 *
	 */
	virtual void setup(repast::Properties& props); // NOTE: 'virtual' needed by some compilers7

	/*!
	 *  \brief Charge a partir du fichier d'initialisation, la matrice map a utiliser pour A*
	 *
	 */
	void loadMap_a_star(repast::Properties& props, std::vector<Coordonnes2D> &sorties);

	// create and provide for agents moving between processes

	/*!
	 *  \brief Fonction qui cree un agent a partir d'une archive serialisee
	 *  \param content : archive serialisee de type AgentPackage
	 *  \return pointeur sur le nouvel Agent cree en memoire
	 *
	 */
	repast::relogo::RelogoAgent* createAgent(const AgentPackage& content);

	/*!
	 *  \brief Fonction qui assigne les valeurs d'un tableau d'archives serialisees a un agent ou un ensemble d'agents
	 *  \param out : tableau d'archives serialisees de type AgentPackage
	 *  \param request : Une requete Repast sur un ou plusieurs agents
	 *  \return pointeur sur le nouvel Agent cree en memoire
	 *
	 */
	void provideContent(const repast::AgentRequest& request, std::vector<AgentPackage>& out);

	/*!
	 *  \brief Fonction qui enregistre les resultats de la simulation dans un fichier tableur.
	 *
	 */
	void enregisterResultats();

	/*!
	 *  \brief Fonction charge la map a partir du fichier d'initialisation
	 *  \param props : proprietes de la simulation
	 *  \param process_cadran : cadran sur lequel travaille le processus actuel
	 *
	 */
	void loadMap(repast::Properties& props, int process_cadran);

	// create and provide for buffer sync
	/*!
	 *  \brief Fonction qui cree des agents, appelee lors d'une synchronisation du buffer de la grille Repast
	 *  \param content : archive serialisee de type AgentPackage
	 *  \param out : reference vers un tableau d'agents a mettre a jour
	 *
	 */
	void createAgents(std::vector<AgentPackage>& content, std::vector<repast::relogo::RelogoAgent*>& out);

	/*!
	 *  \brief Fonction qui fournit aux agents leur contenu, appelee lors d'une synchronisation du buffer de la grille Repast
	 *  \param agent : Agent à mettre a jour.
	 *  \param out : Tableau d'archives serialisees de type AgentPackage
	 *
	 */
	void provideContent(repast::relogo::RelogoAgent* agent, std::vector<AgentPackage>& out);

	/*!
	 *  \brief Fonction qui met à jour des agents deja existants
	 *  \param package : archive serialisee de type AgentPackage
	 *
	 */
	void updateAgent(AgentPackage package);

	/*!
	 *  \brief Fonction qui dessine le decor dans la Fenetre SDL
	 *  \param cadran : cadran a dessiner dans ce processus
	 *
	 */
	void dessinerDecor (int cadran);

	/*!
	 *  \brief Fonction qui convertie des cordonnees du monde Repast vers des coordonnes en pixel dans la Fenetre SDL associee a ce processus
	 *  \param X : coordonne X dans le monde Repast a convertir
	 * 	\param Y : coordonne Y dans le monde Repast a convertir
	 * 	\param cadran : cadran dans lequel on se trouve
	 * 	\return Un Objet de type Coordonnes2D contenant les coordonnees converties
	 */
	Coordonnes2D Rcor2GLCor(int X, int Y, int cadran);

	/*!
	 *  \brief Fonction qui convertie des cordonnees du Fichier vers des coordonnes du monde Repast
	 *  \param X : coordonne X dans le Fichier
	 * 	\param Y : coordonne Y dans le Fichier
	 * 	\return Un Objet de type Coordonnes2D contenant les coordonnees converties
	 */
	Coordonnes2D Fcor2RCor(int posX, int posY);

	/*!
	 *  \brief Fonction qui convertie des cordonnees de la liste de matrices map vers des coordonnes en pixel de la Fenetre SDL
	 *  \param X : coordonne X dans la map
	 * 	\param Y : coordonne Y dans la map
	 * 	\return Un Objet de type Coordonnes2D contenant les coordonnees converties
	 */
	Coordonnes2D Mcor2GLCor(int posX, int posY);

	/*!
	 *  \brief Fonction qui synchronise la map et la met a jour en fonction de la map Repast
	 */
	void synchronizeMap();

	/*!
	 *  \brief Fonction qui remet a 0 la map (liste de matrices en memoire)
	 */
	void razMap();

	/*!
	 *  \brief Fonction qui convertit les coordonnes de la map vers des coordonnees Repast
	 *
	 *  \param c : Objet de type Coordonnes2D qui contient les coordonnes de la map à convertir
	 * 	\param cadran : cadran du processus actuel
	 * 	\return Un Objet de type Coordonnes2D contenant les coordonnees converties
	 */
	Coordonnes2D map2Repast(Coordonnes2D c,int cadran);

	/*!
	 *  \brief Fonction qui affiche dans la console le contenu de la map (utilise pour debugger)
	 */
	void printMap();

	/*!
	 *  \brief Getter de l'attribut m_survivants de la Classe TERObserver
	 * 	\return l'attribut m_survivants de la classe TERObserver
	 */
	int getSurvivants(){return this->m_survivants;}
	/*!
	 *  \brief Setter de l'attribut m_survivants de la Classe TERObserver
	 * 	\param val : l'attribut a affecter a m_survivants de la classe TERObserver
	 */
	void setSurvivant(int val){this->m_survivants = val;}
	//void setDiffAge(int val){this->ageDiff = val;}
	/*!
	 *  \brief Getter de l'attribut proprietes de la Classe TERObserver
	 * 	\return l'attribut proprietes de la classe TERObserver
	 */
	repast::Properties* getProps(){return this->proprietes;}
};

#endif /* TEROBSERVER_H_ */
