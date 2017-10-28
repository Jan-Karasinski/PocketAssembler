#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <boost\filesystem.hpp>

int n_of_d(int i) {
	int n{ 0 };
	while (i /= 10) {
		n++;
	}
	return n;
}

void spaces(std::ostream& stream, int i) {
	while (i--) {
		stream << ' ';
	}
}

struct Point {
	int x{ 0 }, y{ 0 }, z{ 0 };

	Point(int x, int y, int z) : x{ x }, y{ y }, z{ z }
	{}

	bool operator<(const Point& p) const {
		if (x != p.x) {
			return x < p.x;
		}
		if (y != p.y) {
			return y < p.y;
		}
		return z < p.z;
	}
	
	friend std::ostream& operator<<(std::ofstream& stream, const Point& point) {
		stream << point.x; spaces(stream, 4 - n_of_d(point.x));
		stream << point.y; spaces(stream, 4 - n_of_d(point.y));
		stream << point.z; spaces(stream, 4 - n_of_d(point.z));
		return stream;
	}
};

int main() {
	using namespace boost::filesystem;
	
	try {
		// search for input file (.txt) in ms solution directory
		path input_path{ "..\\input.txt" };
		
		if (!exists(status(input_path)))
			throw std::exception("Couldn't find file with input.");
		
		ifstream stream{ input_path };
		std::vector<std::pair<Point, std::string>> input;
		std::string temp{ "" };

		while (!stream.eof()) {
			std::getline(stream, temp);
			std::stringstream ss{ temp }; 

			int x{ 0 }, y{ 0 }, z{ 0 };
			ss >> x >> y >> z; std::getline(ss, temp);
			
			input.emplace_back(std::pair<Point, std::string>{ {x, y, z}, temp });
		}

		std::sort(std::begin(input), std::end(input));

		ofstream out{ "..\\output.txt" };
		for (auto line : input) {
			out << line.first << line.second << '\n';
		}
	}
	catch (filesystem_error& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	//std::cin.get();
    return 0;
}