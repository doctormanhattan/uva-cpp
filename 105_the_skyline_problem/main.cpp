#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

typedef int Sweep ;



struct Point {
    static const int INVALID = -10000;
	int x;
	int y;

	Point() {	// Creates an Invalid point
		this->x = INVALID;
		this->y = INVALID;
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool isValid() { 
		return ( (this->x != INVALID) && (this->y != INVALID) ); 
	}

	friend std::ostream& operator<< (std::ostream& os, const Point& p) {
		os << "(" << p.x << ", " << p.y << ")" ;
		return os;
	}
};

struct Building {
	int left;
	int height;
	int right;

	Building(int l, int h, int r) {
		this->left   = l;
		this->height = h;
		this->right  = r;
	}

	Point intersection(Sweep s) {
		if ( ( s >= this->left ) && ( s < this->right) ) {	
			return Point(s, this->height);
		} else {
			return Point();
		}
	}

	friend std::ostream& operator<< (std::ostream& os, const Building& b) {
		os << "(" << b.left << ", " << b.height << ", " << b.right << ")" ;
		return os;
	}
};

void usage(std::ostream &os, std::string progname) {
	os << "USAGE: " << progname << " <input-file> " << std::endl;
}

void parse(std::string fname, std::vector<Building> &buildings) {

	std::ifstream ifs(fname.c_str());
	int left, height, right;

	while( ifs >> left >> height >> right ) {
		Building b(left, height, right);
		buildings.push_back(b);
	}


}

Point max_intersection(std::vector<Building>& bs, Sweep s) {

	Point max(s, 0);

	for (int i = 0; i < bs.size(); i++) {
		Point p = bs[i].intersection(s);

		if ( p.isValid()  && (p.y > max.y) ) {
			max = p;
		}
	}
	return max;
}

void skyline(std::vector<Building>& bs, 
             int start, 
             int end, 
             std::vector<int>& sv) { 

	int current = 0;

	for(Sweep s = start; s < end; s++) {
		Point p = max_intersection(bs, s);

		if ( current != p.y ) {
			sv.push_back(p.x);
			sv.push_back(p.y);
			current = p.y;
		}
	}

}

void print_skyline(std::vector<int>& sv) {

	std::copy(sv.begin(), sv.end() - 1, std::ostream_iterator<int>(std::cout, " "));
	std::cout << sv.back() << std::endl;
}

int main(int argc, char *argv[]) {

	if ( argc < 2 ) {
		usage(std::cerr, argv[0]);
		return 1;
	}

	std::vector<Building> buildings;
	
	parse(argv[1], buildings);

	std::vector<int> skyline_vector;

	skyline(buildings, 0, 10000, skyline_vector);

	print_skyline(skyline_vector);

	return 0;
}
