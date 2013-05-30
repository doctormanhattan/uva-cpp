#include <iostream>

void usage(std::ostream &os, std::string progname) {
	os << "USAGE: " << progname << " <input-file> " << std::endl;
}

int main(int argc, char *argv[]) {

	if ( argc < 2 ) {
		usage(std::cerr, argv[0]);
		return 1;
	}

	return 0;
}
