#include "relogo/AgentSet.h"
#include "relogo/Patch.h"
#include "Observer.h"

#include "repast_hpc/RepastProcess.h"

#include "Humain.h"

using namespace repast::relogo;
using namespace repast;

void Humain::getPos(){
	std::cout << " [ " << RepastProcess::instance()->rank()<< "] : Position X = " << pxCor() << std::endl << "Position Y = " << pyCor() << std::endl ;
}
