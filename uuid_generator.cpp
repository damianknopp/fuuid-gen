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

#include "uuid_generator.h"

using namespace std;
using namespace boost;
namespace fs = filesystem;

namespace dk{

	uuid_generator::uuid_generator(const fs::path &test_dir, unsigned int max): max(max){
		if (!fs::exists(test_dir)){
			 clog << test_dir << " does not exist. creating..." << "\n";
			 fs::create_directory(test_dir.file_string());
		}   
		boost::uuids::uuid uid = gen();
		ostringstream ss;
		ss << uid << ".txt";
		this->file_name = (test_dir / ss.str()).file_string();
	}

	void uuid_generator::generate(){
		ofstream out(this->file_name.c_str());
		unsigned int count = 1;
		while(count <= this->max){
			boost::uuids::uuid uuid = gen();
			out << uuid << "\n";
			count++;
		}	
		out.close();
	}

	void uuid_generator::operator()(){
		this->generate();
	}
};//end dk namespace
