#include <boost/mpi.hpp>
#include <sstream>

#include "repast_hpc/io.h"
#include "repast_hpc/RepastProcess.h"
#include "relogo/SimulationRunner.h"
#include "relogo/Patch.h"
//#include "repast_hpc/initialize_random.h"
#include "fenetre.h"
#include "TERObserver.h"

using namespace repast;
using namespace relogo;


void usage() {
	std::cerr << "usage: X  string string" << std::endl;
	std::cerr << "  first string: string is the path to the Repast HPC \n\tconfiguration properties file"
			<< std::endl;
	std::cerr << "  second string: string is the path to the model properties file" << std::endl;
}

void runTER(std::string propsFile, int argc, char ** argv) {

	boost::mpi::communicator world;
	Properties props(propsFile, argc, argv, &world);

	std::string time;
	repast::timestamp(time);

	props.putProperty("date_time.run", time);

	props.putProperty("process.count", world.size());

	SimulationRunner runner(&world);

	if(world.rank() == 0) std::cout << " Starting... " << std::endl;

	runner.run<TERObserver, Patch>(props);




}

int main(int argc, char **argv) {
	boost::mpi::environment env(argc, argv);
	std::string config, props;
	boost::mpi::communicator world;

	std::cout << "AGRV0 = " << argv[0] << std::endl;

	if (argc >= 3) {
		config = argv[1];
		props = argv[2];

	} else {
		if (world.rank() == 0) usage();
		return 0;
	}

	if (config.size() > 0 && props.size() > 0) {
		RepastProcess::init(config, &world);
		runTER(props, argc, argv);
	} else {
		if (world.rank() == 0) usage();
		return 0;
	}

	RepastProcess::instance()->done();

	//fen->main_loop();

	//delete fen;
	std::cout << "Processus " << world.rank() << " terminé ! " << std::endl;

	return 0;
}
