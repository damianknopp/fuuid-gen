#include <ctype.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <vector>
   
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/progress.hpp>

using namespace std;
namespace fs = boost::filesystem;
namespace uuids = boost::uuids;

namespace dk{

#ifndef __UUID_GENERATOR_H
#define __UUID_GENERATOR_H

class uuid_generator{
	protected:
		uuids::basic_random_generator<boost::mt19937> gen;
		string file_name;
		unsigned int max;

	public:
		uuid_generator(const fs::path &test_dir, unsigned int max);
		void generate();
		void operator()();

};
#endif

};//end dk namespace
