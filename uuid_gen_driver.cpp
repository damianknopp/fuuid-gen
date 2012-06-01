#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <vector>

#include <boost/thread/thread.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/progress.hpp>

#include <dkUtil.h>
#include <uuid_generator.h>

namespace fs = boost::filesystem;
namespace uuids = boost::uuids;
using namespace std;
using namespace dk;

//set to 0 to turn off debug
#define DEBUG 1

//void log(const string &msg);
void log(const char* const msg);
void handler();

static const string USAGE = "[OPTION]\n\t-gen <number of ids per thread>";


int main(int argc, const char** argv){
	// Turn off synchronization with corresponding C standard library files. This
	// gives a significant speed improvement on platforms where the standard C++
	// streams are implemented using standard C files.
	std::ios::sync_with_stdio(false);
	boost::progress_timer t( std::clog );


	dkUtil util;
	vector<string> args = util.parseCommandLine(argc, argv);
	unsigned int numIds = 0;

	if(DEBUG){
		const char* const version = "v.02";
		clog << "----uuid generator (" << version << ") ----" << "\n";
		clog << "debugging: printing command line args\n";
		util.printVector(args);
	}

	try{
		if(args.size() >= 3){
			log("popping number of ids to gen");
			string const idArg = args.back();
			if(dkUtil::containsAllDigits(idArg)){
				numIds = dkUtil::convertToInt(idArg);
			}
			log(string("numIds = ").append(dkUtil::intToString(numIds)).c_str());
		}else{
			clog << args.front() << " " << USAGE << endl;
			exit(EXIT_SUCCESS);
		}

		char * test_path = "test_data/";
		fs::path test_dir(test_path);


		//generator.generate(numIds);
		boost::thread_group threads;
		for(int i = 0; i < 5; i++){
			clog << "creating thread " << i << endl;
			uuid_generator generator(test_dir, numIds);
			threads.create_thread(generator);
		}
		threads.join_all();
		return EXIT_SUCCESS;
	}catch(std::exception & e){
		cerr << "Exception thrown in main." << endl;
		cerr << e.what() << endl;
		cerr << "Killing program..." << endl;
		return EXIT_FAILURE;
	}
}

void log(const char* const msg){
	if(DEBUG){
		clog << "debugging: " << msg << "\n";
	}
}

/*     
*method to handle unchecked exceptions
*/
void handler(){  
	cerr << "Excpetion thrown in main and nothing to catch it! Killing program..." << endl;
	exit(EXIT_FAILURE);
}//end handler
