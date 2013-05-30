#include <iostream>
#include <fstream>


bool is_odd(int n) { 

	return (n%2) != 0 ; 
}

int next(int n) {

	if (is_odd(n))
		return 3*n + 1;
	else
		return n/2;
}

int sequence_length(int n) {

	if ( n == 1)
		return 1;
	else
		return 1 + sequence_length(next(n));
	
}

int max_sequence_length(int from, int to) {

	int max = sequence_length(from);

	for(int i = from; i <= to; i++) {
		if(max < sequence_length(i))
			max = sequence_length(i);
	}

	return max;
}

void usage(std::ostream &os, std::string progname) {
	os << "USAGE: " << progname << " <input-file> " << std::endl;
}

int main(int argc, char *argv[]) {

	if ( argc < 2 ) {
		usage(std::cerr, argv[0]);
		return 1;
	}
	
	std::ifstream ifs(argv[1]);

	int start;
	int end;

	while( ifs >> start >> end ) 
		std::cout << start << " " << end << " " << max_sequence_length(start, end) << std::endl;


	return 0;
}
